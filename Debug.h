//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include"main.h"
#include"Scene2D.h"

#define MAX_NUM_DEBUG (20)
//レンダリングクラス
class CDebug : public CScene2D
{
public:
	CDebug(SCENE_NUMBER_TYPE m_Number);
	~CDebug();
	typedef enum
	{
		DEBUG_TYPE_BASE = 0,
		DEBUG_TYPE_1,
		DEBUG_TYPE_MAX
	}DEBUG_TYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		float f_sizeX;
		float f_sizeY;
		float f_rot;
		int  type;
	}Debug;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CorisionDebug(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3	*pMove);
	D3DXVECTOR3	GetPos(void) { return m_pos; };
	float GetSizeX(void) { return CScene2D::GetLengthX(); };
	float GetSizeY(void) { return CScene2D::GetLengthY(); };

	void Save(void);
	static void Loads(void);

	static int GetNumBlock(void);

	static Debug *Getblock(void);

	static CDebug *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY, DEBUG_TYPE type) {
		//インスタンス
		CDebug*pBlock = NULL;
		pBlock = new CDebug(SCENE_NUMBER_TYPE_DEBUG);
		pBlock->Init(pos, move, rot, LengthX, LengthY);
		pBlock->BindTexture(m_pTexture[type]);

		return pBlock;
		//インスタンス
	};


private:
	static LPDIRECT3DTEXTURE9		m_pTexture[DEBUG_TYPE_MAX];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 Oldpos;
	D3DXCOLOR col;
	D3DXVECTOR3 pPos;//現在の位置
	D3DXVECTOR3 pPosold;//前回の位置
	D3DXVECTOR3 pMove;//移動の量

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//カウンタ変数
									//float m_fPosSize = 0.0f;	//サイズ変更用
	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float mf_pos = 0.0f;//(posの長さの変数)
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	bool m_bjump;
	bool m_bDisp;
	int nCountBullet;
	static int nNumBlock;
	static Debug m_block[MAX_NUM_DEBUG];
};

#define DEBUG_POLYGON_SIZE (25)
#define	MAX_TypeDEBUG			(4)		// 弾の最大数
#define	MAX_DEBUG			(40)		// 弾の最大数
#define DEBUG_POS_X			(0)		//弾の左上X座標
#define DEBUG_POS_Y			(0)		//弾の左上Y座標
#define DEBUG_HEIGHT			(40)		//弾の高さ
#define DEBUG_WIDTH              (150)
#define DEBUGN_TEXTURE_SPEED	(0.5f)			//弾アニメーションスピード
#define DEBUG_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define DEBUG_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲
#define	DEBUG_CM				(40)//壁との距離




#endif