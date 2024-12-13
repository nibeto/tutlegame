//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"gameover.h"
#include"Fade.h"
#include"input.h"
#include"sound.h"
#include "font.h"
#include"Bg.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
LPDIRECT3DTEXTURE9 CGameOver::m_pTexture[MAX_TEXTURE_RESULT] = {};
//CBg*CTitle::m_pBg = NULL;
//=============================================================================
// Create�֐�
//=============================================================================
CGameOver *CGameOver::Create(void)
{
	//�C���X�^���X
	CGameOver*pGameClear = NULL;
	pGameClear = new CGameOver;
	if (pGameClear != NULL)
	{
		pGameClear->Init();

	}
	return pGameClear;

}
HRESULT CGameOver::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GameOver.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_pTexture[2]);

	return S_OK;
}
void CGameOver::UnLoad(void)
{//unload//�j��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_RESULT; nCntTexture++)
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
CGameOver::CGameOver()
{//clear�i�N���A�j
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGameOver::~CGameOver()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CGameOver::Init(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

#if 0
	for (int ncntData = 0; ncntData < MAX_TEXTURE_RESULT; ncntData++)
	{
		for (int nData = 0; nData < Resulttype; nData++)
		{

			switch (Resulttype)
			{
			case CResult::Result_Type_GameCrear:
				m_apScene2D[0] = CScene2D::Create();
				m_apScene2D[0]->Init();
				m_apScene2D[0]->BindTexture(m_pTexture[0]);


				break;
			case CResult::Result_Type_GAmeOver:
				m_apScene2D[1] = CScene2D::Create();
				m_apScene2D[1]->Init();
				m_apScene2D[1]->BindTexture(m_pTexture[1]);

				break;
			case CResult::Result_Type_MAX:
				m_apScene2D[2] = CScene2D::Create();
				m_apScene2D[2]->Init();
				m_apScene2D[2]->BindTexture(m_pTexture[2]);
				break;
			default:
				break;


			}
		}
	}
#endif
	m_apScene2D[0] = CScene2D::Create();
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);


	m_apScene2D[1] = CScene2D::Create();
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);

	m_apScene2D[2] = CScene2D::Create();
	m_apScene2D[2]->Init();
	m_apScene2D[2]->BindTexture(m_pTexture[2]);


	CSound *pPlaySound = CManeger::GetSound();
	pPlaySound->Play(pPlaySound->SOUND_LABEL_BGM002);

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
void CGameOver::Uninit(void)
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
void CGameOver::Update(void)
{
	try
	{

	CFade *pFade = CManeger::GetFade();
	CFade::FADE  m_fade = pFade->FADE_MAX;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CManeger::MODE m_mode = CManeger::GetMode();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	if (pInputKeyboard->GetPress(DIK_I))
	{
		Resulttype = CGameOver::Result_Type_MAX;

	}
	if (pInputKeyboard->GetPress(DIK_O))
	{
		Resulttype = CGameOver::Result_Type_GAmeOver;
		Resulttype = CGameOver::Result_Type_MAX;

	}
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;
	for (int nCuntPos = 0; nCuntPos < MAX_POLIGON_RESULT; nCuntPos++)
	{

		pos = m_apScene2D[nCuntPos]->GetPotion();
		move = m_apScene2D[nCuntPos]->GetMove();
	}
	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//���͂��ꂽ
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}
	for (int nCuntPos = 0; nCuntPos < MAX_POLIGON_RESULT; nCuntPos++)
	{

		m_apScene2D[1]->SetBgAnimation(tex);
	}
	pos += move;
	move *= 0.1f;
	for (int nCuntPos = 0; nCuntPos < MAX_POLIGON_RESULT; nCuntPos++)
	{

		m_apScene2D[nCuntPos]->Update();
		m_apScene2D[nCuntPos]->GetPotion();
		m_apScene2D[nCuntPos]->GetMove();
		m_apScene2D[nCuntPos]->GetLength();
		m_apScene2D[nCuntPos]->GetfRot();
	}
	m_apScene2D[0]->SetNOMAL(D3DXVECTOR3(pos.x + 550.0f, pos.y, pos.z), 750.0f, 750.0f);
	m_apScene2D[1]->SetNOMAL(pos, 1250.0f, 750.0f);

	if (m_mode == CManeger::MODE_GAMEOVER)
	{
		if (pInputKeyboard != NULL && pFade != NULL)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				CSound *pPlaySound = CManeger::GetSound();
				pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM002);

				if (m_fade != pFade->FADE_OUT)
				{

					pFade->SetFade(CManeger::MODE_TITLE);

				}
			}
		}
	}
	}
	catch (const std::exception&)
	{

	}


}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CGameOver::Draw(void)
{
	try
	{

	for (int nCuntPos = 0; nCuntPos < MAX_POLIGON_RESULT; nCuntPos++)
	{

		m_apScene2D[nCuntPos]->Draw();
	}
	}
	catch (const std::exception&)
	{

	}

}
