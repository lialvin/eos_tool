//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2018
//
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.hpp"

#include "tcpclient.hpp"


int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 4)
    {
      std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 .\n";
      return 1;
    }
    boost::asio::io_context io_context(1);
 
    // 定时器
    int count = 0;

    dapp::server::tcpClient  pcli(io_context);
    //asio::detail::thread t(boost::bind(&asio::io_context::run,&io));
    //asio::steady_timer cliTimer(io, asio::chrono::seconds(1));	
    //cliTimer.async_wait(boost::bind(print, asio::placeholders::error, &t, &count));

    // Initialise the server.
    dapp::server::server s(io_context,argv[1], argv[2]);

    // Run the server until stopped.
    io_context.run();
 
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
