
const int maxWeight = 10000;
const int DeafultVertices = 30;			//代表最大顶点数 =n
template<class T, class E>
struct Edge
{
	int dest;			//边的另一个顶点位置
	E cost;				//边上的权值
	Edge<T, E> * link;	//下一条边链指针
	Edge() { cost = maxWeight; }
	Edge(int num, E weight) : dest(num), cost(weight), link(NULL) {}
	bool operator != (Edge<T, E>& R)const
	{
		return (dest != R.dest) ? true : false;
	}r
};
template<class T, class E>
struct Vertex
{
	T data;
	Edge<T, E> *adj;			//边链表的头指针
};
template<class T, class E>
class Graph
{
public:
	Graph(int sz = DeafultVertices) {};
	~Graph() {}
	bool GraphEmpty()const
	{
		if (numEdges == 0)
			return true;
		else
		{
			return false;
		}
	}
	bool GraphFull()const
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		else return false;
	}
	int NumberOfVertices() { return numVertices; }		//返回当前顶点数
	int NunberOfEdges() { return numEdges; }			//返回当前边数
	virtual T getValue(int i) = 0;							//取顶点i的值
	virtual E getWeight(int v1, int v2) = 0;					//取边（v1，v2）上的权值
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取邻接顶点w的下一个邻接顶点
	virtual bool insertVertex(const T vertex) = 0;			//插入一个顶点vertex
	virtual bool insertEdge(int v1, int v2, E cost) = 0;		//插入边(v1,v2),权为cost
	virtual bool removeVertex(int v) = 0;					//删去顶点v和所有与v相关的边
	virtual bool removeEdge(int v1, int v2) = 0;				//删去边(v1,v2)
protected:
	int maxVertices;
	int numEdges;
	int numVertices;
	int getVertexPos(T vertex);				//给出顶点vertex在图中的位置
};