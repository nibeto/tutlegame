//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include"main.h"
#include"Scene2D.h"
#define	MAX_BLOCK	(40)	// 自機

//レンダリングクラス
class Cblock : public CScene2D
{
public:
	Cblock(SCENE_NUMBER_TYPE m_Number);
	~Cblock();
	typedef enum
	{
		BLOCK_TYPE_TYPE_1 = 0,
		BLOCK_TYPE_TYPE_2,
		BLOCK_TYPE_TYPE_MAX

	}BLOCK_TYPE;

	typedef struct
	{

		D3DXVECTOR3 pos;


	}BLOCCK;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);
	float Vec3Dot(D3DXVECTOR3 *pV1, D3DXVECTOR3 *pV2);
	void Vec3Cross(D3DXVECTOR3 *pOut, D3DXVECTOR3*pV1, D3DXVECTOR3 *pV2);
	inline static Cblock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BLOCK_TYPE type, float rot, float LengthX, float LengthY) {
		//インスタンス
		Cblock*pBlock = NULL;
		pBlock = new Cblock(SCENE_NUMBER_TYPE_BLOCK);
		pBlock->Init(pos, move, rot, LengthX, LengthY);
		pBlock->BindTexture(m_pTexture[type]);

		return pBlock;

	};
	D3DXVECTOR3 GetBlock(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 Posold;//前回の位置
	D3DXVECTOR3 pMovee;//移動の量

	char nData[256];
	D3DXVECTOR3 m_move;
	BLOCCK m_aBlock[MAX_BLOCK];
	bool bLand;
	int nPattanAnim;

};

#define	MAX_TEX_BLOCK	(2)	// 自機

#define BLOCK_WIDTH			(30)		//プレイヤーの幅
#define BLOCK_HEIGHT			(30)		//プレイヤーの高さ
#define BLOCK_POS_X			(0)		//弾の左上X座標
#define BLOCK_POS_Y			(0)		//弾の左上Y座標
#define	BLOCK_POS_X2			(BLOCK_WIDTH - BLOCK_POS_X / 2)		//弾の左上X座標
#define BLOCK_POS_Y2			(BLOCK_HEIGHT -BLOCK_POS_Y / 2)		//弾の左上X座標
#define BLOCK_LONG_X			(BLOCK_WIDTH/2)
#define BLOCK_LONG_Y			(BLOCK_HEIGHT/2)


#endif