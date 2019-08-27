#ifndef rbtree_h
#define rbtree_h

#include"_rbTreeNode.h"
#include"RBTreeIterator.h"
template<typename _Tp>
class rbtree
{
	public:
		friend class RBTreeIterator<_Tp>;
		friend class _rbTreeNode<_Tp>;
		typedef RBTreeIterator<_Tp> iterator;
		typedef unsigned int size_type;
		typedef typename iterator::value_type value_type;
	private:
		typedef typename iterator::node_type node_type;
		typedef typename node_type::color_type color_type;
		static const color_type RED,BLACK;
	public:
		rbtree();
		~rbtree();
		iterator begin();
		iterator end();
		iterator rbegin();
		iterator rend();
		void insert(value_type key);
	 	node_type * search(value_type key);
		void erase(value_type key);
		size_type size();
		void clear();
		bool operator == (const rbtree<_Tp> &rhs)const;
		bool operator != (const rbtree<_Tp> &rhs)const;
		bool operator < (const rbtree<_Tp> &rhs)const;
		bool operator > (const rbtree<_Tp> &rhs)const;
	private:
		void _clear(node_type*);
		void leftRotate(node_type*);
		void rightRotate(node_type*);
	
		void rbDelete(node_type*);
		void rbDeleteFixup(node_type*);
	
		void rbInsertFixup(node_type*);
	
		node_type* prev(node_type*)const;
		node_type* next(node_type*)const;
		
		node_type* minimum(node_type*)const;
		node_type* maximum(node_type*)const;
	private:
		node_type *nil;
		node_type *root;
		size_type _size;
};

template<typename _Tp>
const
typename rbtree<_Tp>::color_type
rbtree<_Tp>::RED = rbtree<_Tp>::node_type::RED;

template<typename _Tp>
const
typename rbtree<_Tp>::color_type
rbtree<_Tp>::BLACK = rbtree<_Tp>::node_type::BLACK;

template<typename _Tp>
rbtree<_Tp>::rbtree()
{
	root = nil = new node_type; 
	_size = 0;
}

template<typename _Tp>
rbtree<_Tp>::~rbtree()
{
	
}

template<typename _Tp>
void rbtree<_Tp>::clear()
{
	_clear(root);
	root = nil;
	_size = 0;
}

template<typename _Tp>
void rbtree<_Tp>::_clear(node_type *x)
{
	if(x==nil)return;
	_clear(x->left);
	_clear(x->right);
	delete x;
}

template<typename _Tp>
typename rbtree<_Tp>::iterator
rbtree<_Tp>::begin()
{
	return iterator(this,minimum(root));
}

template<typename _Tp>
typename rbtree<_Tp>::iterator
rbtree<_Tp>::end()
{
	return iterator(this,nil);
}

template<typename _Tp>
typename rbtree<_Tp>::iterator
rbtree<_Tp>::rbegin()
{
	return iterator(this,maximum(root));
}

template<typename _Tp>
typename rbtree<_Tp>::iterator
rbtree<_Tp>::rend()
{
	return iterator(this,nil);
}

template<typename _Tp>
typename rbtree<_Tp>::size_type
rbtree<_Tp>::size()
{
	return _size;
}

template <typename _Tp>
void rbtree<_Tp>::insert(typename rbtree<_Tp>::value_type key)
{
	node_type* t = new node_type;
	t->key = key;
	node_type* x = root;
	node_type* y = nil;
	while( x != nil )
	{
		y = x;
		if( key < x->key )
			x = x->left;
		else
			x = x->right;
	}
	t->p = y;
	if( y == nil )
		root = t;
	else
	{
		if ( t->key < y->key )
			y->left = t;
		else
			y->right = t;
	}
	t->left = nil;
	t->right = nil;
	t->color = RED;
	rbInsertFixup( t );
	++_size;
}

