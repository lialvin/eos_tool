//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread> 
#include<chrono>  

using boost::asio::ip::tcp;

enum { max_length = 10240 };

void call(int argc , char * argv[]);
void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len );

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
      std::cerr << "Usage: tcp_client <host> <port>\n";
      return 1;
    }
    call(argc,argv);
}

/*
*/
void sndfun(tcp::socket   & s) //拷贝构造函数  
{  
    std::cout << "Thread " <<  " executing\n";  
    //this_thread::sleep_for(chrono::milliseconds(10));  

    char request[1028]={"strlen"};
    for(int i=0;i<100;i++)
    {
       strcat(request,"higklmnopq");
    }
    
    size_t request_length = std::strlen(request);

    while(1)
    {
       boost::asio::write(s, boost::asio::buffer(request, request_length));
       std::this_thread::sleep_for(std::chrono::milliseconds(10));  
    }    
    std::cout << "Thread finished " <<  " executing\n";  
}

void call(int argc , char * argv[])
{
    boost::asio::io_context io_context;
   
    char request[1028]={"strlen"};
    for(int i=0;i<100;i++)
    {
       strcat(request,"higklmnopq"); 
    }

    char reply[max_length];

    while(1)
    {
      tcp::socket s(io_context);
      tcp::resolver resolver(io_context);
      boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

      // std::cout << "Enter message: ";
      //  char request[1025max_length]={"send msg"};
      // std::cin.getline(request, max_length);

       std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
      std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);      

     size_t reply_length =0;
     size_t total_len=0;

     std::thread t3(sndfun, std::ref(s)); //引用  
     /*while(1) 
     {
      //   size_t request_length = std::strlen(request);
      //   boost::asio::write(s, boost::asio::buffer(request, request_length));

         reply_length = boost::asio::read(s,
                             boost::asio::buffer(reply, max_length));

         //std::cout<<"Reply length = "<< reply_length<<std::endl;

         printflow(ut_second, reply_length, total_len );
      }*/ 

      boost::system::error_code ignored_ec;
      s.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
      sleep(1);
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

