//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"

#define MAX_PAUSE (3)
#define PAUSE_TEXTURE (2)

//#define POLYGON_POS_X			(20)							//頂点座標Xの移動量
//#define POLYGON_POS_Y			(20)							//頂点座標Yの移動量
//#define TEX_POS_X_INIT			(1.0f)							//テクスチャ座標Uの初期位置
//#define TEX_POS_Y_INIT			(1.0f)							//テクスチャ座標Vの初期位置
//#define TEX_LEFT				(0.0f)							//テクスチャ座標U左
//#define TEX_RIGHT				(1.0f)							//テクスチャ座標U右
//#define TEX_TOP					(0.0f)							//テクスチャ座標V上
//#define TEX_BOT					(1.0f)							//テクスチャ座標V下
//#define TIME					(60)							//タイム


//レンダリングクラス
class CPAUSESELECT;
class CScene2D;

class CPause : public CScene
{
public:
	CPause();
	~CPause();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause *Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[PAUSE_TEXTURE];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	CScene2D *m_apScene2D[2];//ポリゴンの数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//カウンタ変数
	int nScore = 0; 						//float m_fPosSize = 0.0f;	//サイズ変更用
	int m_aScoreDigit[50]; 						//float m_fPosSize = 0.0f;	//サイズ変更用

	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float mf_pos = 0.0f;//(posの長さの変数)
	LPDIRECT3DDEVICE9 pDevice;
	CPAUSESELECT *m_apPause[MAX_PAUSE];
	int	m_nTime;				// タイム
	int m_nAnswer = 0;
	int m_nCntTimer;
	bool bDraw;

};
#endif
