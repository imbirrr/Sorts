#ifndef SORTSMAINWINDOW_H
#define SORTSMAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QIntValidator>
#include <QMessageBox>
#include "sortspresenter.h"
#include <QFileDialog>

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
    int getGenSize();
    void setSortTime(int t);

private:
	Ui::SortsMainWindow *ui;
	// Умный указатель на Презентер, использовать как обычный указатель,
	// но вся работа с памятью переходит на его плечи
	QSharedPointer<SortsPresenter> presenter;
    QSharedPointer<QIntValidator> genValidator;

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
    void addAsmSortName(QString name);
	void blockUI(bool);
    void setWritingTime(QString time);
    void setGeneratingTime(QString time);

private slots:
	void on_sortButtonCilcked();
	void on_generateButtonClicked();
	void on_sortChanged(int sort);

    void on_genLineEdit_textChanged(const QString &arg1);

    void on_action_00_triggered();
    void on_action_01_triggered();
    void on_action_02_triggered();

    void on_writeToFileButton_clicked();

    void on_generateButton_clicked(bool checked);

    void on_sortAsmButton_clicked();

    void on_sortAsmChooser_currentIndexChanged(int index);

signals:
	void sortChanged(int sort);
    void sortAsmChanged(int sort);
	void generateButtonPressed();
	void sortButtonPressed();
    void writeToFilePlease();
    void sortAsmButtonPressed();
};

#endif // SORTSMAINWINDOW_H
