#ifndef SORTSPROFILER_H
#define SORTSPROFILER_H

#include <QTime>

// Профайлер
class SortsProfiler
{
public:
	// ret_t -- тип значений, с которыми работает профайлер.
	using ret_t = unsigned int;
	SortsProfiler() {
		reset();
	}

//	~SortsProfiler();

	// Вызывать при сравнении
	void comparison() {
		comparisons++;
	}

	// Вызывать при свапе
	void swap() {
		swaps++;
	}

	// "Запускает" секундомер
	void startStopwatch() {
		startTime = QTime::currentTime();
	}

	// "Останавливает" секундомер
	void stopStopwatch() {
		stopTime = QTime::currentTime();
	}

	// Сброс значений
	void reset() {
		comparisons = 0;
		swaps = 0;
		startTime = QTime();
		stopTime = QTime();
	}

	// Возвращает количество перестановок
	auto getSwaps() const {
		return swaps;
	}

	// ВОзвращает количество сравнений
	auto getComparisons() const {
		return comparisons;
	}

	// Возвращает время секундомера в милисекундах
	auto getTime() {
		startTime.msecsTo(stopTime);
	}


private:
	ret_t comparisons, swaps;
	QTime startTime, stopTime;
};

#endif // SORTSPROFILER_H
