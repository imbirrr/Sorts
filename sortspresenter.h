#ifndef SORTSPRESENTER_H
#define SORTSPRESENTER_H

#include <QObject>
#include <QThread>
#include <QWeakPointer>
#include "sortssorts.h"
#include "sortsmainwindow.h"
#include "sortsgenerator.h"

class SortsMainWindow;

class SortsPresenter : public QObject
{
	Q_OBJECT
public:
	// тип данных, в котором будут сортировочные элементы
	using sort_t = int;
	explicit SortsPresenter(SortsMainWindow* mainWindow);
	~SortsPresenter();

//signals:
//	void setProgressBarRange(int min, int max);
//	void setProgressEnabled(bool enabled);
//	void setStatus(QString status);
//	void setProgress(int progress);
//	void addSort(QString name);

public slots:
	void generate();
	void sort();
	void changeSort(int sort) {
		currentSort = sort;
	}

private slots:
	void sorted();

private:
	QThread sortingThread;
	const size_t size; // кол-во элементов
	int currentSort; // текущая сортировка
	// Сортировочки
	QSharedPointer<SortsSorts<sort_t>> mySorts;
	// Указатеь на окно
	SortsMainWindow* mainWindow;
};

#endif // SORTSPRESENTER_H
