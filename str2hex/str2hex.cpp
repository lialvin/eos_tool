#include "readcfg.h"
#include <string>

#include <string.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>


using namespace std;


int   readstrfiletohex( char *pinfile, char * poutfile  );

int   readbintohex( char *pinfile, char * poutfile  );


class CTestA
{
public:
   CTestA(){};
   ~CTestA(){};
   
   int fun(int a,int b)
   { 
     //cout<<a<<b<<endl;
   
   }
   std::function< int(int ,int )> datahandlefun_;

};


class CTest
{
public:
   CTest(){
        //aaa.datahandlefun_= std::bind(&CTest::fun, *this, std::placeholders::_1, std::placeholders::_2);
        aaa.datahandlefun_= std::bind(&CTest::fun, this, std::placeholders::_1, std::placeholders::_2);
    }
   ~CTest(){};

   int fun(int a,int b) 
   {
     cout<<a<<"==a            b=="<<b<<endl;

   }
   CTestA  aaa;
};

void printhelp()
{
       cout<<"1  help  :"  <<endl;
       cout<<"2  h2b  ; readstrfiletohex  hexfile1 binfile2 "<<endl;
       cout<<"3  b2h  ; readbintohex  binfile1  hexfile2    "<<endl;

       cout<<"4  encrypt ;ras encrypt file  "<<endl;
       cout<<"5  decrypt ;ras decrypt file  "<<endl;
       cout<<"6  encryptint ;ras encrypt int  "<<endl;

}

void callFun(int argc, char* argv[] )
{

    if(argc<2) // help 
    {
       printhelp();
       return ;
    }

    std::string stropt;
    if(argc>1)
    {
        stropt = string(argv[1]);
    }
    if(stropt==string("help") )
    {
       printhelp();
       return;
    }
    else if(stropt==string("h2b") )
    {
       readstrfiletohex(argv[1],argv[2]);
       //readbintohex(argv[1],argv[2]);
       return;
    }
    else if(stropt==string("b2h") ) ///from net
    {
       readbintohex(argv[1],argv[2]);
       return ;
       int blockno =boost::lexical_cast<uint64_t>(argv[2]);
       return;
    }
}

int main(int argc, char* argv[])
{

  
   CTest  bb;
   bb.aaa.datahandlefun_(1121,121);
   
   string  dbuser , dbpass;
 
   char * p; 
   char szBuf[128];

   // if(argc<3 ) return 0 ;

   try
   {

     std::cout <<" test read block file  "<<std::endl;
     callFun(argc, argv );

     system("pause");

    // thitio::chain::named_thread_pool thread_pool("abc",3);
    // thread_pool.stop();

   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << "\n";
   }


   return 0;
}


