//=============================================================================
//
// 入力処理 [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数

//==================================================================
//	クラスの定義
//==================================================================
//キーボード入力クラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);
//===================================================================
// キーボードの入力情報(プレス情報)を取得
//===================================================================
inline	bool GetPress(int nKey){return (m_aKeyState[nKey] & 0x80) ? true : false;};
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
inline	bool GetTrigger(int nKey) {return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;};


private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

#endif // !_INPUTKEYBOARD_H_
