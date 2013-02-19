
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
    *	\brief 线程处理函数
    */
    static unsigned __stdcall ThreadFunc(void* arg);

	/*
	 *	\brief 写发送图片大小
	 */
	int SendBufferSize();

	/*
	 *	\brief 查找本地COM口
	 */
	int FindLocalCOM();

	/*
	 *	\brief 加载数据
	 */
	int Load(CImage &image);
private:
	LPBYTE m_lpBits;
	DWORD   m_lSize;
	CComboBox m_Comm;

	// 串口通信对象
	CCommCtrl m_CommCtrl;

	// 图片宽度
	CStatic m_Width;

	// 图片高度
	CStatic m_Height;

	CBitmapView m_BmpView;

	CString m_filePath;
public:
	afx_msg void OnBnClickedBtnComm();
	afx_msg void OnDestroy();
};
