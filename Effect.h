
//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//レンダリングクラス
class CEffect : public CScene2D
{
public:
	CEffect(SCENE_NUMBER_TYPE m_Number);
	~CEffect();
	typedef enum
	{
		EFFECT_TYPE_PLAYER = 0,
		EFFECT_TYPE_ENEMY,
		EFFECT_TYPE_MAX

	}EFFECT_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA,float rot, float LengthX, float LengthY, float Radius, EFFECT_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	int m_TypeEffect;

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA,float rot, float LengthX, float LengthY, float Radius, EFFECT_TYPE type, int nType);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ

	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	bool m_bDisp;
	bool bUse;
	int m_nCountEffect;
	int m_Tex;
	float m_fRadius;
	float colR,  colG,  colB,  colA = 1.0f;
};
#define EFFECT_SIZE		(10)						//弾のサイズ
#define MAX_EFFECT_LIFE	(50)						//弾の寿命
#define	MAX_EFFECT				(1250)		// 弾の最大数
#define EFFECT_POS_X			(0)		//弾の左上X座標
#define EFFECT_POS_Y			(0)		//弾の左上Y座標
#define EFFECT_WIDTH			(5)		//弾の幅
#define EFFECT_HEIGHT			(5)		//弾の高さ
#define EFFECT_POS_X2			(EFFECT_WIDTH - EFFECT_POS_X / 2)		//弾の左上X座標
#define EFFECT_POS_Y2			(EFFECT_HEIGHT - EFFECT_POS_Y / 2)		//弾の左上X座標

#define EFFECT_TEXTURE_SPEED	(0.01f)			//弾アニメーションスピード
#define EFFECT_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define EFFECT_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲

#endif