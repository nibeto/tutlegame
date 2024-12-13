//=============================================================================
//
// メイン処理 [renderer.h]
// Author :moritakamasaya
//
//=============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//レンダリングクラス
class CRenderer
{
public:
	enum CsceneName
	{
		CsceneName_SceneName3D,
		CsceneName_Scene2D,
		CsceneName_MAX
	};
	CRenderer();
	~CRenderer();
	inline LPDIRECT3DDEVICE9	GetDevice(void) { return m_pD3DDevice; };//ポインター返すときのみ

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawPlayerFps(void);
	void DrawBlockFps(void);

#endif

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG

	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
#endif
	//変数
	int m_nLife;
	int m_nAttack;
	int m_nSpeed;

	CsceneName sceneName;
protected:


};


#endif