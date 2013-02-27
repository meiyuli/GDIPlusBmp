#if !defined(AFX_BITMAPVIEW_H_INCLUDED_)
#define AFX_BITMAPVIEW_H_INCLUDED_

#define BITMAPVIEWER_CLASSNAME  _T("MFCBitmapViewCtrl")   // Window class name

class CBitmapView : public CWnd
{
public:
	CBitmapView();
	virtual ~CBitmapView();
public:
	BOOL SetBitmap(UINT nIDResource);

	BOOL SetBitmap(DWORD dwSize,void* lpBits);

	BOOL SetBitmap(int nWidth,int nHeight,void * lpBits);

	int LoadPicture(CString &filePath);

	void DrawImage(int x, int y, CDC* pDC);
public:
	BOOL Create(CWnd* pParentWnd,const RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE);

protected:
	virtual void PreSubclassWindow();
	BOOL RegisterWindowClass();

protected:
	CBitmap m_Bitmap;
	/*
	 *	Com组件图片接口
	 */
	IPicture *pPicture;
	
	IStream *pStream;
protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_BITMAPVIEW_H_INCLUDED_)