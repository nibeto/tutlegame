//=============================================================================
//
// 入力処理 [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TRUN (32768.0f)
#define GAMEPAD_MAX_RANGE (1024)
#define	NUM_JOY_MAX			(256)	// キーの最大数
#define COUNT_WAIT_REPEAT (20)
#define INTERVAL_REPEAT (1)
#define MAX_GAMEPAD (4)

//==================================================================
//	クラスの定義
//==================================================================
//キーボード入力クラス
class CJoypad : public CInput
{
public:
	CJoypad();
	~CJoypad();

	// 構造体番号(enum)
	typedef enum
	{
		JOYPADKEY_X = 0,
		JOYPADKEY_Y,
		JOYPADKEY_A,
		JOYPADKEY_B,
		JOYPADKEY_LEFT_1,
		JOYPADKEY_RIGHT_1,
		JOYPADKEY_LEFT_2,
		JOYPADKEY_RIGHT_2,
		JOYPADKEY_LEFT_STICK,
		JOYPADKEY_RIGHT_STICK,
		JOYPADKEY_BACK,
		JOYPADKEY_START,
		JOYPADKEY_LEFT,
		JOYPADKEY_RIGHT,
		JOYPADKEY_UP,
		JOYPADKEY_DOWN,
		JOYPADKEY_MAX,
	}JOYPADKEY;

	typedef struct
	{

		DIMOUSESTATE2 mouseState;
		float posX;
		float posZ;

	}MOUSE;
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE pdidoi, LPVOID pContext);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);








	//===================================================================
	// キーボードの入力情報(プレス情報)を取得
	//===================================================================
	inline	bool GetPress(JOYPADKEY key) { return m_aJoyStateGamepad[key]; };
	//=============================================================================
	// キーボードの入力情報(トリガー情報)を取得
	//=============================================================================
	inline	bool GetTrigger(JOYPADKEY key) { return m_aJoyStateTriggerGamepad[key]; };
	//===================================================================
	//
	//ジョイパッドの破棄
	//
	//===================================================================
	inline	bool GetJoyboardRelease(JOYPADKEY key) { return m_aJoyStateReleaseGamepad[key]; };
	//===================================================================
	//
	//ジョイパッドの繰り返し
	//
	//===================================================================
	inline	bool GetJoyboardRepeat(JOYPADKEY key) { return m_aJoyStateRepeatGamepad[key]; };
	//===================================================================
	//
	//ゲームパッドの左を取得
	//
	//===================================================================
	inline	int GetGamepadTriggerLeft(JOYPADKEY key) { return m_aGamepadState.rgbButtons[JOYPADKEY_LEFT_2]; };
	//===================================================================
	//
	//ゲームパッドの右を取得
	//
	//===================================================================
	inline int GetGamepadTriggerRight(JOYPADKEY key) { return m_aGamepadState.rgbButtons[JOYPADKEY_RIGHT_2]; };
	//===================================================================
	//
	//ゲームパッドのスティックの左を取得
	//
	//===================================================================
	inline	void GetGamepadStickLeft(int *pValueH, int *pValueV) { *pValueH = m_aGamepadState.lX; *pValueV = -m_aGamepadState.lY; };
	//===================================================================
	//
	//ゲームパッドのスティックの右を取得
	//
	//===================================================================
	inline void GetGamepadStickRight(int *pValueH, int *pValueV) { *pValueH = m_aGamepadState.lZ; *pValueV = -m_aGamepadState.lRz; };



	void SetJoyStateGamepad(void);
private:


static	LPDIRECTINPUTDEVICE8 m_pDevJoyboard;		// 入力デバイスへのポインタ
	DIJOYSTATE2 m_aGamepadState;					// ゲームパッド状態を受け取るワーク
	D3DXVECTOR3 m_aJoyStateAxis;					// スティックの位置情報
	int m_nCntWaitRepeat = 0;										// カウントマックス
	int m_nIntervalRepeat = 0;									// 往復の間
	static int m_nCntpad;											// カウント
	int	m_aJoyStateRepeatCntGamepad[NUM_JOY_MAX];	// リピート回数
	bool m_aJoyStateGamepad[NUM_JOY_MAX];			// ゲームパッド状態の保存場所
	bool m_aJoyStateTriggerGamepad[NUM_JOY_MAX];	// ゲームパッド状態のオン・オフ
	bool m_aJoyStateReleaseGamepad[NUM_JOY_MAX];	// ゲームパッド状態の返し
	bool m_aJoyStateRepeatGamepad[NUM_JOY_MAX];	// ゲームパッド状態を繰り返し

	const DIDEVICEINSTANCE* pdidInstance;
	VOID* pContext;
	HRESULT hr;

};

#endif // !_INPUTKEYBOARD_H_
