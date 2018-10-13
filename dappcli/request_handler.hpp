#ifndef DAPP_SERVER3_REQUEST_HANDLER_HPP
#define DAPP_SERVER3_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "reply.hpp"

namespace dapp{
namespace server {

class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit request_handler(){};

  /// Handle a request and produce a reply.
  void handle_request(unsigned char *  req, int len, reply & replyobj ){};


private:

};

} // namespace server
} // namespace dapp

#endif // DAPP_SERVER3_REQUEST_HANDLER_HPP

