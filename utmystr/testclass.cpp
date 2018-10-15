#include "testclass.h"

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

