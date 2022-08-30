#pragma once
#ifndef DATA_PREPROCESS_H_
#define DATA_PREPROCESS_H_
#include<string>
#include<kfr.h>
#include "loadfile.h"

using namespace kfr;

template <typename T >
class Data_preprocess:public loadfile
{
private:
	struct Node
	{
		T data;
		Node *next;
	};
	Node *head;
	Node *p;
	int num;//采样点的个数

public:
	int caculate(float reader);
	Stack();
	bool empty() const;
	bool push();
	bool pop();

};

template <typename T>
Data_preprocess<T>::Stack()
{
	head = NULL;
	length = 0;
}

template <typename T>
bool Data_preprocess<T>::empty()const
{
	return head;
}

template <typename T>
void Data_preprocess<T>::push(T data);
#endif