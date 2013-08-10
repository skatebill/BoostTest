#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<algorithm>
#include<boost/progress.hpp>
using namespace std;
#define ALL_NUM 100000
int* ptr[ALL_NUM];
void main()
{
	{
		boost::progress_timer t;
		vector<int*> testv;
		for(int i=0;i<ALL_NUM;++i)
		{
			ptr[i]=new int;
			//testv.push_back(ptr[i]);
		}
		for(int i=ALL_NUM-1;i>0-1;--i)
		{
			testv.push_back(ptr[i]);
		}
		list<int> testm;
		std::sort(testv.begin(),testv.end());	
	}/*
	{
		boost::progress_timer t;
		list<int*> testv;
		for(int i=ALL_NUM-1;i>0-1;--i)
		{
			testv.push_back(ptr[i]);
		}
		std::sort(testv.begin(),testv.end());	
	}*/
	system("pause");
}