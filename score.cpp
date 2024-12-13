//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"score.h"
#include"Scene2D.h"
#include"Number.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

LPDIRECT3DTEXTURE9 CScore::m_pTexture[MAX_SOORE_TEXTUR] = {};

//=============================================================================
// Create�֐�
//=============================================================================
CScore *CScore::Create(void)
{
	//�C���X�^���X
	CScore*pScore = NULL;
	pScore = new CScore;

	try
	{
		if (pScore != NULL)
		{
			pScore->Init();
		}

	}
	catch (const std::exception&)
	{

	}
	return pScore;

}

HRESULT CScore::Load(void)
{//load//�ǂݍ���
	try
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		// ���_����ݒ�
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture[0]);
		// ���_����ݒ�
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_pTexture[1]);

	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
void CScore::UnLoad(void)
{//unload//�j��
	try
	{
		for (int nCntBg = 0; nCntBg < MAX_SOORE_TEXTUR; nCntBg++)
		{

			//�e�N�X�`���̔j��
			if (m_pTexture[nCntBg] != NULL)
			{
				m_pTexture[nCntBg]->Release();
				m_pTexture[nCntBg] = NULL;
			}
		}

	}
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore():CScene(SCENE_NUMBER_TYPE_SCORE)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CScore::Init(void)
{
	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_DIGIT; nCntNumber++)
	{


		m_apNUMber[nCntNumber] =
			CNUmber::Create(D3DXVECTOR3(1025.0f+ nCntNumber*50, 65.0f, 0.0f), 15.0f, 0);


	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fRot = 0.25f;
	}
	catch (const std::exception&)
	{

	}


	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CScore::Uninit(void)
{
	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Uninit();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CScore::Update(void)
{
	try
	{

		AddScore(5);
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Update();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================
void CScore::Draw(void)
{
	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Draw();

	}
	}
	catch (const std::exception&)
	{

	}

}

void CScore::AddScore(int nValue)
{
	try
	{
	nScore += nValue;
	m_aScoreDigit[0] = nScore % 100000 / 10000;
	m_aScoreDigit[1] = nScore % 10000 / 1000;
	m_aScoreDigit[2] = nScore % 1000 / 100;
	m_aScoreDigit[3] = nScore % 100 / 10;
	m_aScoreDigit[4] = nScore % 10 / 1;

	for (nScore = 0; nScore < MAX_SCORE_DIGIT; nScore++)
	{
		m_apNUMber[nScore]->SetNumber(m_aScoreDigit[nScore]);

	}



	}
	catch (const std::exception&)
	{

	}




}
int CScore::GetScoer(void)
{
	try
	{
	return nScore;
	}
	catch (const std::exception&)
	{

	}

}

