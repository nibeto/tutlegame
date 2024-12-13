//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#define MAX_FADE (1)
#include"main.h"
#include"Scene2D.h"
#include"manager.h"
class CManeger;

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;
	CFade();
	~CFade();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(CManeger::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManeger::MODE modeNext);

	static CFade *Create(CManeger::MODE modeNext);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	CScene2D *m_apScene2D;//ポリゴンの数
	//CManeger *mManeger;
	D3DXCOLOR m_Fadecol;
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	CManeger::MODE					m_modeNext;				// 次のモード
	FADE m_Fade;

};
#endif