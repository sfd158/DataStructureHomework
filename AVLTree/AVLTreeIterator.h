#ifndef AVLTreeIterator_h
#define AVLTreeIterator_h

#include"AVLTreeNode.h"
#include<vector>
template<typename T>
	class AVLTree;

template<typename T>
class AVLTreeIterator{
	friend class AVLTree<T>;
	friend class AVLTreeNode<T>;
	public:
		AVLTreeIterator();
		~AVLTreeIterator();
	private:
		AVLTreeIterator(const AVLTree<T>* tr,AVLTreeNode<T> *rhs);
	public:
		bool operator == (const AVLTreeIterator<T> &rhs)const;
		bool operator != (const AVLTreeIterator<T> &rhs)const;
		const T& operator * ();
	private:
		AVLTreeNode<T> *node;
			
	public:
		AVLTreeIterator<T>& operator ++ ();
		AVLTreeIterator<T>  operator ++ (int);
		AVLTreeIterator<T>& operator -- ();
		AVLTreeIterator<T>  operator -- (int);
	private:
		AVLTreeNode<T>* prev(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* next(AVLTreeNode<T> *rhs);
	private:
		const AVLTree<T> *tree;
};

template<typename T>
AVLTreeIterator<T>::AVLTreeIterator()
{
	node = nullptr;
}

template<typename T>
AVLTreeIterator<T>::~AVLTreeIterator(){}

template<typename T>
AVLTreeIterator<T>::AVLTreeIterator(const AVLTree<T> *tr,AVLTreeNode<T> *rhs):tree(tr),node(rhs){}

template<typename T>
bool AVLTreeIterator<T>::operator == (const AVLTreeIterator<T> &rhs)const
{
	return this->node == rhs.node;
}

template<typename T>
bool AVLTreeIterator<T>::operator != (const AVLTreeIterator<T> &rhs)const
{
	return this->node != rhs.node;
}

template<typename T>
AVLTreeIterator<T>& AVLTreeIterator<T>::operator ++ ()
{
	node = next(node);
	return *this;
}

template<typename T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator ++ (int)
{
	AVLTreeIterator<T> rhs = *this;
	node = next(node);
	return *this;
}

template<typename T>
AVLTreeIterator<T>& AVLTreeIterator<T>::operator -- ()
{
	node = prev(node);
	return *this;
}

template<typename T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator -- (int)
{
	AVLTreeIterator<T> rhs = *this;
	node = prev(node);
	return *this;
}

template<typename T>
AVLTreeNode<T>* AVLTreeIterator<T>::prev(AVLTreeNode<T> *rhs)
{
	if(rhs->left!=nullptr)
		return tree->maximum(rhs->left);
	std::vector<AVLTreeNode<T>* > s;
	AVLTreeNode<T> *p = tree->root;
	while(p!=nullptr)
	{
		s.push_back(p);
		if(p->value<rhs->value)
			p = p->right;
		else if(rhs->value<p->value)
			p = p->left;
		else break;
	}
	for(int j = s.size()-1;j>=1;j--)
	{
		if(s[j-1]->right == s[j])return s[j-1];
	}
	return nullptr;
}
template<typename T>
AVLTreeNode<T>* AVLTreeIterator<T>::next(AVLTreeNode<T> *rhs)
{
	if(rhs->right!=nullptr)
		return tree->minimum(rhs->right);
	std::vector<AVLTreeNode<T>* > s;
	AVLTreeNode<T> *p = tree->root;
	while(p!=nullptr)
	{
		s.push_back(p);
		if(p->value<rhs->value)
			p = p->right;
		else if(rhs->value<p->value)
			p = p->left;
		else break;
	}
	for(int j = s.size()-1;j>=1;j--)
	{
		if(s[j-1]->left == s[j])return s[j-1];
	}
	return nullptr;
} 

template<typename T>
const T& AVLTreeIterator<T>::operator * ()
{
	return node->value;
}
#endif

