
#include <list>  
#include <string>  
#include <iostream>  
#include <boost/multi_index_container.hpp>  
#include <boost/multi_index/ordered_index.hpp>  
#include <boost/multi_index/identity.hpp>  
#include <boost/multi_index/member.hpp>  
  
#include <boost/lambda/lambda.hpp>  
 
  
#pragma region ���� employee   
//ʹ�����ֿռ���Ϊ�˷�ֹ�����������Ƴ�ͻ  
namespace kagula  
{  
    namespace datatype  
    {  
        //Ϊ�˺���Ĵ�����ͨ��id��name����ȡ��ͼ���������������ṹ  
        struct id{};  
        struct name{};  
  
        //employee������ʾ�������б�Ľṹ  
        struct employee  
        {  
            int          id;  
            std::string name;  
  
            employee(int id, const std::string& name) :id(id), name(name){}  
  
            //����<����������ú�����Ϊid����ͼ����id�ֶε���������  
            bool operator<(const employee& e)const{ return id<e.id; }  
            //����<=�����������Ϊ�˵õ�ָ��id�ֶ�ֵ��Χ�ļ�¼  
            bool operator<=(const employee& e)const{ return id<=e.id; }  
            //����<<�����������Ϊ�����Ƿ����ӡ��¼������  
            friend std::ostream& operator<<(std::ostream& os, const employee& dt);  
        };  
        std::ostream& operator<<(std::ostream& os, const employee& dt)  
        {  
            os << "[" << dt.id << ',' << dt.name.c_str() << "]";  
            return os;  
        }  
        //����Ĵ��룬����ָ����¼name�ֶε�ֵҪ�õ�change_name��  
        //ͨ�����ʾ�������֪������޸ķ������������ģ�ָ����¼�������ֶ�ֵ  
        struct change_name  
        {  
            change_name(const std::string& new_name) :new_name(new_name){}  
  
            void operator()(employee& e)  
            {  
                e.name = new_name;  
            }  
  
        private:  
            std::string new_name;  
        };  
  
        // �������id��name�ؼ��ʵĶ�ֵ������������  
        // ���������id��name������ͼ  
        typedef boost::multi_index::multi_index_container<  
            employee,  
  
            boost::multi_index::indexed_by<  
            //��һ����ͼ��ʹ��employeeʵ����Ϊkey�����Բ�����employee::operator<���������������˻���id�ֶ�  
            //boost::multi_index::ordered_unique�е�uniqueָ��keyֻ��Ψһ���������޷�����id�ֶ�ֵ��ͬ�ļ�¼��  
            //boost::multi_index::ordered_unique�е�orderedָ����һ����ͼ������key���������У���������������˳�����ҵ�  
            //����������Զ�����boost::multi_index::ordered_unique���͵���ͼ  
            //boost::multi_index::identity�Ѷ�����Ϊ������key  
            //boost::multi_index::tag<id>��Ϊ���Ժ���ͨ��id��ȡ��һ����ͼ  
            //�����ȥ��boost::multi_index::tag<id>������㲻��Ҫ��������id��ȡ��ͼ�Ļ�  
            boost::multi_index::ordered_unique<boost::multi_index::tag<id>, boost::multi_index::identity<employee> >,  
            //�ڶ�����ͼ������key��employee�����name�ֶΣ���������key������std::string  
            //����ʹ����std::string::operator<�������������  
            //boost::multi_index::ordered_non_unique�е�non_uniqueָ�����key�������ظ�.  
            //boost::multi_index::ordered_non_unique�е�orderedָ���ڶ���ͼ�������key��������  .  
            //����㲻��Ҫ��ͼ����key��˳�����У�������hashed����ordered������  
            //boost::multi_index::ordered_non_unique ������Ϊ boost::multi_index::hashed_non_unique  
            //�Ϳ��Ա���Բ��������������Ҫ����<boost/multi_index/hashed_index.hpp>ͷ�ļ�  
            //boost::multi_index::member�Ѷ���ĳ�Ա��Ϊ������key  
            //boost::multi_index::tag<name>��Ϊ���Ժ�Ĵ�����ͨ��name��ȡ�ڶ�����ͼ������ͼ�ܶ��ʱ��������ܽ���ǳ�����  
            boost::multi_index::ordered_non_unique<boost::multi_index::tag<name>, boost::multi_index::member<employee, std::string, &employee::name> >  
            //������ͼ�Ķ��������������﷨��ʽ  
            //(ordered_unique | ordered_non_unique) <[(key extractor)[, (comparison predicate)]]>  
            //��Ϊkey�Ķ������ͱ���ʵ��<�����������������ָ����comparison predicate.  
            >  
  
        > employee_set;  
    }  
}  
#pragma endregion  
  
