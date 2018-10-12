#ifndef _NETDLL_NET_PDU_TYPE_H_
#define _NETDLL_NET_PDU_TYPE_H_
	
#include "ostypedef.h"

#define	BUF_LENGTH_1K		1024
#define	BUF_LENGTH_2K		2*1024
#define	BUF_LENGTH_4K		4*1024
#define	BUF_LENGTH_8K		8*1024
#define	BUF_LENGTH_16K		16*1024



//NET TCP UDP
#define  NET_PACKAGE_HEAD_FLAG		"@#$%"
#define  NET_PACKAGE_TAIL_FLAG		"%$#@"

// 协议pdu 中间传送的pdu
#define  SET_HEAD_FLAG(head) {*(head)='@';*(head+1)='#';*(head+2)='$';*(head+3)='%';}
#define  SET_MEMPDU_FLAG(head) {*(head)='#';*(head+1)='#';*(head+2)='@';*(head+3)='@';}
#define  SET_TAIL_FLAG(tail) {*(tail)='%';*(tail+1)='$';*(tail+2)='#';*(tail+3)='@';}
#define  CHECK_HEAD_FLAG(head)  (*(head)=='@'&&*(head+1)=='#'&&*(head+2)=='$'&&*(head+3)=='%')

#pragma	pack(1)	

typedef struct
{  
        int      nPackageLength;       
        char     szStartMark[4];    
        int      nServerType;          

        union
        {
                int      nLinkStatusCode;               //ping鍖呯殑閾捐矾杩炴帴鐘舵�佸瓧
                char szData[4];                 //姝ｅ父鍖呯殑鏁版嵁瀹為檯闀垮害
        }u;			
}NET_PKG_HEAD;

typedef  struct
{
	int   cmdtype;  // 
	WORD  dataLen;  // << 63*1024
	WORD  flag;     // 0x01: head  0x02 :body 0x04: tail
	char  context[4]; // 

}FILE_SCAN_STRU;

enum SCAN_CMD_TYPE
{
	CMD_PING           = 0,
	CMD_DIR_REQ_SCAN   = 1, //
	CMD_DIR_RES_SCAN   = 2, //
	CMD_FILE_REQ_TRANS = 3, //
	CMD_FILE_RES_TRANS = 4, //
	

	CMD_SCREEN_REQ_COPY = 7, //
	CMD_SCREEN_RES_COPY = 8, //

	CMD_SEND_FILE_REQ   = 9,  //
	CMD_SEND_FILE_RES   = 10,//
    CMD_REQ_VERSION     = 11,
    CMD_RES_VERSION     = 12,
    
    CMD_REQ_CMD_EXEC    = 13, // do cmd exec 
    CMD_RES_CMD_EXEC    = 14, // do cmd exec
    
	CMD_REQ_FAILED      = 99,//

};

typedef  struct
{
	int   cmdtype;  // 
	WORD  dataLen;  //  << 63*1024
	WORD  flag;     // 0x01: head  0x02 :body 0x04: tail
	char  context[4]; //

}SCAN_FILE_RESP_STRU;




#pragma pack()

#endif  //_NETDLL_NET_PDU_TYPE_H_

