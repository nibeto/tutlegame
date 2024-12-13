//=============================================================================
//
// ���͏��� [input.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "input.h"

//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
LPDIRECTINPUT8	CInput::m_pInput = NULL;		//DirectInput�f�o�C�X�̃|�C���^

//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CInput::CInput()
{
	//m_pDevice = NULL;
}
CInput::~CInput()
{

}

//===================================================================
//	����������
//===================================================================
HRESULT CInput::Init(HINSTANCE hInstance,HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

	}
	return S_OK;
}

//===================================================================
//	�I������
//===================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}


