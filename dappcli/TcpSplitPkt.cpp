 
#include "TcpSplitPkt.h"



CTcpSplitPkt::CTcpSplitPkt(  )  
{
	m_pTcpBuf = new BYTE[RECV_SPLI_BUF_SIZE];
	m_nLeftLen = 0;
}

void    CTcpSplitPkt::SplitPkt(BYTE*&  pBuf  , int & nDataSize )
{
	
	NET_PKG_HEAD * pPack = (NET_PKG_HEAD *) pBuf;
	
	Decode(pBuf ,pPack->nPackageLength );
	
	pBuf+= pPack->nPackageLength;
	nDataSize -= pPack->nPackageLength;
	
}	

void    CTcpSplitPkt::Decode(BYTE * pBuf ,int nPktLen )
{
    //m_pSplitObj->DealCliPkt(pBuf,nPktLen); 
    request_handler_.handle_request(request_, reply_);
	
}

bool  CTcpSplitPkt::IsFullPkg(BYTE *& pReadPos,int & nReadLen)
{
	NET_PKG_HEAD * pPack;
	while(nReadLen > 4) // 
	{
		if(CHECK_HEAD_FLAG(pReadPos)  )
		{
			pPack = (NET_PKG_HEAD *) pReadPos;
			if( nReadLen  < sizeof(NET_PKG_HEAD))
			{
				return false;
			}
			// 
			if(pPack->nPackageLength > nReadLen ) //  
			{
				if(pPack->nPackageLength >RECV_HALF_SIZE) //  
				{
					pReadPos++;
					nReadLen--;
					continue;
				}
				return false;
			}
			//  
			return true;
		}
		else
		{
			pReadPos++;
			nReadLen--;
		}		
	}
	return false;
}

// pTcpBuf two TCP_RECV_BUF_LEN length
int  CTcpSplitPkt::DealConnectData(  BYTE * pData, int nDataSize  )
{
	
	BYTE*  pReadPos = NULL;	
	BYTE * pTcpBuf = m_pTcpBuf;
	int ret = 1;
	nRetLen= nDataSize;
	if(nRetLen == 0)
	{	
		return 0;
	}
	
	
	if(m_nLeftLen >RECV_HALF_SIZE ){
		m_nLeftLen =0;// 
		return 0;
	}
	
	memcpy(pTcpBuf +m_nLeftLen,pData,nDataSize);
		
	m_nLeftLen = m_nLeftLen + nRetLen;
	
	
	if(m_nLeftLen > RECV_HALF_SIZE  + nRetLen  )
	{
		return 0; 	
	}

	
	pReadPos = pTcpBuf;
	int nReadLen = m_nLeftLen;

	while(1)
	{
		if(IsFullPkg(pReadPos, nReadLen) == false)
		{
			if((m_nLeftLen - nReadLen) >0 && nReadLen>0) // 
			{
				memmove(pTcpBuf ,pReadPos,nReadLen);				
			}
			m_nLeftLen = nReadLen;
			break;
		}
		SplitPkt(pReadPos ,nReadLen );
		
		if(nReadLen==0 ) // all pkg deal
		{
            ret= 2;
		}	
	}
	return ret;
}


