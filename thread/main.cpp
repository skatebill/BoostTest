#include<iostream>
#include<string>
#include<boost\thread.hpp>
#include<boost\function.hpp>
#include <boost/utility/result_of.hpp>
using namespace std;
typedef boost::posix_time::ptime system_time;
typedef boost::posix_time::seconds system_seconds;
typedef boost::posix_time::milliseconds system_miliseconds;


template<typename Content>
class basic_atom{
private:
	boost::mutex mtx;
public:
	Content n;
	Content operator ++ ()
	{
		boost::mutex::scoped_lock lock(mtx);
		cout<<"current num:"<<n<<endl;
		return ++n;
	}
	operator Content(){return n;}
	basic_atom(basic_atom& other):n(other.n){}
	basic_atom(Content _n):n(_n){}
};

template<typename T>
class threadFun_Obj{
private:
	boost::mutex mtx;
	T t;
public:
	typedef void result_type;
	threadFun_Obj():t(){}
	threadFun_Obj(T _t):t(_t){}
	void operator ()(){
		while(1)
		{
			boost::mutex::scoped_lock(mtx);
			boost::this_thread::sleep(system_miliseconds(50));
			cout<<++t<<endl;
		}
	}
	void operator()(const char* s){
		while(1)
		{
			boost::mutex::scoped_lock(mtx);
			boost::this_thread::sleep(system_miliseconds(500));
			cout<<t<<" "<<s<<endl;
			++t;
		}
	}
};

basic_atom<int> test(100);

void testF(const char* s){
	while(1){
		cout<<s<<endl;
	}
}


//
//void main(){
//	threadFun_Obj<basic_atom<int>> obj(test); 
//	//function<void()> tf(ref(obj));
//	//function<void(const char*)> tf2(boost::bind(&testF,_1));
//	function<void(const char*)> tf2(ref(obj));
//	function<void(const char*)> tf3(ref(obj));
//	//ref(obj)("test");
//	//boost::thread t1(tf);
//	boost::thread t2(tf2,"test");
//	boost::thread t3(tf3,"test");
//	system("pause");	
//}
boost::mutex io_mtx;
void threadFunMutex()
{
	while(1)
	{
		//cout<<"hello world"<<endl;
		boost::mutex::scoped_lock t(io_mtx);
		cout<<"h"<<"e"<<"l"<<"l"<<"o"<<endl;
		boost::this_thread::sleep(system_miliseconds(200));
	}
}
//void main(){
//	threadFun_Obj<basic_atom<int>> obj(test); 
//	boost::function<void(const char*)> fc(ref(obj));
//	boost::thread t1(fc,"functoin 1");
//	//boost::thread t2(fc);
//	{
//		boost::thread t3(fc,"functoin 3");
//		system("pause");	
//		t3.interrupt();
//	}
//	system("pause");	
//	//t2.timed_join(system_seconds(1));
//	//t3.join();
//}



/////// consumer && producer
#include<stack>
class buffer{
private:
	boost::mutex buffer_mutex;
	int max;
	std::stack<int> data;
	int unread;

	boost::condition_variable_any put_con;
	boost::condition_variable_any get_con;
	function<bool()> isFull;
	function<bool()> isEmpty;
	function<bool()> isNotFull;
	function<bool()> isNotEmpty;
public:
	buffer(int _max):max(_max),unread(0){
		isFull = boost::bind(&buffer::is_Full,this);
		isEmpty = boost::bind(&buffer::is_Empty,this);
		isNotFull = !boost::bind(&buffer::is_Full,this);		//不能写为 !isFull
		isNotEmpty = !boost::bind(&buffer::is_Empty,this);
	}
	bool is_Full(){
		return unread == max;
	}
	bool is_Empty(){return unread == 0;}
	void put(int x){
		boost::mutex::scoped_lock lock(buffer_mutex);
		/*while(is_Full())
		{
			{
				boost::mutex::scoped_lock lock(io_mtx);
				cout<<"full! waiting"<<endl;
			}
			put_con.wait(buffer_mutex);
		}*/
		get_con.wait(buffer_mutex,isNotFull);   //可以理解为 wait untill isNotFull 所以需要这么一种形式
		data.push(x);
		++unread;
		get_con.notify_one();
	}
	int get(){
		boost::mutex::scoped_lock lock(buffer_mutex);
		/*while(is_Empty())
		{
			{
				boost::mutex::scoped_lock lock(io_mtx);
				cout<<"empty! waiting"<<endl;
			}
			get_con.wait(buffer_mutex);
		}*/
		get_con.wait(buffer_mutex,isNotEmpty);
		--unread;
		int r = data.top();
		data.pop();
		put_con.notify_one();
		return r;

	}
};

buffer buf(3);
template<int id>
void producer(int num){
	for(int i=0;i<num;++i)
	{
		buf.put(i);
		boost::mutex::scoped_lock lock(io_mtx);
		cout<<"producer["<<id<<"] put No.["<<i<<"] into buf"<<endl;
	}
}
void consumer(int num,int id){
	for(int i=0;i<num;++i)
	{
		int r = buf.get();
		boost::mutex::scoped_lock lock(io_mtx);
		cout<<"consumer["<<id<<"] used No.["<<r<<"] from buf"<<endl;
	}
}
void main(){
	function<void(int)> prod1(producer<1>);
	function<void(int)> prod2(producer<2>);
	function<void(int)> cons1(boost::bind(consumer,_1,1));
	function<void(int)> cons2(boost::bind(consumer,_1,2));
	function<void(int)> cons3(boost::bind(consumer,_1,3));

	boost::thread pt1(prod1,10);
	boost::thread pt2(prod2,10);
	boost::thread ct1(cons1,5);
	boost::thread ct2(cons2,5);
	boost::thread ct3(cons3,10);
	
	pt1.join();
	pt2.join();
	ct1.join();
	ct2.join();
	ct3.join();

	system("pause");

}