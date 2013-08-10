#include<iostream>
#include<boost\typeof\typeof.hpp>
#include<vector>
void main(){
	std::vector<int> test(100,2);
	std::cout<<test.size();
	for(BOOST_AUTO(ite,test.begin());ite!=test.end();ite++)
		std::cout<<*ite<<std::endl;
}