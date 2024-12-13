//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include"main.h"
#include"Scene2D.h"
class CNUmber;
class CScene2D;
#define MAX_SOORE_TEXTUR (2)
class CScore : public CScene
{
public:
	CScore();
	~CScore();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	inline	int GetScoer(void);

	static CScore *Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_SOORE_TEXTUR];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	CScene2D *m_apScene2D[2];//ポリゴンの数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//カウンタ変数
	int nScore = 0; 						//float m_fPosSize = 0.0f;	//サイズ変更用
	int m_aScoreDigit[1250]; 						//float m_fPosSize = 0.0f;	//サイズ変更用

	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float mf_pos = 0.0f;//(posの長さの変数)
	LPDIRECT3DDEVICE9 pDevice;
	CNUmber *m_apNUMber[MAX_SCORE_DIGIT];
};
#define SCORE_SIZE (15.0f)//スコアのサイズ
#define SCORE_POS_X	(1250)//スコアの幅
#define SCORE_POS_Y	(50)//スコアの高さ

#endif