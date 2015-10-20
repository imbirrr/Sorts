#include "sortspresenter.h"

SortsPresenter::SortsPresenter(SortsMainWindow* mainWindow) :
	QObject{},
	size{1000000},
	mySorts{}
{
	this->mainWindow = mainWindow;

	connect(mainWindow, &SortsMainWindow::sortButtonPressed,
		this, &SortsPresenter::sort);
	connect(mainWindow, &SortsMainWindow::generateButtonPressed,
		this, &SortsPresenter::generate);
	connect(mainWindow, &SortsMainWindow::sortChanged,
		this, &SortsPresenter::changeSort);

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
	mainWindow->setStatus("Подожите, идет генерация…");
	generate();
	mainWindow->setStatus("Генерация завершена.");
}

SortsPresenter::~SortsPresenter()
{

}

void SortsPresenter::generate()
{
	mySorts->setData(SortsGenerator::generate(size));
	mainWindow->setSwaps(0);
	mainWindow->setComparisons(0);
	//emit setProgressBarRange(0, size);
	//emit setProgressBarProgress(0);
//	mainWindow->setProgressBarRange(0, size);
//	mainWindow->setProgressBarProgress(0);
}

void SortsPresenter::sort()
{

	switch (currentSort) {
	case 1:

		break;
	default:
		break;
	}
}

void SortsPresenter::sorted()
{

}

