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
        sortType{0},
        asmSortType{0}
	{

	}

    const SortsProfiler* getProfiler() const { return sorts->cpro();}

	auto getData() {
		return sorts->getData();
	}

private:
	QSharedPointer<SortsSorts<int>> sorts;
    int sortType;
    int asmSortType;

signals:
	void sorted();//QSharedPointer<SortsSorts<int>> result);

public slots:
	void setSortType(int type) {
		sortType = type;
	}

    void setAsmSortType(int type) {
        asmSortType = type;
    }

    void setUnsortData(){
        sorts->setUnsortedData();
    }

	void setData(QList<int> data) {
		sorts->setData(data.toVector());
//        sorts->writeDataToFile("setted");
//        qDebug() << "WRITED";
	}

    void writeDataToFile(const QString &filename) const {
        sorts->writeDataToFile(filename);
    }

    void writeSortedDataToFile(const QString &filename) const {
        sorts->writeSortedDataToFile(filename);
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
        case 2:
            qDebug() << "quick" << !sorts.isNull();
            sorts->quickSort();
            emit sorted();
            break;
		}

		qDebug() << "SORTED";
        //sorts->writeDataToFile("sorted");
        qDebug() << "WRITED";
	}

    void goAsm(){
        switch (asmSortType) {
        case 0:
            qDebug() << "quickAsm" << !sorts.isNull();
            sorts->qSortAsm();
            emit sorted();
            break;
        case 1:
            qDebug() << "bubble" << !sorts.isNull();
            sorts->bubleSortAsm();
            emit sorted();
            break;
        default:
            break;

        }
    }
};

#endif // SORTSWORKER_H
