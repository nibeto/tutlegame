//=============================================================================
//
// ポーズメニュー処理 [pauseselect.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include"Scene2D.h"

#define PAUSESERECT_TEXTURE (3)
//レンダリングクラス
class CPAUSESELECT
{
public:
	//*****************************************************************************
	// 構造体定義
	//*****************************************************************************
	typedef enum
	{
		SELECTMODE_NONE = 0,
		SELECTMODE_CONTINUE,		//続行状態
		SELECTMODE_RETRY,			//リトライ状態
		SELECTMODE_QUIT,			//終了
		SELECTMODE_MAX				//状態の総数
	}SELECTMODE;						//列挙型

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//選ばれていない状態
		SELECTTYPE_SELECT,		//選ばれている	状態
		SELECTTYPE_MAX				//状態の総数
	}SELECT;

	typedef struct
	{
		SELECT		select;		//セレクト
		D3DXVECTOR3 pos;		//位置
		D3DXCOLOR	col;		//カラー
	}PAUSESELECT;

	CPAUSESELECT();
	~CPAUSESELECT();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);
	void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col);


	static CPAUSESELECT *Create(D3DXVECTOR3 pos, float Length, int nType);
	inline	SELECTMODE *GetPauseMode(void) { return &m_SelectMode; };


private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[PAUSESERECT_TEXTURE];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;
	LPDIRECT3DTEXTURE9		m_pTexturePauseSelect[PAUSESERECT_TEXTURE] = {};		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPauseSelect = NULL;					// 頂点バッファへのポインタ
	PAUSESELECT				m_aPauseMenu[PAUSESERECT_TEXTURE];					// ポーズメニュー
	D3DXVECTOR3				m_PauseMenuPos;
	SELECTMODE				m_SelectMode = SELECTMODE_NONE;
	int						m_nSelect;

};
#endif