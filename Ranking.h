//=============================================================================
//
// ランキングの処理 [Ranking.h]
// Author :
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#define MAX_RANKING				(5)							//ランキングの数

class CRankes;
class CRankingGata;
class CRankes;

class CRanking
{
public:
	//*****************************************************************************
	// 構造体定義
	//*****************************************************************************
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
							//int nCounterAnim;	//アニメーションカウンター
							//int nPatternAnim;	//アニメーションパターンNoを初期化
		D3DXCOLOR col;		//カラー
	}Ranking;
	CRanking();
	~CRanking();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRanking *Create(void);
	void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
	void SetRanking(int nRanking);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	int						m_nRanking = 0;					// スコア
	int						m_aScore[MAX_RANKING];
	Ranking					m_aRanking[MAX_RANKING];
	D3DXVECTOR3				m_RankingPos;
	int						m_nCounterTimer = 0;
	int						m_nRankNum;
	int						m_nCntRankTimer = 0;
	int						m_RankChange = 0;
	static CRankingGata *m_pRankingata;
	static CRankes *m_pRankes;

};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
						//int nCounterAnim;	//アニメーションカウンター
						//int nPatternAnim;	//アニメーションパターンNoを初期化
	D3DXCOLOR col;		//カラー
}Ranking;

////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//void InitRanking(void);
//void UninitRanking(void);
//void UpdateRanking(void);
//void DrawRanking(void);
//void SetRanking(int aRanking);
#endif
