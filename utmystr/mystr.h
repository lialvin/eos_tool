#pragma once
#include <iostream>  
using namespace std;
class MyString
{
public:
	MyString(const char *str = NULL);// ��ͨ���캯��
	MyString(const MyString &other);    // �������캯��
	MyString(  MyString &&other);    // �ƶ����캯��
	~MyString(void);    // ��������
	MyString&  operator=(MyString&& other);
	MyString & operator = (const MyString &other); // ��ֵ����
	friend ostream & operator<< (ostream &os,const MyString &st)
	{
		os << st.m_data << endl;
		return os;
	}

	  
private:
	char *m_data;// ���ڱ����ַ���
};


