#include <stdlib.h>
#include <string.h>
#include "mystr.h"

//���дMyString������4��������
//��ͨ���캯��

MyString::MyString(const char *str)
{

	if (str == NULL)
	{
		m_data = new char[1]; // �÷ֵ㣺�Կ��ַ����Զ������Ž�����־'\0'��//�ӷֵ㣺��m_data��NULL �ж�
		*m_data = '\0';
	}
	else
	{
	        size_t length = strlen(str);
		m_data = new char[length + 1]; // ���ܼ� NULL �ж������
		strcpy(m_data, str);
	}

}

MyString::MyString( MyString &&other)    // �ƶ����캯��
{
	m_data = other.m_data;
	other.m_data = NULL;

}
// MyString����������
MyString::~MyString(void)
{
	delete[] m_data; // ��delete m_data;
	m_data = NULL;
}
//�������캯��

MyString::MyString(const MyString &other)  // �÷ֵ㣺�������Ϊconst��
{
	size_t length = strlen(other.m_data);
	m_data = new char[length + 1]; //�ӷֵ㣺��m_data��NULL �ж�
	strcpy(m_data, other.m_data);
}

MyString & MyString::operator = (const MyString &other) // �÷ֵ㣺�������Ϊconst ��
{

	if (this == &other)                  //�÷ֵ㣺����Ը�ֵ
		return *this;
	delete[] m_data;            //�÷ֵ㣺�ͷ�ԭ�е��ڴ���Դ
	size_t length = strlen(other.m_data);
	m_data = new char[length + 1]; //�ӷֵ㣺��m_data��NULL �ж�
	strcpy(m_data, other.m_data);
	return *this;
};  //�÷ֵ㣺���ر����������  */

//�ƶ���ֵ����� 
MyString& MyString::operator=(MyString&& other)
{
	if (this == &other)
		return *this;
	if (m_data)
		delete[] m_data;
 
	m_data = other.m_data;	 
	other.m_data = nullptr;
 
	return *this;
}



