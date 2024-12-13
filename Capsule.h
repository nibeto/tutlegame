//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _CAPSULE_H_
#define _CAPSULE_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CCapsule : public CScene2D
{
public:
	CCapsule(SCENE_NUMBER_TYPE m_Number);
	~CCapsule();
	typedef enum
	{
		CAPSULE_TYPE_BASE = 0,
		CAPSULE_TYPE_1 = 1,
		CAPSULE_TYPE_2,
		CAPSULE_TYPE_MAX

	}CAPSULE_TYPE;
	typedef enum
	{//タイプ
		CAPSULE_CLASS_TYPE_BASE = 0,
		CAPSULE_CLASS_TYPE_1 = 1,
		CAPSULE_CLASS_TYPE_2,
		CAPSULE_CLASS_TYPE_3,
		CAPSULE_CLASS_TYPE_4,
		CAPSULE_CLASS_TYPE_5,
		CAPSULE_CLASS_TYPE_LIFE,
		CAPSULE_CLASS_TYPE_LIFE_1,
		CAPSULE_CLASS_TYPE_MAX

	}CAPSULE_CLASS_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCapsule *Create(D3DXVECTOR3 pos, float LengthX, float LengthY, CAPSULE_TYPE type, CAPSULE_CLASS_TYPE nType);



private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

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
	CAPSULE_CLASS_TYPE m_nType;//タイプ
	float m_posx;
	float m_posy;
};
#define CAPSULE_POLYGON_SIZE (25)

#define	MAX_TypeCAPSULE			(4)		// 弾の最大数

#define	MAX_CAPSULE			(40)		// 弾の最大数
#define CAPSULE_POS_X			(0)		//弾の左上X座標
#define CAPSULE_POS_Y			(0)		//弾の左上Y座標
#define CAPSULE_HEIGHT			(55)		//弾の高さ
#define CAPSULE_WIDTH              (55)
#define CAPSULE_TEXTURE_SPEED	(0.5f)			//弾アニメーションスピード
#define CAPSULE_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define CAPSULE_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲
#define	CAPSULE_CM				(40)//壁との距離
#define	CAPSULE_POS_X2			(CAPSULE_WIDTH - CAPSULE_POS_X / 2)		//弾の左上X座標
#define CAPSULE_POS_Y2			(CAPSULE_HEIGHT - CAPSULE_POS_Y / 2)		//弾の左上X座標




#endif