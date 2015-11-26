#ifndef SORTSSORTS_H
#define SORTSSORTS_H

#include <QList>
#include <QDebug>
#include "sortsprofiler.h"
#include <queue>
#include <vector>
#include <cstring>


template <class T> // T -- тип сортируемой информации
class SortsSorts
{

private:
    using sort_t = QVector<T>;
    SortsProfiler profiler;
    sort_t data;

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

    void mergeSort() {
	    qDebug() << "merge…";
	    data = mergeSort(data);
    }

    sort_t mergeSort(sort_t); //сортировка слиянием
    auto merge(auto l, auto r);//слияние

    void qSortAsm()
    {
        profiler.reset();
        profiler.startStopwatch();

        T *p = data.data();
        T *m = new T[data.size()];
        memcpy(m, p, sizeof(T)*data.size()); //теперь в м адрес исходного массива
        size_t n = data.size(); //размер массива
        size_t n1 = data.size() - 1;
        auto step = sizeof(T); //шаг сдвига
        auto l = 0;

        asm(
        "qsort:"
        "movl m, %esi"
        "movl l, %eax"
        "movl %eax, %ecx"
        "movl n1, %ebx"
        "add %ebx, %ecx"
        "shr $1, %ecx"
        "movl (%esi,%ecx,$4), %ecx"
        "cmp %ebx, %eax"
        "ja end_while1"
        "begin_while1:"
        "loop_while2:"
        "cmp %ecx, (%esi,%eax,$4)"
        "jge end_while2"
        "inc %eax"
        "jmp loop_while2"
        "end_while2:"
        " "
        "loop_while3:"
        "cmp %ecx, (%esi,%ebx,$4)"
        "jle end_while3"
        "dec %ebx"
        "jmp loop_while3"
        "end_while3:"
        " "
        "cmp %ebx, %eax"
        "ja end_if1"
        "jz no_change"
        "pushl %ecx"
        "movl (%esi,%eax,$4), %ecx"
        "movl (%esi,%ebx,$4), %edx"     //тут меняем местами
        "movl %edx, (%esi,%eax,$4)"
        "movl %ecx, (%esi,%ebx,$4)"
        "popl %ecx"
        "no_change:"
        "inc %eax"
        "dec %ebx"
        "end_if1:"
        " "
        "cmp %ebx, %eax"
        "jbe begin_while1"
        "end_while1:"
        " "
        "cmp %ebx, l"
        "jae end_if2"
        "pushl %eax"
        "call "
        );

        profiler.stopStopwatch();
    }

    void mergeSortAsm()
    {
        profiler.reset();
        profiler.startStopwatch();

        T *p = data.data();
        T *m = new T[data.size()];
        memcpy(m, p, sizeof(T)*data.size()); //теперь в м адрес исходного массива
        size_t n = data.size(); //размер массива
        auto step = sizeof(T); //шаг сдвига

        asm
        (
        ""
        );

        profiler.stopStopwatch();
    }

    void bubleSortAsm()
    {

    }

    void bubleSort() //пузырек.. для тестирования
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
