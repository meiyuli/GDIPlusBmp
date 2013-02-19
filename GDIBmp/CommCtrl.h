#pragma once
#include "ComConfig.h"

/*
 *	\brief ����ͨ�Žӿ�
 */
class CCommCtrl{
public:
	CCommCtrl();
	virtual ~CCommCtrl();
public:
	// �򿪴���
	int OpenCom(LPCTSTR com);

	// д����
	int WriteCom(const void *,DWORD);

	// ������
	int ReadCom(void *,DWORD);

	int CloseCom();
protected:
private:
	// ���ھ������
	HANDLE m_hCom;
	// ���ڼ����߳�
	HANDLE m_hComWatchThread;
};