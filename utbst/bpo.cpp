#include <iostream>  
#include <vector>  
#include <string>  
#include <boost/program_options.hpp>  

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

    return 0;
}


int main(int argc, char const *argv[])  
{  
    //�ⲿ���������ڱ����ȡ�Ĳ���ֵ  
    int apple_num = 0, orange_num = 0;  
    std::vector<std::string> addr;  
    bpo::options_description opt("all options");  

    opt.add_options()  
    //ָ���ò�����Ĭ��ֵ 
    // "apple,a" : ָ��ѡ���ȫд��ʽΪ --apple, ��д��ʽΪ -a
    //value<type>(ptr) : ptrΪ��ѡ���Ӧ���ⲿ�����ĵ�ַ, ����ѡ�������, 
    //��ͨ�������notify()������ѡ���ֵ�������ⲿ����,�ñ�����ֵ���Զ�����
    //defaut_value(num) : numΪ��ѡ���Ĭ��ֵ, ����������δ�����ѡ��, ���ѡ���ֵȡΪnum
    ("apple,a", bpo::value<int>(&apple_num)->default_value(10), "ƻ��������")  
    ("orange,o", bpo::value<int>(&orange_num)->default_value(20), "���ӵ�����")  
    //�ò�����ʵ������Ϊvector,�����������������ֵ�����Ƕ��,
    //multitoken()�����þ��Ǹ��߱�����,��ѡ��ɽ��ܶ��ֵ  
    ("address", bpo::value<std::vector<std::string> >()->multitoken(), "������")  
    ("help", "����ƻ�������ӵ�������");  

    bpo::variables_map vm;  

    try{  
        bpo::store(parse_command_line(argc, argv, opt), vm);  
    }  
    catch(...){  
        std::cout << "����Ĳ����д���δ�����ѡ�\n";  
        return 0;  
    }  
    //����������ɺ�֪ͨvariables_mapȥ�������е��ⲿ����
    //��仰ִ�к�, ��ʹ��apple_num��orange_num��ֵ�Զ�����Ϊѡ��ָ����ֵ   
    bpo::notify(vm);  

    if(vm.count("help") ){  
        std::cout << opt << std::endl;  
        return 0;  
    }  
    if(vm.count("address") ){  
        std::cout << "������Ϊ��";  
        //����ѡ��ֵ  
        for(auto& str : vm["address"].as<std::vector<std::string> >() )  
            std::cout << str << " ";  
        std::cout << std::endl;   
    }  
    std::cout << "ƻ��������:" << apple_num << std::endl;  
    std::cout << "���ӵ�����:" << orange_num << std::endl;  
    std::cout << "����������:" << orange_num + apple_num << std::endl;  
    return 0;  
}  
