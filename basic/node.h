#ifndef NODE__H
#define NODE__H
#include <iostream>

enum Status{white, grey, black};

template<class T>
class Node{
public:
	T member;

	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node<T>* next;

	Status status;

	Node();
	Node(const Node& x);
	Node(const T x);
};

//----- defination goes here -----
template <class T>
Node<T>::Node():
	member(),
	next(nullptr),
	parent(nullptr),
	left(nullptr),
	right(nullptr),
	status(white)
{}

template <class T>
Node<T>::Node(const Node& x):
	member(x.member),
	next(x.next)
{}

template <class T>
Node<T>::Node(const T val):
	member(val),
	next(nullptr),
	parent(nullptr),
	left(nullptr),
	right(nullptr)
{}


#endif
