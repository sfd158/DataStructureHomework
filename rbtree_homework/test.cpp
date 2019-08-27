#include<iostream>
#include"rbtree.h"
int main()
{
	rbtree<int> tree;
	for(int i=0;i<20;i++)
	{
		tree.insert(i);
		std::cout<<"Size:"<<tree.size()<<" ";
		for(rbtree<int>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
			std::cout<<*iter<<" ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	for(int i=0;i<20;i++)
	{
		tree.erase(i);
		std::cout<<"Size:"<<tree.size()<<" ";
		for(rbtree<int>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
			std::cout<<*iter<<" ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
