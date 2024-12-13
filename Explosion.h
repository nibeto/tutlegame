//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CExplosion : public CScene2D
{
public:
	CExplosion(SCENE_NUMBER_TYPE m_Number);
	~CExplosion();

	static HRESULT Load(void);
	static void UnLoad(void);

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 move,float rot, float Length);
	inline static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length) {
		//インスタンス
		CExplosion*pExprosion = NULL;
		//
		pExprosion = new CExplosion(SCENE_NUMBER_TYPE_EXPROSION);
		pExprosion->Init(pos, move, tex, nPattenAnime, rot, Length);
		pExprosion->BindTexture(m_pTexture);
		return pExprosion;

	}
	;

	//void SetTexture(OBJECT_TEXTYPE textype);
private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	int m_nCntExprocion;
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	bool m_bjump;
	bool m_bDisp;
	bool bUse;
	int nCountAnime;
	int nPattenAnime;
	D3DXVECTOR3				m_move;						//移動量



};

#define	MAX_PLAYER	(1)	// 自機

#define PLAYER_WIDTH			(30)		//プレイヤーの幅

#define PLAYER_HEIGHT			(30)		//プレイヤーの高さ
#define PLAYER_POS_X			(0)		//弾の左上X座標
#define PLAYER_POS_Y			(0)		//弾の左上Y座標
#define	PLAYER_POS_X2			(PLAYER_WIDTH - PLAYER_POS_X / 2)		//弾の左上X座標
#define PLAYER_POS_Y2			(PLAYER_HEIGHT - PLAYER_POS_Y / 2)		//弾の左上X座標
#define PLAYER_LONG_X			(PLAYER_WIDTH/2)
#define PLAYER_LONG_Y			(PLAYER_HEIGHT/2)


#endif