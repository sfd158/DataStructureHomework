#ifndef _rbTreeNode_h
#define _rbTreeNode_h
template <typename _Tp>
class rbtree;
template <typename _Tp>
class RBTreeIterator;

template <typename _Tp>
class _rbTreeNode{
	friend class rbtree<_Tp>;
	friend class RBTreeIterator<_Tp>;
	private:
		typedef bool color_type;
		typedef _Tp value_type;
		typedef _rbTreeNode<_Tp> node_type;
	private:
		static const color_type BLACK,RED;
		value_type key;
		node_type *left,*right,*p;
		color_type color;			// true == red  &&  false == black
	private:
		_rbTreeNode();
		_rbTreeNode(value_type _key);
};

template <typename _Tp>
const typename _rbTreeNode<_Tp>::color_type
_rbTreeNode<_Tp>::BLACK = false;

template <typename _Tp>
const typename _rbTreeNode<_Tp>::color_type
_rbTreeNode<_Tp>::RED = true;

template<typename _Tp>
_rbTreeNode<_Tp>::_rbTreeNode()
{
	left = right = p = nullptr;
	color = BLACK;
}

template<typename _Tp>
_rbTreeNode<_Tp>::_rbTreeNode(value_type _key)
{
	left = right = p = nullptr;
	color = RED;
	key = _key;
}
#endif
