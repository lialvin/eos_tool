#include <iostream>  
#include <vector>  
#include <string>  
#include <boost/program_options.hpp>  
#include <algorithm>  
#include "boost/lambda/lambda.hpp"  
#include "boost/tuple/tuple.hpp"  

namespace bpo = boost::program_options;  

#define define_functor_type(func_name) class tfn_##func_name {\
   public: template <typename... Args> auto operator()(Args&&... args) const ->decltype(func_name(std::forward<Args>(args)...))\
   {  \
      return func_name(std::forward<Args>(args)...);\
   } \
}

//test code
int add(int a, int b)
{
    return a + b;
}

int add_one(int a) 
{ 
    return 1 + a; 
}

define_functor_type(add);
define_functor_type(add_one);

int test()
{
    tfn_add add_functor;
    add_functor(1, 2); //result is 3

    tfn_add_one add_one_functor;
    add_one_functor(1); //result is 2


    using namespace boost::lambda;  
    using namespace std;  
  
  
    boost::tuple<int,double,string> triple(42, 3.245, "The amazing tuple!");  
    int  a0  =  triple.get<0>();  
    double  a1  =  triple.get<1>();  
    string  a2  =  triple.get<2>();  
      
    std::vector<int> vec(3);  
    vec[0] = 12;  
    vec[1] = 10;  
    vec[2] = 7;  
  
    //Transform using a lambda expression  
    std::cout<<endl;
    std::for_each(vec.begin(), vec.end(), std::cout<<_1);  
    std::cout<<endl;
    std::for_each(vec.begin(), vec.end(), std::cout<<_1<<' ');  
    std::cout<<endl;
    //std::transform(vec.begin(), vec.end(), vec.begin(), _1-= 4);  
    //
    return 0;
}


int main(int argc, char const *argv[])  
{  
    //外部变量，用于保存获取的参数值  
     
    test();
    int apple_num = 0, orange_num = 0;  
    std::vector<std::string> addr;  
    bpo::options_description opt("all options");  

    opt.add_options()  
    //指定该参数的默认值 
    // "apple,a" : 指定选项的全写形式为 --apple, 简写形式为 -a
    //value<type>(ptr) : ptr为该选项对应的外部变量的地址, 当该选项被解析后, 
    //可通过下面的notify()函数将选项的值赋给该外部变量,该变量的值会自动更新
    //defaut_value(num) : num为该选项的默认值, 若命令行中未输入该选项, 则该选项的值取为num
    ("apple,a", bpo::value<int>(&apple_num)->default_value(10), "苹果的数量")  
    ("orange,o", bpo::value<int>(&orange_num)->default_value(20), "橘子的数量")  
    //该参数的实际类型为vector,所以命令行中输入的值可以是多个,
    //multitoken()的作用就是告诉编译器,该选项可接受多个值  
    ("address", bpo::value<std::vector<std::string> >()->multitoken(), "生产地")  
    ("help", "计算苹果和橘子的总数量");  

    bpo::variables_map vm;  

    try{  
        bpo::store(parse_command_line(argc, argv, opt), vm);  
    }  
    catch(...){  
        std::cout << "输入的参数中存在未定义的选项！\n";  
        return 0;  
    }  
    //参数解析完成后，通知variables_map去更新所有的外部变量
    //这句话执行后, 会使得apple_num和orange_num的值自动更新为选项指定的值   
    bpo::notify(vm);  

    if(vm.count("help") ){  
        std::cout << opt << std::endl;  
        return 0;  
    }  
    if(vm.count("address") ){  
        std::cout << "生产地为：";  
        //遍历选项值  
        for(auto& str : vm["address"].as<std::vector<std::string> >() )  
            std::cout << str << " ";  
        std::cout << std::endl;   
    }  
    std::cout << "苹果的数量:" << apple_num << std::endl;  
    std::cout << "橘子的数量:" << orange_num << std::endl;  
    std::cout << "总数量数量:" << orange_num + apple_num << std::endl;  
    return 0;  
}  
