#include<boost\progress.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<boost\bind.hpp>
#include<boost\function.hpp>
#include<boost\signals2.hpp>
#include<boost\assign.hpp>
#include<boost\ref.hpp>
using namespace std;
using namespace boost;
using namespace boost::signals2;
void slott1()
{
	cout<<"slot 1 called"<<endl;
}
void slott2()
{
	cout<<"slot 2 called"<<endl;
}
class callbackObjct{
private:
	string info;
public:
	callbackObjct(string s):info(s){}
	void operator ()() const{
		cout<<"call back called! the infomation is ["<<info<<"]"<<endl;
	}
};
class callBakcBase{
public:
	virtual void callback()=0;
	void operator ()(){
		callback();
	}
};
class Imp1:public callBakcBase{
public:
	void callback(){
		cout<<"继承的回调函数调用了!"<<endl;
	}
};
int slott3(int k){
	cout<<"slot 3 "<<k<<endl;
	return k;
}
int slott4(int k){
	cout<<"slot 4 "<<k<<endl;
	return k;
}
class my_stream{
public:
	my_stream(ostream& _dst):dst(_dst){}
	template<typename Input>
	const my_stream& operator <<  (Input in) const
	{
		dst.get() << in;
		return *this;
	}
private:
	boost::reference_wrapper<ostream> dst;
};
void main(){
	boost::signals2::signal<void()> s;
	s.connect(&slott1);
	s.connect(&slott2);
	callbackObjct info1("hello world");
	callbackObjct info2("你好 世界");
	s.connect(info1);
	s.connect(info2);
	s.connect(Imp1());
	int x=0;
	x=1234;
	s.connect(boost::bind(slott3,boost::ref(x)));
	s();
	boost::signals2::signal<int(int)> s2;
	s2.connect(&slott3);
	s2.connect(&slott4);
	boost::function<int()> refFun(boost::bind(slott3,boost::ref(x)));	//这里显然有问题 
	s2.connect(boost::bind(slott3,boost::ref(x)));						//明明没有调用参数 却可以这样connect	
	//s2.connect(refFun);			这样就不可以
	x=100;
	s2(2);
	my_stream test(cout);
	test << "stream test!!!!\n" <<"test Line 2\n";
	std::ofstream outputF("hello.txt");
	my_stream tes2t(outputF);
	tes2t << "stream test!!!!\n" <<"test Line 2\n" <<int(100)<<float(100.1234);
	refFun();
	system("pause");
}