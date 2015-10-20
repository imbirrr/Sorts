#ifndef SORTSWORKER_H
#define SORTSWORKER_H

#include <QObject>
#include <QSharedPointer>
#include "sortssorts.h"

// только для int, т.к. QObject не может быть шаблонным классом
class SortsWorker : public QObject
{
	Q_OBJECT
	using sort_t = int;
public:
	explicit SortsWorker(QSharedPointer<SortsSorts<int>> s, int sort) :
		QObject(),
		sorts{s},
		sortType{sort}
	{

	}

private:
	QSharedPointer<SortsSorts<int>> sorts;
	int sortType;

signals:
	void sorted();//QSharedPointer<SortsSorts<int>> result);

public slots:
	void go() {
		qDebug() << "GO";
		switch (sortType) {
		case 0:
			qDebug() << sorts.isNull();

			// ошибка: undefined reference to `SortsSorts<int>::sort1()'
			//sorts->sort1(); // че к чему(
			emit sorted();
			break;
		default:
			break;
		}
		qDebug() << "SORTED";
	}
};

#endif // SORTSWORKER_H
