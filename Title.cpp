//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Title.h"
#include"Fade.h"
#include"input.h"
#include"sound.h"
#include "font.h"
#include"Bg.h"
#include"TitleUi.h"
#include "robo.h"
#include"fontMode.h"
#include"PLESENTER.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_ROT (5.0f)//��]��
#define POS_SIZE_Y (50.0f)
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TEXTURE_TITLE] = {};
CFONT*CTitle::m_pFont = NULL;
CFontMode*CTitle::m_pFontMode = NULL;
CBg*CTitle::m_pBg = NULL;
CTitleUi*CTitle::m_pTitleUI = NULL;
CRobo*CTitle::m_pRobo = NULL;
CPLESEENTER*CTitle::m_pPleseEnter = NULL;
//=============================================================================
// Create�֐�
//=============================================================================
CTitle *CTitle::Create(void)
{
	//�C���X�^���X
	CTitle*pTitle = NULL;
	pTitle = new CTitle;
	if (pTitle != NULL)
	{
		pTitle->Init();

	}
	return pTitle;

}
HRESULT CTitle::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ice.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/preaseEnter.jpg", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/FDG.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mousetarget01.png", &m_pTexture[4]);

	return S_OK;
}
void CTitle::UnLoad(void)
{//unload//�j��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_TITLE; nCntTexture++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{//clear�i�N���A�j
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CTitle::Init(void)
{
	try
	{

	m_pBg = CBg::Create();


	CManeger::MODE m_mode = CManeger::GetMode();

	m_pFontMode = CFontMode::Create(CManeger::MODE_TITLE);
	m_pPleseEnter = CPLESEENTER::Create(D3DXVECTOR3(500.0f, 500.0f, 0.0f), 50.0f, 0);



	CSound *pPlaySound = CManeger::GetSound();
	pPlaySound->Play(pPlaySound->SOUND_LABEL_BGM000);

	m_nTime = 60;

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
void CTitle::Uninit(void)
{
	//CSceneNum3D::Release3DALL();
	CScene::ReleaseALL();
	//CSCENE3D::ReleaseALL();
	CScene2D::ReleaseALL();

	m_apfade = NULL;
	if (m_apfade != NULL)
	{//�L�[�{�[�h
		m_apfade->Uninit();
		// �L�[�{�[�h�̏I������
		delete m_apfade;
		m_apfade = NULL;

	}
	else
	{

	}
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CTitle::Update(void)
{

	m_pFontMode->Update(CManeger::MODE_TITLE);

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CFade *pFade = CManeger::GetFade();

	CFade::FADE  m_fade = pFade->FADE_MAX;

	CManeger::MODE m_mode = CManeger::GetMode();

	if (m_mode == CManeger::MODE_TITLE)
	{

		if (pInputKeyboard != NULL && pFade != NULL)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				CSound *pPlaySound = CManeger::GetSound();
				pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

				pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM000);


				if (m_fade != pFade->FADE_OUT)
				{
					//Uninit();
					pFade->SetFade(CManeger::MODE_GAME);

				}
			}
			f_posY = 200;//�L�[���͂ŌŒ�

		}
	}



}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CTitle::Draw(void)
{


}