template <typename _Tp>
typename rbtree<_Tp>::node_type*
rbtree<_Tp>::search(typename rbtree<_Tp>::value_type key)
{
	node_type * x = root;
	while( x != nil && key != x->key )
	{
		if( key < x->key )
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template <typename _Tp>
void rbtree<_Tp>::erase(typename rbtree<_Tp>::value_type key )
{
	node_type * x = search( key );
	if( x != nil )
	{
		rbDelete( x );
		--_size;	
	}
}

template<typename _Tp>
typename rbtree<_Tp>::node_type*
rbtree<_Tp>::prev(typename rbtree<_Tp>::node_type *x)const
{
	if( x->left != nil ){
		x = x->left;
		while( x->right != nil )
			x = x->right;
		return x;
	}
	node_type * y = x->p;
	while( y != nil && x == y->left )
	{
		x = y;
		y = y->p;
	}
	return y;
}

template <typename _Tp>
typename rbtree<_Tp>::node_type* 
rbtree<_Tp>::next(typename rbtree<_Tp>::node_type *x)const
{
	if( x->right != nil ){
		x = x->right;
		while( x->left != nil )
			x = x->left;
		return x;
	}
	node_type * y = x->p;
	while( y != nil && x == y->right )
	{
		x = y;
		y = y->p;
	}
	return y;
}

template <typename _Tp>
typename rbtree<_Tp>::node_type* 
rbtree<_Tp>::minimum(typename rbtree<_Tp>::node_type *x)const
{
	if(x==nil)return x;
	while(x->left!=nil)
		x = x->left;
	return x;
}

template <typename _Tp>
void rbtree<_Tp>::leftRotate( node_type *x )
{
	node_type * y = x->right;
	if( x->p == nil )
		root = y;
	else{
		if( x == x->p->left )
			x->p->left = y;
		else
			x->p->right = y;
	}
	y->p = x->p;
	x->right = y->left;
	y->left->p = x;
	y->left = x;
	x->p = y;
}

template <typename _Tp>
void rbtree<_Tp>::rightRotate( node_type *x ){
	node_type * y = x->left;
	if( x->p == nil )
		root = y;
	else{
		if( x->p->left == x )
			x->p->left = y;
		else
			x->p->right = y;
	}
	y->p = x->p;
	x->left = y->right;
	y->right->p = x;
	y->right = x;
	x->p = y;
}


template <typename _Tp>
void rbtree<_Tp>::rbInsertFixup( node_type *z )
{
	while( z->p->color  == RED )
	{
		if( z->p == z->p->p->left )
		{
			node_type * y = z->p->p->right;
			if( y->color == RED )
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if( z == z->p->right )
				{
					z = z->p;
					leftRotate( z );
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				z->p->right->color = BLACK; 
				rightRotate( z->p->p );
			}
		}
		else{
			node_type * y = z->p->p->left;
			if( y->color == RED )
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if( z == z->p->left )
				{
					z = z->p;
					rightRotate( z );
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				z->p->left->color = BLACK;
				leftRotate( z->p->p );
			}
		}
	}
	root->color = BLACK;
}


template <typename _Tp>
void rbtree<_Tp>::rbDelete( node_type *z ){
	node_type * x = nil;
	node_type * y = nil;
	if( z->left == nil || z->right == nil )
		y = z;
	else
		y = next( z );
	if( y->left != nil )
		x = y->left;
	else
		x = y->right;
	x->p = y->p;
	if( y->p == nil )
		root = x;
	else
	{
		if( y == y->p->left )
			y->p->left = x;
		else
			y->p->right = x;
	}
	if( y != z )
		z->key = y->key;
	if( y->color == BLACK )
		rbDeleteFixup( x );
	delete y;
}

template <typename _Tp>
void rbtree<_Tp>::rbDeleteFixup(node_type * x)
{
	while( x != root && x->color == BLACK )
	{
		node_type * w = 0;
		if( x->p->left == x )
		{
			w = x->p->right;
			if( w->color == RED )
			{
				w->color = BLACK;
				x->p->color = RED;
				leftRotate( x->p );
				w = x->p->right;
			}
			if( w->left->color == BLACK && w->right->color == BLACK )
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if( w->right->color == BLACK )
				{
					w->left->color = BLACK;
					w->color = RED;
					rightRotate( w );
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftRotate( x->p );
				x = root;
			}
		}
		else
		{
			w = x->p->left;
			if( w->color == RED )
			{
				w->color = BLACK;
				x->p->color = RED;
				rightRotate( x->p );
				w = x->p->left;
			}
			if( w->right->color == BLACK && w->left->color == BLACK )
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if( w->left->color == BLACK )
				{
					w->right->color = BLACK;
					w->color = RED;
					leftRotate( w );
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightRotate( x->p );
				x = root;
			}
		}
	}
	x->color = BLACK;
}

template<typename _Tp>
bool 
rbtree<_Tp>::operator == (const rbtree<_Tp> &rhs)const
{
	if(_size != rhs._size)return false;
	node_type *a = (*this).minimum(root),*b = rhs.minimum(rhs.root);
	for(int i=0;i<_size;i++)
	{
		if(a->key != b->key)return false;
		a = (*this).next(a);
		b = rhs.next(b); 
	}
	return true;
}

template<typename _Tp>
bool 
rbtree<_Tp>::operator != (const rbtree<_Tp> &rhs)const
{
	return !((*this) == rhs);
}

template<typename _Tp>
bool 
rbtree<_Tp>::operator < (const rbtree<_Tp> &rhs)const
{
	size_type cnt = (*this)._size;
	if(cnt > rhs._size)cnt = rhs._size;
	node_type *a = (*this).minimum(root),*b = rhs.minimum(rhs.root);
	for(size_type i=0;i<cnt;i++)
	{
		if(a->key > b->key)return false;
		else if(a->key < b->key)return true;
		a = (*this).next(a);
		b = rhs.next(b);
	}
	return (*this)._size < rhs._size;
}

template<typename _Tp>
bool 
rbtree<_Tp>::operator > (const rbtree<_Tp> &rhs)const
{
	size_type cnt = (*this)._size;
	if(cnt > rhs._size)cnt = rhs._size;
	node_type *a = (*this).minimum(root),*b = rhs.minimum(rhs.root);
	for(size_type i=0;i<cnt;i++)
	{
		if(a->key < b->key)return false;
		else if(a->key > b->key)return true;
		a = (*this).next(a);
		b = rhs.next(b);
	}
	return (*this)._size > rhs._size;
}

#endif
