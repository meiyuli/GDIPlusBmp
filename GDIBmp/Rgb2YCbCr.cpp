#include "StdAfx.h"
#include "Rgb2YCbCr.h"

CRgb2YCbCr* CRgb2YCbCr::m_pObject = NULL;

CRgb2YCbCr::CRgb2YCbCr(void)
{
}

CRgb2YCbCr::~CRgb2YCbCr(void)
{
	DeInstance();
}

CRgb2YCbCr* CRgb2YCbCr::Instance()
{
	if (NULL == m_pObject)
	{
		m_pObject = new CRgb2YCbCr;
	}
	return m_pObject;
}

void CRgb2YCbCr::DeInstance()
{
	if (m_pObject)
	{
		delete m_pObject;
		m_pObject = NULL;
	}
}

void CRgb2YCbCr::RGB2YCbCr(BYTE rgb[],ULONG ulSize,BYTE ycbcr[])
{
	CFile file;
	if(!file.Open(_T("RGB2YUV.txt"),CFile::modeWrite | CFile::modeCreate))
	{
		return ;
	}
	char buf[200];
	// RGB转换为YCbCr
	for(int i = 0 ;i < ulSize;)
	{
		UCHAR r,g,b;
		r = rgb[i+0];
		g = rgb[i+1];
		b = rgb[i+2];
		ycbcr[i+0]= (unsigned char)(r * 0.256789 + g * 0.504129 + b * 0.097906)+ 16; 
		ycbcr[i+1]= (unsigned char)(r *-0.148223 + g * -0.290992 + b * 0.439215)+ 128;
		ycbcr[i+2]= (unsigned char)(r * 0.439215 + g * -0.367789 + b *-0.071426)+ 128; 
		sprintf_s(buf,"RGB(%d,%d,%d)->YUV(%d,%d,%d)\n\r",rgb[i+0],rgb[i+1],rgb[i+2],
			ycbcr[i+0],ycbcr[i+1],ycbcr[i+2]);
		file.Write(buf,strlen(buf));
		i += 3;
	}
	file.Close();
}

void CRgb2YCbCr::YCbCr2RGB(BYTE ycbcr[],ULONG ulSize,BYTE rgb[])
{
	// YCbCr转换为RGB
	for(int i =0 ; i < ulSize; )
	{
		UCHAR y,u,v;
		y = ycbcr[i+0];
		u = ycbcr[i+1];
		v = ycbcr[i+2];
		rgb[i+0]= (unsigned char)(1.164383*(y- 16) + 0 + 1.596027*(v - 128)); 
		rgb[i+1]= (unsigned char)(1.164383*(y- 16) - 0.391762*(u - 128) - 0.812969*(v - 128)); 
		rgb[i+2]= (unsigned char)(1.164383*(y- 16) + 2.017230*(u - 128) + 0 );
		i += 3;
	}
}