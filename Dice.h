//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _DISE_H_
#define _DISE_H_
#include"main.h"
#include"Scene2D.h"
class CPoligon;
//レンダリングクラス
class CDice : public CScene2D
{
public:
	CDice(SCENE_NUMBER_TYPE m_Number);
	~CDice();
	typedef enum
	{
		DISE_TYPE_BASE = 0,
		DISE_TYPE_1,
		DISE_TYPE_2,
		DISE_TYPE_3,
		DISE_TYPE_4,
		DISE_TYPE_5,
		DISE_TYPE_MAX

	}DISE_TYPE;
	typedef enum
	{//タイプ
		DICE_CLASS_TYPE_BASE = 0,
		DICE_CLASS_TYPE_1,
		DICE_CLASS_TYPE_2,
		DICE_CLASS_TYPE_3,
		DICE_CLASS_TYPE_4,
		DICE_CLASS_TYPE_5,
		DICE_CLASS_TYPE_LIFE,
		DICE_CLASS_TYPE_LIFE_1,
		DICE_CLASS_TYPE_MAX
	}DICE_CLASS_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float f_R, float f_G, float f_B, float f_A);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CntScore(bool score);
	inline static CDice *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, DISE_TYPE type, DICE_CLASS_TYPE nType, float f_R, float f_G, float f_B, float f_A) {
		//インスタンスw
		CDice*pEnemy = NULL;
		pEnemy = new CDice(SCENE_NUMBER_TYPE_DICE);
		pEnemy->Init(pos, move, LengthX, LengthY, f_R, f_G, f_B, f_A);
		pEnemy->m_nType = nType;
		pEnemy->BindTexture(m_pTexture[type]);
		return pEnemy;
		//インスタンス

	};
	inline	int GetLife(void) { return m_nLife; };

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[6];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int m_nLife = 5;
	float fMoveX1;
	float fMoveY1;
	float fMoveX;
	float fMoveY;
	float fSpeed;
	float fRot = 0.0f;
	int nCountBullet;
	DICE_CLASS_TYPE m_nType;
	D3DXVECTOR3 m_move;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;
	DISE_TYPE m_nDiseType;
	CPoligon* pPoligon = NULL;
};
#define DICE_POLYGON_SIZE (25)
#define DICE_POS_X			(0)		//弾の左上X座標
#define DICE_POS_Y			(0)		//弾の左上Y座標
#define DICE_WIDTH			(5)		//弾の幅
#define DICE_HEIGHT			(5)		//弾の高さ
#define DICE_POS_X2			(DICE_POLYGON_SIZE - DICE_POS_X / 2)		//弾の左上X座標
#define DICE_POS_Y2			(DICE_POLYGON_SIZE - DICE_POS_X / 2)		//弾の左上X座標

#endif