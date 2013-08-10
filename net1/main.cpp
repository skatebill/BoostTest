#include<iostream>
#include<string>
#include<vector>
#include<boost\thread.hpp>
#include<boost\function.hpp>
#include<boost\asio.hpp>
using namespace boost::asio;
ip::address localip = boost::asio::ip::address::from_string("127.0.0.1");
io_service ioservices;
boost::mutex io_mutex;
void client() try 
{
	while(1)
	{
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		ip::tcp::endpoint port(localip,8899);
		ip::tcp::socket soc(ioservices);

		soc.connect(port);
		std::vector<char> str(100,0);
		soc.read_some(buffer(str));
		io_mutex.lock();
		std::cout<<"recived from["<<soc.remote_endpoint()<<"]"<<std::endl;
		std::cout<<&str[0];
		io_mutex.unlock();
	}

} catch(std::exception &e){
	std::cout<<e.what()<<std::endl;
}

void server() try {
	ip::tcp::acceptor acc(ioservices,ip::tcp::endpoint(localip,8899));
	while(1)
	{
		ip::tcp::socket soc(ioservices);
		acc.accept(soc);
		soc.write_some(buffer("hello asio::tcp!\n"));
		io_mutex.lock();
		std::cout<<"accepted from["<<soc.remote_endpoint()<<"]"<<std::endl;
		io_mutex.unlock();
	}

} catch(std::exception &e){
	std::cout<<e.what()<<std::endl;
}

void main() try
{
	ioservices.run();
	boost::thread ser(server);
	boost::thread cli(client);
	system("pause");
} catch(std::exception &e){
	std::cout<<e.what()<<std::endl;
	system("pause");
}