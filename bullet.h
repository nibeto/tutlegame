//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//レンダリングクラス
class CBullet : public CScene2D
{
public:
	CBullet(SCENE_NUMBER_TYPE m_Number);
	~CBullet();
	typedef enum
	{//テクスチャータイプ
		BULLET_TYPE_PLAYER = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_ROBO,
		BULLET_TYPE_MAX

	}BULLET_TYPE;
	typedef enum
	{//タイプ
		BULLET_OBJ_TYPE_PLAYER = 0,
		BULLET_OBJ_TYPE_PLAYER_1,
		BULLET_OBJ_TYPE_PLAYER_2,
		BULLET_OBJ_TYPE_PLAYER_3,
		BULLET_OBJ_TYPE_PLAYER_4,
		BULLET_OBJ_TYPE_ENEMY,
		BULLET_OBJ_TYPE_ENEMY_1,
		BULLET_OBJ_TYPE_ENEMY_2,
		BULLET_OBJ_TYPE_ROBO,
		BULLET_OBJ_TYPE_AROUND,
		BULLET_OBJ_TYPE_MAX

	}BULLET_OBJ_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	//クリエイト
	inline static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, BULLET_TYPE type, BULLET_OBJ_TYPE nType) {
		//インスタンス
		CBullet*pBullet = NULL;
		pBullet = new CBullet(SCENE_NUMBER_TYPE_BULLET);
		pBullet->Init(pos, move, rot, Length);
		pBullet->BindTexture(m_pTexture[type]);
		pBullet->Type = nType;
		return pBullet;

	};

	BULLET_OBJ_TYPE Type;//タイプ

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[3];		// テクスチャへのポインタ
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	bool m_bDisp;
	bool bUse;
	int m_nCountBullet;
	int m_Tex;
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fMoveX1 = 0.0f, fMoveY1 = 0.0f;
	float fMoveX2 = 0.0f, fMoveY2 = 0.0f;
	float fRoboMoveX = 0.0f, fRoboMoveY = 0.0f;
	float fAroundMoveX = 0.0f, fAroundMoveY = 0.0f;
	float fRot;
	float fRot1;
	float fRot2;
	float fRoboRot;
	float fAroundRot = D3DX_PI * 0.25f;

};
#define BULLET_SIZE		(10)						//弾のサイズ
#define MAX_BULLET_LIFE	(50)						//弾の寿命
#define	MAX_BULLET				(1250)		// 弾の最大数
#define BULLET_POS_X			(0)		//弾の左上X座標
#define BULLET_POS_Y			(0)		//弾の左上Y座標
#define BULLET_WIDTH			(5)		//弾の幅
#define BULLET_HEIGHT			(5)		//弾の高さ
#define BULLET_POS_X2			(BULLET_WIDTH - BULLET_POS_X / 2)		//弾の左上X座標
#define BULLET_POS_Y2			(BULLET_HEIGHT - BULLET_POS_Y / 2)		//弾の左上X座標


#define BULLET_TEXTURE_SPEED	(0.01f)			//弾アニメーションスピード
#define BULLET_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define BULLET_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲



#endif