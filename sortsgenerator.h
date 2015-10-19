#ifndef SORTSGENERATOR_H
#define SORTSGENERATOR_H

#include <QList>

template <class T>
class SortsGenerator
{
public:
    SortsGenerator() = delete;
    //~SortsGenerator();
    static QList<T> generate();
};

#endif // SORTSGENERATOR_H
