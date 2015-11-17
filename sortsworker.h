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
	explicit SortsWorker(SortsSorts<int> *s) :
		QObject(),
		sorts{s},
		sortType{0}
	{

	}

	auto getData() {
		return sorts->getData();
	}

private:
	QSharedPointer<SortsSorts<int>> sorts;
	int sortType;

signals:
	void sorted();//QSharedPointer<SortsSorts<int>> result);

public slots:
	void setSortType(int type) {
		sortType = type;
	}

	void setData(QList<int> data) {
		sorts->setData(data);
	}

	void go() {
		qDebug() << "GO in thread" << this->thread();
		switch (sortType) {
		case 0:
			qDebug() << "Is data here?" << !sorts.isNull();
			sorts->sort0();
			emit sorted();
			break;
		default:
			break;
		}
		qDebug() << "SORTED";
	}
};

#endif // SORTSWORKER_H
