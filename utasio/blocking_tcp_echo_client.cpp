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

using boost::asio::ip::tcp;

enum { max_length = 1024 };

void call(int argc , char * argv[]);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
      std::cerr << "Usage: tcp_client <host> <port>\n";
      return 1;
    }
    call(argc,argv);
}

void call(int argc , char * argv[])
{
    boost::asio::io_context io_context;

    while(1)
    {
      tcp::socket s(io_context);
      tcp::resolver resolver(io_context);
      boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

      // std::cout << "Enter message: ";
      char request[max_length]={"send msg"};
      // std::cin.getline(request, max_length);
      size_t request_length = std::strlen(request);
      boost::asio::write(s, boost::asio::buffer(request, request_length));

      char reply[max_length];
      size_t reply_length = boost::asio::read(s,
      boost::asio::buffer(reply, request_length));
      std::cout << "Reply is: ";
      std::cout.write(reply, reply_length);
      std::cout << "\n";
      boost::system::error_code ignored_ec;
      s.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
      sleep(600);
    }

}
