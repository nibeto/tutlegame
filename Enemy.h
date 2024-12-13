//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_NUM_ENEMY (27)

//レンダリングクラス
class CEnemy : public CScene2D
{
public:
	CEnemy(SCENE_NUMBER_TYPE m_Number);
	~CEnemy();
	typedef enum
	{
		ENEMY_TYPE_BASE = 0,
		ENEMY_TYPE_1,
		ENEMY_TYPE_2,
		ENEMY_TYPE_3,
		ENEMY_TYPE_4,
		ENEMY_TYPE_5,
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;
	typedef enum
	{//タイプ
		ENEMY_CLASS_TYPE_BASE = 0,
		ENEMY_CLASS_TYPE_1,
		ENEMY_CLASS_TYPE_2,
		ENEMY_CLASS_TYPE_3,
		ENEMY_CLASS_TYPE_4,
		ENEMY_CLASS_TYPE_5,
		ENEMY_CLASS_TYPE_LIFE,
		ENEMY_CLASS_TYPE_LIFE_1,
		ENEMY_CLASS_TYPE_MAX
	}ENEMY_CLASS_TYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		float f_sizeX;
		float f_sizeY;
		int  type;
		int  ntype;
		float f_R ;
		float f_G ;
		float f_B ;
		float f_A ;
	}Enemy;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CntScore(bool score);
	static int GetNumEnemy(void);
	static Enemy *GetEnemy(void);
	inline static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY,ENEMY_TYPE type, ENEMY_CLASS_TYPE nType, float colR, float colG, float colB, float colA) {
		//インスタンス
		CEnemy*pEnemy = NULL;
		pEnemy = new CEnemy(SCENE_NUMBER_TYPE_ENEMY);
		pEnemy->Init(pos, move, LengthX, LengthY, colR, colG, colB, colA);
		pEnemy->m_nType = nType;
		pEnemy->BindTexture(m_pTexture[type]);
		return pEnemy;
	};
	void Save(void);
	static	void Loads(void);
	int GetLife(void) { return m_nLife; };
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[ENEMY_TYPE_MAX];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int m_nLife = 5;
	float fMoveX1;
	float fMoveY1;
	float fMoveX;
	float fMoveY;
	float fSpeed;
	float fRot = 0.0f;
	int nCountBullet;
	ENEMY_CLASS_TYPE m_nType;
	D3DXVECTOR3 m_move;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;
	static int nNumEnemy;
	static Enemy m_Enemy[MAX_NUM_ENEMY];
	int nPattanAnim;
};
#define ENEMY_POLYGON_SIZE (25)
#define ENEMY_POS_X			(0)		//弾の左上X座標
#define ENEMY_POS_Y			(0)		//弾の左上Y座標
#define ENEMY_WIDTH			(5)		//弾の幅
#define ENEMY_HEIGHT			(5)		//弾の高さ
#define ENEMY_POS_X2			(ENEMY_POLYGON_SIZE - ENEMY_POS_X / 2)		//弾の左上X座標
#define ENEMY_POS_Y2			(ENEMY_POLYGON_SIZE - ENEMY_POS_Y / 2)		//弾の左上X座標

#endif