//=============================================================================
//
// 入力処理 [InputKeyboard.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "joypad.h"

LPDIRECTINPUTDEVICE8 CJoypad::m_pDevJoyboard = NULL;
int CJoypad::m_nCntpad = 0;
//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CJoypad::CJoypad()
{
	for (int nCntButton = 0; nCntButton <  NUM_JOY_MAX; nCntButton++)
	{
		m_nCntWaitRepeat = 0;
		m_nIntervalRepeat = 0;
		m_aJoyStateRepeatCntGamepad[nCntButton];	// リピート回数	//
		m_aJoyStateGamepad[nCntButton];			// ゲームパッド状態の保存場所
		m_aJoyStateTriggerGamepad[nCntButton];	// ゲームパッド状態のオン・オフ}
		m_aJoyStateReleaseGamepad[nCntButton];	// ゲームパッド状態の返しCJoypad::~CJoypad()
		m_aJoyStateRepeatGamepad[nCntButton];	// ゲームパッド状態を繰り返し{
	}
}
CJoypad::~CJoypad()
{

}
//===================================================================
//	初期化処理
//===================================================================
HRESULT CJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	// DirectInputオブジェクトの作成
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	m_nCntWaitRepeat = COUNT_WAIT_REPEAT;
	m_nIntervalRepeat = INTERVAL_REPEAT;

	for (m_nCntpad = 0; m_nCntpad < MAX_GAMEPAD; m_nCntpad++)
	{
		// 入力デバイス（ゲームパッド）の作成
		hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL,  EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
		if (FAILED(hr) || m_pDevJoyboard == NULL)
		{
			return hr;
		}


		// データフォーマットを設定
		hr = m_pDevJoyboard->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(hr))
		{
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr = m_pDevJoyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			return hr;
		}

		// デバイスの設定
		DIPROPRANGE diprg;

		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);

		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -GAMEPAD_MAX_RANGE;
		diprg.lMax = GAMEPAD_MAX_RANGE;
		m_pDevJoyboard->SetProperty(DIPROP_RANGE, &diprg.diph);

		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevJoyboard->SetProperty(DIPROP_RANGE, &diprg.diph);

		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevJoyboard->SetProperty(DIPROP_RANGE, &diprg.diph);

		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevJoyboard->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 入力制御開始
		m_pDevJoyboard->Acquire();

		// クリア
		memset(&m_aGamepadState, 0, sizeof(m_aGamepadState));
		memset(&m_aJoyStateGamepad[m_nCntpad], 0, sizeof(m_aJoyStateGamepad[m_nCntpad]));
		memset(&m_aJoyStateTriggerGamepad[m_nCntpad], 0, sizeof(m_aJoyStateTriggerGamepad[m_nCntpad]));
		memset(&m_aJoyStateReleaseGamepad[m_nCntpad], 0, sizeof(m_aJoyStateReleaseGamepad[m_nCntpad]));
		memset(&m_aJoyStateRepeatGamepad[m_nCntpad], 0, sizeof(m_aJoyStateRepeatGamepad[m_nCntpad]));
	}
	// 初期化完了
	return S_OK;

}
//===================================================================
//
// ジョイパッド能力取得
//
//===================================================================
BOOL CALLBACK CJoypad::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	static GUID pad_discrimination[MAX_GAMEPAD];
	DIDEVCAPS diDevCaps;

	if (FAILED(m_pInput->CreateDevice(pdidInstance->guidInstance, &m_pDevJoyboard, NULL)))
	{
		return DIENUM_CONTINUE;
	}

	// デバイスの能力取得
	diDevCaps.dwSize = sizeof(DIDEVCAPS);

	if (FAILED(m_pDevJoyboard->GetCapabilities(&diDevCaps)))
	{
		m_pDevJoyboard->Release();
		m_pDevJoyboard = NULL;
		return DIENUM_CONTINUE;
	}

	// デバイスの識別子を保存
	pad_discrimination[m_nCntpad] = pdidInstance->guidInstance;

	return DIENUM_STOP;
}

