//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_TEXTURE_TITLE (5)
#define MAX_POLIGON_TITLE (5)
#include"font.h"
class CBg;
class CTitleUi;
class CFade;
class CRobo;
class CFontMode;
class CPLESEENTER;
class CTitle
{
public:
	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	static CTitle *Create(void);
	inline	static CFontMode* GetFontMode(void) { return m_pFontMode; };
	inline static CFONT* GetFont(void) { return m_pFont; };
	inline	static CBg* GetBg(void) { return m_pBg; };
	inline	static CTitleUi* GetTitleUI(void) { return m_pTitleUI; };
	inline	static CRobo * GetRobo(void) { return m_pRobo; };
	inline	static CPLESEENTER * GetPleseEnter(void) { return m_pPleseEnter; };

private:
	static CBg *m_pBg;
	static CRobo *m_pRobo;
	static CPLESEENTER *m_pPleseEnter;
	static CTitleUi *m_pTitleUI;
	static CFONT *m_pFont;
	static CFontMode *m_pFontMode;
	CFade *m_apfade;
	CManeger::MODE m_mode;
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXTURE_TITLE];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	CScene2D *m_apScene2D[MAX_POLIGON_TITLE];//ポリゴンの数
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;
	bool m_bTitleDisp = true;
	float f_posY = 0.0f;
	int	m_nTime;				// タイム

};
#endif