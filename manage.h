#pragma once
#include<fstream>
#include<string>
#include"Graphlnk.h"
class manage
{
public:
	void input();
	void output();
protected:
	Graphlnk<string,int> gi;
};
