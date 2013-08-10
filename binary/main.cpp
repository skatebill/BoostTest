#include<iostream>
#include<boost\progress.hpp>
#include<boost\exception\all.hpp>
#include<exception>
#include<string>
using namespace std;
using namespace boost;
#define ERROR_TYPE(type,name) typedef error_info<struct tag_##__FILE__##__LINE__##name,type> name

struct testException:virtual std::exception,
					virtual boost::exception
{
	const char* what(){
		return "test exception";
	}
};
ERROR_TYPE(int,error_no);
ERROR_TYPE(string,error_str);	

void main() try{
	progress_timer t;
	try{
		throw testException() << error_no(10);
	}catch(testException& e){
		cout<<" error number:"<<*get_error_info<error_no>(e)<<endl;
		cout<<e.what()<<endl;
		e << error_str("this is just a test!");
		throw;
	}

}catch(testException& e){
		cout<<" error info:"<<*get_error_info<error_str>(e)<<endl;
}