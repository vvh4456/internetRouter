#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <Graphlnk.h>
using namespace std;
int input(void * a) {
	Graphlnk<int, int>& g = *(Graphlnk<int, int>*)a;
	fstream s;
	s.open("Router.txt",ios::in);
	char buffer[1024];
	
	int v, tv,w;
	s.getline(buffer, 1024);
	stringstream ss1(buffer);
		ss1 >> v;
	while (ss1) {
		g.insertVertex(v);
		ss1 >> v;
	}
	s.getline(buffer, 1024);
	stringstream ss(buffer);
	ss >> v;
	for (;s.good();) {
		ss >> tv;
		ss >> w;
		while (ss) {
			g.insertEdge(v, tv, w);
			ss >> tv;
			ss >> w;
		}
		s.getline(buffer, 1024);
		ss.str(buffer);
		ss.clear();
		ss >> v;
	};
	return 0;
};