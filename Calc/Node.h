#pragma once


template <typename TElement>
struct TNode {
	TElement data;
	TNode<TElement>* next;
	TNode(TElement newData, TNode<TElement>* nextNode);
};

template<typename TElement>
TNode<TElement>::TNode(TElement newData, TNode<TElement>* nextNode) {
	data = newData;
	next = nextNode;
}