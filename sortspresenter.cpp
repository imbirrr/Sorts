#include "sortspresenter.h"

SortsPresenter::SortsPresenter(SortsMainWindow* mainWindow) :
    QObject{},
	worker{new SortsWorker(new SortsSorts<sort_t>())}
{
	this->mainWindow = mainWindow;

	currentSort = 0;
    currentAsmSort = 0;
    mainWindow->addSortName(QString::fromLocal8Bit("Сортировка пузырьком"));
    mainWindow->addSortName(QString::fromLocal8Bit("Сортировка слиянием"));
    mainWindow->addSortName(QString::fromLocal8Bit("Быстрая сортировка"));
    mainWindow->addAsmSortName(QString::fromLocal8Bit("Быстрая сортировка ассемблер"));
    mainWindow->addAsmSortName(QString::fromLocal8Bit("Сортировка пузырьком ассемблер"));

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
    connect(this, &SortsPresenter::runSortInThread,
        worker.data(), &SortsWorker::goAsm, Qt::QueuedConnection);
	sortingThread.start();

    mainWindow->setStatus(QString::fromLocal8Bit("Идет генерация, пожалуйста, подождите"));
	generate();
    mainWindow->setStatus(QString::fromLocal8Bit("Генерация завершена"));
}

SortsPresenter::~SortsPresenter()
{
	sortingThread.quit();
	sortingThread.wait();
}

void SortsPresenter::generate()
{
    SortsProfiler prof;
    prof.startStopwatch();
    size = mainWindow->getGenSize();
	qDebug() << "GEN";
    worker->setData(SortsGenerator::generate(size));
	mainWindow->setSwaps(0);
	mainWindow->setComparisons(0);
	//emit setProgressBarRange(0, size);
	//emit setProgressBarProgress(0);
//	mainWindow->setProgressBarRange(0, size);
//	mainWindow->setProgressBarProgress(0);
    prof.stopStopwatch();
    mainWindow->setGeneratingTime(QString::number(prof.getTime()) + QString::fromLocal8Bit("мс"));
}

void SortsPresenter::sort()
{
	qDebug() << "SORT";
	mainWindow->blockUI(true);
    mainWindow->setStatus(QString::fromLocal8Bit("Сортировка началась"));
	worker->setSortType(currentSort);
	qDebug() << "ds" << currentSort;
	emit runSortInThread();
    qDebug() << "RUNNED from thread" << this->thread() << "in thread" << worker->thread() ;
    worker->setUnsortData();
}

void SortsPresenter::sortAsm()
{
    qDebug() << "SORT";
    mainWindow->blockUI(true);
    mainWindow->setStatus(QString::fromLocal8Bit("Сортировка началась"));
    worker->setAsmSortType(currentAsmSort);
    qDebug() << "ds" << currentAsmSort;
    emit runSortInThread();
    qDebug() << "RUNNED from thread" << this->thread() << "in thread" << worker->thread() ;
    worker->setUnsortData();
}

//void SortsPresenter::writeToFile(QString filename)
//{
//    qDebug() << "writing to file...";
//    worker->writeDataToFile(filename);
//    worker->setUnsortData();
//}

//void SortsPresenter::writeSortedToFile(QString filename)
//{
//    qDebug() << "writing to file...";
//    worker->writeSortedDataToFile(filename);
//    worker->setUnsortData();
//}

void SortsPresenter::connections()
{
    connect(mainWindow, &SortsMainWindow::sortButtonPressed,
		this, &SortsPresenter::sort);
    connect(mainWindow, &SortsMainWindow::sortAsmButtonPressed,
        this, &SortsPresenter::sortAsm);
	connect(mainWindow, &SortsMainWindow::generateButtonPressed,
		this, &SortsPresenter::generate);
	connect(mainWindow, &SortsMainWindow::sortChanged,
		this, &SortsPresenter::changeSort);
    connect(mainWindow, &SortsMainWindow::sortAsmChanged,
        this, &SortsPresenter::changeAsmSort);
}

void SortsPresenter::sorted()
{
	qDebug() << "DONE" << worker->getData().size();
    mainWindow->setStatus(QString::fromLocal8Bit("Отсортировано"));
    mainWindow->blockUI(false);
    auto prof = worker->getProfiler();
    mainWindow->setSortTime(prof->getTime());
    mainWindow->setComparisons(prof->getComparisons());
    mainWindow->setSwaps(prof->getSwaps());
    worker->setUnsortData();
}

