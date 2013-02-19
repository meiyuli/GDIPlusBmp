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
	m_hCom = CreateFile(com,		// COM1��
		GENERIC_READ | GENERIC_WRITE,	// �������д
		0,	// ��ռ��ʽ
		NULL,
		OPEN_EXISTING,  // �򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	// �ص���ʽ
		NULL
		);

	if (INVALID_HANDLE_VALUE == m_hCom)
	{
		// �򿪴���ʧ��
		//AfxMessageBox(_T("��com1ʧ��"));
		return -1;
	}

	SetupComm(m_hCom,100,SIZE_SEND_BUFFER);	// ���뻺����������������Ĵ�С����100

	COMMTIMEOUTS TimeOuts;
	// �趨����ʱ
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	// �ڶ�һ�����뻺���������ݺ���������������أ�
	// �������Ƿ������Ҫ����ַ���

	// ����д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(m_hCom,&TimeOuts);

	DCB dcb;
	GetCommState(m_hCom,&dcb);
	dcb.BaudRate = CBR_9600;		// ������Ϊ9600
	dcb.ByteSize = 8;				// ÿ���ֽ���8λ
	dcb.Parity = NOPARITY;			// ����żУ��λ
	dcb.StopBits = ONESTOPBIT;		// һ��ֹͣλ
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