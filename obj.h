
//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _OBJ_H_
#define _OBJ_H_
#include"main.h"
#include"Scene2D.h"

//レンダリングクラス
class CObj : public CScene2D
{
public:
	CObj(SCENE_NUMBER_TYPE m_Number);
	~CObj();
	typedef enum
	{
		OBJ_TYPE_BASE = 0,
		OBJ_TYPE_1 = 1,
		OBJ_TYPE_2,
		OBJ_TYPE_MAX

	}OBJ_TYPE;
	typedef enum
	{
		OBJ_BOX_TYPE_BASE = 0,
		OBJ_BOX_TYPE_1 = 1,
		OBJ_BOX_TYPE_2,
		OBJ_BOX_TYPE_MAX

	}OBJ_BOX_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, OBJ_TYPE type, OBJ_BOX_TYPE nType);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	OBJ_BOX_TYPE m_nType;
	int m_nLife = 5;
	int NcuntRot = 0;
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3 m_move;
	int  nPattenAnime;
};
#define OBJ_POLYGON_SIZE (25)
#define OBJ_POS_X			(0)		//弾の左上X座標
#define OBJ_POS_Y			(0)		//弾の左上Y座標
#define OBJ_WIDTH			(5)		//弾の幅
#define OBJ_HEIGHT			(5)		//弾の高さ
#define OBJ_POS_X2			(OBJ_POLYGON_SIZE - OBJ_POS_X / 2)		//弾の左上X座標
#define OBJ_POS_Y2			(OBJ_POLYGON_SIZE - OBJ_POS_Y / 2)		//弾の左上X座標


#endif