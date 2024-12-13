//=============================================================================
//
// ���͏��� [InputKeyboard.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "mouse.h"

//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CMouse::CMouse()
{
	try
	{

	for (int nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
	{
		m_aButtonState[nCntButton] = 0;			// �}�E�X�̓��͏�񃏁[�N
		m_aButtonStateTrigger[nCntButton] = 0;	// �}�E�X�̃g���K�[
		m_aButtonStateDouble[nCntButton] = 0;	// �}�E�X�̃I���I�t
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
//	����������
//===================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	try
	{

	CInput::Init(hInstance, hWnd);

	m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL);
	m_pDevice->SetDataFormat(&c_dfDIMouse2); // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�

	m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// ���͐���J�n
	m_pDevice->Acquire();
	// ���
	m_hWnd = hWnd;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;

}

//===================================================================
//	�I������
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
//	�X�V����
//===================================================================
void CMouse::Update(void)
{
	try
	{
	// �ϐ��錾
	int nCntButton;
	POINT point;

	// �l�̏�����
	m_mouse.mouseState.rgbButtons[0] = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_mouse.posX = (float)point.x;
	m_mouse.posZ = (float)point.y;

	// �l�̍X�V
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_mouse.mouseState)))
	{
		for (nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// �r���I�_���a���ǂ������f
			m_aButtonStateTrigger[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.mouseState.rgbButtons[nCntButton]) & m_mouse.mouseState.rgbButtons[nCntButton];
			m_aButtonStateDouble[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.mouseState.rgbButtons[nCntButton]);
			m_aButtonState[nCntButton] = m_mouse.mouseState.rgbButtons[nCntButton];	// �L�[�v���X���ۑ�
		}
	}

	else
	{
		m_pDevice->Acquire(); // �P���ڂ�Q���ڂɃG���[���o�邪�������Ă悢�B
	}

	}
	catch (const std::exception&)
	{

	}

}