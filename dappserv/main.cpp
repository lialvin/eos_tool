//
// main.cpp
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include "server.hpp"

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 5)
    {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 1 .\n";
      return 1;
    }
   // boost::asio::io_context io_context(1);
   typedef boost::shared_ptr<boost::asio::io_context> io_context_ptr;
    io_context_ptr io_context(new boost::asio::io_context);
    // Initialise the server. 
    std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
    dapp::server2::server s(argv[1], argv[2],  num_threads);

    boost::shared_ptr<boost::thread> thread(new boost::thread(
          boost::bind(&boost::asio::io_context::run, io_context)));

    // Run the server until stopped.
    s.run();

    thread->join(); 

  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
