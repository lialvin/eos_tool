#include <stdio.h>
#include "include/a.h"
#include "mystr.h"
#include "readcfg.h"
#include "testmain.h"
#include <boost/format.hpp>


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

void test1()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator
  int a = it->second;
  a = it->second;
  it=mymap.find('c');

  a = it->second;
  
  mymap.erase ('c');                  // erasing by key

  it++;

  a = it->second;

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}
#define STRING(x)  #x#x#x
#define TEXT(x)  "class"#x"Info"
#define CLASS_NAME(name) class##name

int main(int argc, char* argv[])
{

   int aab=100;
   test1();
   MyString abc{"abcdef" };
   MyString abd("abcdef" );
   MyString(STRING(aab));
   MyString(STRING(aabbb));
   MyString(CLASS_NAME(Timer22));

   MyString cabc=MyString("abc");
   std::string abcd;
   std::string abcd1("11111111111111111111111111111111222222222222222222222222222222222222aaaaaaaaaaaaaaa"
        "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
   int length = sizeof(abcd);
   length = sizeof(abcd1);
   cout<<"sizeof(abcd) = "<< length <<"  std::string= "<< sizeof(std::string)<<endl;
   
   int m = [](int x) { return [](int y) { return y * 2; }(x+3)+x+6; }(5);
    
   cout<< m <<std::endl ; 

   int64_t  COIN=100000000;   
   uint64_t  infCOIN=-1;   
   int64_t  MAX_MONEY = int64_t(1000) * 21000000 * COIN;
 
   string  dbuser ,dbhost, dbpass;
   int startheight, endheight;
   readcfg(startheight,endheight,dbuser,dbhost,dbpass);


   std::string str1{"abcderg"};     
   for(auto c : str1.substr(1)) 
   {
      cout<< c<<", str1="<<str1<<endl;      
   }
      
   cout<< " str1="<<str1.substr(1)<<endl;      

   for(auto c : str1.substr(1)) 
   {
      cout<< c<<", str1="<<str1<<endl;      
   }
    
   double b=25.0;
   double a=0.0;
   char szBuf[128];
   sprintf(szBuf  ,"a is %lf,b is %lf\n" , a,b);
    
   print(1,23,3.5,"abcd");   

   return 0;
}