using namespace kagula::datatype;  
  
  
void print_out_by_id(const employee_set& es)  
{  
    //�õ�id��ͼ�����ǻ���id�ֶεģ�  
    const employee_set::index<id>::type& id_index = es.get<id>();  
      
    //����ע�͵��Ĵ��룬�ǻ������������ͼ��0�����һ����ͼ��1����ڶ�����ͼ����������  
    //const employee_set::nth_index<0>::type& id_index = es.get<0>();  
      
    //����ͬstd::set����һ���ķ�ʽ��ӡԪ��  
    std::copy(  
        id_index.begin(), id_index.end(),  
        std::ostream_iterator<employee >(std::cout));  
    std::cout << std::endl << std::endl;  
}  
  
void print_out_by_name(const employee_set& es)  
{  
    //�õ�name��ͼ�����ǻ���name�ֶεģ�  
    const employee_set::index<name>::type& name_index = es.get<name>();  
  
    //����ע�͵��Ĵ��룬�ǻ������������ͼ������ڶ�����ͼ����������  
    //const employee_set::nth_index<1>::type& name_index = es.get<1>();  
  
    //����ͬstd::set����һ���ķ�ʽ��ӡԪ��  
    std::copy(  
        name_index.begin(), name_index.end(),  
        std::ostream_iterator<employee>(std::cout));  
    std::cout << std::endl << std::endl;  
}  
  
//������������  
void CreateSample(employee_set& table)  
{  
    table.insert(employee(0, "Z"));  
    table.insert(employee(1, "Z"));  
    table.insert(employee(2, "X"));  
    //Error:����������¼�޷��ɹ����룬��Ϊ�ڽ�����һ����ͼʱָ����id����Ψһ  
    //      ����ִ�в�����Ϊ2�ļ�¼��û��Ч��, ��table��idΪ2�ļ�¼������ԭ����ֵ  
    //      ���Ǵ���Ҳ�����׳�Excetion��  
    //table.insert(employee(2, L"�²����idΪ2�ļ�¼"));  
  
    //����name�ֶε�ֵΪ"Z"�ɹ�  
    //��Ȼname�ֶε�ֵ�Ѿ����ڣ��������ڶ���ͼ��ʱ��ָ����name�ֶε�ֵ�������ظ�  
    //�����������Ӽ�¼���ܿ�����������  
    table.insert(employee(3, "Z"));  
  
  
    table.insert(employee(100, "Judy Smith"));  
    table.insert(employee(101, "Judy Smith"));  
  
    table.insert(employee(200, "Anna Jones"));  
    table.insert(employee(201, "Anna Jones"));  
}  
  
  
void select_stat(employee_set& table)  
{  
    std::cout << "��һ����ͼ����id�ֶε���������" << std::endl;   
    print_out_by_id(table);  
  
    {  
        std::cout << "��һ����ͼ����id�ֶεĽ����ӡ" << std::endl;  
        const employee_set::index<id>::type&  viewId = table.get<id>();  
        std::copy(viewId.rbegin(), viewId.rend(),  
            std::ostream_iterator<employee>(std::cout));  
        std::wcout << std::endl << std::endl;  
    }  
  
    std::cout << "�ڶ�����ͼ����name�ֶε���������" << std::endl;  
    print_out_by_name(table);  
  
    {  
        std::cout << "������id==2�ļ�¼" << std::endl;  
        employee cond(2, "");  
        employee_set::index<id>::type::iterator iter = table.find(cond);  
        std::cout << *iter << std::endl << std::endl;  
    }  
  
    {  
        std::cout << "ͨ��boost::lambda������ָ��id��Χ�ļ�¼����" << std::endl;;  
        std::pair<employee_set::iterator, employee_set::iterator> p;  
        p = table.range(employee(100, "") <= boost::lambda::_1, boost::lambda::_1 <= employee(200, "")); // 100<= x <=200  
        //���汻ע�͵��Ĵ��룬��ʾ�����ȡָ����Χ�ļ�¼  
        //p = table.range(employee(100, L"")<boost::lambda::_1, boost::lambda::_1<employee(200, L""));   // 100<  x < 200  
        //p = table.range(employee(100, L"") <= boost::lambda::_1, boost::lambda::_1<employee(200, L""));  // 100<= x < 200  
        //p = table.range(employee(100, L"") <= boost::lambda::_1, boost::multi_index::unbounded); // 100 <= x  
        //p = table.range(boost::multi_index::unbounded, boost::lambda::_1<employee(200, L""));  //   x <  200  
        //p = table.range(boost::multi_index::unbounded, boost::multi_index::unbounded); // equiv. to std::make_pair(s.begin(),s.end())       
        for (employee_set::iterator it = p.first; it != p.second; it++)  
        {  
            std::cout << *it << " , ";  
        }  
        std::cout << std::endl << std::endl;  
    }  
  
    {  
        std::cout << "������name==Judy Smith�ĵ�һ����¼" << std::endl;  
        const employee_set::index<name>::type& viewName = table.get<name>();  
        employee_set::index<name>::type::iterator it = viewName.find("Judy Smith");  
        std::cout << *it << std::endl << std::endl;  
  
        std::cout << "ͳ��name==Judy Smith�ļ�¼�ж���" << std::endl;  
        unsigned int count = viewName.count("Judy Smith");  
        std::cout << count << std::endl << std::endl;  
    }  
  
    {  
        std::cout << "������name==z�ļ�¼����" << std::endl;;  
        const employee_set::index<name>::type& viewName = table.get<name>();  
        std::pair<employee_set::index<name>::type::iterator, employee_set::index<name>::type::iterator> p;  
  
        p = viewName.equal_range("Z");   
  
        for (employee_set::index<name>::type::iterator it = p.first; it != p.second; it++)  
        {  
            std::cout << *it << " , ";  
        }  
        std::cout << std::endl << std::endl;  
    }  
  
}  
  
