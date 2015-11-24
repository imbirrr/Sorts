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
    using sort_t = QVector<T>;
    sort_t data;

public:
<<<<<<< HEAD
=======

>>>>>>> 2596ea74d9b1f14ae8d5d074dd630e0eebdbce4d
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

<<<<<<< HEAD
    void mergeSort() {
	    qDebug() << "merge…";
	    data = mergeSort(data);
    }

    sort_t mergeSort(sort_t);
    auto merge(auto l, auto r);

=======
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
>>>>>>> 2596ea74d9b1f14ae8d5d074dd630e0eebdbce4d


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


template <class T>
auto SortsSorts<T>::merge(auto l, auto r) {
	sort_t result;

//	qDebug() <<"merge" << l << "and" << r;
	while (l.size() > 0 && r.size() > 0) {
		if (l.first() <= r.first()){
			result += l.takeFirst();
		} else {
			result += r.takeFirst();
		}
	}
	if (l.size() > 0)
		result += l;
	if (r.size() > 0)
		result += r;

//	qDebug() <<"result" << result;
	return result;
}

//сортировка слиянием
template <class T>
typename SortsSorts<T>::sort_t SortsSorts<T>::mergeSort(sort_t m) {
	profiler.reset();
	profiler.startStopwatch();


	sort_t left, right, result;
	if (m.size() <= 1)
		return m;

	auto middle = m.size() / 2;
	for (auto i = 0; i < middle; i++)
		left += m[i];

	for (auto i = middle; i < m.size(); i++)
		right += m[i];

//	qDebug() << left.size() << "L";
	left = mergeSort(left);
//	qDebug() << right.size() << "R";
	right = mergeSort(right);
	result = merge(left, right);

	profiler.stopStopwatch();
	return result;
}

#endif // SORTSSORTS_H
