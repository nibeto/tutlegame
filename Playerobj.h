
//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _PLAYEROBJ_H_
#define _PLAYEROBJ_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CPlayerObj : public CScene2D
{
public:
	CPlayerObj(SCENE_NUMBER_TYPE m_Number);
	~CPlayerObj();
	typedef enum
	{
		PLAYEROBJ_TYPE_1,
		PLAYEROBJ_TYPE_2,
		PLAYEROBJ_TYPE_MAX

	}PLAYEROBJ_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos ,float LengshX,float LengshY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CPlayerObj *Create(D3DXVECTOR3 pos, PLAYEROBJ_TYPE type,float LengshX, float LengshY);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
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
	int m_TexType;
	int m_Data = 0;
	char nData[256];
	int nCountBullet;
	float f_Speed;
	int nPattanAnim;
};
#define GRAVITYOBJ (35.0f)

#define	MAX_PLAYEROBJ	(1)	// 自機
#define	MAX_TEX_PLAYEROBJ	(2)	// 自機

#define PLAYEROBJ_WIDTH			(30)		//プレイヤーの幅
#define PLAYEROBJ_SIZE			(30)		//プレイヤーの幅

#define PLAYEROBJ_HEIGHT			(30)		//プレイヤーの高さ
#define PLAYEROBJ_POS_X			(0)		//弾の左上X座標
#define PLAYEROBJ_POS_Y			(0)		//弾の左上Y座標
#define	PLAYEROBJ_POS_X2			(PLAYEROBJ_WIDTH - PLAYEROBJ_POS_X / 2)		//弾の左上X座標
#define PLAYEROBJ_POS_Y2			(PLAYEROBJ_HEIGHT - PLAYEROBJ_POS_Y / 2)		//弾の左上X座標
#define PLAYEROBJ_LONG_X			(PLAYEROBJ_WIDTH/2)
#define PLAYEROBJ_LONG_Y			(PLAYEROBJ_HEIGHT/2)


#endif