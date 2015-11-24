#ifndef SORTSSORTS_H
#define SORTSSORTS_H

#include <QList>
#include <QDebug>
#include "sortsprofiler.h"
#include <queue>
#include <vector>


template <class T> // T -- тип сортируемой информации
class SortsSorts
{

private:
    using sort_t = QVector<T>;
    SortsProfiler profiler;
    QVector<T> data;

public:

    SortsSorts() = default;
    //	~SortsSorts();

    // закинуть данные
    void setData(QVector<T> data) {
        this->data = data;
        qDebug() << this->data.size();
    }

    // получитьданные, неизменяемые, по ссылке
    auto getData() const {
        return static_cast<const decltype(data) &>(data);
    }

    // кол-во элементов
    auto size() const {
        return data.size();
    }

    void mergeSort()//сортировка слиянием
    {
        profiler.reset();
        profiler.startStopwatch();

        int n = data.size();

        T *buf(new T[n]);

        for(auto size = 1; size < n; size*=2)
        {
            int start = 0;

            for(; (start+size) < n; start += size*2)
            {
                if(size < (n - start - size)){
                    merge(data.data() + start, size, data.data() + start + size, size, buf + start);
                }else{
                    merge(data.data() + start, size, data.data() + start + size, n - start - size, buf + start);
                }
            }

            for(; start<n; ++start)
                buf[start] = data.data()[start];
            T *temp = buf;
            buf = data.data();
            data.data() = temp;
        }

        delete[] buf;

        profiler.stopStopwatch();
    }

    void merge(T const *const A, int const nA, T const *const B, int const nB, T *const C)
    {
        int a(0),
                b(0);
        while(a + b <= nA + nB)
        {
            if((b >= nB) || ((a < nA) && (A[a] <= B[b])))
            {
                C[a + b] = A[a];
                ++a;
            } else {
                C[a + b] = B[b];
                ++b;
            }
        }
    }


    void sort0() //пузырек.. для тестирования
    {
        // Ну тут типа сортировка
        qDebug() << "sort0…";
        profiler.reset();
        profiler.startStopwatch();
        for (int j = 0; j < data.size()-1; j++) {
            for (int i = 0; i < data.size()-j-1; i++) {
                profiler.comparison();
                if (data[i] > data[i+1]) {
                    profiler.swap();
                    std::swap(data[i], data[i+1]);
                }
            }
        }
        profiler.stopStopwatch();

        qDebug() << "done" << "\nсравнений:" << profiler.getComparisons() <<
                    "\nсвапов:" << profiler.getSwaps() <<
                    "\nвремя:" << profiler.getTime();
    }

};

#endif // SORTSSORTS_H
