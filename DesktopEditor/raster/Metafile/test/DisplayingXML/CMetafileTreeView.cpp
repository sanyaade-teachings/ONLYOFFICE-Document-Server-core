#include "CMetafileTreeView.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>
#include <CTextEditDelegate.h>

#include "CEditItemWidget.h"

CMetafileTreeView::CMetafileTreeView(QWidget *parent) :
    QTreeView(parent)
{}

CMetafileTreeView::~CMetafileTreeView()
{}

void CMetafileTreeView::SetMetafile(const std::wstring &wsXmlFilePath)
{
        setModel(nullptr);

        if (wsXmlFilePath.empty())
                return;

        QFile *oXmlFile = new QFile(QString::fromStdWString(wsXmlFilePath));

        if (!oXmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
                QMessageBox::warning(this, "Warning", "Couldn't open XML file");
                oXmlFile->close();
                delete oXmlFile;
                return;
        }

        XmlUtils::CXmlNode oXmlRootNode;

        if (!oXmlRootNode.FromXmlFile(wsXmlFilePath) ||
            (oXmlRootNode.GetName() != L"EMF" &&
             oXmlRootNode.GetName() != L"WMF"))
        {
                oXmlFile->close();
                delete oXmlFile;
                return;
        }

        setHeaderHidden(true);

        QStandardItemModel *pStandardItemModel = new QStandardItemModel;
        QStandardItem *pStandardItem = new QStandardItem(QString::fromStdWString(L'<' + oXmlRootNode.GetName() + L'>'));
        pStandardItem->setEditable(false);

        ReadXmlNode(oXmlRootNode, pStandardItem, 1);

        pStandardItemModel->appendRow(pStandardItem);
        setModel(pStandardItemModel);

        oXmlFile->close();
        delete oXmlFile;
}

bool CMetafileTreeView::IsClear()
{
        return NULL == model();
}

void CMetafileTreeView::SetMode(bool bLightMode)
{
        if (dynamic_cast<CTextEditDelegate*>(itemDelegate()) != nullptr)
        {
                CTextEditDelegate *pTextEditDelegate = static_cast<CTextEditDelegate*>(itemDelegate());
                pTextEditDelegate->SetMode(bLightMode);
                pTextEditDelegate->updateEditorGeometry(this, QStyleOptionViewItem(), QModelIndex());
        }
}

void CMetafileTreeView::Clear()
{
        QAbstractItemModel *pModel = model();
        if (NULL != pModel)
        {
                delete pModel;
                setModel(NULL);
        }

        m_mStatistics.clear();
}

QMap<QString, unsigned int>* CMetafileTreeView::GetStatistics()
{
        return &m_mStatistics;
}

bool CMetafileTreeView::SaveInXmlFile(const std::wstring& wsSaveFilePath)
{
        QStandardItemModel *pStandardItemModel = (QStandardItemModel*)model();
        QStandardItem *pRootNode = pStandardItemModel->item(0);

        XmlUtils::CXmlWriter oXmlWriter;

        oXmlWriter.WriteString(L"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");

        WriteXmlNode(oXmlWriter, pRootNode);

        return oXmlWriter.SaveToFile(wsSaveFilePath);
}

void CMetafileTreeView::ReadXmlNode(XmlUtils::CXmlNode& oXmlNode, QStandardItem* oStandartItem, unsigned int unLevel)
{
        XmlUtils::CXmlNodes oXmlChilds;

        if (oXmlNode.GetChilds(oXmlChilds))
        {
                if (unLevel == 2)
                        ++m_mStatistics[QString::fromStdWString(oXmlNode.GetName())];

                for (unsigned int i = 0; i < oXmlChilds.GetCount(); ++i)
                {
                        XmlUtils::CXmlNode oXmlChild;
                        if (oXmlChilds.GetAt(i, oXmlChild))
                        {
                                QStandardItem *pStandardItem = new QStandardItem(QString("<%1>").arg(QString::fromStdWString(oXmlChild.GetName())));

                                if (unLevel > 1)
                                        pStandardItem->setEditable(false);

                                ReadXmlNode(oXmlChild, pStandardItem, unLevel + 1);
                                oStandartItem->appendRow(pStandardItem);
                        }
                }
        }
        else
        {
                std::wstring wsText = oXmlNode.GetText();
                if (!wsText.empty())
                {
                        QString qsText = oStandartItem->text();
                        oStandartItem->setText(qsText + (QString::fromStdWString(wsText)) + qsText[0] + '/' + qsText.mid(1));
                }
        }
}

std::wstring StringNormalization(std::wstring wsString)
{
    std::wstring wsText;
    for (wchar_t wChar : wsString)
        if (wChar == L'<')
               wsText += L"&lt;";
        else if (wChar == L'>')
               wsText += L"&gt;";
        else if (wChar == L'&')
               wsText += L"&amp;";
        else if (wChar == L'\'')
               wsText += L"&apos;";
        else if (wChar == L'"')
               wsText += L"&quot;";

        else wsText += wChar;
    return wsText;
}

void CMetafileTreeView::WriteXmlNode(XmlUtils::CXmlWriter &oXmlWriter, QStandardItem *oStandartItem)
{
        unsigned int unCountNodes = oStandartItem->rowCount();

        QString qsNodeText = oStandartItem->text();

        unsigned int unFirstQuotationMark = qsNodeText.indexOf(L'>');
        unsigned int unLastSlash = qsNodeText.lastIndexOf(L'/');

        std::wstring wsName = qsNodeText.mid(1, ((unLastSlash > unFirstQuotationMark) ? (unFirstQuotationMark) : (unLastSlash)) - 1).toStdWString();

        if (oStandartItem->rowCount() == 0)
        {
                std::wstring wsValue;

                if (unLastSlash > unFirstQuotationMark)
                        wsValue = qsNodeText.mid(unFirstQuotationMark + 1, unLastSlash - unFirstQuotationMark - 2).toStdWString();

                oXmlWriter.WriteNode(wsName, StringNormalization(wsValue));

                return;
        }

        oXmlWriter.WriteNodeBegin(wsName);

        for (unsigned int unIndexNode = 0; unIndexNode < unCountNodes; ++unIndexNode)
        {
                QStandardItem *pNode = oStandartItem->child(unIndexNode);
                WriteXmlNode(oXmlWriter, pNode);
        }

        oXmlWriter.WriteNodeEnd(wsName);
}

void CMetafileTreeView::EditItem(QStandardItem *pStandardItem)
{
        if (NULL == pStandardItem)
                return;

        CEditItemWidget *pEditItemWidget = new CEditItemWidget;
        pEditItemWidget->SetMainWindow((MainWindow*)parent()->parent()->parent());
        pEditItemWidget->SetItem(pStandardItem);
        pEditItemWidget->show();
}
