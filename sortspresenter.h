#ifndef SORTSPRESENTER_H
#define SORTSPRESENTER_H

#include <QObject>
#include "sortssorts.h"

class SortsPresenter : public QObject
{
    Q_OBJECT
public:
    explicit SortsPresenter(QObject *parent = 0);
    ~SortsPresenter();

signals:

public slots:

private:
    SortsSorts mySorts;
};

#endif // SORTSPRESENTER_H
