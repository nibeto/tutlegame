//=============================================================================
//
//	ランクの処理 [Rankes.h]
// Author :
//
//=============================================================================
#ifndef _RANKES_H_
#define _RANKES_H_

#include "main.h"

class CRankes
{
public:
	CRankes();
	~CRankes();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRankes *Create(void);
	void MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3				m_RankPos;

};


////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//void InitRankes(void);
//void UninitRankes(void);
//void UpdateRankes(void);
//void DrawRankes(void);
#endif

