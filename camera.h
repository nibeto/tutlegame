//=============================================================================
//
// ���͏��� [input.h]
// Author :
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include"Scene3D.h"
#define MAX_CAMERA (4)
//�����_�����O�N���X
class CCAMERA
{
public:
	//*****************************************************************************
	// �J�����̍\����
	//*****************************************************************************
	typedef struct
	{
		D3DXVECTOR3 posV;			//���_
		D3DXVECTOR3 posR;			//�����_
		D3DXVECTOR3 posU;			//������x�N�g��
		D3DXVECTOR3 posVDest;
		D3DXVECTOR3 posRDest;
		D3DXVECTOR3 rotCamera;		//����
		D3DXVECTOR3 rotDest;
		D3DXVECTOR3 DiffAngle;
		D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X(�e���r)
		D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X(�J�����}��)
		float nCounterAngle;			//�J�����A���O�����ς��J�E���^�[
		D3DVIEWPORT9 Viewport;		//�r���[�|�[�g
	}Camera;
	CCAMERA();
	~CCAMERA();
	static CCAMERA *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(int nIdxCamera);
	void cameraPos(void);
	void CameraGame(float fMove, float fSpeedMove, float fMovePos);
	void CameraTutorial(float fMove, float fSpeedMove, float fMovePos);
	void CameraTitle(void);
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;				// ���̓f�o�C�X�ւ̃|�C���^

private:
	Camera m_Camera[MAX_CAMERA];	//�J�����̏��
	float fLength;

	float fAngle = 0.0f;					//�p�x
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 posV;				//���_
	D3DXVECTOR3 posR;				//���ӓ_
	D3DXVECTOR3 vecU;				//������x�N�g��


};

#endif
