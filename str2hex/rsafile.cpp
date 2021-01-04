#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
 
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;
 
//加密
std::string EncodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData )
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPubKeyFile = fopen(strPemFileName.c_str(), "rb");
	if( hPubKeyFile == NULL )
	{
		assert(false);
		return ""; 
	}
	std::string strRet;
	RSA* pRSAPublicKey = RSA_new();
	if(PEM_read_RSA_PUBKEY(hPubKeyFile, &pRSAPublicKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}
 
	int nLen = RSA_size(pRSAPublicKey);
	char* pEncode = new char[nLen + 1];
	int ret = RSA_public_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPublicKey, RSA_PKCS1_PADDING);
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(pRSAPublicKey);
	fclose(hPubKeyFile);
	CRYPTO_cleanup_all_ex_data(); 
	return strRet;
}
 
//解密
std::string DecodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData )
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPriKeyFile = fopen(strPemFileName.c_str(),"rb");
	if( hPriKeyFile == NULL )
	{
		assert(false);
		return "";
	}
	std::string strRet;
	RSA* pRSAPriKey = RSA_new();
	if(PEM_read_RSAPrivateKey(hPriKeyFile, &pRSAPriKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}
	int nLen = RSA_size(pRSAPriKey);
	char* pDecode = new char[nLen+1];
 
	int ret = RSA_private_decrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pDecode, pRSAPriKey, RSA_PKCS1_PADDING);
	if(ret >= 0)
	{
		strRet = std::string((char*)pDecode, ret);
	}
	delete [] pDecode;
	RSA_free(pRSAPriKey);
	fclose(hPriKeyFile);
	CRYPTO_cleanup_all_ex_data(); 
	return strRet;
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
 
int main1()
{
	//原文
	const string one = "skl;dfhas;lkdfhslk;dfhsidfhoiehrfoishfsidf";
	cout << "one: " << one << endl;
 
	//密文（二进制数据）
	string two = EncodeRSAKeyFile("pubkey.pem", one);
	cout << "two: " << two << endl;
 
	//顺利的话，解密后的文字和原文是一致的
	string three = DecodeRSAKeyFile("prikey.pem", two);
	cout << "three: " << three << endl;
	return 0;
}
