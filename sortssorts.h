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
    SortsProfiler profiler;
    QVector<T> data;

public:
    struct MergePosInfo
    {
        int left;
        int mid;
        int right;
    };
    using sort_t = QVector<T>;
    SortsSorts() = default;
    //	~SortsSorts();

    // закинуть данные
    void setData(sort_t data) {
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
        int mid,
                left = 0,
                right = data.size() - 1;
        std::vector<std::pair<int, int>> list;
        std::vector<MergePosInfo> mlist;
        list.push_back(std::pair<int, int>(left, right));

        MergePosInfo info;
        while(true){
            if(list.size() == 0)
                break;

            left = list.back().first;
            right = list.back().second;
            list.pop_back();
            mid = (right + left) / 2;

            if(left < right)
            {
                info.left = left;
                info.right = right;
                info.mid = mid + 1;

                mlist.push_back(info);
                list.push_back(std::pair<int, int>(left, mid));
                list.push_back(std::pair<int, int>((mid+1), right));
            }
        }

        for(auto i = mlist.size() - 1; i >= 0; i--)
            merge(data, mlist[i].left, mlist[i].mid, mlist[i].right);

        profiler.stopStopwatch();
    }

    void merge(sort_t numbers, int left, int mid, int right)//функция слияния
    {
        sort_t temp;
        temp.resize(25);
        int i,
                left_end,
                num_elements,
                tmp_pos;

        left_end = mid -1;
        tmp_pos = left;
        num_elements = right - left + 1;

        while((left <= left_end) && (mid <= right)){
            if(numbers[left] <= numbers[mid])
                temp[tmp_pos++] = numbers[left++];
            else
                temp[tmp_pos++] = numbers[mid++];
        }

        while(left <= left_end)
            temp[tmp_pos++] = numbers[left++];

        while(mid <= right)
            temp[tmp_pos++] = numbers[mid++];

        for(i = 0; i < num_elements; i++)
            numbers[right--] = temp[right];
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
