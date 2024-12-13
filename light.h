//=============================================================================
//
// ���͏��� [input.h]
// Author :
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//�����_�����O�N���X
class CLIGHT
{
public:
	CLIGHT();
	~CLIGHT();
	static CLIGHT*Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;				// ���̓f�o�C�X�ւ̃|�C���^

private:
	D3DLIGHT9 m_light;				//���C�g�̏��

};

#endif
