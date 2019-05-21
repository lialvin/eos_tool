//
// uos_moni_cli.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread> 
#include <chrono>  
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <regex>

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

using boost::asio::ip::tcp;

enum { max_length = 10240 };

namespace bp = boost::process;

void call();
void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len );
std::vector<std::string> read_vds(std::string filestr);
size_t   collectdata( std::string & nodeinfo, size_t  buflen,std::string filestr);
std::string do_exec(std::string filestr );


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
        keywords::file_name = "vdsmoni_%N.log",                                        /*< file name pattern >*/
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
    initlog();
    testlog();
}


int main(int argc, char* argv[])
{
    uselog();
    if (argc != 1)
    {
      std::cerr << "Usage: vds_moni\n";
      return 1;
    }
    call();
}

namespace bp = ::boost::process;



std::string  getnumber(std::string ipline)
{
    std::string result;

    std::string regString("(\\d+)");
    std::smatch ms;
    std::regex_constants::syntax_option_type fl = std::regex_constants::icase;
    std::regex regExpress(regString, fl);

     // 查找     
    if(std::regex_search(ipline, ms, regExpress))
    {
        result= ms[0];
        return result;
    }
    return  std::string("");

}


void call()
{
    boost::asio::io_context io_context;
   

    std::string getinfo("/home/vds/vdsmoni/getvds.sh");
    std::string getremoteinfo("/home/vds/vdsmoni/getremotevds.sh");
    std::string masterstatus("/home/vds/vdsmoni/masternode.sh");
    int  oldblockno=0;
    int  nMasternodestatus; 
    int  nNodeState =3;  // default 3 ,  0: no start , 1: start no sync , 2 sync finish ,can getinfo . no master , 3: master status recovery
    std::time_t  node_start_time=0;
    int  nGetInfoCount=0;
    int  nMasterStatusCount=6;
    int  waitTime1 = 10*60 , waitTime2= 5*60 , waitTime3= 60; 

    // do every step , stop 3 minute;  
       

    while(1)
    {

      try{

         nMasternodestatus = 0;
         std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
         std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);      

         size_t reply_length =0;
         size_t total_len=0;



         std::string vdsdisstart ;
         
         int datalen= collectdata(vdsdisstart , 2000,"/home/vds/vdsmoni/vdsisstart.sh");
         std::size_t found = vdsdisstart.find("vdsd");
         if (found!=std::string::npos)
         {   
             //nNodeState =      
         } 
         else
         {
             nNodeState = 0;

             BOOST_LOG_TRIVIAL(info) << "vdsnode no  start, now is  "<<  ctime(&ut_second) << "  ";

             //  datalen= collectdata(vdsdisstart , 2000,"/home/vds/vdsmoni/vdsstart.sh");
             std::string resstr = do_exec( "/home/vds/vdsmoni/vdsstart.sh"  );

             sleep(2);

             BOOST_LOG_TRIVIAL(info) << "vdsnode  start, after 10 second  " << resstr<<  "  ";
             
             datalen= collectdata(vdsdisstart , 2000,"/home/vds/vdsmoni/vdsisstart.sh");

             found = vdsdisstart.find("vdsd");
             if (found!=std::string::npos)
             {
                 nNodeState = 1;     
                 node_start_time = std::chrono::high_resolution_clock::to_time_t(now_secondlevel); 
                 BOOST_LOG_TRIVIAL(info) << "vdsnode  start, success  " << "  ";
             }  
             else
             {
                 BOOST_LOG_TRIVIAL(info) << "vdsnode  start, failed   " << "  ";
                 continue; 
             }
         }

         
         //BOOST_LOG_TRIVIAL(info) << "vdsnode  starting time  "<<  ut_second << "  "<< node_start_time <<"";
         if(ut_second - node_start_time < 60*10)   
         {
             BOOST_LOG_TRIVIAL(info) << "vdsnode  starting , now is  "<<  ctime(&ut_second) << "  ";

             sleep(60);
             continue; 
         }

        
 
         std::string strinfo,remoteinfo,masterinfo; 
         datalen= collectdata(strinfo, 2000,getinfo);
         std::string result = getnumber(strinfo);
   
        
         int block = 0 ;
         int remoteblock = 0 ;

         try{ 
             block = boost::lexical_cast<int>(result) ;
         }
         catch(boost::bad_lexical_cast & e)  
         {
             BOOST_LOG_TRIVIAL(info) << "vdsnode getinfo failed , now is  "<<  ctime(&ut_second) << "  ";
             nGetInfoCount++;
             if(nGetInfoCount > 5)
             { 
                  BOOST_LOG_TRIVIAL(info) << "vdsnode getinfo failed , stop node  now is  "<<  ctime(&ut_second) << "  ";
                  int len= collectdata(strinfo, 2000,"/home/vds/vdsmoni/vdsstop.sh");
             }
             sleep(60);
             continue; 
         }

         nGetInfoCount = 0 ;
         datalen= collectdata(remoteinfo, 2000,getremoteinfo);

         found = remoteinfo.find("height");
         if (found!=std::string::npos)
         {
             std::string tempstr(remoteinfo.data()+ found, remoteinfo.length()- found );
             std::string resultnew = getnumber(tempstr);
             remoteblock = boost::lexical_cast<int>(resultnew) ;             
      
         }

         BOOST_LOG_TRIVIAL(info) << "vdsnode localnode no "<< block << "  remotenode no  "<< remoteblock << "   now is  "<<  ctime(&ut_second) << "  ";
    
         if(remoteblock<10000 || block <10000)
         {
             sleep(20);
             continue;
         }         
  
         if(block < remoteblock-10 ) //need sync 
         {
             if(block > oldblockno ) 
             {   
                 oldblockno= block; 
                 sleep(120);
             }
             else  // no sync need stop vds
             {
                 BOOST_LOG_TRIVIAL(info) << "vdsnode stop "<<block<<"  "<<oldblockno<<" now is  "<<  ctime(&ut_second) << "  ";
                 int len= collectdata(strinfo, 2000,"/home/vds/vdsmoni/vdsstop.sh");
                 sleep(120);
             }
            
         }   
         else
         {
             datalen= collectdata(masterinfo, 3000,masterstatus);

         
            // BOOST_LOG_TRIVIAL(info) << "vdsnode masternode  info  is  "<< masterstatus<<"  " <<  masterinfo << "  ";

             found = masterinfo.find("successfully");

             if (found != std::string::npos)
             {
                 BOOST_LOG_TRIVIAL(info) << "vdsnode masternode success,   now is  "<<  ctime(&ut_second) << "  ";
                 nMasternodestatus = 1;
                 nMasterStatusCount=0;
             }
             else
             {
                 nMasterStatusCount++;
                 BOOST_LOG_TRIVIAL(info) << "vdsnode masternode  failed.info=  "<<masterinfo<< "   now is  "<<  ctime(&ut_second) << "  ";
                 if(nMasterStatusCount>5)
                 {
                    BOOST_LOG_TRIVIAL(info) << "vdsnode masternode  failed ,send masternode   now is  "<<  ctime(&ut_second) << "  ";
                    nMasternodestatus = 0;
                    int len= collectdata(masterinfo, 2000,"/home/vds/vdsmoni/startmaster.sh");
                 }
             } 

         } 
         
      }
      catch (std::exception& e)
      {
         std::cerr << "Exception: " << e.what() << "\n";
      }


      sleep(60);
      sleep(60);
    }
}


