
// GDIBmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GDIBmp.h"
#include "GDIBmpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIBmpDlg dialog

typedef struct{
	byte red;
	byte green;
	byte blue;
}PIEXY_VALUE;


CGDIBmpDlg::CGDIBmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGDIBmpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lpBits = NULL;
}

void CGDIBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO_COMM,m_Comm);
	DDX_Control(pDX,IDC_CUSTOM_SHOW,m_BmpView);
	DDX_Control(pDX,IDC_EDIT_WIDTH,m_Width);
	DDX_Control(pDX,IDC_EDIT_HEIGHT,m_Height);
}

BEGIN_MESSAGE_MAP(CGDIBmpDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGDIBmpDlg::OnBtnOpenClick)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_COMM, &CGDIBmpDlg::OnBnClickedBtnComm)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGDIBmpDlg message handlers

BOOL CGDIBmpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_lpBits = NULL;
// 	m_Comm.AddString(_T("COM1"));
// 	m_Comm.AddString(_T("COM2"));
// 	m_Comm.AddString(_T("COM3"));
// 	m_Comm.AddString(_T("COM4"));
// 	m_Comm.AddString(_T("COM5"));
	FindLocalCOM();
	if (0 == m_Comm.GetCount())
	{
		m_Comm.AddString(_T("本地无串口!"));
	}
	m_Comm.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGDIBmpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGDIBmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGDIBmpDlg::OnBtnOpenClick()
{

	WCHAR szFilters[]=
		_T("Bitmap Files (*.bmp)|*.bmp|JEPG Files (*.jpeg)|*.jpeg|All Files (*.*)|*.*||");

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg (TRUE, _T("bmp"), _T("*.bmp"),
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if (NULL != m_lpBits)
	{
		delete m_lpBits;
		m_lpBits = NULL;
	}
	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if( fileDlg.DoModal ()==IDOK )
	{
		m_filePath = fileDlg.GetPathName();
		m_BmpView.LoadPicture(m_filePath);
		CImage image;
		image.Load(m_filePath);
		int nWidth = image.GetWidth();	// 获取图像宽度
		int nHeight = image.GetHeight();  // 获取图像高度
		//int nWidthbytes = (image.GetBPP()*nWidth + 31)/32*4;	// 获取图像每一行的字节数
		CString strWidth;
		CString strHeight;
		strWidth.Format(_T("%d"),nWidth);
		strHeight.Format(_T("%d"),nHeight);
		m_Width.SetWindowText(strWidth);
		m_Height.SetWindowText(strHeight);

		CString srcSize;
		srcSize.Format(L"图片大小(X:%d  Y:%d)",nWidth,nHeight);
		((CStatic*)GetDlgItem(IDC_SRC_PIC_SIZE))->SetWindowText(srcSize);
// 		LPBYTE lpBits = (LPBYTE)image.GetPixelAddress(0,nHeight-1);
// 		CFile file;
// 		if(!file.Open(_T("RGB.txt"),CFile::modeWrite | CFile::modeCreate))
// 		{
// 			return ;
// 		}
// 		m_lSize = nHeight * nWidth * sizeof(PIEXY_VALUE);
// 		m_lpBits = new byte[m_lSize];
// 		for(int i = 0; i < nHeight; i++)
// 		{
// 			for(int j = 0; j < nWidth; j++)
// 			{
// 				int nLen;
// 				PIEXY_VALUE piexy;
// 				nLen = i*nWidthbytes + j*3;
// 				piexy.red = lpBits[nLen + 2];
// 				piexy.green = lpBits[nLen + 1];
// 				piexy.blue = lpBits[nLen];
// 				memcpy((void*)(m_lpBits + i*nWidth*sizeof(PIEXY_VALUE) + j*sizeof(PIEXY_VALUE)),(void*)&piexy,sizeof(PIEXY_VALUE));
// 			}
// 		}
// 		
// 		file.Write((void*)m_lpBits,nHeight*nWidth*sizeof(PIEXY_VALUE));
// 		file.Close();
	}
}

void CGDIBmpDlg::OnBnClickedBtnComm()
{
	// TODO: Add your control notification handler code here
	if (m_filePath.IsEmpty())
	{
		AfxMessageBox(_T("请先打开图片数据"));
		return ;
	}

	if (NULL != m_lpBits)
	{
		delete m_lpBits;
		m_lpBits = NULL;
	}
	CImage image;
	image.Load(m_filePath);
	Load(image);

	m_CommCtrl.CloseCom();
	CString str;
	m_Comm.GetLBText(m_Comm.GetCurSel(),str);
	if(m_CommCtrl.OpenCom(str) < 0)
	{
		return ;
	}

	WORD wBuf;
	wBuf = NOTICE_SEND_BUFFER;
	//m_CommCtrl.OpenCom();

	m_CommCtrl.WriteCom(&wBuf,2);

	HANDLE hThread = NULL;
	unsigned threadId;
	hThread = (HANDLE)_beginthreadex(NULL,0,ThreadFunc,(void*)&m_CommCtrl,0,&threadId);

	WaitForSingleObject(hThread,INFINITE);

	CloseHandle(hThread);

	//SendBufferSize();
	// 写图片数据
	int nBufferSize;
	nBufferSize = m_lSize;

	int i = 0;
	while(nBufferSize >= SIZE_SEND_BUFFER)
	{
		m_CommCtrl.WriteCom(m_lpBits + i*SIZE_SEND_BUFFER,SIZE_SEND_BUFFER);
		nBufferSize -= SIZE_SEND_BUFFER;
		i++;
	}
	m_CommCtrl.WriteCom(m_lpBits+i*SIZE_SEND_BUFFER,nBufferSize);

	m_CommCtrl.CloseCom();
}

unsigned CGDIBmpDlg::ThreadFunc(void* arg)
{
	CCommCtrl *pComCtrl = (CCommCtrl *)reinterpret_cast<CCommCtrl*>(arg);

	WORD wBuf = 0x0;
	pComCtrl->ReadCom(&wBuf,2);

	while (START_SEND_BUFFER != wBuf)   // START_SEND_BUFFER
	{
		Sleep(100);
		pComCtrl->ReadCom(&wBuf,2);
	}
	
	return 1;
}

int CGDIBmpDlg::SendBufferSize()
{
	m_CommCtrl.WriteCom((void*)&m_lSize,sizeof(m_lSize));
	return 0;
}

int CGDIBmpDlg::FindLocalCOM()
{
	HKEY hkey;

	long ret0=::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_QUERY_VALUE,&hkey);
	if (ret0!=ERROR_SUCCESS)
	{
		//MessageBox(_T(""));
		return 0;
	}
	TCHAR szBuffer[256];
	TCHAR bData[256];
	DWORD dwData = 256;
	DWORD dwSize=256;
	ZeroMemory(szBuffer,256);
	DWORD dIndex;
	dIndex=0L;
	while(RegEnumValue(hkey,dIndex,szBuffer,&dwSize,NULL,NULL,(LPBYTE)bData,&dwData)==ERROR_SUCCESS)
	{
		m_Comm.AddString((LPCTSTR)bData);
		
		dIndex++;
		ZeroMemory(szBuffer,256); //注意这两行
		dwSize=256;               //
	}

	return 1;
}

void CGDIBmpDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if (NULL != m_lpBits)
	{
		delete m_lpBits;
		m_lpBits = NULL;
	}
	m_CommCtrl.CloseCom();
}

int CGDIBmpDlg::Load(CImage &image)
{
	UpdateData();
	int nHOffset = -1;
	int nWidth,nHeight;

	nWidth = image.GetWidth();	// 获取图像宽度
	nHeight = image.GetHeight();  // 获取图像高度
	int nWidthbytes = (image.GetBPP()*nWidth + 31)/32*4;	// 获取图像每一行的字节数

	LPBYTE lpBits = (LPBYTE)image.GetPixelAddress(0,nHeight-1);

	if (nWidth > GetDlgItemInt(IDC_EDIT_WIDTH))
	{
		nWidth = GetDlgItemInt(IDC_EDIT_WIDTH);
	}

	if (nHeight > GetDlgItemInt(IDC_EDIT_HEIGHT))
	{
		nHOffset = nHeight - GetDlgItemInt(IDC_EDIT_HEIGHT) - 1;
		nHeight = GetDlgItemInt(IDC_EDIT_HEIGHT);
	}
	CFile file;
	if(!file.Open(_T("RGB.txt"),CFile::modeWrite | CFile::modeCreate))
	{
		return -1;
	}
	m_lSize = nHeight * nWidth * sizeof(PIEXY_VALUE);
	m_lpBits = new byte[m_lSize];
	for(int i = 0; i < nHeight; i++)
	{
		for(int j = 0; j < nWidth; j++)
		{
			int nLen;
			PIEXY_VALUE piexy;
			nLen = (nHeight + nHOffset - i)*nWidthbytes + j*3;
			piexy.red = lpBits[nLen + 2];
			piexy.green = lpBits[nLen + 1];
			piexy.blue = lpBits[nLen];
			memcpy_s((void*)(m_lpBits + i*nWidth*sizeof(PIEXY_VALUE) + j*sizeof(PIEXY_VALUE)),
				sizeof(m_lpBits),(void*)&piexy,sizeof(PIEXY_VALUE));
		}
	}
	//m_BmpView.SetBitmap(nWidth,nHeight,m_lpBits);
	file.Write((void*)m_lpBits,nHeight*nWidth*sizeof(PIEXY_VALUE));
	file.Close();
	return 1;
}

int CGDIBmpDlg::SendHeader()
{
	UINT nHeight;
	UINT nWidth;
	nHeight = GetDlgItemInt(IDC_EDIT_HEIGHT);
	nWidth = GetDlgItemInt(IDC_EDIT_WIDTH);

	return 0;
}