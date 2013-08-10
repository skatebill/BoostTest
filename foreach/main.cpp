#include<iostream>
#include<boost\progress.hpp>
#include<boost\typeof\typeof.hpp>
#include<string>
#include<boost\foreach.hpp>
#include<boost\assign.hpp>
#include<vector>
#include<list>
#include<map>
using namespace std;
using namespace boost;
using namespace boost::assign;
#define foreach BOOST_FOREACH

void main(){
	progress_timer t;
	vector<string> stringVector = list_of("one")("tow")("three")("four")("five");
	foreach(string& s,stringVector){
		cout<<s<<endl;
	}
	map<int,string> map = map_list_of(1,"string")(2,"test")(3,"hello");
	pair<int,string> m;
	foreach(m,map)
	{
		cout<<m.first<<"----"<<m.second<<endl;
	}
	cin>>*(new int);
}