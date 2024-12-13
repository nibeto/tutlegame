//=============================================================================
//
// ���͏��� [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TRUN (32768.0f)
#define GAMEPAD_MAX_RANGE (1024)
#define	NUM_JOY_MAX			(256)	// �L�[�̍ő吔
#define COUNT_WAIT_REPEAT (20)
#define INTERVAL_REPEAT (1)
#define MAX_GAMEPAD (4)

//==================================================================
//	�N���X�̒�`
//==================================================================
//�L�[�{�[�h���̓N���X
class CJoypad : public CInput
{
public:
	CJoypad();
	~CJoypad();

	// �\���̔ԍ�(enum)
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
	// �L�[�{�[�h�̓��͏��(�v���X���)���擾
	//===================================================================
	inline	bool GetPress(JOYPADKEY key) { return m_aJoyStateGamepad[key]; };
	//=============================================================================
	// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
	//=============================================================================
	inline	bool GetTrigger(JOYPADKEY key) { return m_aJoyStateTriggerGamepad[key]; };
	//===================================================================
	//
	//�W���C�p�b�h�̔j��
	//
	//===================================================================
	inline	bool GetJoyboardRelease(JOYPADKEY key) { return m_aJoyStateReleaseGamepad[key]; };
	//===================================================================
	//
	//�W���C�p�b�h�̌J��Ԃ�
	//
	//===================================================================
	inline	bool GetJoyboardRepeat(JOYPADKEY key) { return m_aJoyStateRepeatGamepad[key]; };
	//===================================================================
	//
	//�Q�[���p�b�h�̍����擾
	//
	//===================================================================
	inline	int GetGamepadTriggerLeft(JOYPADKEY key) { return m_aGamepadState.rgbButtons[JOYPADKEY_LEFT_2]; };
	//===================================================================
	//
	//�Q�[���p�b�h�̉E���擾
	//
	//===================================================================
	inline int GetGamepadTriggerRight(JOYPADKEY key) { return m_aGamepadState.rgbButtons[JOYPADKEY_RIGHT_2]; };
	//===================================================================
	//
	//�Q�[���p�b�h�̃X�e�B�b�N�̍����擾
	//
	//===================================================================
	inline	void GetGamepadStickLeft(int *pValueH, int *pValueV) { *pValueH = m_aGamepadState.lX; *pValueV = -m_aGamepadState.lY; };
	//===================================================================
	//
	//�Q�[���p�b�h�̃X�e�B�b�N�̉E���擾
	//
	//===================================================================
	inline void GetGamepadStickRight(int *pValueH, int *pValueV) { *pValueH = m_aGamepadState.lZ; *pValueV = -m_aGamepadState.lRz; };



	void SetJoyStateGamepad(void);
private:


static	LPDIRECTINPUTDEVICE8 m_pDevJoyboard;		// ���̓f�o�C�X�ւ̃|�C���^
	DIJOYSTATE2 m_aGamepadState;					// �Q�[���p�b�h��Ԃ��󂯎�郏�[�N
	D3DXVECTOR3 m_aJoyStateAxis;					// �X�e�B�b�N�̈ʒu���
	int m_nCntWaitRepeat = 0;										// �J�E���g�}�b�N�X
	int m_nIntervalRepeat = 0;									// �����̊�
	static int m_nCntpad;											// �J�E���g
	int	m_aJoyStateRepeatCntGamepad[NUM_JOY_MAX];	// ���s�[�g��
	bool m_aJoyStateGamepad[NUM_JOY_MAX];			// �Q�[���p�b�h��Ԃ̕ۑ��ꏊ
	bool m_aJoyStateTriggerGamepad[NUM_JOY_MAX];	// �Q�[���p�b�h��Ԃ̃I���E�I�t
	bool m_aJoyStateReleaseGamepad[NUM_JOY_MAX];	// �Q�[���p�b�h��Ԃ̕Ԃ�
	bool m_aJoyStateRepeatGamepad[NUM_JOY_MAX];	// �Q�[���p�b�h��Ԃ��J��Ԃ�

	const DIDEVICEINSTANCE* pdidInstance;
	VOID* pContext;
	HRESULT hr;

};

#endif // !_INPUTKEYBOARD_H_
