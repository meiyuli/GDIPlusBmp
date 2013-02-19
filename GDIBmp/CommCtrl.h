#pragma once
#include "ComConfig.h"

/*
 *	\brief 串口通信接口
 */
class CCommCtrl{
public:
	CCommCtrl();
	virtual ~CCommCtrl();
public:
	// 打开串口
	int OpenCom(LPCTSTR com);

	// 写串口
	int WriteCom(const void *,DWORD);

	// 读串口
	int ReadCom(void *,DWORD);

	int CloseCom();
protected:
private:
	// 串口句柄对象
	HANDLE m_hCom;
	// 串口监视线程
	HANDLE m_hComWatchThread;
};