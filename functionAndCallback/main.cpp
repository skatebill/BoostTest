#include<boost\progress.hpp>
#include<iostream>
#include<boost\bind.hpp>
#include<boost\function.hpp>
using namespace std;
using namespace boost;
int f(int a,int b)
{
	cout<<" a: "<<a<<endl;
	cout<<" b: "<<b<<endl; 
	return 0;
}
class demo{
public:
	int a;
	int b;
	void f(){
		cout<<" a: "<<a<<endl;
		cout<<" b: "<<b<<endl; 
	}
};
class demo_class2{
public:
	demo_class2(int n):_n(n),_f(0){}
	template<typename CALLBACK>
	void accept(CALLBACK &c){
		_f = c;
	}
	void run(){
		_f(_n);
	}
private:
	boost::function<int(int)> _f;
	int _n;
};
class callback_obj{
private:
	int id;
public:
	callback_obj(int n):id(n){};
	callback_obj(const callback_obj& other):id(other.id){
		cout<<"拷贝构造函数调用 id :"<<id<<endl;
	}
	int operator ()(int x) const
	{
		cout<<"id:"<<id<<endl;
		cout<<"hello object function!"<<endl;
		return 0;
	}
	void operator = (const callback_obj &other)
	{
		this->id == other.id + 100;
		cout<<"等号赋值函数调用"<<endl;
	}
};
typedef int(*fun)(int,int);

void main(){
	boost::bind(f,1,2)();
	demo c;
	c.a=1;
	c.b=100;
	boost::bind(&demo::f,&c)();
	boost::function<int(int,int)> testf;
	testf = f;
	testf(100,200);
	
	demo_class2 test2(100);
	int x = 1234;
	test2.accept(boost::bind(f,x,_1));
	test2.run();
	x = 4321;
	test2.run();

	callback_obj callback(123);
	test2.accept(callback);
	test2.run();

	{
		callback_obj linshi(456);
		test2.accept(linshi);
	}
	test2.run();


	cin>>*(new int);
	
}