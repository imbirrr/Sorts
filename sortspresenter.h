#ifndef SORTSPRESENTER_H
#define SORTSPRESENTER_H

#include <QObject>
#include <QThread>
#include <QWeakPointer>
#include <QApplication>
#include "sortssorts.h"
#include "sortsmainwindow.h"
#include "sortsgenerator.h"
#include "sortsworker.h"

class SortsMainWindow;

class SortsPresenter : public QObject
{
	Q_OBJECT
public:
	// тип данных, в котором будут сортировочные элементы
	using sort_t = int;
	explicit SortsPresenter(SortsMainWindow* mainWindow);
	~SortsPresenter();

//    void writeToFile(QString filename);
//    void writeSortedToFile(QString filename);

//signals:
//	void setProgressBarRange(int min, int max);
//	void setProgressEnabled(bool enabled);
//	void setStatus(QString status);
//	void setProgress(int progress);
//	void addSort(QString name);
signals:
	void runSortInThread();

public slots:
	void generate();
    void sort();
    void sortAsm();
	void changeSort(int sort) {
		qDebug() << "CHANGE";
		currentSort = sort;
	}
    void changeAsmSort(int sort) {
        qDebug() << "CHANGE";
        currentAsmSort = sort;
    }

private slots:
	void connections();
	void sorted();

private:
	QThread sortingThread;
    size_t size; // кол-во элементов
	int currentSort; // текуща€ сортировка
    int currentAsmSort;
	// —ортировочки
	QSharedPointer<SortsWorker> worker;
	// ”казатеь на окно
	SortsMainWindow* mainWindow;
};

#endif // SORTSPRESENTER_H
