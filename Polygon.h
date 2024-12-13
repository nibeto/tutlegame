//=============================================================================
// メイン処理 [POLIGON.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _POLIGON_H_
#define _POLIGON_H_
#include"main.h"
#include"Scene2D.h"
#include "Dice.h"
class CDice;
//レンダリングクラス
class CPoligon : public CScene2D
{
public:
	CPoligon(SCENE_NUMBER_TYPE m_Number);
	~CPoligon();
	typedef enum
	{
		POLIGON_TYPE_1,
		POLIGON_TYPE_2,
		POLIGON_TYPE_MAX

	}POLIGON_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float LengshX, float LengshY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CPoligon* Create(D3DXVECTOR3 pos, POLIGON_TYPE type, float LengshX, float LengshY) {
		//インスタンス
		CPoligon* pPoligon = NULL;
		pPoligon = new CPoligon(SCENE_NUMBER_TYPE_POLIGON);
		pPoligon->Init(pos, LengshX, LengshY);
		pPoligon->BindTexture(m_pTexture[type]);

		return pPoligon;

	};

	static void TEXTUREDELEATE(CPoligon* pPoligon) {
		if (pPoligon != NULL)
		{
			pPoligon->Uninit();
		}

	}



	inline	D3DXVECTOR3	GetPos(void) { return CScene2D::GetPotion(); };
	inline	D3DXVECTOR3	GetMove(void) { return CScene2D::GetMove(); };
	inline	D3DXVECTOR2	GetTex(void) { return CScene2D::GetTex(); };
	inline	float GetfmoveX(void) { return fMoveX; };
	inline	float GetfmoveY(void) { return fMoveY; };
	inline	float GetfmoveZ(void) { return fMoveZ; };
	inline	int GetPOLIGONLife(void) { return m_nLife; };
	inline	int GetMagicPoint(void) { return m_nMagicPoint; };
	inline	int GetPrioTy(void) { return m_nPriority; };

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ


	CDice::DISE_TYPE m_nDiseType;

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
	int m_nLife;
	bool bLand;
	int nPattanAnim;
};
#define GRAVITY (55.0f)

#define	MAX_POLIGON	(1)	// 自機
#define	MAX_TEX_POLIGON	(2)	// 自機

#define POLIGON_WIDTH			(30)		//プレイヤーの幅

#define POLIGON_HEIGHT			(30)		//プレイヤーの高さ
#define POLIGON_POS_X			(0)		//弾の左上X座標
#define POLIGON_POS_Y			(0)		//弾の左上Y座標
#define	POLIGON_POS_X2			(POLIGON_WIDTH - POLIGON_POS_X / 2)		//弾の左上X座標
#define POLIGON_POS_Y2			(POLIGON_HEIGHT - POLIGON_POS_Y / 2)		//弾の左上X座標
#define POLIGON_LONG_X			(POLIGON_WIDTH/2)
#define POLIGON_LONG_Y			(POLIGON_HEIGHT/2)


#endif