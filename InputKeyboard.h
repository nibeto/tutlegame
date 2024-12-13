//=============================================================================
//
// ���͏��� [inputKeyboard.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#include "input.h"

//==================================================================
// �}�N����`
//==================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔

//==================================================================
//	�N���X�̒�`
//==================================================================
//�L�[�{�[�h���̓N���X
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);
//===================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//===================================================================
inline	bool GetPress(int nKey){return (m_aKeyState[nKey] & 0x80) ? true : false;};
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
inline	bool GetTrigger(int nKey) {return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;};


private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

#endif // !_INPUTKEYBOARD_H_
