#include "CommCtrl.h"

CCommCtrl::CCommCtrl()
{
	m_hCom = INVALID_HANDLE_VALUE;
	m_hComWatchThread = INVALID_HANDLE_VALUE;
}

CCommCtrl::~CCommCtrl()
{

}

int CCommCtrl::OpenCom(LPCTSTR com)
{
	m_hCom = CreateFile(com,		// COM1口
		GENERIC_READ | GENERIC_WRITE,	// 允许读和写
		0,	// 独占方式
		NULL,
		OPEN_EXISTING,  // 打开而不是创建
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	// 重叠方式
		NULL
		);

	if (INVALID_HANDLE_VALUE == m_hCom)
	{
		// 打开串口失败
		//AfxMessageBox(_T("打开com1失败"));
		return -1;
	}

	SetupComm(m_hCom,100,SIZE_SEND_BUFFER);	// 输入缓冲区和输出缓冲区的大小都是100

	COMMTIMEOUTS TimeOuts;
	// 设定读超时
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	// 在读一次输入缓冲区的内容后读操作就立即返回，
	// 而不管是否读入了要求的字符。

	// 设置写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(m_hCom,&TimeOuts);

	DCB dcb;
	GetCommState(m_hCom,&dcb);
	dcb.BaudRate = CBR_9600;		// 波特率为9600
	dcb.ByteSize = 8;				// 每个字节有8位
	dcb.Parity = NOPARITY;			// 无奇偶校验位
	dcb.StopBits = ONESTOPBIT;		// 一个停止位
	SetCommState(m_hCom,&dcb);

	PurgeComm(m_hCom,PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	return 1;
}

int CCommCtrl::WriteCom(const void *pBuffer,DWORD dwBytesWrite)
{
	OVERLAPPED m_osWrite;
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	//DWORD dwBytesWrite;
	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
	bWriteStat = WriteFile(m_hCom,pBuffer,
		dwBytesWrite,&dwBytesWrite,&m_osWrite);

	if (!bWriteStat)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent,1000);
		}
	}
	return 1;
}

int CCommCtrl::ReadCom(void* pBuffer,DWORD dwBytesRead)
{
	OVERLAPPED m_osRead;
	memset(&m_osRead,0,sizeof(OVERLAPPED));
	m_osRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bReadStat;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
	dwBytesRead = min(dwBytesRead,(DWORD)ComStat.cbInQue);
	bReadStat = ReadFile(m_hCom,pBuffer,
		dwBytesRead,&dwBytesRead,&m_osRead);

	if (!bReadStat)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osRead.hEvent,2000);
		}
	}

	PurgeComm(m_hCom,PURGE_TXABORT | PURGE_TXCLEAR |
		PURGE_RXCLEAR | PURGE_RXABORT);

	return 1;
}

int CCommCtrl::CloseCom()
{
	if (INVALID_HANDLE_VALUE != m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = INVALID_HANDLE_VALUE;
	}
	
	return 1;
}