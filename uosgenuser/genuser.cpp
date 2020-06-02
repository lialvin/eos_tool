//
// uos_gen_account.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread> 
#include <chrono>  
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <regex>

#include <memory>
#include <utility>

#include<fstream>

enum { max_length = 10240 };


std::vector<std::string> read_file(std::string filestr);
void  genaccount(std::vector<std::string>& keys ,  std::vector<std::string> & newusers,   std::vector<std::string>&  creators );
void  givemoney(std::vector<std::string> & creators,   std::vector<std::string> & newusers);
void  genuidaccount(std::vector<std::string>& keys ,  std::vector<std::string> & newusers,   std::vector<std::string>&  creators);


using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
      std::cerr << "Usage: 1 givemoney ,2 gen account 3 gen uid test\n";
      return 1;
    }

    std::string strcmd(argv[1]);

    std::vector<std::string> keys =  read_file("key.txt");
    std::vector<std::string> newusers =  read_file("newuser.txt");
    std::vector<std::string> creators =  read_file("creator.txt");
   
    if(strcmd.find("1")!=std::string::npos)
       givemoney( creators,  newusers)  ;     
    if(strcmd.find("2")!=std::string::npos)
       genaccount( keys , newusers, creators)  ;     
    if(strcmd.find("3")!=std::string::npos)
       genuidaccount( keys , newusers, creators)  ;     

}

void  givemoney(std::vector<std::string> & creators,   std::vector<std::string> & newusers)  
{
  fstream fout("out.sh", ios::out);
  if(!fout)
  {
     cout<<"文件打开失败！"<<endl;
     exit(1);
  } 
  int creatorcount = creators.size();
  int newcount = newusers.size();

  fout<<"# .bashrc"<<std::endl;

  fout <<"cli='cluos --wallet-url http://127.0.0.1:1222 -u http://124.232.153.72:9008'" <<std::endl;

  for(int i =0 ; i< newcount; i++)
  {
//   cli transfer ulorduserno1   uosuidwallet  "100.0000 UOS"  "testtesttest--"

    fout<<"$cli  "<< " transfer  "  <<  creators[i%creatorcount]<<  "  " << newusers[i]<< "  "<<  " \"20.0000 UOS\"  \"\" "<<std::endl;
    fout<<"echo give money  "<< newusers[i] <<std::endl;
    fout<<"sleep 2"<<std::endl;

  }
  fout<<"#Hello World";
  fout.close();

}

void  genuidaccount(std::vector<std::string>& keys ,  std::vector<std::string> & newusers,   std::vector<std::string>&  creators )
{
  fstream fout("uid.sh", ios::out);
  if(!fout)
  {
     cout<<"文件打开失败！"<<endl;
     exit(1);
  }
  int newcount = newusers.size();
  int keycount = keys.size();
  int creatorcount = creators.size(); 

   fout<<"# .bashrc"<<std::endl;

  fout <<"cli='cluos --wallet-url http://127.0.0.1:1177 -u http://114.67.37.198:9008'" <<std::endl;

  for(int i =0 ; i< newcount; i++)
  {
    auto curkey= keys[i%keycount ] ;
    auto curcreator = creators[i%creatorcount ];
//cli  system newaccount uoswalletorg --transfer uosuidwallet  UOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV  --stake-net "0.5000 UOS" --stake-cpu "0.5000 UOS" --buy-ram-kbytes 6 
    fout<<"$cli "  << "transfer ulorduserno1  uosuidwallet   \"100.0000 UOS\"  \""<< newusers[i] << "--\"  " <<std::endl;  
    fout<<" $cli  "<< " system newaccount ulorduserno1  "     << "  --transfer  " << newusers[i]<< "  "<< curkey << " --stake-net \"0.5000 UOS\" --stake-cpu \"0.5000 UOS \" --buy-ram-kbytes 6  "<< std::endl;
    fout<<"echo creater user "<< newusers[i] <<std::endl;
    fout<<"sleep 6"<<std::endl;

  }
  fout<<"#Hello World";
  fout.close();  


}

void  genaccount(std::vector<std::string>& keys ,  std::vector<std::string> & newusers,   std::vector<std::string>&  creators )
{

  fstream fout("out.sh", ios::out);
  if(!fout)
  {
     cout<<"文件打开失败！"<<endl;
     exit(1);
  } 
  int newcount = newusers.size();
  int keycount = keys.size();
  int creatorcount = creators.size();

  fout<<"# .bashrc"<<std::endl;

  fout <<"cli='cluos --wallet-url http://127.0.0.1:1277 -u http://124.232.153.72:9008'" <<std::endl;

  for(int i =0 ; i< newcount; i++)
  {
    auto curkey= keys[i%keycount ] ; 
    auto curcreator = creators[i%creatorcount ];
//cli  system newaccount uoswalletorg --transfer uosuidwallet  UOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV  --stake-net "0.5000 UOS" --stake-cpu "0.5000  UOS" --buy-ram-kbytes 6   
    fout<<" $cli  "<< " system newaccount  "  <<  curcreator<< "  --transfer  " << newusers[i]<< "  "<< curkey << " --stake-net \"0.5000 UOS\" --stake-cpu \"0.5000 UOS \" --buy-ram-kbytes 6  "<< std::endl;
    fout<<"echo creater user "<< newusers[i] <<std::endl;
    fout<<"sleep 6"<<std::endl;

  }
  fout<<"#Hello World";
  fout.close();

}


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

std::vector<std::string> read_file(std::string filestr)
{   
    //std::cout<<"std::cout read uos  "<< std::endl; 
    std::vector<std::string> data;
    std::string line;
    
    //ofstream fout("test.dat", ios::out);

    ifstream fin(filestr, ios::in);
    while(std::getline(fin ,line))
    {   
        data.push_back(line);
        //std::cout<<"std::cout "<< line<< std::endl; 
    }
    
    return data;

}


