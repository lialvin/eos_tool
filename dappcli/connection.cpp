//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "TcpSplitPkt.h"
#include "reply.hpp"

namespace dapp {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket,connection_manager& manager)
  : socket_(std::move(socket)),   connection_manager_(manager)

{
}

void connection::start()
{
  do_read();
}

void connection::stop()
{
  socket_.close();
}

void connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
		
        if (!ec)
        {

	   int  ret = splitPkt_.DealConnectData((BYTE*)buffer_.data(),   bytes_transferred);
				
			if (ret==2 ) //success 
			{
				//request_handler_.handle_request(request_, reply_);
				do_write();
			  
			}
			else if (ret==0) // error 
			{
	
  			 // request_handler_.handle_request(request_, reply_);
			  do_write();

					
			}
			
			else if(ret==1) // continue read 
			{
			    do_read();
			  
			}
       		  
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

void connection::do_write()
{
     auto self(shared_from_this());

     boost::asio::async_write(socket_, reply_.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t)
        {
          if (!ec)
          {
             // Initiate graceful connection closure.
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
          }

          if (ec != boost::asio::error::operation_aborted)
          {
            connection_manager_.stop(shared_from_this());
          }
      });
}

} // namespace server
} // namespace dapp


