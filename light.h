//=============================================================================
//
// 入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//レンダリングクラス
class CLIGHT
{
public:
	CLIGHT();
	~CLIGHT();
	static CLIGHT*Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;				// 入力デバイスへのポインタ

private:
	D3DLIGHT9 m_light;				//ライトの情報

};

#endif
