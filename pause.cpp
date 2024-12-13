//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"pause.h"
#include"Scene2D.h"
#include"pauseselect.h"
#include"Fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)


//=============================================================================
// Create�֐�
//=============================================================================
CPause *CPause::Create(void)
{
	//�C���X�^���X
	CPause*pScore = NULL;
	pScore = new CPause;
	if (pScore != NULL)
	{
		pScore->Init();
	}
	return pScore;

}

HRESULT CPause::Load(void)
{//load//�ǂݍ���
	return S_OK;
}
void CPause::UnLoad(void)
{//unload//�j��

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPause::CPause() :CScene(SCENE_NUMBER_TYPE_PAUSE)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CPause::Init(void)
{


	for (int nCntNumber = 0; nCntNumber < PAUSE_TEXTURE; nCntNumber++)
	{


		m_apPause[nCntNumber] =
			CPAUSESELECT::Create(D3DXVECTOR3(525.0f + nCntNumber * 50, 65.0f, 0.0f), 15.0f, 0);


	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	bDraw = true;
	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CPause::Uninit(void)
{
	for (int nCntNumber = 0; nCntNumber < PAUSE_TEXTURE; nCntNumber++)
	{
		m_apPause[nCntNumber]->Uninit();

	}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CPause::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

	if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		bDraw = bDraw ? false : true;
	}

	for (int nCntNumber = 0; nCntNumber < PAUSE_TEXTURE; nCntNumber++)
	{
		m_apPause[nCntNumber]->Update();

	}
}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CPause::Draw(void)
{
	if (bDraw == true)
	{
		for (int nCntNumber = 0; nCntNumber < PAUSE_TEXTURE; nCntNumber++)
		{
			m_apPause[nCntNumber]->Draw();
		}
	}
}