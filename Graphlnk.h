#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include "Graph.h"
#include<vector>
using namespace std;
template<class T, class E>
struct Edge
{
	T dest1;          //���϶���
	T dest2;			//�ߵ���һ������
	E cost;				//���ϵ�Ȩֵ
	Edge<T, E> * link;	//��һ������ָ��
	Edge<T, E>*next;    //�ڽӱ��е���һ��ָ��
	Edge<T, E>*last;    //�ڽӱ��е���һ��ָ��
	Edge<T, E>*brother; //�ڽӱ���ֵ�ָ�룬����ָ������
	Edge(T Vertex1, T Vertex2, E dis)dest1(Vertex1), dest2(Vertex2), cost(dis), next(NULL), last(NULL), brother(NULL) {};
	Edge() {};
};
template<class T,class E>
struct Vertex
{
	T data;                    //����Ԫ��ֵ
	Edge<T, E> *adj;			//�������ͷָ��
	Vertex<T, E>*next;        //ָ����һ��
	Vertex<T, E>*last;       //ָ����һ��
	int degree;//����Ķ�
	Vertex(T Vertex1, Vertex<T, E>left, Vertex<T, E>right) data(Vertex1), last(left), next(right) {};
	Vertex() {};
};
template<class T,class E>
class Graphlnk
{
public:
	Graphlnk() {};
	~Graphlnk();
	T getValue(int i)					//ȡλ��Ϊi�Ķ����е�ֵ
	{
		return vi.at(i).data;
	}
	E getWeight(int v1,int v2);			//���ر�(v1,v2)��Ȩֵ
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
	int getVertexPos(const T vertex)//����Ԫ���������е�λ��
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
{//Graph��һ����Ȩ����ͼ�����㷨����һ�����飬dist[j],0<=j<n;�ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path����󵽵����·��
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