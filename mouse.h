//=============================================================================
//
// ���͏��� [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX				(256)	// �L�[�̍ő吔
#define	NUM_BUTTON_MAX			(8)		// �{�^��(�}�E�X)�̍ő吔

//==================================================================
//	�N���X�̒�`
//==================================================================
//�L�[�{�[�h���̓N���X
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
	// �L�[�{�[�h�̓��͏��(�v���X���)���擾
	//===================================================================
	inline bool GetPress(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
	//=============================================================================
	inline bool GetTrigger(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// �}�E�X�̃_�u������
	//=============================================================================
	inline	bool GetMousePressDouble(int nButton) { return (m_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false; };
	//=============================================================================
	// �}�E�X��X���W�̎擾
	//=============================================================================
	inline	LONG GetMouseX(void) { return (LONG)m_mouse.posX; };
	//=============================================================================
	// �}�E�X��Y���W�̎擾
	//=============================================================================
	inline	LONG GetMouseY(void) { return (LONG)m_mouse.posZ; };

private:
	MOUSE					m_mouse;								// �}�E�X�̏��

	BYTE					m_aButtonState[NUM_BUTTON_MAX];			// �}�E�X�̓��͏�񃏁[�N
	BYTE					m_aButtonStateTrigger[NUM_BUTTON_MAX];	// �}�E�X�̃g���K�[
	BYTE					m_aButtonStateDouble[NUM_BUTTON_MAX];	// �}�E�X�̃I���I�t
	HWND					m_hWnd;									// �E�B���h�E�n���h��

};

#endif // !_INPUTKEYBOARD_H_
