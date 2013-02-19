
// GDIBmpDlg.h : header file
//

#pragma once
#include "CommCtrl.h"
#include "BitmapView.h"
// CGDIBmpDlg dialog
class CGDIBmpDlg : public CDialog
{
// Construction
public:
	CGDIBmpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GDIBMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	afx_msg void OnBtnOpenClick();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	/**
    *	\brief �̴߳�����
    */
    static unsigned __stdcall ThreadFunc(void* arg);

	/*
	 *	\brief д����ͼƬ��С
	 */
	int SendBufferSize();

	/*
	 *	\brief ���ұ���COM��
	 */
	int FindLocalCOM();

	/*
	 *	\brief ��������
	 */
	int Load(CImage &image);
private:
	LPBYTE m_lpBits;
	DWORD   m_lSize;
	CComboBox m_Comm;

	// ����ͨ�Ŷ���
	CCommCtrl m_CommCtrl;

	// ͼƬ���
	CStatic m_Width;

	// ͼƬ�߶�
	CStatic m_Height;

	CBitmapView m_BmpView;

	CString m_filePath;
public:
	afx_msg void OnBnClickedBtnComm();
	afx_msg void OnDestroy();
};
