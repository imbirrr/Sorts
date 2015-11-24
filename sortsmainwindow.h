#ifndef SORTSMAINWINDOW_H
#define SORTSMAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "sortspresenter.h"

namespace Ui {
class SortsMainWindow;
}

// ������ ������� ��� ���, ����� ���������� ����, ��� �� ����
class SortsPresenter;

class SortsMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SortsMainWindow(QWidget *parent = 0);
	~SortsMainWindow();

private:
	Ui::SortsMainWindow *ui;
	// ����� ��������� �� ���������, ������������ ��� ������� ���������,
	// �� ��� ������ � ������� ��������� �� ��� �����
	QSharedPointer<SortsPresenter> presenter;

	// � ���� ������� ��� ����������
	void connections();

public slots:
//	void setProgressBarProgress(int progress);
//	void setProgressBarEnabled(bool enabled);
//	void setProgressBarRange(int minimum, int maximum);
	void setSwaps(uint s);
	void setComparisons(uint c);
	void setStatus(QString status);
	void addSortName(QString name);
	void blockUI(bool);

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
