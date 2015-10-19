#ifndef SORTSWORKER_H
#define SORTSWORKER_H

#include <QObject>
#include <QSharedPointer>
#include "sortssorts.h"

class SortsWorker : public QObject
{
	Q_OBJECT
	using sort_t = int;
public:
	explicit SortsWorker(QSharedPointer<SortsSorts<int>> s, int sort) :
		QObject(),
		sorts{s}
	{

	}

private:
	QSharedPointer<SortsSorts<int>> sorts;
	int sortType;

signals:

public slots:
	void go() {
		switch (sortType) {
		case 1:

			break;
		default:
			break;
		}
	}
};

#endif // SORTSWORKER_H
