//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DAPP_SERVER2_HEADER_HPP
#define DAPP_SERVER2_HEADER_HPP

#include <string>

namespace dapp {
namespace server2 {

struct header
{
  std::string name;
  std::string value;
};

} // namespace server2
} // namespace http

#endif // DAPP_SERVER2_HEADER_HPP


