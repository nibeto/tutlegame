//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{
#include"score.h"
#include"manager.h"
#include"Scene3D.h"
#include"renderer.h"
#include"input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define SCREEN_WHIDH_VIEWPORT (1280)
#define SCREEN_HIGHT_VIEWPORT (720)


//=============================================================================
// ���C���֐�
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSCENE3D::CSCENE3D(LAYER m_Number = LAYER_MAX) :CScene(m_nNumber3D)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSCENE3D::~CSCENE3D()
{

}

CSCENE3D *CSCENE3D::Create(void)
{
	//�C���X�^���X
	CSCENE3D*pScene3D = NULL;

	//
	pScene3D = new CSCENE3D;
	//������
	pScene3D->Init();

	if (pScene3D != NULL)
	{

	}

	//�l��Ԃ�
	return pScene3D;

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CSCENE3D::Init(void)
{
	// �ʒu�E�����̏����ݒ�
	m_pos = D3DXVECTOR3(-70.0f, 20.0f, 0.0f);		//�ʒu�̏����ݒ�
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			//�����̏����Zxyz
	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CSCENE3D::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
		// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh = NULL;
	}

		// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat = NULL;
	}

	Save();
	//delete this;

	Release();
}
void CSCENE3D::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{

	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;
}
void CSCENE3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{

	m_pTexture = pTexture;

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CSCENE3D::Update(void)
{


}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CSCENE3D::Draw(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&m_matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//
	for (int nCntMat1 = 0; nCntMat1 < (int)m_nNumMat; nCntMat1++)
	{
		// �}�e���A���̐ݒ�
		//pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat1);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&m_matDef);

}
void CSCENE3D::SetCamera(void)
{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_Bt0),								//��
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//��ʔ䗦
		10.0f,												//�J�������猩����O�̈ʒu
		1000.0f);											//�J�������猩�����s���̈ʒu

															// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV,
		&m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//******************************************
//�|���S����set
//******************************************

void CSCENE3D::SetNOMAL(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXMATRIX mtxWorld)
{

	m_pos = pos;
	m_move = move;
	m_rot = rot;
	m_mtxWorld = mtxWorld;
}
//******************************************
//�|���S����GET
//******************************************

D3DXVECTOR3 CSCENE3D::GetPotion(void)
{

	return m_pos;

}
D3DXVECTOR3 CSCENE3D::GetPotionV(void)
{

	return m_posV;

}
D3DXVECTOR3 CSCENE3D::GetPotionR(void)
{

	return m_posR;

}
D3DXVECTOR3 CSCENE3D::GetPotionU(void)
{

	return m_vecU;


}
//******************************************
//�ړ���GET
//******************************************

D3DXVECTOR3 CSCENE3D::GetMove(void)
{

	return m_move;

}
//******************************************
//�|���S���̃T�C�Y��GET
//******************************************

float CSCENE3D::GetLength(void)
{

	return m_fPosSize;

}
//******************************************
//�|���S���̉�]��GET
//******************************************

D3DXVECTOR3 CSCENE3D::GetfRot(void)
{

	return m_rot;


}
//******************************************
//pos�̏������T�C�Y��SAVE
//******************************************

void CSCENE3D::Save(void)
{


	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}

}
//******************************************
//pos�̏������T�C�Y��LOAD
//******************************************

void CSCENE3D::Load(void)
{


	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}

}