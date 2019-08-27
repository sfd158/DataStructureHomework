#ifndef RBTreeIterator_h
#define RBTreeIterator_h
#include"_rbTreeNode.h"
template<typename _Tp>
class RBTreeIterator{
	friend class rbtree<_Tp>;
	friend class _rbTreeNode<_Tp>;
	public:
		typedef _rbTreeNode<_Tp> node_type;
		typedef typename node_type::value_type value_type;
		RBTreeIterator();
		~RBTreeIterator();
	private:
		RBTreeIterator(const rbtree<_Tp>* tree,node_type *rhs);	
	private:
		typedef typename node_type::color_type color_type;	
	public:
		bool operator == (const RBTreeIterator<_Tp> &rhs)const;
		bool operator != (const RBTreeIterator<_Tp> &rhs)const;
		const value_type& operator * ();
	private:
		node_type *node;
		const rbtree<_Tp> *tree;	
	public:
		RBTreeIterator<_Tp>& operator ++ ();
		RBTreeIterator<_Tp>  operator ++ (int);
		RBTreeIterator<_Tp>& operator -- ();
		RBTreeIterator<_Tp>  operator -- (int);
};

template<typename _Tp>
RBTreeIterator<_Tp>::RBTreeIterator()
{
	node = nullptr;
}

template<typename _Tp>
RBTreeIterator<_Tp>::RBTreeIterator(const rbtree<_Tp> *_tree,typename RBTreeIterator<_Tp>::node_type *_node):tree(_tree),node(_node)
{
	
}

template<typename _Tp>
RBTreeIterator<_Tp>::~RBTreeIterator(){}

template<typename _Tp>
bool RBTreeIterator<_Tp>::operator == (const RBTreeIterator<_Tp> &rhs)const
{
	return this->node == rhs.node;
}

template<typename _Tp>
bool RBTreeIterator<_Tp>::operator != (const RBTreeIterator<_Tp> &rhs)const
{
	return this->node != rhs.node;
}

template<typename _Tp>
RBTreeIterator<_Tp>& RBTreeIterator<_Tp>::operator ++ ()
{
	node = tree->next(node);
	return *this;
}

template<typename _Tp>
RBTreeIterator<_Tp> RBTreeIterator<_Tp>::operator ++ (int)
{
	RBTreeIterator<_Tp> rhs = *this;
	node = tree->next(node);
	return rhs;
}

template<typename _Tp>
RBTreeIterator<_Tp>& RBTreeIterator<_Tp>::operator -- ()
{
	node = tree->prev(node);
	return *this;
}

template<typename _Tp>
RBTreeIterator<_Tp> RBTreeIterator<_Tp>::operator -- (int)
{
	RBTreeIterator<_Tp> rhs = *this;
	node = tree->prev(node);
	return rhs;
}

template<typename _Tp>
const typename RBTreeIterator<_Tp>::value_type& RBTreeIterator<_Tp>::operator * ()
{
	return node->key;
}
#endif 
