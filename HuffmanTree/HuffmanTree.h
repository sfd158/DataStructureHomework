#ifndef HuffmanTree_h
#define HuffmanTree_h 1
#include<queue>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<algorithm>
#include<stdexcept>

template<typename WeightType, typename ValueType>
	class HuffmanTree;
template<typename WeightType, typename ValueType>
	class HuffmanTreeNode;
 
template<typename WeightType, typename ValueType>
struct HuffmanNode
{
	HuffmanNode(WeightType _weight = 0, ValueType _value = 0):weight(_weight), value(_value){}
	WeightType weight;
	ValueType value;
};

template<typename WeightType, typename ValueType>
class HuffmanTreeNode:public HuffmanNode<WeightType, ValueType> 
{
	friend class HuffmanTree<WeightType, ValueType>;
	private:
		HuffmanTreeNode(WeightType _weight,
						ValueType _value,
						HuffmanTreeNode<WeightType, ValueType> *_left = nullptr,
						HuffmanTreeNode<WeightType, ValueType> *_right = nullptr,
						HuffmanTreeNode<WeightType, ValueType> *_parent = nullptr):
							left(_left),right(_right),parent(_parent),HuffmanNode<WeightType, ValueType>(_weight,_value){}
		~HuffmanTreeNode(){}
	private:
		HuffmanTreeNode<WeightType, ValueType> *left,*right,*parent;
};

template<typename WeightType,typename ValueType>
class HuffmanTree
{
	friend class HuffmanTreeNode<WeightType,ValueType>;
	public:
		typedef HuffmanTreeNode<WeightType,ValueType> treenode;
		typedef HuffmanNode<WeightType, ValueType> node;
		typedef unsigned int size_type;
	private:
		typedef std::pair<WeightType,treenode*> pwt;
	private:
		treenode *root;
		std::map<ValueType,treenode*> record;
		size_type _size;
	private:
		void _clear(treenode *p);
		template<typename InputTypename>
			void build_tree(InputTypename _first,InputTypename _last)
			{
				std::priority_queue<pwt,std::vector<pwt>,std::greater<pwt> > q;
				for(InputTypename iter = _first;iter != _last;++iter)
				{
					treenode* tmp = new treenode((*iter).weight,(*iter).value);
					record.insert(std::make_pair((*iter).value,tmp));
					q.push(std::make_pair((*iter).weight,tmp));
					_size++;
				}
				while(q.size() > 1)
				{
					pwt a = q.top();
					q.pop();
					pwt b = q.top();
					q.pop();
					WeightType w = (*a.second).weight+(*b.second).weight;
					treenode* tmp = new treenode(w,0,a.second,b.second);
					(*a.second).parent = (*b.second).parent = tmp; 
					q.push(std::make_pair(w,tmp));
				}
				root = q.top().second;
				q.pop();
			}
	public:
		HuffmanTree():root(nullptr),_size(0){};
		~HuffmanTree()
		{
			_clear(root);
		}
		size_type size()
		{
			return _size;
		}
		std::string GetHuffmanCode(ValueType &_value);
		const ValueType& GetHuffmanValue(const std::string &_code);
		void erase()
		{
			_clear(root);
			record.clear();
			root = nullptr;
			_size = 0;
		}
		template<typename InputTypename>
			HuffmanTree(InputTypename _first,InputTypename _last):root(nullptr),_size(0)
			{
				build_tree(_first, _last);
			}
		template<typename InputTypename>
			void SetTreeNode(InputTypename _first,InputTypename _last)
			{
				erase();
				build_tree(_first,_last);
			}
};

template<typename WeightType, typename ValueType>
void HuffmanTree<WeightType, ValueType>::_clear(treenode *p)
{
	if(p == nullptr)return;
	_clear(p->left);
	_clear(p->right);
	delete p;
}

template<typename WeightType, typename ValueType>
std::string HuffmanTree<WeightType, ValueType>::GetHuffmanCode(ValueType &_value)
{
	typename std::map<ValueType,treenode*>::iterator iter = record.find(_value);
	if(iter == record.end())
		return "not found.";
	treenode *t = iter->second;
	std::ostringstream oss;
	if(t==root)oss<<'0';
	while(t!=root)
	{
		if(t == t->parent->left)oss<<'0';
		else oss<<'1';
		t = t->parent;
	}
	std::string s = oss.str();
	reverse(s.begin(),s.end());
	return s;
}

template<typename WeightType, typename ValueType>
const ValueType& HuffmanTree<WeightType, ValueType>::GetHuffmanValue(const std::string &_code)
{
	treenode *t = root;
	for(int i = 0; i < _code.size() && t != nullptr; ++i)
	{
		if(_code[i] == '0')t = t->left;
		else if(_code[i] == '1')t = t->right;
		else throw std::invalid_argument("wrong code."); 
	}
	return t->value;
}
#endif
