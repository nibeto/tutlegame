//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _3DPLAYER_H_
#define _3DPLAYER_H_
#include"main.h"
#include"Scene3D.h"

//レンダリングクラス
class C3DPlayer : public CSCENE3D
{
public:
	C3DPlayer(SCENE_NUMBER_TYPE m_Number);
	~C3DPlayer();
	typedef enum
	{
		PLAYER3D_TYPE_1,
		PLAYER3D_TYPE_2,
		PLAYER3D_TYPE_MAX

	}PLAYER3D_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static C3DPlayer *Create(D3DXVECTOR3 pos, PLAYER3D_TYPE type);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	static LPD3DXMESH		m_pMesh;		// テクスチャへのポインタ
	static LPD3DXBUFFER		m_pBuffMat;		// テクスチャへのポインタ
	static DWORD		m_nNumMat;		// テクスチャへのポインタ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 Posold;//前回の位置
	D3DXVECTOR3 pMovee;//移動の量


	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//カウンタ変数
									//float m_fPosSize = 0.0f;	//サイズ変更用
	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float mf_pos = 0.0f;//(posの長さの変数)
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	bool m_bjump;
	bool m_bDisp;
	int nCountBullet;
	int m_TexType;
	int m_Data = 0;
	char nData[256];

};
#define GRAVITY3D (35.0f)

#define	MAX_PLAYER3D	(1)	// 自機
#define	MAX_TEX_PLAYER3D	(1)	// 自機

#define PLAYER3D_WIDTH			(30)		//プレイヤーの幅

#define PLAYER3D_HEIGHT			(30)		//プレイヤーの高さ
#define PLAYER3D_POS_X			(0)		//弾の左上X座標
#define PLAYER3D_POS_Y			(0)		//弾の左上Y座標
#define	PLAYER3D_POS_X2			(PLAYER3D_WIDTH - PLAYER3D_POS_X / 2)		//弾の左上X座標
#define PLAYER3D_POS_Y2			(PLAYER3D_HEIGHT - PLAYER3D_POS_Y / 2)		//弾の左上X座標
#define PLAYER3D_LONG_X			(PLAYER3D_WIDTH/2)
#define PLAYER3D_LONG_Y			(PLAYER3D_HEIGHT/2)


#endif