//=============================================================================
//
// 入力処理 [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX				(256)	// キーの最大数
#define	NUM_BUTTON_MAX			(8)		// ボタン(マウス)の最大数

//==================================================================
//	クラスの定義
//==================================================================
//キーボード入力クラス
class CMouse : public CInput
{
public:
	CMouse();
	~CMouse();

	typedef struct
	{

		DIMOUSESTATE2 mouseState;
		float posX;
		float posZ;

	}MOUSE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	//===================================================================
	// キーボードの入力情報(プレス情報)を取得
	//===================================================================
	inline bool GetPress(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// キーボードの入力情報(トリガー情報)を取得
	//=============================================================================
	inline bool GetTrigger(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// マウスのダブル処理
	//=============================================================================
	inline	bool GetMousePressDouble(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// マウスのX座標の取得
	//=============================================================================
	inline	LONG GetMouseX(void) { return (LONG)m_mouse.posX; };
	//=============================================================================
	// マウスのY座標の取得
	//=============================================================================
	inline	LONG GetMouseY(void) { return (LONG)m_mouse.posZ; };

private:
	MOUSE					m_mouse;								// マウスの情報

	BYTE					m_aButtonState[NUM_BUTTON_MAX];			// マウスの入力情報ワーク
	BYTE					m_aButtonStateTrigger[NUM_BUTTON_MAX];	// マウスのトリガー
	BYTE					m_aButtonStateDouble[NUM_BUTTON_MAX];	// マウスのオンオフ
	HWND					m_hWnd;									// ウィンドウハンドル

};

#endif // !_INPUTKEYBOARD_H_
