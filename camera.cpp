//=============================================================================
//
// ���͏��� [input.cpp]
// Author :
//
//=============================================================================
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include"Scene3D.h"
#include "Game.h"
//*************************************************************************************************************************
#define MOVE_CAMERA			(17.3f)						//���f���ړ���
#define MOVE_SIN_COS_TOP_CAMERA	(0.75f)						//�J�����ړ���
#define MOVE_SIN_COS_BOT_CAMERA	(0.25f)						//�J�����ړ���

CCAMERA *CCAMERA::Create(void)
{
	//�C���X�^���X
	CCAMERA*pCamera = NULL;
	pCamera = new CCAMERA();
	pCamera->Init();
	return pCamera;
	//�C���X�^���X
}


CCAMERA::CCAMERA()
{

	m_pDevice = NULL;

}
CCAMERA::~CCAMERA()
{

}


HRESULT  CCAMERA::Init(void)
{

	cameraPos();
	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CCAMERA::Uninit(void)
{


}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CCAMERA::Update(void)
{

	CameraTutorial(0.0f, 0.0f, 0.0f);
}
void CCAMERA::SetCamera(int nIdxCamera)
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//�@�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&m_Camera[nIdxCamera].Viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera[nIdxCamera].mtxProjection);

	if (nIdxCamera == 0)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&m_Camera[nIdxCamera].mtxProjection,
			D3DXToRadian(45.0f),
			(float)m_Camera[nIdxCamera].Viewport.Width / (float)m_Camera[nIdxCamera].Viewport.Height,
			10.0f,
			6000.0f);
	}
	if (nIdxCamera == 1)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&m_Camera[nIdxCamera].mtxProjection,
			D3DXToRadian(30.0f),
			(float)m_Camera[nIdxCamera].Viewport.Width / (float)m_Camera[nIdxCamera].Viewport.Height,
			10.0f,
			6000.0f);
	}
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Camera[nIdxCamera].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera[nIdxCamera].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_Camera[nIdxCamera].mtxView,
		&m_Camera[nIdxCamera].posV,
		&m_Camera[nIdxCamera].posR,
		&m_Camera[nIdxCamera].posU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_Camera[nIdxCamera].mtxView);
	}
	catch (const std::exception&)
	{

	}

}

void CCAMERA::cameraPos(void)
{
	try
	{

		//�r���[�|�[�g�̏�����
	m_Camera[0].Viewport.X = 0;
	m_Camera[0].Viewport.Y = 0;
	m_Camera[0].Viewport.Width = SCREEN_WIDTH;
	m_Camera[0].Viewport.Height = SCREEN_HEIGHT;
	m_Camera[0].Viewport.MinZ = 0.0f;
	m_Camera[0].Viewport.MaxZ = 1.0f;

	m_Camera[0].posV = D3DXVECTOR3(0.0f, 200.0f, -1500.0f);
	m_Camera[0].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera[0].posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Camera[0].rotCamera = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_Camera[0].nCounterAngle = 0;

	fLength = sqrtf(
		//X�̋��������߂�@X�̋�����2��
		(m_Camera[0].posR.x - m_Camera[0].posV.x) * (m_Camera[0].posR.x - m_Camera[0].posV.x)
		//Z�̋��������߂�@Z�̋�����2��
		+ (m_Camera[0].posR.z - m_Camera[0].posV.z) * (m_Camera[0].posR.z - m_Camera[0].posV.z));



	//�r���[�|�[�g�̏�����
	m_Camera[1].Viewport.X = 0;
	m_Camera[1].Viewport.Y = 420;
	m_Camera[1].Viewport.Width = 300;
	m_Camera[1].Viewport.Height = SCREEN_HEIGHT;
	m_Camera[1].Viewport.MinZ = 0.0f;
	m_Camera[1].Viewport.MaxZ = 1.0f;

	m_Camera[1].posV = D3DXVECTOR3(0.0f, 6000.0f, 0.0f);
	m_Camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera[1].posU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Camera[1].rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera[1].nCounterAngle = 0;
	}
	catch (const std::exception&)
	{

	}

}

