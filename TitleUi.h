//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_
#include"main.h"
#include"Scene2D.h"

class CTitleUi : public CScene
{
public:
	CTitleUi();
	~CTitleUi();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	static CTitleUi *Create(void);
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


#define	MAX_TITLEUI	(1)	// 自機
#define	MAX_TITLEUI_TEX	(2)	// 自機

#define TITLEUI_WIDTH			(30)		//プレイヤーの幅
#define TITLEUI_HEIGHT			(30)		//プレイヤーの高さ
#define TITLEUI_POS_X			(0)		//弾の左上X座標
#define TITLEUI_POS_Y			(0)		//弾の左上Y座標
#define	TITLEUI_POS_X2			(TITLEUI_WIDTH - TITLEUI_POS_X / 2)		//弾の左上X座標
#define TITLEUI_POS_Y2			(TITLEUI_HEIGHT - TITLEUI_POS_Y / 2)		//弾の左上X座標
#define TITLEUI_LONG_X			(TITLEUI_WIDTH/2)
#define TITLEUI_LONG_Y			(TITLEUI_HEIGHT/2)


#endif