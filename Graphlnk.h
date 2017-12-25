#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include "Graph.h"
#include<vector>
using namespace std;
template<class T, class E>
struct Edge
{
	T dest1;          //边上顶点
	T dest2;			//边的另一个顶点
	E cost;				//边上的权值
	Edge<T, E> * link;	//下一条边链指针
	Edge<T, E>*next;    //邻接表中的下一个指针
	Edge<T, E>*last;    //邻接表中的上一个指针
	Edge<T, E>*brother; //邻接表的兄弟指针，可以指向自身
	Edge(T Vertex1, T Vertex2, E dis)dest1(Vertex1), dest2(Vertex2), cost(dis), next(NULL), last(NULL), brother(NULL) {};
	Edge() {};
};
template<class T,class E>
struct Vertex
{
	T data;                    //顶点元素值
	Edge<T, E> *adj;			//边链表的头指针
	Vertex<T, E>*next;        //指向下一点
	Vertex<T, E>*last;       //指向上一点
	int degree;//顶点的度
	Vertex(T Vertex1, Vertex<T, E>left, Vertex<T, E>right) data(Vertex1), last(left), next(right) {};
	Vertex() {};
};
template<class T,class E>
class Graphlnk
{
public:
	Graphlnk() {};
	~Graphlnk();
	T getValue(int i)					//取位置为i的顶点中的值
	{
		return vi.at(i).data;
	}
	E getWeight(int v1,int v2);			//返回边(v1,v2)的权值
	bool insertVertex(const T vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2,E cost);
	bool removeEdge(int v1,int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v,int w );
	int NumberOfVertices()
	{
		return this->numVertices;
	}
	int getVertexPos(T Vertex);
	ShortestPath();
private:
	vector<Vertex<T,E>> vi;
	vector<Vertex<T,E>>::iterator iter = vi.begin();
	int num = vi.size;
	int getVertexPos(const T vertex)//返回元素在容器中的位置
	{
		int i;
		for (i=0;;i<num;i++)
		{
			if (vi.at(i) == Vertex)return i;
		}
		return -1;
	}
};
template<class T,class E>
Graphlnk<T,E>::~Graphlnk()
{
	for(int i = 0;i<maxVertices;i++)
	{
		Edge<T,E> * p = NodeTable[i].adj;
		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
}
template<class T,class E>
int Graphlnk<T,E>::getFirstNeighbor(int v)
{
	if(v != -1)
	{
		Edge<T,E> * p = NodeTable[v].adj;
		if( p != NULL) return p->dest;
	}
	return -1;
}
template<class T,class E>
int Graphlnk<T,E>::getNextNeighbor(int v,int w )
{
	if(v != -1)
	{
		Edge<T,E> * p = NodeTable[v].adj;
		while (p!= NULL && p->dest != w)
		{
			p = p->link;
		}
		if( p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}
template<class T,class E>
E Graphlnk<T,E>::getWeight(int v1,int v2)
{
	if( v1 != -1 && v2 != -1)
	{
		Edge<T,E> *p = NodeTable[v1].adj;
		while (p!= NULL && p->dest != v2)
		{
			p = p->link;
		}
		if(p != NULL) 
			return p->cost;
		else return maxWeight;
	}
}
template<class T,class E>
bool Graphlnk<T,E>::insertVertex(const T vertex)
{

	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}
template<class T,class E>
bool Graphlnk<T,E>::removeVertex(int v)
{
	if(numVertices == 1|| v<0 || v>=numVertices )return false;
	Edge<T,E> *p,*s,*t;
	int i,k;
	while (NodeTable[v].adj != NULL)
	{
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;
		t = NULL;
		while(s != NULL && s->dest !=v)
		{
			t = s;
			s = s->link;
		}
		if(s != NULL)
		{
			if( t == NULL) NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	numVertices --;
	NodeTable[v].data = NodeTable[numVertices].data;
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p!= NULL)
	{
		s = NodeTable[p->dest].adj;
		while (s!= NULL)
			if(s ->dest == numVertices){ s->dest = v;break;}
			else s = s->link;
	}
	return true;
}
template<class T,class E>
bool Graphlnk<T,E>::insertEdge(int v1, int v2,E cost)
{
	if(v1 >=0 && v1< numVertices && v2>=0 && v2<numVertices)
	{
		Edge<T,E> *q,*p = NodeTable[v1].adj;
		while (p!=NULL && p->dest != v2)
		{
			p = p->link;
		}
		if(p != NULL ) return false;
		p = new Edge<T,E>;
		q = new Edge<T,E>;
		p->dest = v2;
		p->cost = cost;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q ->dest = v1;
		q ->cost = cost;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges ++;
		return true;
	}
	return false;
}
template<class T,class E>
bool Graphlnk<T,E>::removeEdge(int v1,int v2)
{
	if(v1 != -1 &&v2 != -1)
	{
		Edge<T,E> *p = NodeTable[v1].adj, *q = NULL,*s = p;
		while(p!= NULL && p->dest != v2)
		{
			 q = p;
			 p = p->link;
		}
		if(p!= NULL)
		{
			if(p == s)
				NodeTable[v1].adj = p->link;
			else
			{
				 q ->link = p->link;
			}
			delete p;
		}
		else
		{
			return false;
		}
		p = NodeTable[v2].adj;
		q = NULL;
		s = p;
		while (p->dest !=v1)
		{
			q=  NULL;
			s = p;
		}
		if(p == s)
			NodeTable[v2].adj = p->link;
		else
		{
			q->link = p->link;
		}
		delete p;
		return true;
	}
	return false;
}
template<class T, class E>
void ShortestPath(int v, E dist[], int path[])
{//Graph是一个带权有向图，本算法建立一个数组，dist[j],0<=j<n;是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path存放求到的最短路径
	int n = G.NumberOfVertices();
	bool *S = new bool[n];
	int i, j, k;
	E w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] <maxValue)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = maxValue;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w <maxValue && dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	printPath(G, v, dist, path);
}

#endif