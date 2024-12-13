//=============================================================================
// 授業作成
// ランクの背景の処理 [RankGata.h]
// Author :
//
//=============================================================================
#ifndef _RANKGATA_H_
#define _RANKGATA_H_

class CRankingGata
{
public:
	CRankingGata();
	~CRankingGata();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRankingGata *Create(void);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;

};
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//void InitRankingGata(void);
//void UninitRankingGata(void);
//void UpdateRankingGata(void);
//void DrawRankingGata(void);
#endif