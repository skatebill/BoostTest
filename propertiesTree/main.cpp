#include<iostream>
#include<boost\progress.hpp>
#include<boost\exception\all.hpp>
#include<exception>
#include<string>
#include<boost\property_tree\ptree.hpp>
#include<boost\property_tree\xml_parser.hpp>
#include<boost\property_tree\info_parser.hpp>
using namespace std;
using namespace boost;
using namespace boost::property_tree;

void main(){
	progress_timer t;
	ptree pt;
	read_xml("test.xml",pt);
	pt.add("conf.urls.url","www.sina.com.cn");
	write_xml("test2.xml",pt);
	write_info("test.info",pt);

}