void CCAMERA::CameraGame(float fMove, float fSpeedMove, float fMovePos)
{
	try
	{

	CPlayer *pPLayer = CGame::GetPlayer();

	m_Camera[0].posRDest.x = pPLayer->GetPos().x - sinf(pPLayer->GetRot().y);
	m_Camera[0].posRDest.y = pPLayer->GetPos().y;
	m_Camera[0].posRDest.z = pPLayer->GetPos().z - cosf(pPLayer->GetRot().y);

	m_Camera[0].posV.x += ((m_Camera[0].posVDest.x - m_Camera[0].posV.x) * fMove);
	m_Camera[0].posV.y += ((m_Camera[0].posVDest.y - m_Camera[0].posV.y) * fMove) + fMovePos;
	m_Camera[0].posV.z += ((m_Camera[0].posVDest.z - m_Camera[0].posV.z) * fMove);

	m_Camera[1].posR.x += (m_Camera[0].posRDest.x - m_Camera[0].posR.x) * fMove;
	m_Camera[1].posR.y += (m_Camera[0].posRDest.y - m_Camera[0].posR.y) * fMove;
	m_Camera[1].posR.z += (m_Camera[0].posRDest.z - m_Camera[0].posR.z) * fMove;

	m_Camera[1].posV.x += ((m_Camera[0].posVDest.x - m_Camera[0].posV.x) * fMove);
	m_Camera[1].posV.y += ((m_Camera[0].posVDest.y - m_Camera[0].posV.y) * fMove) + fMovePos;
	m_Camera[1].posV.z += ((m_Camera[0].posVDest.z - m_Camera[0].posV.z) * fMove);
	}
	catch (const std::exception&)
	{

	}

}

void CCAMERA::CameraTutorial(float fMove, float fSpeedMove, float fMovePos)
{
	try
	{

	m_Camera[0].posR.x += (m_Camera[0].posRDest.x - m_Camera[0].posR.x) * fMove;
	m_Camera[0].posR.y += (m_Camera[0].posRDest.y - m_Camera[0].posR.y) * fMove;
	m_Camera[0].posR.z += (m_Camera[0].posRDest.z - m_Camera[0].posR.z) * fMove;


	m_Camera[0].posV.x += ((m_Camera[0].posVDest.x - m_Camera[0].posV.x) * fMove);
	m_Camera[0].posV.y += ((m_Camera[0].posVDest.y - m_Camera[0].posV.y) * fMove) + fMovePos;
	m_Camera[0].posV.z += ((m_Camera[0].posVDest.z - m_Camera[0].posV.z) * fMove);

	m_Camera[1].posR.x += (m_Camera[0].posRDest.x - m_Camera[0].posR.x) * fMove;
	m_Camera[1].posR.y += (m_Camera[0].posRDest.y - m_Camera[0].posR.y) * fMove;
	m_Camera[1].posR.z += (m_Camera[0].posRDest.z - m_Camera[0].posR.z) * fMove;


	m_Camera[1].posV.x += ((m_Camera[0].posVDest.x - m_Camera[0].posV.x) * fMove);
	m_Camera[1].posV.y += ((m_Camera[0].posVDest.y - m_Camera[0].posV.y) * fMove) + fMovePos;
	m_Camera[1].posV.z += ((m_Camera[0].posVDest.z - m_Camera[0].posV.z) * fMove);
	}
	catch (const std::exception&)
	{

	}


}

void CCAMERA::CameraTitle(void)
{
	try
	{

	m_Camera[0].nCounterAngle++;
	if (m_Camera[0].nCounterAngle < 300)
	{
		m_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
		m_Camera[0].posV = D3DXVECTOR3(300.0f, 150.0f, 0.0f);
		m_Camera[0].posR = D3DXVECTOR3(330, 150, -610);
	}
	if (m_Camera[0].nCounterAngle == 300)
	{
		m_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
		m_Camera[0].posV = D3DXVECTOR3(1000.0f, 1500.0f, -2000.0f);
		m_Camera[0].posR = D3DXVECTOR3(1000.0f, 1000.0f, 3000.0f);
	}
	if (m_Camera[0].nCounterAngle == 600)
	{
		m_Camera[0].rotCamera.y = 0.3f * D3DX_PI;
		m_Camera[0].posV = D3DXVECTOR3(7200.0f, 500.0f, 7500.0f);
		m_Camera[0].posR = D3DXVECTOR3(7200.0f, 480.0f, 7500.0f);

	}
	if (m_Camera[0].nCounterAngle == 900)
	{
		m_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
		m_Camera[0].posV = D3DXVECTOR3(1900.0f, 300.0f, 6600.0f);
		m_Camera[0].posR = D3DXVECTOR3(1900.0f, 450.0f, 6600.0f);
	}
	if (m_Camera[0].nCounterAngle == 1200)
	{
		m_Camera[0].nCounterAngle = 0;
		m_Camera[0].rotCamera.y = 0.0f * D3DX_PI;
	}

	m_Camera[0].rotCamera.y += 0.003f;
	// 3.14��������
	if (m_Camera[0].rotCamera.y > D3DX_PI)
	{
		// 3.14�� -3.14�ɂ���
		m_Camera[0].rotCamera.y -= D3DX_PI * 2.0f;
	}
	m_Camera[0].posV.x = m_Camera[0].posR.x + sinf(m_Camera[0].rotCamera.y + D3DX_PI)* fLength;
	m_Camera[0].posV.z = m_Camera[0].posR.z + cosf(m_Camera[0].rotCamera.y + D3DX_PI)* fLength;
	}
	catch (const std::exception&)
	{

	}

}