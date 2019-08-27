#ifndef AVLTreeNode_h
#define AVLTreeNode_h

#include"AVLTreeNode.h" 
template<typename T>
	class AVLTree;
template<typename T>
	class AVLTreeIterator;

template<typename T>
class AVLTreeNode{
	friend class AVLTree<T>;
	friend class AVLTreeIterator<T>;
	private:
		AVLTreeNode(const T &rhs);
		~AVLTreeNode();
	private:
		AVLTreeNode<T> *left,*right;
		T value;
		int height;
};

template<typename T>
AVLTreeNode<T>::AVLTreeNode(const T &rhs):value(rhs)
{
	left = right = nullptr;
	height = 0;
}

template<typename T>
AVLTreeNode<T>::~AVLTreeNode(){}
#endif
