#ifndef SORTSPROFILER_H
#define SORTSPROFILER_H

#include <QTime>

// ���������
class SortsProfiler
{
public:
	// ret_t -- ��� ��������, � �������� �������� ���������.
	using ret_t = unsigned int;
	SortsProfiler() {
		reset();
	}

//	~SortsProfiler();

	// �������� ��� ���������
	void comparison() {
		comparisons++;
	}

	// �������� ��� �����
	void swap() {
		swaps++;
	}

	// "���������" ����������
	void startStopwatch() {
		startTime = QTime::currentTime();
	}

	// "�������������" ����������
	void stopStopwatch() {
		stopTime = QTime::currentTime();
	}

	// ����� ��������
	void reset() {
		comparisons = 0;
		swaps = 0;
		startTime = QTime();
		stopTime = QTime();
	}

	// ���������� ���������� ������������
	auto getSwaps() const {
		return swaps;
	}

	// ���������� ���������� ���������
	auto getComparisons() const {
		return comparisons;
	}

	// ���������� ����� ����������� � ������������
    auto getTime() const {
		return startTime.msecsTo(stopTime);
	}

    void setComparisons (int inp){
        comparisons = inp;
    }

    void setSwaps (int inp){
        swaps = inp;
    }


private:
	ret_t comparisons, swaps;
	QTime startTime, stopTime;
};

#endif // SORTSPROFILER_H
