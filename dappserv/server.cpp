//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include "connection_manager.hpp"
#include <boost/bind.hpp>

namespace dapp {
namespace server2 {

server::server(const std::string& address, const std::string& port,
         std::size_t io_context_pool_size)
  : io_context_pool_(io_context_pool_size),
    signals_(io_context_pool_.get_io_context()),
    acceptor_(io_context_pool_.get_io_context()),
    connection_manager_(),
    new_connection_()
{
  // Register to handle the signals that indicate when the server should exit.
  // It is safe to register for the same signal multiple times in a program,
  // provided all registration for the specified signal is made through Asio.
  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
  signals_.async_wait(boost::bind(&server::handle_stop, this));

  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(acceptor_.get_executor().context());
  boost::asio::ip::tcp::endpoint endpoint =
    *resolver.resolve(address, port).begin();
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  start_accept();
//  do_accept();
  
}

void server::run()
{
  io_context_pool_.run();
}
// new_connection_ is can support two connect ?

void server::start_accept()
{

  new_connection_.reset(new connection(
        io_context_pool_.get_io_context(), connection_manager_));
  //      io_context_pool_.get_io_context(), request_handler_));
  
  acceptor_.async_accept(new_connection_->socket(),
      boost::bind(&server::handle_accept, this,
        boost::asio::placeholders::error));

}

void server::handle_accept(const boost::system::error_code& e)
{
  if (!e)
  {
    new_connection_->start();
    //  connection_manager_.start(new_connection_);
  }

  start_accept();
}


void server::do_accept() 
{
  acceptor_.async_accept(
      [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
      {
        // Check whether the server was stopped by a signal before this
        // completion handler had a chance to run.
        if (!acceptor_.is_open())
        {
          return;
        } 
        
        if (!ec)
        {
            boost::shared_ptr<connection> conn(new connection(std::move(socket), connection_manager_));
            connection_manager_.start(conn);  
        }     
        
        do_accept();
      });
}     

void server::do_await_stop()
{
  signals_.async_wait(
      [this](boost::system::error_code , int )
      {
        // The server is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_context::run()
        // call will exit.
        acceptor_.close();
        connection_manager_.stop_all();
      });
}  



void server::handle_stop()
{
  io_context_pool_.stop();
}

} // namespace server2
} // namespace http
