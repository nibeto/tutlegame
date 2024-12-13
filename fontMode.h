#ifndef _FONTMODE_H_
#define _FONTMODE_H_

#include"manager.h"
#include "Scene2D.h"
#include "font.h"


class CFontMode
{
public:
	typedef enum
	{//フォントのナンバー
		FONT_NUMBER_0,
		FONT_NUMBER_1,
		FONT_NUMBER_2,
		FONT_NUMBER_3,
		FONT_NUMBER_4,
		FONT_NUMBER_5,
		FONT_NUMBER_6,
		FONT_NUMBER_7,
		FONT_NUMBER_8,
		FONT_NUMBER_9,
		FONT_NUMBER_10,
		FONT_NUMBER_11,
		FONT_NUMBER_12,
		FONT_NUMBER_13,
		FONT_NUMBER_14,
		FONT_NUMBER_15,
		FONT_NUMBER_16,
		FONT_NUMBER_17,
		FONT_NUMBER_18,
		FONT_NUMBER_MAX,
	}FONT_NUMBER;
	typedef enum
	{//フォントのナンバー
		FONT_TYMER_0,
		FONT_TYMER_1,
		FONT_TYMER_2,
		FONT_TYMER_3,
		FONT_TYMER_4,
		FONT_TYMER_5,
		FONT_TYMER_6,
		FONT_TYMER_7,
		FONT_TYMER_8,
		FONT_TYMER_9,
		FONT_TYMER_10,
		FONT_TYMER_11,
		FONT_TYMER_12,
		FONT_TYMER_13,
		FONT_TYMER_14,
		FONT_TYMER_15,
		FONT_TYMER_16,
		FONT_TYMER_17,
		FONT_TYMER_18,
		FONT_TYMER_19,
		FONT_TYMER_20,
		FONT_TYMER_21,
		FONT_TYMER_22,
		FONT_TYMER_23,
		FONT_TYMER_24,
		FONT_TYMER_25,
		FONT_TYMER_26,
		FONT_TYMER_27,
		FONT_TYMER_28,
		FONT_TYMER_29,
		FONT_TYMER_30,
		FONT_TYMER_31,
		FONT_TYMER_32,
		FONT_TYMER_33,
		FONT_TYMER_34,
		FONT_TYMER_35,
		FONT_TYMER_36,
		FONT_TYMER_37,
		FONT_TYMER_38,
		FONT_TYMER_39,
		FONT_TYMER_40,
		FONT_TYMER_41,
		FONT_TYMER_42,
		FONT_TYMER_43,
		FONT_TYMER_44,
		FONT_TYMER_45,
		FONT_TYMER_46,
		FONT_TYMER_47,
		FONT_TYMER_48,
		FONT_TYMER_49,
		FONT_TYMER_50,
		FONT_TYMER_51,
		FONT_TYMER_52,
		FONT_TYMER_53,
		FONT_TYMER_54,
		FONT_TYMER_55,
		FONT_TYMER_56,
		FONT_TYMER_57,
		FONT_TYMER_58,
		FONT_TYMER_59,
		FONT_TYMER_60,
		FONT_TYMER_MAX,
	}FONT_TYMER;

	CFontMode();
	~CFontMode();
	void Init(CManeger::MODE mode);
	void Uninit(void);
	void Update(CManeger::MODE mode);
	void FontMode(CManeger::MODE mode);
	inline	static CFONT* GetFont(void) { return m_pFont; };
	static CFontMode *Create(CManeger::MODE mode) {//インスタンス
		CFontMode*pFontMode = NULL;
		pFontMode = new CFontMode;
		if (pFontMode != NULL)
		{
			pFontMode->Init(mode);
		}
		return pFontMode;
	};


private:
	static CFONT *m_pFont;
static	CManeger::MODE m_mode;
	int	m_nTime;				// タイム
};

#endif