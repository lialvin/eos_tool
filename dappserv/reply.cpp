//
// reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "reply.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace dapp {
namespace server2 {


namespace misc_strings {

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

} // namespace misc_strings

std::vector<boost::asio::const_buffer> reply::to_buffers()
{
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(status_strings::to_buffer(status));
  for (std::size_t i = 0; i < headers.size(); ++i)
  {
    header& h = headers[i];
    buffers.push_back(boost::asio::buffer(h.name));
    buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
    buffers.push_back(boost::asio::buffer(h.value));
    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  }
  buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  buffers.push_back(boost::asio::buffer(content));
  return buffers;
}

} // namespace server2
} // namespace dapp

