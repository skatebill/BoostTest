
#pragma comment(lib,"libboost_filesystem-vc100-mt-gd-1_53.lib")

#include<boost\filesystem.hpp>
#include<boost\progress.hpp>
#include<iostream>
#include<boost\typeof\typeof.hpp>
using namespace std;
using namespace boost;
using namespace boost::filesystem;
namespace fs = boost::filesystem;
typedef recursive_directory_iterator rd_ite;
void scan(path& root,int depth = -1) try
{
	rd_ite end,pos(root);
	for(;pos != end; ++pos)
	{
		if( depth != -1)
			if( pos.level() == depth)
				if(is_directory(*pos))
					pos.no_push();
		//for(int i=0;i<pos.level();i++)
	//		cout<<"\t";
		//cout<<pos->path().filename()<<"\t"<<pos.level()<<endl;
	}
} catch(filesystem_error &e)
{
	cout<<e.what()<<endl;
}




void main(){
	progress_timer t;
	path p("c:/");
	p /= "windows/";
	p /= "ststem32/";
	cout<<system_complete(p)<<endl;
	path testXml("./test.xml");
	path testInfo("./test.info");
	cout<<testXml.filename()<<" "<<system_complete(testXml)<<endl;
	cout<<"\t"<<testXml.extension()<<endl;
	testInfo=system_complete(testInfo);
	BOOST_AUTO(ite,testInfo.begin());
	while(ite != testInfo.end())
	{
		cout<<"["<<*ite<<"]"<<endl;
		ite++;
	}
	try{
		path p("c:/test.txt");
		file_size(p);
	}catch(filesystem_error &e){
		//cout<<e.path1()<<endl;
		cout<<e.what()<<endl;
	}
	cout<<initial_path()<<endl;
	cout<<current_path()<<endl;
	const int GBytes = 1024*1024*1024;
	space_info dpan = space("d:/");
	cout<<"D盘可用空间:"<<dpan.available / GBytes<<" GB"<<endl;
	cout<<"D盘总空间:"<<dpan.capacity / GBytes<<" GB"<<endl;
	cout<<"D盘free空间:"<<dpan.free / GBytes<<" GB"<<endl;
	path current = current_path();
	path testTxt = current / "test.txt";
	if(exists(testTxt))
	{
		cout<<"已经存在txt文件 删除txt文件"<<endl;
		if( fs::is_empty(testTxt) )
		{ 
			fs::remove(testTxt);
		}else
		{
			fs::remove_all(testTxt);
		}

	}
	ofstream testTxtOs(testTxt.c_str());
	testTxtOs<<"hello world"<<endl;
	testTxtOs.close();
	if(exists(testTxt))
	{
		cout<<"创建txt文件成功"<<endl;
	}
	directory_iterator pos("d:/"),end;
	cout<<"开始浏览d盘下所有文件"<<endl;
	for(;pos!=end;++pos)
	{
		cout<<"\t"<<*pos<<endl;
	}
	const int depth = 3;
	cout<<"开始扫描D盘下深度为 " << depth << " 以内的文件"<<endl;
	{
		progress_timer p;
		scan(path("d:/"),depth);
	}
	cin>>*(new int);

}