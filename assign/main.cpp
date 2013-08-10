#include<iostream>
#include<boost\assign.hpp>
#include<boost\typeof\typeof.hpp>
#include<boost/progress.hpp>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<string>
void main(){
	using namespace boost::assign;
	std::vector<std::string> sVector;
	push_back(sVector)("one")("two")("three")("four")("five")("six");
	for(BOOST_AUTO(ite,sVector.begin());ite!=sVector.end();ite++)
	{
		std::cout<<*ite<<std::endl;
	}
}