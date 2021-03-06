//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "uos_server.hpp"
#include "uos_save.hpp"

using namespace std;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

int testlog( );
void initlog()
{
//    boost::log::add_file_log("dbmgr.log", keywords::auto_flush = true);  
    auto file_sink = logging::add_file_log
        (
        keywords::file_name = "qitserv_%N.log",                                        /*< file name pattern >*/
        keywords::auto_flush = true,
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%]: %Message%"                                 /*< log record format >*/
        );

//    logging::core::get()->set_filter(logging::trivial::severity>=logging::trivial::trace);
    file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
        keywords::target = "logs",        //folder name.  
        keywords::max_size = 50 * 1024 * 1024,    //The maximum amount of space of the folder.  
        keywords::min_free_space = 100 * 1024 * 1024  //Reserved disk space minimum.  
        ));

    file_sink->locked_backend()->scan_for_files();

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
    logging::add_common_attributes();

}


void uselog()
{
//    initlog();
//    testlog();
}

int testlog( )
{
    BOOST_LOG_TRIVIAL(trace)<<"A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An from informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A from warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An from error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

//    system("pause");
    return 0;
}
   

int main(int argc, char* argv[])
{
  try
  {
    uselog();
    if (argc != 3)
    {
       std::cerr << "Usage: async_tcp_echo_server <port> <save_file>\n";
       return 1;
    }

    boost::asio::io_context io_context(1);

    int count = 0;
    timeSave  tiSave(io_context,std::string(argv[2]));
    g_uosSave = &tiSave;
    server s(io_context, std::atoi(argv[1]) );

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: exit " << e.what() << "\n";
  }

  return 0;
}
