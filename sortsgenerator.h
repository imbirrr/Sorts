#ifndef SORTSGENERATOR_H
#define SORTSGENERATOR_H

#include <QList>
#include <random>
#include <limits>

//template <class T>
class SortsGenerator
{
public:
    SortsGenerator() = delete;
    //~SortsGenerator();
    static QList<int> generate(int size);
};

#endif // SORTSGENERATOR_H
