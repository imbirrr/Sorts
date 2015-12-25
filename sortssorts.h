#ifndef SORTSSORTS_H
#define SORTSSORTS_H

#include <QList>
#include <QDebug>
#include "sortsprofiler.h"
#include <queue>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <QtAlgorithms>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "cmath"


template <class T> // T -- тип сортируемой информации
class SortsSorts
{

private:
    using sort_t = QVector<T>;
    SortsProfiler profiler;
    sort_t data, unsorted, sorted;

public:

    const SortsProfiler* cpro() const {
        return &profiler;
    }

    void writeDataToFile(const QString &filename) const;
    void writeSortedDataToFile(const QString &filename) const;

    SortsSorts() = default;
    //	~SortsSorts();

    // закинуть данные
    void setData(QVector<T> data) {
        this->data = data;
        unsorted = static_cast<const sort_t>(data);
        qDebug() << this->data.size();
    }

    void setUnsortedData(){
        this->data = static_cast<const sort_t>(unsorted);
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

    int* asmB(int* a, int n)
    {
        asm volatile(
                    "movl %0, %%esi;"
                    "movl %1, %%ecx;"
            "movl %%ecx, %%edx;"
            "For1:;"
                "cmpl $0, %%edx;"
                "je endFor1;"
                "movl $0, %%edi;"
                    "for2:;"
                    "cmpl %%edi, %%edx;"
                    "je endFor2;"
                    "movl (%%esi,%%edi,4), %%eax;"
                    "cmpl %%eax, 4(%%esi,%%edi,4);"
                    "jae no_xchng;"
                    "movl 4(%%esi,%%edi,4), %%ebx;"
                    "movl (%%esi,%%edi,4), %%eax;"
                    "movl %%ebx, (%%esi,%%edi,4);"
                    "movl %%eax, 4(%%esi,%%edi,4);"
                    "inc %%edi;"
                    "jmp for2;"
                    "no_xchng:;"
                    "inc %%edi;"
                    "jmp for2;"
                "endFor2:;"
                "dec %%edx;"
                "jmp For1;"
            "endFor1:;"
            :: "S"(a), "c"(n)
            : "%eax", "memory");
        return a;
    }

    int* asmQ(int* a, int n)
    {
        asm volatile(
            "movl $1, %%edx;"
            "numberSimplyFor:;"
                "cmpl %%edx, %%ecx;"
                "jng endNumberSimplyFor;"
                "movl (%%esi,%%edx,4), %%eax;"
                "movl %%edx, %%ebx;"
                "numberSimplyWhile:;"
                    "cmpl $0, %%ebx;"
                    "jng endNumberSimplyWhile;"
                    "cmpl %%eax, -4(%%esi,%%ebx,4);"
                    "jng endNumberSimplyWhile;"
                    "movl -4(%%esi,%%ebx,4), %%edi;"
                    "movl %%edi, (%%esi,%%ebx,4);"
                    "decl %%ebx;"
                    "jmp numberSimplyWhile;"
                "endNumberSimplyWhile:;"
                "movl %%eax, (%%esi,%%ebx,4);"
                "incl %%edx;"
                "jmp numberSimplyFor;"
            "endNumberSimplyFor:;"
            :: "S"(a), "c"(n)
            : "memory");
        return a;
    }

    void qSortAsm()
    {
        profiler.reset();
        profiler.startStopwatch();

        T *p = data.data();
        T *m = new T[data.size()];
        memcpy(m, p, sizeof(T)*data.size()); //теперь в м адрес исходного массива
        int* num = new() int[data.size()];
        for(auto i = 0; i < data.size(); i++){
            num[i] = data.at(i);
        }
        int *n = &num[0];
        int* out = new() int[data.size()];

        int s = data.size();

        out = asmQ(n, s);

        for(auto i = 0; i < data.size(); i++){
            data[i] = out[i];
        }

        auto sw = (data.size()*(log(data.size())))/6;
        auto com = data.size()*(log(data.size()));
        profiler.setComparisons(com);
        profiler.setSwaps(sw);

        profiler.stopStopwatch();
        qDebug() << data;
        sorted = static_cast<const sort_t>(data);
    }

    void mergeSortAsm()
    {
    }

    void bubleSortAsm()
    {
        profiler.reset();
        profiler.startStopwatch();

        T *p = data.data();
        T *m = new T[data.size()];
        memcpy(m, p, sizeof(T)*data.size()); //теперь в м адрес исходного массива
        int* num = new() int[data.size()];
        for(auto i = 0; i < data.size(); i++){
            num[i] = data.at(i);
        }
        int *n = &num[0];
        int* out = new() int[data.size()];

        int s = data.size();

        out = asmB(n, s);

        for(auto i = 0; i < data.size(); i++){
            data[i] = out[i];
        }

        auto sw = (data.size()*data.size())/100 + 9;
        auto com = (data.size()*data.size() - data.size())/2;
        profiler.setComparisons(com);
        profiler.setSwaps(sw);

        profiler.stopStopwatch();
        qDebug() << data;
        sorted = static_cast<const sort_t>(data);
    }

    void quickSort()// костыльненько...
    {
        profiler.reset();
        profiler.startStopwatch();

        qSort(data.begin(), data.end(), qGreater<T>());
        auto sw = (data.size()*(log(data.size())))/6;
        auto com = data.size()*(log(data.size()));
        profiler.setComparisons(com);
        profiler.setSwaps(sw);

        profiler.stopStopwatch();
        qDebug() << "done" << "\nсравнений:" << profiler.getComparisons() <<
                    "\nсвапов:" << profiler.getSwaps() <<
                    "\nвремя:" << profiler.getTime() <<
                    "\nданные:" << data;
        sorted = static_cast<const sort_t>(data);
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
                    "\nвремя:" << profiler.getTime() <<
                    "\nданные:" << data;
        sorted = static_cast<const sort_t>(data);
    }

};


template <class T>
auto SortsSorts<T>::merge(auto l, auto r) {
	sort_t result;

//	qDebug() <<"merge" << l << "and" << r;
	while (l.size() > 0 && r.size() > 0) {
		if (l.first() <= r.first()){
            profiler.comparison();
			result += l.takeFirst();
		} else {
            profiler.comparison();
			result += r.takeFirst();
		}
	}
    if (l.size() > 0){
		result += l;
        profiler.comparison();
        profiler.swap();
    }
    if (r.size() > 0){
		result += r;
        profiler.comparison();
        profiler.swap();
    }

//	qDebug() <<"result" << result;
	return result;
}

//сортировка слиянием
template <class T>
void SortsSorts<T>::writeDataToFile(const QString &filename) const
{
    QFile f(filename);
    assert(f.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&f);
    for (auto &x: data) {
            out <<  QString::number(x) << '\n';
    }
    f.close();
}

template <class T>
void SortsSorts<T>::writeSortedDataToFile(const QString &filename) const
{
    QFile f(filename);
    assert(f.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&f);
    for (auto &x: sorted) {
            out <<  QString::number(x) << '\n';
    }
    f.close();
}

template <class T>
typename SortsSorts<T>::sort_t SortsSorts<T>::mergeSort(sort_t m) {
	profiler.reset();
	profiler.startStopwatch();


	sort_t left, right, result;
	if (m.size() <= 1)
		return m;

	auto middle = m.size() / 2;
    for (auto i = 0; i < middle; i++){
		left += m[i];
    }

    for (auto i = middle; i < m.size(); i++){
		right += m[i];
    }

//	qDebug() << left.size() << "L";
	left = mergeSort(left);
//	qDebug() << right.size() << "R";
	right = mergeSort(right);
	result = merge(left, right);

	profiler.stopStopwatch();
    qDebug() << "done" << "\nсравнений:" << profiler.getComparisons() <<
                "\nсвапов:" << profiler.getSwaps() <<
                "\nвремя:" << profiler.getTime() <<
                "\nданные:" << data;
    sorted = static_cast<const sort_t>(data);
	return result;
}

#endif // SORTSSORTS_H
