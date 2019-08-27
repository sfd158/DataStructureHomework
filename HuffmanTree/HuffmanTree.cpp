#include"HuffmanTree.h"
#include<iostream>

int main(int argc,char **argv)
{
	using std::cout;
	using std::endl;
	std::vector<HuffmanNode<int,char> > t;
	t.push_back(HuffmanNode<int,char>(9,'A'));
	t.push_back(HuffmanNode<int,char>(12,'B'));
	t.push_back(HuffmanNode<int,char>(6,'C'));
	t.push_back(HuffmanNode<int,char>(3,'D'));
	t.push_back(HuffmanNode<int,char>(5,'E'));
	t.push_back(HuffmanNode<int,char>(15,'F'));
	HuffmanTree<int,char> tr(t.begin(),t.end());
	cout<<"size:"<<tr.size()<<endl;
	for(char i = 'A'; i<='F';i++)
		cout<<i<<":"<<tr.GetHuffmanCode(i)<<" "<<tr.GetHuffmanValue(tr.GetHuffmanCode(i))<<endl;
	cout<<endl;
	return 0;
}
