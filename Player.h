//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CPlayer : public CScene2D
{
public:
	CPlayer(SCENE_NUMBER_TYPE m_Number);
	~CPlayer();
	typedef enum
	{
		PLAYER_TYPE_1,
		PLAYER_TYPE_2,
		PLAYER_TYPE_MAX

	}PLAYER_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float LengshX, float LengshY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void collision(void);

	void Save(void);
	void Loads(void);

	static CPlayer *Create(D3DXVECTOR3 pos, PLAYER_TYPE type, float LengshX, float LengshY) {
		//インスタンス
		CPlayer*pPlayer = NULL;
		pPlayer = new CPlayer(SCENE_NUMBER_TYPE_PLAYER);
		pPlayer->Init(pos, LengshX, LengshY);
		pPlayer->BindTexture(m_pTexture[type]);

		return pPlayer;

	};
	inline	D3DXVECTOR3	GetPos(void) { return CScene2D::GetPotion(); };
	inline	D3DXVECTOR3	GetMove(void) { return CScene2D::GetMove(); };
	inline	D3DXVECTOR2	GetTex(void) { return CScene2D::GetTex(); };
	inline	float GetfmoveX(void) { return fMoveX; };
	inline	float GetfmoveY(void) { return fMoveY; };
	inline	float GetfmoveZ(void) { return fMoveZ; };
	inline	int GetPLayerLife(void) { return m_nLife; };
	inline	int GetMagicPoint(void) { return m_nMagicPoint; };
	inline	int GetPrioTy(void) { return m_nPriority; };

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 Posold;//前回の位置
	D3DXVECTOR3 pMovee;//移動の量

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	char nData[256];
	float fMoveX = 0.0f, fMoveY = 0.0f, fMoveZ = 0.0f;
	float fRot = 0.0f;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;
	float fSpped;
	int m_nLife = 2;
	bool bLand;
	int nPattanAnim;
};
#define GRAVITY (55.0f)

#define	MAX_PLAYER	(1)	// 自機
#define	MAX_TEX_PLAYER	(2)	// 自機

#define PLAYER_WIDTH			(30)		//プレイヤーの幅

#define PLAYER_HEIGHT			(30)		//プレイヤーの高さ
#define PLAYER_POS_X			(0)		//弾の左上X座標
#define PLAYER_POS_Y			(0)		//弾の左上Y座標
#define	PLAYER_POS_X2			(PLAYER_WIDTH - PLAYER_POS_X / 2)		//弾の左上X座標
#define PLAYER_POS_Y2			(PLAYER_HEIGHT - PLAYER_POS_Y / 2)		//弾の左上X座標
#define PLAYER_LONG_X			(PLAYER_WIDTH/2)
#define PLAYER_LONG_Y			(PLAYER_HEIGHT/2)


#endif