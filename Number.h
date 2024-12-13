//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"

#define NUMBER_SIZE		(10)						//弾のサイズ
#define MAX_NUMBER_LIFE	(50)						//弾の寿命
#define	MAX_NUMBER				(1250)		// 弾の最大数
#define NUMBER_POS_X			(0)		//弾の左上X座標
#define NUMBER_POS_Y			(0)		//弾の左上Y座標
#define NUMBER_WIDTH			(5)		//弾の幅
#define NUMBER_HEIGHT			(5)		//弾の高さ
#define NUMBER_POS_X2			(NUMBER_WIDTH - NUMBER_POS_X / 2)		//弾の左上X座標
#define NUMBER_POS_Y2			(NUMBER_HEIGHT - NUMBER_POS_Y / 2)		//弾の左上X座標


#define NUMBER_TEXTURE_SPEED	(0.01f)			//弾アニメーションスピード
#define NUMBER_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define NUMBER_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲


//レンダリングクラス
class CNUmber
{
public:
	CNUmber();
	~CNUmber();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float Length );
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	static CNUmber *Create(D3DXVECTOR3 pos,   float Length,  int nType);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;

};


#endif
