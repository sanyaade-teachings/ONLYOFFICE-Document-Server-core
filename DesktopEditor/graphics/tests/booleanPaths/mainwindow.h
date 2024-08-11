#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPoint>
#include <QMouseEvent>
#include "../../pro/Graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

const double RECTANGLE[4]	= {0.0, 0.0, 200.0, 200.0};
const double TRIANGLE[6]	= {100.0, 0.0, 200.0, 200.0, 0.0, 100.0};

class CustomLabel : public QLabel
{
	Q_OBJECT

public:
	CustomLabel(QWidget *parent = nullptr);

	QPointF GetStartPoint() const noexcept;
	double GetDifferenceX() const noexcept;
	double GetDifferenceY() const noexcept;

	bool GetMovable()	const noexcept;
	void ResetMovable()	noexcept;

signals:
	void mousePress();
	void mouseMove();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	bool Movable	= false;
	QPointF StartP	= {0.0, 0.0};
	QPointF CurrP	= {0.0, 0.0};
};

class CustomButton : public QPushButton
{
	Q_OBJECT

public:
	CustomButton(QWidget *parent = nullptr);

public slots:
	void SetFigure() noexcept;
};

class BooleanButton : public QPushButton
{
	Q_OBJECT

public:
	BooleanButton(QWidget *parent = nullptr);

public slots:
	void SetCommand() noexcept;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	Aggplus::CGraphicsPath* SetPath(double offsetX, double offsetY);
	void AddPath(NSGraphics::IGraphicsRenderer* pathRenderer, Aggplus::CGraphicsPath* path);
	void Draw(Aggplus::CGraphicsPath *path = nullptr);
	void SetCoords(QLabel* label, Aggplus::CGraphicsPath* path);

private slots:
	void DrawPath1();
	void DrawPath2();
	void BooleanOp();
	void CheckMousePress();
	void Move();

public:
	static inline QString Figure;
	static inline Aggplus::BooleanOpType Op;

	double Offsets[4] = {100.0, 100.0, 200.0, 200.0};
	double OldOffsets[4];

	bool Move1	 = false;
	bool Move2	 = false;

	Aggplus::CGraphicsPath* Path1;
	Aggplus::CGraphicsPath* Path2;

	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
