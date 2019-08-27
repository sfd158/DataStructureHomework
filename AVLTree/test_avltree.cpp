#include"AVLTree.h"
#include<iostream>
int main()
{
	AVLTree<int> tree;
	for(int i=0;i<20;i++)
	{
		tree.insert(i);
		for(AVLTree<int>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
			std::cout<<*iter<<" ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	for(int i=0;i<20;i++)
	{
		tree.remove(i);
		for(AVLTree<int>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
			std::cout<<*iter<<" ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
