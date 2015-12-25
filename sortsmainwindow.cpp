#include "sortsmainwindow.h"
#include "ui_sortsmainwindow.h"

SortsMainWindow::SortsMainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::SortsMainWindow),
    genValidator(new QIntValidator(1,10000000000))
{
	ui->setupUi(this);

	presenter.reset(new SortsPresenter(this));

    ui->genLineEdit->setValidator(genValidator.data());

    connections();
}

SortsMainWindow::~SortsMainWindow()
{
    delete ui;
}

int SortsMainWindow::getGenSize()
{
    return ui->genLineEdit->text().toInt();
}

void SortsMainWindow::setSortTime(int t)
{
    ui->sortTimeLabel->setText(QString::number(t));
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
    ui->swapsLabel->setText(QString::fromLocal8Bit("Замен:") + QString::number(s));
}

void SortsMainWindow::setComparisons(uint c)
{
    ui->comparisonsLabel->setText(QString::fromLocal8Bit("Сравнений:") + QString::number(c));
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

void SortsMainWindow::addAsmSortName(QString name)
{
    ui->sortAsmChooser->addItem(name);
}

void SortsMainWindow::blockUI(bool block)
{
    ui->centralWidget->setEnabled(!block);
}

void SortsMainWindow::setWritingTime(QString time)
{
    ui->writingTimeLabel->setText(QString::fromLocal8Bit("записано за ") + time);
}

void SortsMainWindow::setGeneratingTime(QString time)
{
    ui->generatingTimeLabel->setText(QString::fromLocal8Bit("сгенерировано за ") + time);
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

void SortsMainWindow::on_genLineEdit_textChanged(const QString &arg1)
{
    auto i = arg1.toInt();
    if (i > 1000000)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromLocal8Bit("<b>Warning!</b>"));
        msgBox.setInformativeText(QString::fromLocal8Bit("Массив такого размера будет сортироваться долго."
                                                         "<br>Будьте уверены в своем решении!"));
//        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.exec();
    }
}

void SortsMainWindow::on_action_00_triggered()
{
    //blockUI(true);
    auto htext = QString::fromLocal8Bit("<b>Инструкция по использованию программы 'Сортировки'</b><br>"
                                        "<br><i>1. Выберите нужную сортировку в поле выбора сортировки;</i>"
                                        "<br><i>2. Введите размер массива для генирации;</i>"
                                        "<br><i>3. Нажмите кнопку 'Генерировать';</i>"
                                        "<br><i>4. Для того, чтобы начать сортировку, нажмите кнопку 'Сортировать';</i>");

    QMessageBox msgBox;
    msgBox.setText(QString::fromLocal8Bit("Справка о программе"));
    msgBox.setInformativeText(htext);
    msgBox.exec();

    //blockUI(false);
}

void SortsMainWindow::on_action_01_triggered()
{
    QFileDialog save;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить сгенерированное"), "",
        tr("Text Files (*.txt)"));
}

void SortsMainWindow::on_action_02_triggered()
{
    QFileDialog saveAsm;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить отсортированное"), "",
        tr("Text Files (*.txt)"));
}

void SortsMainWindow::on_writeToFileButton_clicked()
{
    emit writeToFilePlease();
}

void SortsMainWindow::on_generateButton_clicked(bool checked)
{
}

void SortsMainWindow::on_sortAsmButton_clicked()
{
    emit sortAsmButtonPressed();
}

void SortsMainWindow::on_sortAsmChooser_currentIndexChanged(int index)
{
    emit sortAsmChanged(index);
}
