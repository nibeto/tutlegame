//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"TitleUi.h"
#include"Scene2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
LPDIRECT3DTEXTURE9 CTitleUi::m_pTexture[MAX_TITLEUI_TEX] = {};

//=============================================================================
// Create�֐�
//=============================================================================
CTitleUi *CTitleUi::Create(void)
{
	//�C���X�^���X
	CTitleUi*pBg = NULL;
	pBg = new CTitleUi;
	if (pBg != NULL)
	{
		pBg->Init();
	}
	return pBg;

}
//=============================================================================
// �ǂݍ��݂ƃe�N�X�`���[�̔j��
//=============================================================================
HRESULT CTitleUi::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg.jpg", &m_pTexture[0]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_pTexture[1]);

	return S_OK;
}
void CTitleUi::UnLoad(void)
{//unload//�j��
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitleUi::CTitleUi() :CScene(SCENE_NUMBER_TYPE_TITLEUI)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitleUi::~CTitleUi()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CTitleUi::Init(void)
{
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg] = CScene2D::Create();
		m_apScene2D[nCntBg]->Init();

	}

	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->BindTexture(m_pTexture[nCntBg]);

	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fRot = 0.25f;

	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CTitleUi::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();

	}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CTitleUi::Update(void)
{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;

	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{

		pos = m_apScene2D[nCntBg]->GetPotion();
		move = m_apScene2D[nCntBg]->GetMove();
		m_fRot = m_apScene2D[nCntBg]->GetfRot();
	}
	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//���͂��ꂽ
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{

		m_apScene2D[nCntBg]->SetBgAnimation(tex);
	}

	pos += move;
	move *= 0.1f;

	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->Update();

	}

	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{

		m_apScene2D[nCntBg]->GetPotion();
		m_apScene2D[nCntBg]->GetMove();
		m_apScene2D[nCntBg]->GetLength();
		m_apScene2D[nCntBg]->GetfRot();

		m_apScene2D[nCntBg]->SetBG(pos, 1250.0f, 750.0f, CTitleUi::OBJECT_TYPE_TITLEUI);
	}
}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CTitleUi::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_TITLEUI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->Draw();

	}
}
