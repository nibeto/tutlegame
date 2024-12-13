//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _WEAPONS_H_
#define _WEAPONS_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CWeapons : public CScene2D
{
public:
	CWeapons(SCENE_NUMBER_TYPE m_Number);
	~CWeapons();
	typedef enum
	{
		WEAPONS_TYPE_1 = 0,
		WEAPONS_TYPE_2,
		WEAPONS_TYPE_MAX

	}WEAPONS_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	static CWeapons *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,WEAPONS_TYPE type, float rot, float Length);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 Posold;//前回の位置
	D3DXVECTOR3 pMovee;//移動の量


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
	D3DXVECTOR3 m_move;
	int nPattenAnime;

};

#define	MAX_WEAPONS	(1)	// 自機
#define	MAX_TEX_WEAPONS	(2)	// 自機

#define WEAPONS_WIDTH			(30)		//プレイヤーの幅

#define WEAPONS_HEIGHT			(30)		//プレイヤーの高さ
#define WEAPONS_POS_X			(0)		//弾の左上X座標
#define WEAPONS_POS_Y			(0)		//弾の左上Y座標
#define	WEAPONS_POS_X2			(WEAPONS_WIDTH - WEAPONS_POS_X / 2)		//弾の左上X座標
#define WEAPONS_POS_Y2			(WEAPONS_HEIGHT - WEAPONS_POS_Y / 2)		//弾の左上X座標
#define WEAPONS_LONG_X			(WEAPONS_WIDTH/2)
#define WEAPONS_LONG_Y			(WEAPONS_HEIGHT/2)


#endif