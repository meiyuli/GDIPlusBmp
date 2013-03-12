#pragma once

class CRgb2YCbCr
{
protected:
	CRgb2YCbCr(void);
	~CRgb2YCbCr(void);
public:
	static CRgb2YCbCr * Instance();
	static void DeInstance();
public:
	/*
	 *	\brief RGB 转换 为 YCbCr
	 */
	void RGB2YCbCr(BYTE rgb[],ULONG ulSize,BYTE ycbcr[]);
	/*
	 *	\brief YCbCr 转换 为 RGB
	 */
	void YCbCr2RGB(BYTE ycbcr[],ULONG ulSize,BYTE rgb[]);
private:
	/*
	 *	\brief 唯一实例化对象
	 */
	static CRgb2YCbCr *m_pObject;
};
