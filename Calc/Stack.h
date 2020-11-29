#pragma once
#include "Node.h"

template <typename TElement>
class Stack {
private:
	unsigned int sizeOfstack;
	TNode<TElement>* currentTop;
	
public:
	Stack();
	
	~Stack();

	void push(const TElement element);

	void pop();

	TElement top();

	unsigned int size();
};

template <typename TElement>
Stack<TElement>::Stack() {
	sizeOfstack = 0;
	currentTop = nullptr;
}

template <typename TElement>
Stack<TElement>::~Stack() {
	while (size())
		pop();
}

template <typename TElement>
void Stack<TElement>::push(const TElement element) {
	TNode<TElement>* node = new TNode <TElement>(element, currentTop);
	sizeOfstack++;
	currentTop = node;
}

template <typename TElement>
void Stack<TElement>::pop() {
	sizeOfstack--;
	TNode<TElement>* node = currentTop;
	currentTop = currentTop->next;
	delete node;
}

template <typename TElement>
TElement Stack<TElement>::top() {
	return currentTop->data;
}

template<typename TElement>
unsigned int Stack<TElement>::size() {
	return sizeOfstack;
}