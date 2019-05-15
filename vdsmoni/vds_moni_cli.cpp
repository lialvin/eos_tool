//
// uos_moni_cli.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread> 
#include<chrono>  
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <regex>

using boost::asio::ip::tcp;

enum { max_length = 10240 };

void call();
void  printflow( std::time_t &  old_value, size_t reply_length, size_t & total_len );
std::vector<std::string> read_vds(std::string filestr);
size_t   collectdata( std::string & nodeinfo, size_t  buflen,std::string filestr);

int main(int argc, char* argv[])
{
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
   

    std::string getinfo("//home//vds//sh//getvds.sh");
    std::string getremoteinfo("/home/vds/sh/getremotevds.sh");
    std::string masterstatus("/home/vds/sh/masternode.sh");
    int  oldblocknum=0;

    while(1)
    {

      try{

         std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<int, std::ratio<1>>> now_secondlevel = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<1>>>(std::chrono::high_resolution_clock::now());
         std::time_t  ut_second = std::chrono::high_resolution_clock::to_time_t(now_secondlevel);      

         size_t reply_length =0;
         size_t total_len=0;
 
         std::string strinfo,remoteinfo,masterstatus; 
         size_t datalen=0 ; 
         datalen= collectdata(strinfo, 2000,getinfo);
         std::string result = getnumber(strinfo);
         int block = boost::lexical_cast<int>(result) ;

         datalen= collectdata(remoteinfo, 2000,getremoteinfo);

         std::size_t found = remoteinfo.find("blocks");
         if (found!=std::string::npos)
         {
             std::string tempstr(remoteinfo.data()+ found, remoteinfo.length()- found );
             std::string resultnew = getnumber(tempstr);
             int block = boost::lexical_cast<int>(resultnew) ;             
      
         }
     
         datalen= collectdata(masterstatus, 2000,masterstatus);

          
      }
      catch (std::exception& e)
      {
         std::cerr << "Exception: " << e.what() << "\n";
      }

      sleep(1);
      sleep(2);
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
        std::cout<<"std::cout "<< line<< std::endl; 
    }
    c.wait();
    
    return data;

}

