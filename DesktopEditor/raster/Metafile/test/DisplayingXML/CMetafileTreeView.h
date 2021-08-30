#ifndef CMETAFILETREEVIEW_H
#define CMETAFILETREEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QFont>

#include "../../../../xml/include/xmlutils.h"

class CMetafileTreeView : public QTreeView
{
    public:
        explicit CMetafileTreeView(QWidget *parent);
        virtual ~CMetafileTreeView();

        void SetMetafile(const std::wstring& wsXmlFilePath);
        bool IsClear();
        void SetMode(bool bLightMode);
        void Clear();
        QMap<QString, unsigned int>* GetStatistics();

        bool SaveInXmlFile(const std::wstring& wsSaveFilePath);

        void EditItem(QStandardItem* pStandardItem);

    private:
        void ReadXmlNode(XmlUtils::CXmlNode& oXmlNode, QStandardItem* oStandartItem, unsigned int unLevel = 0);
        void WriteXmlNode(XmlUtils::CXmlWriter& oXmlWriter, QStandardItem* oStandartItem);

        QMap<QString, unsigned int> m_mStatistics;
};

#endif // CMETAFILETREEVIEW_H
