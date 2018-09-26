#ifndef _MONITOR_CLI_TASK_BIZ_MANAGER_H_
#define _MONITOR_CLI_TASK_BIZ_MANAGER_H_
class  CTaskScan;
class  CBizDeal 
{
public:
	CBizDeal();
 
	void         Init(CCliTask   * pTaskScan);
	void         Run(BYTE*,int);

	// 
	int          BeginReqFile(char * szFile);
	// 
	int          BeginReqDir(char * Dir);
	int          BeginReqExecCmd(char * szFile);
	int          BeginReqScreen(char * szFile);
private:
	CCliTask   * m_pTaskScan;
	void         ScanDir(char * context);
	void         TransFile(char * context);
	int          SendFailedPkg();
	bool         SendBinFile(const char * szOrigFile);
	bool         RecvBinFile(char * szDestFile, WORD flag, BYTE * pBuf, int nLen);
	bool         RecvDirFile(char * szDestFile, WORD flag, BYTE * pBuf, int nLen);
	void         SendCmdPkg(int nCmdType, WORD flag, BYTE * pBuf, int nLen,const char * fileName);
	void         RecvCmdExecRes(WORD flag, BYTE * pBuf, int nLen);
	void         RecvCmdExecFail(WORD flag, BYTE * pBuf, int nLen);

	void         RecvCmdScreenReq(WORD flag, BYTE * pBuf, int nLen);
	void         RecvCmdScreenRes(WORD flag, BYTE * pBuf, int nLen);
	int          ExecCmdReq(char * context, int dataLen);
	//BOOL         SaveBitmapToFile(char * lpszFilePath, HBITMAP hBm);
	void         ScreenShot(char * filename);
	BYTE        *m_pSendBuf;
	bool         m_bDataThreadRunFlag;
	bool         m_bRequestThreadRunFlag;
	char       * m_pFileName;
	char         m_szTranFile[256];//放置临时文件。
};

#endif
