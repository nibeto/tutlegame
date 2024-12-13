//=============================================================================
//
// ���͏��� [InputKeyboard.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "InputKeyboard.h"

//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = 0;	//�v���X
		m_aKeyStateTrigger[nCntKey] = 0;
	}

}
CInputKeyboard::~CInputKeyboard()
{

}
//===================================================================
//	����������
//===================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();


	return S_OK;
}

//===================================================================
//	�I������
//===================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//===================================================================
//	�X�V����
//===================================================================
void CInputKeyboard::Update(void)
{

	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	 //�g���K�[
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�v���X

		}
	}
	else
	{
		m_pDevice->Acquire();
	}

}
