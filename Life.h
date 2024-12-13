#ifndef _LIFE_H_
#define _LIFE_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_LIFE_TYPE (2)//a =	透明度 (0～255)

//レンダリングクラス
class cLife : public CScene2D
{
public:
	cLife(SCENE_NUMBER_TYPE m_Number);
	~cLife();
	typedef enum
	{
		LIFE_TYPE_BASE = 0,
		LIFE_TYPE_1 = 1,
		LIFE_TYPE_2,
		LIFE_TYPE_MAX

	}LIFE_TYPE;
	typedef enum
	{//タイプ
		LIFE_OBJ_TYPE_LIFE = 0,
		LIFE_OBJ_TYPE_LIFE_ENEMY,
		LIFE_OBJ_TYPE_MP,
		LIFE_OBJ_TYPE_MAX
	}LIFE_OBJ_TYPE;


	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int  GetLife(int nLife);
	int  GetMagicpoint(int nMagicPoint);

	static cLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, LIFE_TYPE type, LIFE_OBJ_TYPE nType);
	LIFE_OBJ_TYPE Type;//タイプ


private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LIFE_TYPE];		// テクスチャへのポインタ
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
	int m_nLife = 0;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;

};
#define LIFE_POLYGON_SIZE (25)

#define	MAX_LIFE_BOX			(4)		// 弾の最大数

#define	MAX_LIFE			(40)		// 弾の最大数
#define LIFE_POS_X			(0)		//弾の左上X座標
#define LIFE_POS_Y			(0)		//弾の左上Y座標
#define LIFE_HEIGHT			(40)		//弾の高さ
#define LIFE_WIDTH              (150)
#define LIFEN_TEXTURE_SPEED	(0.5f)			//弾アニメーションスピード
#define LIFE_TEXTURE_UV_U		(1.0f)		//弾アニメーションU範囲
#define LIFE_TEXTURE_UV_V		(1.0f)		//弾アニメーションV範囲
#define	LIFE_CM				(40)//壁との距離




#endif // !_COLLISION_H_
