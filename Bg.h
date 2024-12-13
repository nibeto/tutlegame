//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#include"main.h"
#include"Scene2D.h"

class CBg : public CScene
{
public:
	CBg();
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	static CBg *Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	CScene2D *m_apScene2D[2];//ポリゴンの数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//カウンタ変数
									//float m_fPosSize = 0.0f;	//サイズ変更用
	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float mf_pos = 0.0f;//(posの長さの変数)
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*


};


#define	MAX_PLAYER	(1)	// 自機
#define	MAX_BG_TEX	(2)	// 自機

#define PLAYER_WIDTH			(30)		//プレイヤーの幅

#define PLAYER_HEIGHT			(30)		//プレイヤーの高さ
#define PLAYER_POS_X			(0)		//弾の左上X座標
#define PLAYER_POS_Y			(0)		//弾の左上Y座標
#define	PLAYER_POS_X2			(PLAYER_WIDTH - PLAYER_POS_X / 2)		//弾の左上X座標
#define PLAYER_POS_Y2			(PLAYER_HEIGHT - PLAYER_POS_Y / 2)		//弾の左上X座標
#define PLAYER_LONG_X			(PLAYER_WIDTH/2)
#define PLAYER_LONG_Y			(PLAYER_HEIGHT/2)


#endif