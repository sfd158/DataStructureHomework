#include"Dijkstra.h"
#include<vector>
#include<iostream>
using std::vector;
using std::cout;
using std::endl;
int main()
{
	Dijkstra<int> a(6);
	vector<Edge<int> > e;
	e.push_back((Edge<int>){1,2,20});
	e.push_back((Edge<int>){2,3,30});
	e.push_back((Edge<int>){3,4,20});
	e.push_back((Edge<int>){4,5,20});
	e.push_back((Edge<int>){4,5,10}); 
	e.push_back((Edge<int>){1,5,100});
	a.set_start(1);
	a.set_edges(e.begin(),e.end(),true);
	
	for(int i=1;i<=5;i++)
	{
		cout<<"dist from 1 to "<<i<<" is "<<a.get_dist(i)<<endl;
		cout<<"route from 1 to "<<i<<" is ";
		vector<Dijkstra<int>::node_type> tp;
		tp = a.get_route(5);
		for(int i=0;i<tp.size();i++)
			cout<<tp[i]<<" ";
		cout<<endl<<endl;
	}
	return 0; 
}
