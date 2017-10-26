#pragma once
#include <vector>
template<class T>
class ImmovableTable
{
public:	
	ImmovableTable(int granularity);
	~ImmovableTable();

	void add(T i);
	int granularity;
	T underlyingArray[100][100];
};



template<class T>
ImmovableTable<T>::ImmovableTable(int granularity)
{
	this->granularity = granularity;
}

template<class T>
ImmovableTable<T>::~ImmovableTable()
{
}
template<class T>
void ImmovableTable<T>::add(T i) {
	int x = i.GetXPos();
	int y = i.GetYPos();
	//	underlyingArray[x][y]
}

