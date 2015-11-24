#include "sortsgenerator.h"


//template <class T>
QList<int> SortsGenerator::generate(int size)
{
	std::random_device rd; // ��������� ��������� ����� �� ��
	std::mt19937 mt(rd()); // ���������� rd ��� ��������� seed ��� ����� �������� ����������
	// ���������� �������������
	std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
					       std::numeric_limits<int>::max());

	QList<int> data;
	data.reserve(size);
	for (int i = 0; i < size; i++)
		data << dist(mt);

	// ���������� data �� �����
	return data;
}
