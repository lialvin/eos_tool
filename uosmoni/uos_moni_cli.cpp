//
// uos_moni_cli.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread> 
#include<chrono>  
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

using boost::asio::ip::tcp;

enum { max_length = 10240 };

void call(int argc , char * argv[]);
void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len );

std::vector<std::string> read_uos();

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
      std::cerr << "Usage: tcp_client <host> <port>\n";
      return 1;
    }
    call(argc,argv);
}

namespace bp = ::boost::process;

std::vector<std::string> read_uos()
{
    std::cout<<"std::cout read uos  "<< std::endl; 
    std::vector<std::string> data;
    std::string line;

    bp::ipstream is; //reading pipe-stream
    //bp::child c(bp::search_path("cluos"),"-u","http://10.186.11.220:9008", "get", "info",   bp::std_out > is);
    bp::child c(bp::search_path("sh"), "/home/qicity/bin/shuos.sh",   bp::std_out > is);
    //bp::child c(bp::search_path("gcc"),"-v",  bp::std_err >is);
    
    while (c.running() && std::getline(is, line) && !line.empty())
    {
        data.push_back(line);
//        std::cout<<"std::cout "<< line<< std::endl; 
    }
    c.wait();

    return data;

} 

/*
*/
void sndfun(tcp::socket   & s,const char*  buf, size_t buflen) //拷贝构造函数  
{  
    boost::asio::write(s, boost::asio::buffer(buf, buflen ));
    //std::this_thread::sleep_for(std::chrono::milliseconds(10));  
}

/*

*/
size_t   collectdata( std::string & nodeinfo, size_t  buflen)
{
    size_t  data_len=0;
    std::vector<std::string> str_vec;
    str_vec= read_uos();
    for(auto it :str_vec)
    {
       if(data_len< buflen-it.length()) 
       { 
          nodeinfo+=it; 
          nodeinfo+="\n"; 
          data_len+=it.length(); 
       }
    }
    return  data_len; 
}

void call(int argc , char * argv[])
{
    boost::asio::io_context io_context;
   
    char request[2028]={""};

    char reply[max_length];

    while(1)
    {
      tcp::socket s(io_context);
      tcp::resolver resolver(io_context);
      boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));


       std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
      std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);      

     size_t reply_length =0;
     size_t total_len=0;
 
     //std::thread t3(sndfun, std::ref(s)); //引用  
     std::string strinfo; 
     size_t datalen= collectdata(strinfo, 2000);
     sndfun(s, strinfo.data(),datalen);
     
     /*while(1) 
     {
         reply_length = boost::asio::read(s,boost::asio::buffer(reply, max_length));
         printflow(ut_second, reply_length, total_len );
      }*/ 

      sleep(1);
      boost::system::error_code ignored_ec;
      s.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
      sleep(2);
    }
}

void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len )
{
       std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
      std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);
      // ut_def = std::chrono::high_resolution_clock::to_time_t(now_deflevel);

     total_len+=reply_length;
     if(ut_second > old_value+5) 
     {
         std::cout << ctime(&ut_second);
         //std::cout << now_secondlevel << std::endl;
         std::cout << ut_second << std::endl;
         std::cout<<"Reply length total= "<< total_len<<"\n"<<std::endl;
         old_value= ut_second;  
         total_len=0;
     }
}

