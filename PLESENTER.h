//=============================================================================
//
// 背景処理 [Parturn.h]
// Author :
//
//=============================================================================
#ifndef _PLESENTER_H_
#define _PLESENTER_H_
#include"main.h"
#include"Scene2D.h"
class CManeger;

#define MAX_PLESENTER	(1)
//レンダリングクラス
class CPLESEENTER
{
public:
	CPLESEENTER();
	~CPLESEENTER();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPLESEENTER *Create(D3DXVECTOR3 pos, float Length, int nType);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[1];		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;

};
#endif //  _PLESENTER_H
