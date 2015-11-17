#ifndef SORTSSORTS_H
#define SORTSSORTS_H

#include <QList>
#include <QDebug>
#include "sortsprofiler.h"


template <class T> // T -- тип сортируемой информации
class SortsSorts
{

private:
	SortsProfiler profiler;
	QList<T> data;

public:
	SortsSorts() = default;
//	~SortsSorts();

	// закинуть данные
	void setData(QList<T> data) {
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

	void sort0()
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
