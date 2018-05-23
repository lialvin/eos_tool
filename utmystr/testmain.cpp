#include <stdio.h>
#include "include/a.h"
#include "mystr.h"
#include "readcfg.h"
#include "testmain.h"
#include <boost/format.hpp>

//展开函数
//

//递归终止函数
void print()
{
   cout << "empty" << endl;
}
template <class T, class ...Args>
void print(T head, Args... rest)
{
   cout << "parameter " << head << endl;
      print(rest...);
}

#define STRING(x)  #x#x#x
#define TEXT(x)  "class"#x"Info"
#define CLASS_NAME(name) class##name

int main(int argc, char* argv[])
{

   int aab=100;

   MyString abc{"abcdef" };
   MyString abd("abcdef" );
   MyString(STRING(aab));
   MyString(STRING(aabbb));
   MyString(CLASS_NAME(Timer22));

   MyString cabc=MyString("abc");
   std::string abcd;
   int length = sizeof(abcd);
   cout<<"sizeof(abcd) = "<< length <<"  std::string= "<< sizeof(std::string)<<endl;
   
   int m = [](int x) { return [](int x) { return x * 2; } (x)+6; }(5);
    
   cout<< m <<std::endl ; 

   int64_t  COIN=100000000;   
   uint64_t  infCOIN=-1;   
   int64_t  MAX_MONEY = int64_t(1000) * 21000000 * COIN;
 
   string  dbuser ,dbhost, dbpass;
   int startheight, endheight;
   readcfg(startheight,endheight,dbuser,dbhost,dbpass);
    
 
    
   double b=25.0;
   double a=0.0;
   char szBuf[128];
   sprintf(szBuf  ,"a is %lf,b is %lf\n" , a,b);
    
   print(1,23,3.5,"abcd");   

   return 0;
}



