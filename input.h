//=============================================================================
//
// ���͏��� [input.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"


//==================================================================
//	�N���X�̒�`
//==================================================================
//���̓N���X
class CInput
{
public:
	//�R���X�g���N�^&�f�X�g���N�^
	CInput();
	virtual ~CInput();

	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void    Uninit(void);
	virtual void    Update(void) = 0;

protected:
	//�����o�ϐ�
	static LPDIRECTINPUT8	m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevice;

};

#endif //!_INPUT_H_