#ifndef SORTSWORKER_H
#define SORTSWORKER_H

#include <QObject>
#include <QSharedPointer>
#include "sortssorts.h"

// ������ ��� int, �.�. QObject �� ����� ���� ��������� �������
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
		sorts->setData(data.toVector());
	}

	void go() {
		qDebug() << "GO in thread" << this->thread() << "type" << sortType;
		switch (sortType) {
		case 0:
			qDebug() << "sort0" << !sorts.isNull();
			sorts->sort0();
			emit sorted();
			break;
		case 1:
			qDebug() << "merge" << !sorts.isNull();
			sorts->mergeSort();
			emit sorted();
			break;
		default:
			break;
		}
		qDebug() << "SORTED";
	}
};

#endif // SORTSWORKER_H
