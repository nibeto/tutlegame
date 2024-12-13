//=============================================================================
//
// ���͏��� [InputKeyboard.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include "joypad.h"

LPDIRECTINPUTDEVICE8 CJoypad::m_pDevJoyboard = NULL;
int CJoypad::m_nCntpad = 0;
//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CJoypad::CJoypad()
{
	for (int nCntButton = 0; nCntButton <  NUM_JOY_MAX; nCntButton++)
	{
		m_nCntWaitRepeat = 0;
		m_nIntervalRepeat = 0;
		m_aJoyStateRepeatCntGamepad[nCntButton];	// ���s�[�g��	//
		m_aJoyStateGamepad[nCntButton];			// �Q�[���p�b�h��Ԃ̕ۑ��ꏊ
		m_aJoyStateTriggerGamepad[nCntButton];	// �Q�[���p�b�h��Ԃ̃I���E�I�t}
		m_aJoyStateReleaseGamepad[nCntButton];	// �Q�[���p�b�h��Ԃ̕Ԃ�CJoypad::~CJoypad()
		m_aJoyStateRepeatGamepad[nCntButton];	// �Q�[���p�b�h��Ԃ��J��Ԃ�{
	}
}
CJoypad::~CJoypad()
{

}
//===================================================================
//	����������
//===================================================================
HRESULT CJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	// DirectInput�I�u�W�F�N�g�̍쐬
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	m_nCntWaitRepeat = COUNT_WAIT_REPEAT;
	m_nIntervalRepeat = INTERVAL_REPEAT;

	for (m_nCntpad = 0; m_nCntpad < MAX_GAMEPAD; m_nCntpad++)
	{
		// ���̓f�o�C�X�i�Q�[���p�b�h�j�̍쐬
		hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL,  EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
		if (FAILED(hr) || m_pDevJoyboard == NULL)
		{
			return hr;
		}


		// �f�[�^�t�H�[�}�b�g��ݒ�
		hr = m_pDevJoyboard->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(hr))
		{
			return hr;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = m_pDevJoyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			return hr;
		}

		// �f�o�C�X�̐ݒ�
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

		// ���͐���J�n
		m_pDevJoyboard->Acquire();

		// �N���A
		memset(&m_aGamepadState, 0, sizeof(m_aGamepadState));
		memset(&m_aJoyStateGamepad[m_nCntpad], 0, sizeof(m_aJoyStateGamepad[m_nCntpad]));
		memset(&m_aJoyStateTriggerGamepad[m_nCntpad], 0, sizeof(m_aJoyStateTriggerGamepad[m_nCntpad]));
		memset(&m_aJoyStateReleaseGamepad[m_nCntpad], 0, sizeof(m_aJoyStateReleaseGamepad[m_nCntpad]));
		memset(&m_aJoyStateRepeatGamepad[m_nCntpad], 0, sizeof(m_aJoyStateRepeatGamepad[m_nCntpad]));
	}
	// ����������
	return S_OK;

}
//===================================================================
//
// �W���C�p�b�h�\�͎擾
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

	// �f�o�C�X�̔\�͎擾
	diDevCaps.dwSize = sizeof(DIDEVCAPS);

	if (FAILED(m_pDevJoyboard->GetCapabilities(&diDevCaps)))
	{
		m_pDevJoyboard->Release();
		m_pDevJoyboard = NULL;
		return DIENUM_CONTINUE;
	}

	// �f�o�C�X�̎��ʎq��ۑ�
	pad_discrimination[m_nCntpad] = pdidInstance->guidInstance;

	return DIENUM_STOP;
}

//===================================================================
//
// ���̗͂L��
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
//	�I������
//===================================================================
void CJoypad::Uninit(void)
{
	CInput::Uninit();

}

//===================================================================
//	�X�V����
//===================================================================
void CJoypad::Update(void)
{
	bool aJoyState[NUM_JOY_MAX];	// �L�[�{�[�h�̓��͏��
	//int nCntPad;
	int nCntJoy;

		if (m_pDevJoyboard == NULL)
		{
			return;
		}

		for (nCntJoy = 0; nCntJoy < NUM_JOY_MAX; nCntJoy++)
		{
			aJoyState[nCntJoy] = m_aJoyStateGamepad[nCntJoy];	// �L�[�v���X���ۑ�
		}

		// �f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevJoyboard->GetDeviceState(sizeof(m_aGamepadState), &m_aGamepadState)))
		{
			// �L�[���ݒ�
			SetJoyStateGamepad();

			// ���ʒu���L�^
			m_aJoyStateAxis.y = (float)m_aGamepadState.lX / GAMEPAD_MAX_RANGE;
			m_aJoyStateAxis.x = (float)m_aGamepadState.lY / GAMEPAD_MAX_RANGE;
			m_aJoyStateAxis.z = (float)m_aGamepadState.lZ / GAMEPAD_MAX_RANGE;

			for (nCntJoy = 0; nCntJoy < NUM_JOY_MAX; nCntJoy++)
			{
				// �g���K�[�E�����[�X�E���s�[�g���̍쐬
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
// �L�[���ݒ�
//
//===================================================================
void CJoypad::SetJoyStateGamepad(void)
{
	// �ϐ��錾
	int nKey;

	if (m_aGamepadState.rgdwPOV[0] >= 225 * 100 && m_aGamepadState.rgdwPOV[0] <= 315 * 100)
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_LEFT] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_LEFT] = false;
	}

	if (m_aGamepadState.rgdwPOV[0] >= 45 * 100 && m_aGamepadState.rgdwPOV[0] <= 135 * 100)
	{
		// �\���L�[[�E]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_RIGHT] = true;
	}

	else
	{
		// �\���L�[[�E]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_RIGHT] = false;
	}

	if ((m_aGamepadState.rgdwPOV[0] >= 315 * 100 && m_aGamepadState.rgdwPOV[0] <= 360 * 100) ||
		(m_aGamepadState.rgdwPOV[0] >= 0 * 100 && m_aGamepadState.rgdwPOV[0] <= 45 * 100))
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_UP] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_UP] = false;
	}

	if (m_aGamepadState.rgdwPOV[0] >= 135 * 100 && m_aGamepadState.rgdwPOV[0] <= 225 * 100)
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_DOWN] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_aJoyStateGamepad[JOYPADKEY_DOWN] = false;
	}

	for (nKey = JOYPADKEY_X; nKey <= JOYPADKEY_START; nKey++)
	{
		if (m_aGamepadState.rgbButtons[nKey])
		{
			// �{�^����������Ă���
			m_aJoyStateGamepad[nKey] = true;
		}

		else
		{
			m_aJoyStateGamepad[nKey] = false;
		}
	}
}