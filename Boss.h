//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_NUM_BOSS (27)

//レンダリングクラス
class CBoss : public CScene2D
{
public:
	CBoss(SCENE_NUMBER_TYPE m_Number);
	~CBoss();
	typedef enum
	{
		BOSS_TYPE_BASE = 0,
		BOSS_TYPE_1,
		BOSS_TYPE_2,
		BOSS_TYPE_3,
		BOSS_TYPE_4,
		BOSS_TYPE_5,
		BOSS_TYPE_MAX
	}BOSS_TYPE;
	typedef enum
	{//タイプ
		BOSS_CLASS_TYPE_BASE = 0,
		BOSS_CLASS_TYPE_1,
		BOSS_CLASS_TYPE_2,
		BOSS_CLASS_TYPE_3,
		BOSS_CLASS_TYPE_4,
		BOSS_CLASS_TYPE_5,
		BOSS_CLASS_TYPE_LIFE,
		BOSS_CLASS_TYPE_LIFE_1,
		BOSS_CLASS_TYPE_MAX
	}BOSS_CLASS_TYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		float f_sizeX;
		float f_sizeY;
		int  type;
		int  ntype;
		float f_R;
		float f_G;
		float f_B;
		float f_A;
	}Boss;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CntScore(bool score);
	static int GetNumBoss(void);
	static Boss *GetBoss(void);
	inline static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, BOSS_TYPE type, BOSS_CLASS_TYPE nType, float colR, float colG, float colB, float colA) {
		//インスタンスw
		CBoss*pEnemy = NULL;
		pEnemy = new CBoss(SCENE_NUMBER_TYPE_BOSS);
		pEnemy->Init(pos, move, LengthX, LengthY, colR, colG, colB, colA);
		pEnemy->m_nType = nType;
		pEnemy->BindTexture(m_pTexture[type]);
		return pEnemy;
		//インスタンス

	};
	void Save(void);
	static	void Loads(void);
	int GetLife(void) { return m_nLife; };
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[BOSS_TYPE_MAX];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int m_nLife = 5;
	float fMoveX1;
	float fMoveY1;
	float fMoveX;
	float fMoveY;
	float fSpeed;
	float fRot = 0.0f;
	int nCountBullet;
	BOSS_CLASS_TYPE m_nType;
	D3DXVECTOR3 m_move;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;
	static int nNumBoss;
	static Boss m_Boss[MAX_NUM_BOSS];
	int  nPattanAnim;
};
#define BOSS_POLYGON_SIZE (25)
#define BOSS_POS_X			(0)		//弾の左上X座標
#define BOSS_POS_Y			(0)		//弾の左上Y座標
#define BOSS_WIDTH			(5)		//弾の幅
#define BOSS_HEIGHT			(5)		//弾の高さ
#define BOSS_POS_X2			(BOSS_POLYGON_SIZE - BOSS_POS_X / 2)		//弾の左上X座標
#define BOSS_POS_Y2			(BOSS_POLYGON_SIZE - BOSS_POS_X / 2)		//弾の左上X座標

#endif