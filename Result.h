//=============================================================================
// メイン処理 [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#define MAX_TEXTURE_RESULT (3)
#define MAX_POLIGON_RESULT (3)

#include"main.h"
class CFade;
class CResult
{
public:

	typedef enum
	{
		Result_Type_GameCrear,
		Result_Type_GAmeOver,
		Result_Type_MAX
	}Result_Type;
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);


	static CResult *Create(void);
private:
	CManeger::MODE m_mode;
	CFade *m_apfade;

	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXTURE_RESULT];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	CScene2D *m_apScene2D[MAX_POLIGON_RESULT];//ポリゴンの数

	Result_Type Resulttype;
};
#endif