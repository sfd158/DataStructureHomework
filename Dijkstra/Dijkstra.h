#ifndef Dijkstra_h
#define Dijkstra_h
#include<queue>
#include<vector>
#include<cstring>
#include<stdexcept>
#include<algorithm>
template<typename dist_type = int>
struct Edge
{
	typedef unsigned int node_type;
	node_type from,to;
	dist_type dist;
};

template<typename dist_type = int>
class Dijkstra
{
	public:
		typedef Edge<dist_type> edge_type;
		typedef typename Edge<dist_type>::node_type node_type;
		typedef size_t size_type; 
		static const int INF;
	private:
		typedef typename std::pair<dist_type,node_type> pde; 
	private:
		std::vector<std::vector<edge_type> > edges;
		bool *vis;
		dist_type *dist;
		node_type *parent;
		node_type _start;
		size_type max_nodes;
	public:
		Dijkstra(const int _max_nodes);
		~Dijkstra();
		void clear();
		node_type get_dist(const node_type _node);
		template<typename InputType>
			void set_edges(InputType _begin,InputType _end,const bool double_linked = false)
			{
				clear();
				for(InputType iter = _begin; iter != _end; ++iter)
				{
					node_type _from = (*iter).from,_to = (*iter).to;
					dist_type _dist = (*iter).dist;
					edges[_from].push_back((edge_type){_from,_to,_dist}); 
					if(double_linked)
						edges[_to].push_back((edge_type){_to,_from,_dist});
				}
				relax();
			}
		void set_start(const int dijk_start);
		std::vector<node_type> get_route(const node_type _node);
	private:
		void relax();
		void check_node(const node_type _node); 
};

template<typename dist_type>
const int Dijkstra<dist_type>::INF = 0x3F3F3F3F;

template<typename dist_type>
Dijkstra<dist_type>::Dijkstra(const int _max_nodes):max_nodes(_max_nodes)
{
	edges.resize(max_nodes);
	vis = new bool[max_nodes];
	dist = new dist_type[max_nodes];
	parent = new node_type[max_nodes];
	clear();
	_start = 0;
}

template<typename dist_type>
Dijkstra<dist_type>::~Dijkstra()
{
	delete[] vis;
	delete[] dist;
	delete[] parent;
}

template<typename dist_type>
void Dijkstra<dist_type>::clear()
{
	for(int i = 0; i < edges.size(); i++)
	edges[i].clear();
	//memset(vis,0,sizeof(bool)*edges.size());
	//memset(dist,INF,sizeof(dist_type)*max_size);//将dist的每一字节均填充为0x3F.
	//对于4字节的int类型变量，每个int元素都填充为0x3f3f3f3f.
	//这是一个很大的数，且2*INF在int范围内不会上溢出。
			
	//为了提高可读性，采用循环的方式来初始化：
	for(int i = 1; i <= edges.size(); i++)
	{
		vis[i] = false;
		dist[i] = INF;
		parent[i] = i;
	}
}

template<typename dist_type>
typename Dijkstra<dist_type>::node_type Dijkstra<dist_type>::get_dist(const node_type _node)
{
	check_node(_node);
	return dist[_node];
}

template<typename dist_type>
void Dijkstra<dist_type>::set_start(const int dijk_start)
{
	_start = dijk_start;
}

template<typename dist_type>
void Dijkstra<dist_type>::relax()
{
	std::priority_queue<pde,std::vector<pde>,std::greater<pde> > q;
	dist[_start] = 0;
	q.push(std::make_pair(0,_start));
	while(!q.empty())
	{
		pde tmp = q.top();
		q.pop();
		dist_type d = tmp.first;
		node_type node = tmp.second;
		if(vis[node])continue;
		vis[node] = true;
		for(int i=0; i<edges[node].size(); i++)
		{
			edge_type &e = edges[node][i];
			if(vis[e.to])continue;
			if(dist[e.to]>dist[e.from]+e.dist)
			{
				dist[e.to] = dist[e.from]+e.dist;
				parent[e.to] = e.from;
				q.push(std::make_pair(dist[e.to],e.to));
			}
		}
	}
}

template<typename dist_type>
std::vector<typename Dijkstra<dist_type>::node_type> 
Dijkstra<dist_type>::get_route(const node_type _node)
{
	check_node(_node);
	std::vector<node_type> tp;
	if(dist[_node]>=INF)return tp;
	node_type p = _node;
	while(p!=_start)
	{
		tp.push_back(p);
		p = parent[p];
	}
	tp.push_back(_start);
	std::reverse(tp.begin(),tp.end());
	return tp;
}

template<typename dist_type>
void Dijkstra<dist_type>::check_node(const node_type _node)
{
	if(_node < 0 || _node >= max_nodes)throw std::invalid_argument("_node is too small or too large.");
}
#endif