size_t   collectdata( std::string & nodeinfo, size_t  buflen,std::string filestr)
{   
    size_t  data_len=0;
    std::vector<std::string> str_vec;
    str_vec= read_vds(filestr);
    for(auto it :str_vec)
    {  
       if(data_len< buflen-it.length())
       {  
          nodeinfo+=it; 
          nodeinfo+="\n"; 
          data_len+=it.length();
       }
    }
    
    return  nodeinfo.length();
}


void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len )
{
       std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
      std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);
      // ut_def = std::chrono::high_resolution_clock::to_time_t(now_deflevel);

     total_len+=reply_length;
     if(ut_second > old_value+5) 
     {
         std::cout << ctime(&ut_second);
         //std::cout << now_secondlevel << std::endl;
         std::cout << ut_second << std::endl;
         std::cout<<"Reply length total= "<< total_len<<"\n"<<std::endl;
         old_value= ut_second;  
         total_len=0;
     }
}


std::string   do_exec(std::string filestr )
{
    std::string res;
    res = system((char*)filestr.data());

     return res ; 
       //std::cout<<"std::cout read uos  "<< std::endl; 
}

std::vector<std::string> read_vds(std::string filestr)
{   
    //std::cout<<"std::cout read uos  "<< std::endl; 
    std::vector<std::string> data;
    std::string line;
    
    bp::ipstream is; //reading pipe-stream
    //bp::child c(bp::search_path("cluos"),"-u","http://10.186.11.220:9008", "get", "info",   bp::std_out > is);
    bp::child c(bp::search_path("sh"), filestr,   bp::std_out > is);
    //bp::child c(bp::search_path("gcc"),"-v",  bp::std_err >is);
    
    while (c.running() && std::getline(is, line) && !line.empty())
    {   
        data.push_back(line);
        //std::cout<<"std::cout "<< line<< std::endl; 
    }
    c.wait();
    
    return data;

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

