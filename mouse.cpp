//=============================================================================
//
// 入力処理 [InputKeyboard.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "mouse.h"

//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CMouse::CMouse()
{
	try
	{

	for (int nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
	{
		m_aButtonState[nCntButton] = 0;			// マウスの入力情報ワーク
		m_aButtonStateTrigger[nCntButton] = 0;	// マウスのトリガー
		m_aButtonStateDouble[nCntButton] = 0;	// マウスのオンオフ
	}
	}
	catch (const std::exception&)
	{

	}

}
CMouse::~CMouse()
{

}
//===================================================================
//	初期化処理
//===================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	try
	{

	CInput::Init(hInstance, hWnd);

	m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL);
	m_pDevice->SetDataFormat(&c_dfDIMouse2); // マウス用のデータ・フォーマットを設定

	m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// 入力制御開始
	m_pDevice->Acquire();
	// 代入
	m_hWnd = hWnd;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;

}

//===================================================================
//	終了処理
//===================================================================
void CMouse::Uninit(void)
{
	try
	{

	CInput::Uninit();
	}
	catch (const std::exception&)
	{

	}

}

//===================================================================
//	更新処理
//===================================================================
void CMouse::Update(void)
{
	try
	{
	// 変数宣言
	int nCntButton;
	POINT point;

	// 値の初期化
	m_mouse.mouseState.rgbButtons[0] = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_mouse.posX = (float)point.x;
	m_mouse.posZ = (float)point.y;

	// 値の更新
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_mouse.mouseState)))
	{
		for (nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// 排他的論理和かどうか判断
			m_aButtonStateTrigger[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.mouseState.rgbButtons[nCntButton]) & m_mouse.mouseState.rgbButtons[nCntButton];
			m_aButtonStateDouble[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.mouseState.rgbButtons[nCntButton]);
			m_aButtonState[nCntButton] = m_mouse.mouseState.rgbButtons[nCntButton];	// キープレス情報保存
		}
	}

	else
	{
		m_pDevice->Acquire(); // １発目や２発目にエラーが出るが無視してよい。
	}

	}
	catch (const std::exception&)
	{

	}

}