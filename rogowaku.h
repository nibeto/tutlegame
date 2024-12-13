
//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _ROGOWAKU_H_
#define _ROGOWAKU_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_ROGOWAKU_TYPE (4)//a =	透明度 (0～255)
//レンダリングクラス
class CRogowaku : public CScene2D
{
public:
	CRogowaku(SCENE_NUMBER_TYPE m_Number);
	~CRogowaku();
	typedef enum
	{
		ROGOWAKU_TYPE_BASE = 0,
		ROGOWAKU_TYPE_1,
		ROGOWAKU_TYPE_2,
		ROGOWAKU_TYPE_3,
		ROGOWAKU_TYPE_MAX

	}ROGOWAKU_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,  float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CRogowaku *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,  float LengthX, float LengthY, ROGOWAKU_TYPE type, int nType);


private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_ROGOWAKU_TYPE];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int m_nType = 0;
	int m_nLife = 5;
	D3DXVECTOR3 m_move;

};
#define ROGOWAKU_POLYGON_SIZE (25)
#define ROGOWAKU_POS_X			(0)		//弾の左上X座標
#define ROGOWAKU_POS_Y			(0)		//弾の左上Y座標
#define ROGOWAKU_WIDTH			(5)		//弾の幅
#define ROGOWAKU_HEIGHT			(5)		//弾の高さ
#define ROGOWAKU_POS_X2			(ROGOWAKU_POLYGON_SIZE - ROGOWAKU_POS_X / 2)		//弾の左上X座標
#define ROGOWAKU_POS_Y2			(ROGOWAKU_POLYGON_SIZE - ROGOWAKU_POS_Y / 2)		//弾の左上X座標


#endif