//===================================================================
//
// 入力の有無
//
//===================================================================
BOOL CALLBACK CJoypad::EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE pdidoi, LPVOID pContext)
{

	//for (int nCntPad = 0; nCntPad < 2; nCntPad++)
	{
		DIPROPRANGE diprg;

		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.diph.dwHow = DIPH_BYID;
		diprg.lMin = -32768;
		diprg.lMax = 32768;

		if (FAILED(m_pDevJoyboard->SetProperty(DIPROP_RANGE, &diprg.diph)))
		{
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}

//===================================================================
//	終了処理
//===================================================================
void CJoypad::Uninit(void)
{
	CInput::Uninit();

}

//===================================================================
//	更新処理
//===================================================================
void CJoypad::Update(void)
{
	bool aJoyState[NUM_JOY_MAX];	// キーボードの入力情報
	//int nCntPad;
	int nCntJoy;

		if (m_pDevJoyboard == NULL)
		{
			return;
		}

		for (nCntJoy = 0; nCntJoy < NUM_JOY_MAX; nCntJoy++)
		{
			aJoyState[nCntJoy] = m_aJoyStateGamepad[nCntJoy];	// キープレス情報保存
		}

		// デバイスからデータを取得
		if (SUCCEEDED(m_pDevJoyboard->GetDeviceState(sizeof(m_aGamepadState), &m_aGamepadState)))
		{
			// キー情報設定
			SetJoyStateGamepad();

			// 軸位置を記録
			m_aJoyStateAxis.y = (float)m_aGamepadState.lX / GAMEPAD_MAX_RANGE;
			m_aJoyStateAxis.x = (float)m_aGamepadState.lY / GAMEPAD_MAX_RANGE;
			m_aJoyStateAxis.z = (float)m_aGamepadState.lZ / GAMEPAD_MAX_RANGE;

			for (nCntJoy = 0; nCntJoy < NUM_JOY_MAX; nCntJoy++)
			{
				// トリガー・リリース・リピート情報の作成
				m_aJoyStateTriggerGamepad[nCntJoy] = (aJoyState[nCntJoy] ^ m_aJoyStateGamepad[nCntJoy]) & m_aJoyStateGamepad[nCntJoy];
				m_aJoyStateReleaseGamepad[nCntJoy] = (aJoyState[nCntJoy] ^ m_aJoyStateGamepad[nCntJoy]) & !m_aJoyStateGamepad[nCntJoy];
				m_aJoyStateRepeatGamepad[nCntJoy] = m_aJoyStateTriggerGamepad[nCntJoy];

				if (m_aJoyStateRepeatGamepad[nCntJoy])
				{
					m_aJoyStateRepeatCntGamepad[nCntJoy]++;
					if (m_aJoyStateRepeatCntGamepad[nCntJoy] < m_nCntWaitRepeat)
					{
						if (m_aJoyStateRepeatGamepad[nCntJoy] == 1)
						{
							m_aJoyStateRepeatGamepad[nCntJoy] = m_aJoyStateGamepad[nCntJoy];
						}

						else
						{
							m_aJoyStateRepeatGamepad[nCntJoy] = 0;
						}
					}
					else
					{
						if ((m_aJoyStateRepeatGamepad[nCntJoy] - m_nCntWaitRepeat) % m_nIntervalRepeat == 0)
						{
							m_aJoyStateRepeatGamepad[nCntJoy] = m_aJoyStateGamepad[nCntJoy];
						}

						else
						{
							m_aJoyStateRepeatGamepad[nCntJoy] = 0;
						}
					}
				}

				else
				{
					m_aJoyStateRepeatCntGamepad[nCntJoy] = 0;
					m_aJoyStateRepeatGamepad[nCntJoy] = 0;
				}
			}
		}
		else
		{
			m_pDevJoyboard->Acquire();
		}
	}
//===================================================================
//
// キー情報設定
//
//===================================================================
void CJoypad::SetJoyStateGamepad(void)
{
	// 変数宣言
	int nKey;

	if (m_aGamepadState.rgdwPOV[0] >= 225 * 100 && m_aGamepadState.rgdwPOV[0] <= 315 * 100)
	{
		// 十字キー[左]が押されている
		m_aJoyStateGamepad[JOYPADKEY_LEFT] = true;
	}

	else
	{
		// 十字キー[左]が押されている
		m_aJoyStateGamepad[JOYPADKEY_LEFT] = false;
	}

	if (m_aGamepadState.rgdwPOV[0] >= 45 * 100 && m_aGamepadState.rgdwPOV[0] <= 135 * 100)
	{
		// 十字キー[右]が押されている
		m_aJoyStateGamepad[JOYPADKEY_RIGHT] = true;
	}

	else
	{
		// 十字キー[右]が押されている
		m_aJoyStateGamepad[JOYPADKEY_RIGHT] = false;
	}

	if ((m_aGamepadState.rgdwPOV[0] >= 315 * 100 && m_aGamepadState.rgdwPOV[0] <= 360 * 100) ||
		(m_aGamepadState.rgdwPOV[0] >= 0 * 100 && m_aGamepadState.rgdwPOV[0] <= 45 * 100))
	{
		// 十字キー[上]が押されている
		m_aJoyStateGamepad[JOYPADKEY_UP] = true;
	}

	else
	{
		// 十字キー[上]が押されている
		m_aJoyStateGamepad[JOYPADKEY_UP] = false;
	}

	if (m_aGamepadState.rgdwPOV[0] >= 135 * 100 && m_aGamepadState.rgdwPOV[0] <= 225 * 100)
	{
		// 十字キー[下]が押されている
		m_aJoyStateGamepad[JOYPADKEY_DOWN] = true;
	}

	else
	{
		// 十字キー[下]が押されている
		m_aJoyStateGamepad[JOYPADKEY_DOWN] = false;
	}

	for (nKey = JOYPADKEY_X; nKey <= JOYPADKEY_START; nKey++)
	{
		if (m_aGamepadState.rgbButtons[nKey])
		{
			// ボタンが押されている
			m_aJoyStateGamepad[nKey] = true;
		}

		else
		{
			m_aJoyStateGamepad[nKey] = false;
		}
	}
}