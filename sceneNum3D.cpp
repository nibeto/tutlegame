//=============================================================================
//
// ���C������ [scene.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{


#include"sceneNum3D.h"
#include"renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�ÓI�����o�ϐ�
CSceneNum3D *CSceneNum3D::m_apSine3D[(LAYER3D)SCENE3D_NUMBER_TYPE_MAX][MAX_SCENE3D] = {};
int CSceneNum3D::m_nNumAll3D = 0;
//=============================================================================
// ���C���֐�
//=============================================================================





//=============================================================================
// ����������
//=============================================================================
CSceneNum3D::CSceneNum3D(SCENE3D_NUMBER_TYPE m_Number)
{
	//nPrioty = MAX_DEFFULT;
	for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
	{

		if (m_apSine3D[m_Number][nCntScene] == NULL)
		{

			m_apSine3D[m_Number][nCntScene] = this;
			m_nID3D = nCntScene;
			m_nLayer3D = (LAYER3D)m_Number;
			m_nNumAll3D++;
			break;
		}
	}

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneNum3D::~CSceneNum3D()
{

}
void CSceneNum3D::Release3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < m_nNumAll3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{

				// �|���S���̏I������
				m_apSine3D[nCntDeffult][nCntScene]->Uninit();
				delete m_apSine3D[nCntDeffult][nCntScene];
				m_apSine3D[nCntDeffult][nCntScene] = NULL;

			}
		}
	}

}

void CSceneNum3D::Update3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{
				// �|���S���̍X�V����
				m_apSine3D[nCntDeffult][nCntScene]->Update();


			}
		}

	}

}

void CSceneNum3D::Draw3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{
				// �|���S���̏I������
				m_apSine3D[nCntDeffult][nCntScene]->Draw();

			}
		}

	}

}
void CSceneNum3D::Road(void)
{



}

void CSceneNum3D::Release3D(void)
{

	SCENE3D_NUMBER_TYPE   nNumber3D = (SCENE3D_NUMBER_TYPE)m_nLayer3D;

	int nID3D = m_nID3D;//�ϐ��Ƀ����o�[�ɕۑ�

	if (m_apSine3D[nNumber3D][nID3D] != NULL)
	{


		delete m_apSine3D[nNumber3D][nID3D];
		m_apSine3D[nNumber3D][nID3D] = NULL;
		m_nNumAll3D--;


	}

}

//=============================================================================
//�I�u�W�F�N�g�̔j��
//=============================================================================
void CSceneNum3D::SetOBJTYPE3D(OBJECT_TYPE3D type)
{
	m_apType3D = type;

}
CSceneNum3D * CSceneNum3D::GetCSINE3D(SCENE3D_NUMBER_TYPE m_Number3D, int m_IDx)
{
	return m_apSine3D[m_Number3D][m_IDx];
}

