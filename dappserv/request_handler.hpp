#ifndef DAPP_SERVER3_REQUEST_HANDLER_HPP
#define DAPP_SERVER3_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace dapp{
namespace server3 {

class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit request_handler(){};

  /// Handle a request and produce a reply.
  void handle_request(std::string & req, std::string& rep){};

private:

};

} // namespace server3
} // namespace dapp

#endif // DAPP_SERVER3_REQUEST_HANDLER_HPP

