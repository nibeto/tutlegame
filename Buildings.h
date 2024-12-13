//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BUILDING_H_
#define _BUILDING_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_NUM_BUILDING (27)

//レンダリングクラス
class CBUilding : public CScene2D
{
public:
	CBUilding(SCENE_NUMBER_TYPE m_Number);
	~CBUilding();
	typedef enum
	{
		BUILDING_TYPE_BASE = 0,
		BUILDING_TYPE_1,
		BUILDING_TYPE_2,
		BUILDING_TYPE_3,
		BUILDING_TYPE_4,
		BUILDING_TYPE_5,
		BUILDING_TYPE_MAX
	}BUILDING_TYPE;
	typedef enum
	{//タイプ
		BUILDING_CLASS_TYPE_BASE = 0,
		BUILDING_CLASS_TYPE_1,
		BUILDING_CLASS_TYPE_2,
		BUILDING_CLASS_TYPE_3,
		BUILDING_CLASS_TYPE_4,
		BUILDING_CLASS_TYPE_5,
		BUILDING_CLASS_TYPE_LIFE,
		BUILDING_CLASS_TYPE_LIFE_1,
		BUILDING_CLASS_TYPE_MAX
	}BUILDING_CLASS_TYPE;

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
	}Building;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CntScore(bool score);
	static int GetNumBuilding(void);
	static Building *GetBuilding(void);
	inline float GetBulidingSizeX(void) { return f_posX; };
	inline float GetBulidingSizeY(void) { return f_posY; };
	static CBUilding *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, BUILDING_TYPE type, BUILDING_CLASS_TYPE nType, float colR, float colG, float colB, float colA);
	void Save(void);
	static	void Loads(void);
	int GetLife(void) { return m_nLife; };
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[BUILDING_TYPE_MAX];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int m_nLife = 5;
	float fMoveX1;
	float fMoveY1;
	float fMoveX;
	float fMoveY;
	float fSpeed;
	float fRot = 0.0f;
	int nCountBullet;
	BUILDING_CLASS_TYPE m_nType;
	D3DXVECTOR3 m_move;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;
	float f_posX;
	float f_posY;
	static int nNumBuilding;
	static Building m_Building[MAX_NUM_BUILDING];
	int nPattanAnim;
};
#define BUILIDING_POLYGON_SIZE (25)
#define BUILIDING_POS_X			(0)		//弾の左上X座標
#define BUILIDING_POS_Y			(0)		//弾の左上Y座標
#define BUILIDING_WIDTH			(5)		//弾の幅
#define BUILIDING_HEIGHT			(5)		//弾の高さ
#define BUILIDING_POS_X2			(BUILIDING_POLYGON_SIZE - BUILIDING_POS_X / 2)		//弾の左上X座標
#define BUILIDING_POS_Y2			(BUILIDING_POLYGON_SIZE - BUILIDING_POS_Y / 2)		//弾の左上X座標

#endif