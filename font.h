//=============================================================================
//
// フォント処理 [font.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

#include"main.h"
#include "scene2D.h"

//*************************************
// マクロ
//*************************************
#define MAX_FONT			(256)
#define SETFONT_WIDE		(SCREEN_WIDTH * 0.35)
#define SETFONT_HEIGHT		(SCREEN_HEIGHT * 0.4)
#define Font_TextureName	"data/TEXTURE/50音.png"		//50音表
class CManeger;

class CFONT: public CScene
{
public:
	//*************************************
	// フォントの状態
	//*************************************
	typedef enum
	{//文字の状態
		FONTSTATE_NONE = 0,
		FONTSTATE_DELETE,
		FONTSTATE_RANKDOWN,
		FONTSTATE_RANKSET,		//ランキング時のセット
		FONTSTATE_RANKDELETE,	//ランキング時のデリート

	}FONTSTATE;

	typedef struct
	{
		FONTSTATE	state;		//文字の状態
		D3DXCOLOR	col;		//カラー
		RECT		rect;		//文字の表示範囲
		float		fCntState;	//状態管理用
		char		aStr[25];	//文字の量
		char		astr[25];	//文字の量
		bool		bUse;		//使用or未使用
		float fWight;
	}Font;
	CFONT();
	~CFONT();
	static HRESULT Load(void);
	static void UnLoad(void);
	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFont(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nNumber, FONTSTATE state,int nCntFont);
	void ChangeFont(bool bUse, const char *aStr, const char *astr, int nNumber, FONTSTATE state);
	void BreakFont(int nNumber);
	void FontTime(int nNumber);
	void FontTimer(int nNumber,int nCntData);
	int *GetSetFont(void);
	static CFONT* Create(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nCntData,int nNumber, FONTSTATE state,bool buse, int nCntFont) {
		//int nAll = m_nNumAll;
		CFONT* PFont = NULL;
		PFont = new CFONT;
		PFont->Init();
		PFont->SetFont(rect, col, aStr, astr, nNumber, state, nCntFont);
		PFont->ChangeFont(buse, aStr, astr, nNumber, state);
		return PFont;
	};

private:
	static	LPDIRECT3DTEXTURE9 m_pTextureFont;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFont = NULL;	//頂点BUFFERへのポインタ
	LPD3DXFONT			m_pFont0 = NULL;			// フォントへのポインタ
	Font				m_Font[MAX_FONT];
	int					m_nSetFont = 0;
	float m_fSpeed = 0.028f;
};



#endif
