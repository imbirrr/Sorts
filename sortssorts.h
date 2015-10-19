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
		auto t = data;
	qDebug() << t;
	}

	// получитьданные, неизменяемые, по ссылке
	auto getData() const {
		return static_cast<const decltype(data) &>(data);
	}

	// кол-во элементов
	auto size() const {
		return data.size();
	}

	void sort1();

};

#endif // SORTSSORTS_H
