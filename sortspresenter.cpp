#include "sortspresenter.h"

SortsPresenter::SortsPresenter(SortsMainWindow* mainWindow) :
	QObject{},
	size{1000},
	worker{new SortsWorker(new SortsSorts<sort_t>())}
{
	this->mainWindow = mainWindow;

	currentSort = 0;
	mainWindow->addSortName("sort0");

//	connect(this, &SortsPresenter::addSort,
//		mainWindow.data(), &SortsMainWindow::addSortName);
//	connect(this, &SortsPresenter::setStatus,
//		mainWindow.data(), &SortsMainWindow::setStatus);
//	connect(this, &SortsPresenter::setProgress,
//		mainWindow.data(), &SortsMainWindow::setProgressBarProgress);
//	connect(this, &SortsPresenter::setProgressBarRange,
//		mainWindow.data(), &SortsMainWindow::setProgressBarRange);
//	connect(this, &SortsPresenter::setProgressBarEnabled,
//		mainWindow.data(), &SortsMainWindow::setProgressBarEnabled);

//	mainWindow->setProgressBarEnabled(false);
	connections();


	worker->moveToThread(&sortingThread);
//	connect(&sortingThread, &QThread::finished, &worker)
	connect(worker.data(), &SortsWorker::sorted,
		this, &SortsPresenter::sorted, Qt::QueuedConnection);
	connect(this, &SortsPresenter::runSortInThread,
		worker.data(), &SortsWorker::go, Qt::QueuedConnection);
	sortingThread.start();

	mainWindow->setStatus("Подожите, идет генерация…");
	generate();
	mainWindow->setStatus("Генерация завершена.");
}

SortsPresenter::~SortsPresenter()
{
	sortingThread.quit();
	sortingThread.wait();
}

void SortsPresenter::generate()
{
	qDebug() << "GEN";
	worker->setData(SortsGenerator::generate(size));
	mainWindow->setSwaps(0);
	mainWindow->setComparisons(0);
	//emit setProgressBarRange(0, size);
	//emit setProgressBarProgress(0);
//	mainWindow->setProgressBarRange(0, size);
//	mainWindow->setProgressBarProgress(0);
}

void SortsPresenter::sort()
{
	qDebug() << "SORT";
	mainWindow->blockUI(true);
	mainWindow->setStatus("Сортировка начата…");
	worker->setSortType(currentSort);
	emit runSortInThread();
	qDebug() << "RUNNED from thread" << this->thread() << "in thread" << worker->thread() ;
}

void SortsPresenter::connections()
{
	connect(mainWindow, &SortsMainWindow::sortButtonPressed,
		this, &SortsPresenter::sort);
	connect(mainWindow, &SortsMainWindow::generateButtonPressed,
		this, &SortsPresenter::generate);
	connect(mainWindow, &SortsMainWindow::sortChanged,
		this, &SortsPresenter::changeSort);
}

void SortsPresenter::sorted()
{
	qDebug() << "DONE" << worker->getData();
	mainWindow->setStatus("Сортировка закончена!");
	mainWindow->blockUI(false);
}

