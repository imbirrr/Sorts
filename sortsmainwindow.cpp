#include "sortsmainwindow.h"
#include "ui_sortsmainwindow.h"

SortsMainWindow::SortsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SortsMainWindow)
{
    ui->setupUi(this);
}

SortsMainWindow::~SortsMainWindow()
{
    delete ui;
}
