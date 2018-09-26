//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DAPP_SERVER2_REPLY_HPP
#define DAPP_SERVER2_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

namespace dapp {
namespace server2 {

/// A reply to be sent to a client.
struct reply
{
  /// The status of the reply.
  int  length;
  int  msgtype;
  int  cryptflag;
  char msgflag[4];
  
  /// The content to be sent in the reply.
  std::string content;

  /// Convert the reply into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the reply object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> to_buffers();

};

} // namespace server2
} // namespace http

#endif // DAPP_SERVER2_REPLY_HPP

