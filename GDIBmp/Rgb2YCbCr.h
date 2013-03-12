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
	 *	\brief RGB ת�� Ϊ YCbCr
	 */
	void RGB2YCbCr(BYTE rgb[],ULONG ulSize,BYTE ycbcr[]);
	/*
	 *	\brief YCbCr ת�� Ϊ RGB
	 */
	void YCbCr2RGB(BYTE ycbcr[],ULONG ulSize,BYTE rgb[]);
private:
	/*
	 *	\brief Ψһʵ��������
	 */
	static CRgb2YCbCr *m_pObject;
};
