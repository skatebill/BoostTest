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
	/*try{
		throw testException() << error_no(10);
	}catch(testException& e){
		cout<<" error number:"<<*get_error_info<error_no>(e)<<endl;
		cout<<e.what()<<endl;
		e << error_str("this is just a test!");
		throw;
	}*/

	using namespace std;
	char charr[20];
	string str;
	cout << "length of string charr before input:" << strlen(charr) << endl;
	cout << "length of string str before input:" << str.size() << endl;

	cout << "enter a line for text:\n";
	cin.getline(charr, 20);
	cout << "you enter:" << charr << endl;

	cout << "enter another line for text:\n";
	getline(cin, str);
	cout << "you enter :" << str << endl;
	//cin.get();
	
	cout << "length of string charr after input:" << strlen(charr) << endl;
	cout << "length of string str after input:" << str.size() <<endl;




}catch(testException& e){
		cout<<" error info:"<<*get_error_info<error_str>(e)<<endl;
}