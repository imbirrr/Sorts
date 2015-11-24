#include "sortsmainwindow.h"
#include "ui_sortsmainwindow.h"

SortsMainWindow::SortsMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SortsMainWindow)
{
	ui->setupUi(this);

	presenter.reset(new SortsPresenter(this));

    connections();
}

SortsMainWindow::~SortsMainWindow()
{
	delete ui;
}

void SortsMainWindow::connections()
{
	connect(ui->sortButton, &QPushButton::clicked,
		this, &SortsMainWindow::on_sortButtonCilcked);
	connect(ui->generateButton, &QPushButton::clicked,
		this, &SortsMainWindow::on_generateButtonClicked);

	// костыль:
	void (QComboBox:: *signal)(int) = &QComboBox::currentIndexChanged;
	connect(ui->sortChooser, signal,
		this, &SortsMainWindow::on_sortChanged);
}

void SortsMainWindow::setSwaps(uint s)
{
	ui->swapsLabel->setText(QString("Перестановок: ") + QString::number(s));
}

void SortsMainWindow::setComparisons(uint c)
{
	ui->comparisonsLabel->setText(QString("Сравнений: ") + QString::number(c));
}

//void SortsMainWindow::setProgressBarProgress(int progress)
//{
//	ui->progressBar->setValue(progress);
//}

//void SortsMainWindow::setProgressBarEnabled(bool enabled)
//{
//	ui->progressBar->setEnabled(enabled);
//}

//void SortsMainWindow::setProgressBarRange(int minimum, int maximum)
//{
//	ui->progressBar->setRange(minimum, maximum);
//}

void SortsMainWindow::setStatus(QString status)
{
	ui->statusLabel->setText(status);
}

void SortsMainWindow::addSortName(QString name)
{
	ui->sortChooser->addItem(name);
}

void SortsMainWindow::blockUI(bool block)
{
	ui->centralWidget->setEnabled(!block);
}

void SortsMainWindow::on_sortButtonCilcked()
{
	emit sortButtonPressed();
}

void SortsMainWindow::on_generateButtonClicked()
{
	emit generateButtonPressed();
}

void SortsMainWindow::on_sortChanged(int sort)
{
	qDebug() << "c" << sort;
	emit sortChanged(sort);
}
