#include <stdio.h>
#include "include/a.h"
#include "mystr.h"
#include "readcfg.h"
#include "testmain.h"
#include <boost/format.hpp>

#define STRING(x)  #x#x#x
#define TEXT(x)  "class"#x"Info"
#define CLASS_NAME(name) class##name

template <class T> typename std::enable_if<std::is_integral<T>::value,bool>::type
   is_odd (T i) {return bool(i%2);}
template < class T,  class = typename std::enable_if<std::is_integral<T>::value>::type>
   bool is_even (T i) {return !bool(i%2);}



int main(int argc, char* argv[])
{

   short int i = 1;    // code does not compile if type of i is not integral
   double  aa = 0; 
   std::cout << std::boolalpha;
   std::cout << "i is odd: " << is_odd(i) << std::endl;
   std::cout << "i is even: " << is_even(i) << std::endl;
  // std::cout << "i is char: " << is_even(aa) << std::endl;

   int aab=100;

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
    

   return 0;
}



