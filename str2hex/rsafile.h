
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;


std::string EncodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData );
std::string DecodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData );
int   readstrfiletohex( char *pinfile, char * poutfile  );
int   readbintohex( char *pinfile, char * poutfile  );

