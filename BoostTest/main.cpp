#include<iostream>
#include<boost\smart_ptr.hpp>
typedef boost::shared_ptr<int> int_sp;
using namespace std;
using namespace boost;

void main(){
	int_sp test(new int(100));
	cout<<*test;
	assert(*test == 101);
}