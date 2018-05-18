#include "readcfg.h"
#include <string>

#include <string.h>

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int   readstrfiletohex( char *pinfile, char * poutfile  );

int   readbintohex( char *pinfile, char * poutfile  );

int main(int argc, char* argv[])
{

   string  dbuser , dbpass;
 
   char * p; 
   char szBuf[128];

   if(argc<3 ) return 0 ;
    
   readstrfiletohex(argv[1],argv[2]);
   //readbintohex(argv[1],argv[2]);

   system("pause");

   return 0;
}
#define  BUF_LEN 1000
int   readbintohex( char *pinfile, char * poutfile  )
{
    char szbuf[BUF_LEN]="";

    ifstream  ifile;  
    ifile.open(pinfile ,std::ifstream::binary);  

//    int readlen =0;
//    inF.read(szbuf,1000000 );  
    std::vector<char> readbuf;
    while(ifile.read(szbuf, BUF_LEN))
    {     
        readbuf.insert(readbuf.end(), &szbuf[0],&(szbuf[0])+BUF_LEN); 
    }
    readbuf.insert(readbuf.end(), &szbuf[0],&(szbuf[0])+ifile.gcount()); 
    ifile.close();


    ofstream out(poutfile);  
    int linenum = 0;
 
   char printbuf[32]=""; 
   for(auto & achar : readbuf) 
   {
       linenum++;
       sprintf(printbuf,"0x%02x, ",(unsigned char )achar);
       out<<printbuf;
       if(linenum%8==0)
       { 
          out<<endl;
       }
   } 

    out.close();  
  
}

int   readstrfiletohex( char *pinfile, char * poutfile  )
{
   char buffer[1000]="";  
   string  strreadfile; 
   int readlen=0;

   ifstream in(pinfile);  
   if (! in.is_open())  
   {    
       cout << "Error opening file"; exit (1); 
   }  

   std::vector<char> readbuf;  
   while (!in.eof() )  
   {  
       in.getline(buffer,1000);  
       //readlen = in.read(buffer, 500);  
       readlen= strlen(buffer);      
        
       readbuf.insert(readbuf.end(), &buffer[0],&(buffer[0])+readlen);
       readbuf.push_back(0x0a);
      
   }
   readbuf.pop_back();
   in.close();
  

   ofstream out(poutfile);  
   int linenum = 0;
   
   out<<  "namespace json_tests{"<<endl ;
   out<<  "static unsigned const char base58_keys_invalid[] = {"<<endl ;

   char printbuf[32]=""; 

   for(auto & achar : readbuf) 
   {
       linenum++;
       sprintf(printbuf,"0x%02x, ",achar);
       out<<printbuf;
       if(linenum%8==0)
       { 
          out<<endl;
       }
   } 
   out.close();
   return 0;
}


