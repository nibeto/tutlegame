//=============================================================================
//
// ���C������ [scene.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{


#include"scene.h"
#include"renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�ÓI�����o�ϐ�
CScene *CScene::m_apSine[(LAYER)SCENE_NUMBER_TYPE_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;
//=============================================================================
// ���C���֐�
//=============================================================================





//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::CScene(SCENE_NUMBER_TYPE nNumber)
{

		//nPrioty = MAX_DEFFULT;
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apSine[nNumber][nCntScene] == NULL)
			{

				m_apSine[nNumber][nCntScene] = this;
				m_nID = nCntScene;
				m_nLayer = (LAYER)nNumber;
				m_nNumAll++;
				break;
			}
		}
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//�����[�X����
//=============================================================================
void CScene::ReleaseALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < m_nNumAll; nCntScene++)
		{

			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{

				// �|���S���̏I������
				m_apSine[nCntDeffult][nCntScene]->Uninit();
				delete m_apSine[nCntDeffult][nCntScene];
				m_apSine[nCntDeffult][nCntScene] = NULL;

			}
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CScene::UpdateALL(void)
{


	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{


				// �|���S���̍X�V����
				m_apSine[nCntDeffult][nCntScene]->Update();


			}
		}

	}
}
//=============================================================================
//�`�揈��
//=============================================================================
void CScene::DrawALL(void)
{


	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{
				// �|���S���̏I������
				m_apSine[nCntDeffult][nCntScene]->Draw();

			}
		}

	}



}

void CScene::Road(void)
{



}


//=============================================================================
//�I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{



	SCENE_NUMBER_TYPE   nNumber = (SCENE_NUMBER_TYPE)m_nLayer;

	int nID = m_nID;//�ϐ��Ƀ����o�[�ɕۑ�

	if (m_apSine[nNumber][nID] != NULL)
	{


			delete m_apSine[nNumber][nID];
			m_apSine[nNumber][nID] = NULL;
			m_nNumAll--;


		}





}
//=============================================================================
//�I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::SetOBJTYPE(OBJECT_TYPE type)

{
	m_apType = type;

}
CScene * CScene::GetCSINE(SCENE_NUMBER_TYPE  m_Number,int m_IDX)
{

	return m_apSine[m_Number][m_IDX];



}