void delete_stat(employee_set& table)  
{  
    //�ӱ���ɾ��idֵΪ2�ĵļ�¼��name�ֶο���Ϊ����ֵ  
    {  
        std::cout << "ɾ��id==2�ļ�¼" << std::endl;  
        employee cond(2, "");  
        int nCount = table.erase(cond);   
        //nCountΪ1����Ϊ���ǵ�idֵ��Ψһ�ġ�  
        //���id�ֶβ���Ψһ�ģ����ǿ���ͨ���ж�nCount,ɾ�����з��������ļ�¼  
        std::cout << "��" << nCount << "����¼��ɾ����" << std::endl << std::endl;  
    }  
  
    //�ӱ���ɾ��name�ֶ�ֵΪZ��ȫ����¼  
    {  
        std::cout << "ɾ��name==Z�����м�¼" << std::endl;  
        employee_set::index<name>::type& viewName = table.get<name>();  
        while ( table.erase(*viewName.find("Z")) > 0 );  
        print_out_by_id(table);  
    }  
  
    //���½�������  
    table.clear();  
    CreateSample(table);  
  
    //ɾ��id��ָ����Χ�ļ�¼  
    std::cout << "ɾ��100<= id <=200�����м�¼" << std::endl;  
    std::pair<employee_set::iterator, employee_set::iterator> p;  
    p = table.range(employee(100, "") <= boost::lambda::_1, boost::lambda::_1 <= employee(200, "")); // 100<= x <=200  
    table.erase(p.first, p.second);  
    print_out_by_id(table);  
}  
  
void update_stat(employee_set& table)  
{  
    std::cout << "�滻��ΪAnna Jones�ļ�¼ΪAnna Smith������ֻ�޸ķ��������ĵ�һ����¼!" << std::endl;  
    typedef employee_set::index<name>::type employee_set_by_name;  
    //��ΪҪ�޸�iter��ָ������������������䲻��ʹ��const����  
    employee_set_by_name& name_index = table.get<name>();  
  
    employee_set_by_name::iterator it = name_index.find("Anna Jones");  
    //�޸�key��ֵ��key������Զ�д  
    name_index.modify_key(it, boost::lambda::_1 = "Anna Smith");  
    print_out_by_id(table);  
  
    std::cout << "����ΪAnna Smith�ĵ�һ����¼�޸�ΪAnna Jones" << std::endl;  
    //�������ַ��������޸Ķ���ĳ�����Ե�ֵ��������Ҫ����change_name��  
    it = name_index.find("Anna Smith");  
    name_index.modify(it, change_name("Anna Jones"));  
    print_out_by_id(table);  
  
  
    {  
        std::cout << "�޸�����name==Z�ļ�¼Ϊkagula" << std::endl;  
        employee_set_by_name& viewName = table.get<name>();  
        employee_set_by_name::iterator it;  
        while ( (it = viewName.find("Z")) != viewName.end() )  
        {  
            viewName.modify(it, change_name("kagula"));  
        }  
        print_out_by_id(table);  
  
        //Warnning:  
        //��Ҫ�����������У�ʹ������Ĵ������޸����з��������ļ�¼  
        //��Ϊ���û���ϱߵĴ���Σ�����Ĵ���ֻ���޸ĵ�һ�����������ļ�¼  
        //�������˳�ѭ����  
        std::cout << "�޸�����name==kagula�ļ�¼ΪZ" << std::endl;  
        viewName = table.get<name>();  
        std::pair<employee_set_by_name::iterator, employee_set_by_name::iterator> p;  
        p = viewName.equal_range("kagula");  
        for (employee_set_by_name::iterator it = p.first; it != p.second; it++)  
        {  
            viewName.modify(it, change_name("Z"));  
        }  
        print_out_by_id(table);  
    }  
  
  
    //��Ϊ�޸ļ�¼��ֵ��ͨ��it�������Կ���ʹ��select_stat���ܵ�֪ʶ�޸�ָ����Χ�ļ�¼  
}  
  
int main(int argc, char**  argv)  
{  
    //ʹstd::wcout�ܹ���ӡ����  
   // std::wcout.imbue(std::locale(std::locale("chs")));  
  
    //��������  
    //�ȼ�SQL,Add������ع���  
    employee_set table;  
    CreateSample(table);  
  
    //������Եȼ�SQL,Select������ع���  
    select_stat(table);  
      
    //������Եȼ�SQL,Update������ع���  
    update_stat(table);  
  
    //������Եȼ�SQL,Delete������ع���  
    delete_stat(table);  
  
    //��ͣ���������������  
    system("pause");  
    return 0;  
}  
