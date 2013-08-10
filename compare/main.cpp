#include<iostream>
#include<boost\progress.hpp>
#include<boost\operators.hpp>

class test:boost::less_than_comparable<test>,boost::equality_comparable<test>
{
private:	
	int x;
public:
	test(int n):x(n){}
	friend bool operator < (const test&a ,const test& b);
	friend bool operator == (const test&a ,const test& b);
};
bool operator < (const test&a ,const test& b)
{
	return a.x < b.x;
}
bool operator == (const test&a ,const test& b)
{
	return a.x == b.x;
}


void main(){
	using namespace std;
	boost::progress_timer t;
	test a(100),b(200),c(300);
	cout << (a < b) << endl;
	cout << (a > b) << endl;
	cout << (b == b) << endl;
	cout << (c != b) << endl;

}