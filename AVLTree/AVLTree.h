#ifndef AVLTree_h
#define AVLTree_h
#include"AVLTreeIterator.h"

template<typename T>
class AVLTree{
	public:
		friend class AVLTreeIterator<T>;
		friend class AVLTreeNode<T>;
		typedef AVLTreeIterator<T> iterator;
	public:
		AVLTree();
		~AVLTree();
		AVLTreeIterator<T> find(const T& rhs)const;
		AVLTreeIterator<T> insert(const T& value);
		void remove(AVLTreeIterator<T> &rhs);
		void remove(const T &rhs);
		AVLTreeIterator<T> begin()const;
		AVLTreeIterator<T> end()const;
		AVLTreeIterator<T> rbegin()const;
		AVLTreeIterator<T> rend()const;
		void erase();
		bool empty()const;
		unsigned int size()const;
	private:
		AVLTreeNode<T>* minimum(AVLTreeNode<T> *rhs)const;
		AVLTreeNode<T>* maximum(AVLTreeNode<T> *rhs)const;
		AVLTreeNode<T>* left_rotate(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* right_rotate(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* left_left(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* left_right(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* right_left(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* right_right(AVLTreeNode<T> *rhs);
		AVLTreeNode<T>* _insert(AVLTreeNode<T> *rhs,const T &val);
		AVLTreeNode<T>* _remove(AVLTreeNode<T> *rhs,const T &val);
		void _remove_all(AVLTreeNode<T> *rhs);
	private:
		static unsigned int avl_max(const unsigned int x,const unsigned int y);
		void avl_change(AVLTreeNode<T>* rhs);
		int avl_height(AVLTreeNode<T>* rhs);
	private:
		AVLTreeNode<T> *root;
		unsigned int __size;
};
	
template<typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
	__size = 0;
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	_remove_all(root);
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::find(const T& rhs)const
{
	AVLTreeNode<T> *p = root;
	p->left;
	while(p!=nullptr)
	{
		if(p->value < rhs)p = p->right;
		else if(rhs < p->value)p = p->left;
		else return AVLTreeIterator<T>(this,p);
	}
	return AVLTreeIterator<T>(this,nullptr);
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::insert(const T& rhs)
{
	AVLTreeNode<T> *t = _insert(root,rhs);
	if(t!=nullptr)
	{
		++__size;
		root = t;
	}
}

template<typename T>
void AVLTree<T>::remove(AVLTreeIterator<T> &rhs)
{
	_remove(root,*rhs);
	--__size;
}

template<typename T>
void AVLTree<T>::remove(const T &rhs)
{
	if(find(rhs)==end())return;
	root = _remove(root,rhs);
	--__size;
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::begin()const
{
	return AVLTreeIterator<T>(this,minimum(root));
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::end()const
{
	return AVLTreeIterator<T>(this,nullptr);
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::rbegin()const
{
	return AVLTreeIterator<T>(this,maximum(root)); 
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::rend()const
{
	return AVLTreeIterator<T>(this,nullptr); 
}
template<typename T>
void AVLTree<T>::erase()
{
	_remove_all(root);
	__size = 0;
	root = nullptr;
}

template<typename T>
bool AVLTree<T>::empty()const
{
	return __size == 0;
}

template<typename T>
unsigned int AVLTree<T>::size()const
{
	return __size;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T> *rhs)const
{
	if(rhs==nullptr)return nullptr;
	while(rhs->left!=nullptr)rhs=rhs->left;
	return rhs; 
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T> *rhs)const
{
	if(rhs==nullptr)return nullptr;
	while(rhs->right!=nullptr)rhs=rhs->right;
	return rhs; 
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::left_rotate(AVLTreeNode<T> *rhs)
{
	AVLTreeNode<T> *q = rhs->right;
	rhs->right = q->left;
	q->left = rhs;
	avl_change(rhs);
	avl_change(q);
	return q;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::right_rotate(AVLTreeNode<T> *rhs)
{
	AVLTreeNode<T>* p = rhs->left;
	rhs->left = p->right;
	p->right = rhs;
	avl_change(rhs);
	avl_change(p);
	return p;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::left_left(AVLTreeNode<T> *rhs)
{
	return right_rotate(rhs);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::left_right(AVLTreeNode<T> *rhs)
{
	rhs->left = left_rotate(rhs->left);
	return right_rotate(rhs);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::right_left(AVLTreeNode<T> *rhs)
{
	rhs->right = right_rotate(rhs->right);
	return left_rotate(rhs);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::right_right(AVLTreeNode<T> *rhs)
{
	return left_rotate(rhs);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::_insert(AVLTreeNode<T> *rhs,const T &val)
{
	if(rhs == nullptr)
	{
		return new AVLTreeNode<T>(val);
	}
	else if(val < rhs->value)
	{
		rhs->left = _insert(rhs->left,val);
		if(rhs->left == nullptr)return nullptr;
		if(avl_height(rhs->left)-avl_height(rhs->right) == 2)
		{
			if(val < rhs->left->value)
				rhs = left_left(rhs);
			else rhs = left_right(rhs);
		}
	}
	else if(rhs->value < val)
	{
		rhs->right = _insert(rhs->right,val);
		if(rhs->right == nullptr)return nullptr;
		if(avl_height(rhs->right)-avl_height(rhs->left)==2)
		{
			if(val < rhs->right->value)
				rhs = right_left(rhs);
			else rhs = right_right(rhs);
		}
	}
	else
	{
		return nullptr;
	} 
	avl_change(rhs);
	return rhs;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::_remove(AVLTreeNode<T> *rhs,const T &val)
{
	if(rhs == nullptr)return nullptr;
	if(val < rhs->value)
	{
		rhs->left = _remove(rhs->left,val);
		if(avl_height(rhs->right)-avl_height(rhs->left)==2)
		{
			if(avl_height(rhs->right->left)>avl_height(rhs->right->right))
				rhs = right_left(rhs);
			else rhs = right_right(rhs);
		}
	}
	else if(rhs->value < val)
	{
		rhs->right = _remove(rhs->right,val);
		if(avl_height(rhs->left)-avl_height(rhs->right)==2)
		{
			if(avl_height(rhs->left->left)>avl_height(rhs->left->right))
				rhs = left_left(rhs);
			else rhs = left_right(rhs);
		}
	}
	else
	{
		if(rhs->left!=nullptr && rhs->right!=nullptr)
		{
			if(avl_height(rhs->right)>avl_height(rhs->left))
			{
				AVLTreeNode<T> *t = minimum(rhs->right); 
				rhs->value = t->value;
				rhs->right = _remove(rhs->right,t->value);
			}
			else
			{
				AVLTreeNode<T> *t = maximum(rhs->right); 
				rhs->value = t->value;
				rhs->left = _remove(rhs->left,t->value);
			}
		}
		else
		{
			AVLTreeNode<T> *t = rhs;
			rhs = (rhs->left!=nullptr)?(rhs->left):(rhs->right);
			delete t;
		}
	}
	avl_change(rhs);
	return rhs;
}

template<typename T>
void AVLTree<T>::_remove_all(AVLTreeNode<T> *rhs)
{
	if(rhs==nullptr)return;
	_remove_all(rhs->left);
	_remove_all(rhs->right);
	delete rhs;
}

template<typename T>
unsigned int AVLTree<T>::avl_max(const unsigned int x,unsigned int y)
{
	if(x>y)return x;
	else return y;
}

template<typename T>
void AVLTree<T>::avl_change(AVLTreeNode<T>* rhs)
{
	if(rhs!=nullptr)
	rhs->height = avl_max(avl_height(rhs->left),avl_height(rhs->right))+1;
}

template<typename T>
int AVLTree<T>::avl_height(AVLTreeNode<T> *rhs)
{
	if(rhs==nullptr)return -1;
	else return rhs->height;
}

#endif
