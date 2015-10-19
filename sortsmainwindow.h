#ifndef SORTSMAINWINDOW_H
#define SORTSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SortsMainWindow;
}

class SortsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SortsMainWindow(QWidget *parent = 0);
    ~SortsMainWindow();

private:
    Ui::SortsMainWindow *ui;
};

#endif // SORTSMAINWINDOW_H
