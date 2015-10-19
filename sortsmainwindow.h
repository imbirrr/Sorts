#ifndef SORTSMAINWINDOW_H
#define SORTSMAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "sortspresenter.h"

namespace Ui {
class SortsMainWindow;
}

// Просто объявим его тут, чтобы компилятор знал, что он есть
class SortsPresenter;

class SortsMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SortsMainWindow(QWidget *parent = 0);
	~SortsMainWindow();

private:
	Ui::SortsMainWindow *ui;
	// Умный указатель на Презентер, использовать как обычный указатель,
	// но вся работа с памятью переходит на его плечи
	QSharedPointer<SortsPresenter> presenter;

	// в этой функции все соединения
	void connections();

public slots:
//	void setProgressBarProgress(int progress);
//	void setProgressBarEnabled(bool enabled);
//	void setProgressBarRange(int minimum, int maximum);
	void setSwaps(uint s);
	void setComparisons(uint c);
	void setStatus(QString status);
	void addSortName(QString name);

private slots:
	void on_sortButtonCilcked();
	void on_generateButtonClicked();
	void on_sortChanged(int sort);

signals:
	void sortChanged(int sort);
	void generateButtonPressed();
	void sortButtonPressed();
};

#endif // SORTSMAINWINDOW_H
