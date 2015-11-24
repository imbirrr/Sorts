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
	// ��� ������, � ������� ����� ������������� ��������
	using sort_t = int;
	explicit SortsPresenter(SortsMainWindow* mainWindow);
	~SortsPresenter();

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
	void changeSort(int sort) {
		qDebug() << "CHANGE";
		currentSort = sort;
	}

private slots:
	void connections();
	void sorted();

private:
	QThread sortingThread;
	const size_t size; // ���-�� ���������
	int currentSort; // ������� ����������
	// ������������
	QSharedPointer<SortsWorker> worker;
	// �������� �� ����
	SortsMainWindow* mainWindow;
};

#endif // SORTSPRESENTER_H
