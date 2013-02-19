#include "stdafx.h"
#include "GDIBmp.h"
#include "BitmapView.h"

CBitmapView::CBitmapView()
{
	RegisterWindowClass();
}

CBitmapView::~CBitmapView()
{

}

BOOL CBitmapView::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst,BITMAPVIEWER_CLASSNAME,&wndcls)))
	{
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = BITMAPVIEWER_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CBitmapView,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CBitmapView::OnPaint()
{
	if (m_Bitmap.GetSafeHandle() != NULL)
	{
		CPaintDC dc(this);

		CDC MemDC;
		if (!MemDC.CreateCompatibleDC(&dc))
			return ;

		CRect rect;
		GetClientRect(&rect);

		BITMAP bm;
		m_Bitmap.GetBitmap(&bm);

		CBitmap* pOldBmp = (CBitmap*) MemDC.SelectObject(&m_Bitmap);
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,bm.bmWidth,
			bm.bmHeight,SRCCOPY);
		MemDC.SelectObject(pOldBmp);
	}
}

BOOL CBitmapView::OnEraseBkgnd(CDC* pDC)
{
	if (m_Bitmap.GetSafeHandle() != NULL)
		return TRUE;

	return CWnd::OnEraseBkgnd(pDC);
}

void CBitmapView::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
}

BOOL CBitmapView::Create(CWnd* pParentWnd,const RECT& rect, UINT nID, DWORD dwStyle /* = WS_VISIBLE */)
{
	return CWnd::Create(BITMAPVIEWER_CLASSNAME,_T(""),dwStyle,rect,pParentWnd,nID);
}

BOOL CBitmapView::SetBitmap(UINT nIDResource)
{
	m_Bitmap.Detach();
	Invalidate(TRUE);
	return m_Bitmap.LoadBitmap(nIDResource);
}

BOOL CBitmapView::SetBitmap(DWORD dwSize,void* lpBits)
{
	return m_Bitmap.SetBitmapBits(dwSize,lpBits);
}

BOOL CBitmapView::SetBitmap(int nWidth,int nHeight,void * lpBits)
{
	CDC *pDC = GetDC();
	
	CRect rect;
	GetClientRect(&rect);
	
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			int nPos = i*nWidth*3 + j*3;
			BYTE r = *((BYTE*)lpBits + nPos);
			BYTE g = *((BYTE*)lpBits + nPos + 1);
			BYTE b = *((BYTE*)lpBits + nPos + 2);
			pDC->SetPixel(j,i,RGB(r,g,b));
			TRACE(_T("%d %d %d\n"),r,g,b);
		}
	}

	ReleaseDC(pDC);
	return FALSE;
}