//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"

namespace dapp {
namespace server2 {

connection_manager::connection_manager()
{
}

void connection_manager::start( boost::shared_ptr<connection>  c)
{
  connections_.insert(c);
  c->start();
}

void connection_manager::stop(boost::shared_ptr<connection>  c)
{
  connections_.erase(c);
//  c->stop();
}

void connection_manager::stop_all()
{
  for (auto c: connections_)
    c->stop();
  connections_.clear();
}

} // namespace server
} // namespace http
