//=============================================================================
//
// ���C������ [renderer.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"scene.h"
#include"Scene2D.h"
#include "InputKeyboard.h"
#include "joypad.h"
#include"mouse.h"
#include"sound.h"
#include"Title.h"
#include"Game.h"
#include"Result.h"
#include"gameclear.h"
#include"gameover.h"
#include"Fade.h"

#include"Player.h"
#include"Polygon.h"
#include"bullet.h"
#include"Explosion.h"
#include"Enemy.h"
#include"Bg.h"
#include"block.h"
#include"sound.h"
#include"score.h"
#include"Effect.h"
#include"obj.h"
#include"Weapons.h"
#include"Number.h"
#include"rogowaku.h"
#include"Time.h"
#include"Playerobj.h"
#include"BulletLife.h"
#include"bulletNumber.h"
#include"robo.h"
#include"Life.h"
#include"Goal.h"
#include"pause.h"
#include"pauseselect.h"
#include "Timer.h"
#include "level.h"
#include"Capsule.h"
#include"CapsuleEnemy.h"
#include"Dice.h"
#include"TitleUi.h"
#include"Debug.h"
#include"Buildings.h"
#include"GameStage2.h"
#include"Boss.h"
#include"PLESENTER.h"
#include "Ranking.h"
#include "Rankes.h"
#include "RankGata.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************



//=============================================================================
// ���C���֐�
//=============================================================================
CMouse *CManeger::m_pMouse = NULL;//�L�[�{�[�h
CJoypad *CManeger::m_pjoypad = NULL;//�L�[�{�[�h
CInputKeyboard *CManeger::m_pinputKeyboard = NULL;//�L�[�{�[�h
CSound*CManeger::m_pPlaySound = NULL;//�T�E���h
CRenderer *CManeger::m_pRenderer = NULL;//�|���S��
CTitle * CManeger::m_ptitle = NULL;//�^�C�g��
CGame * CManeger::m_pGame = NULL;//�Q�[��
CGameStage2* CManeger::m_pGameStage2 = NULL;
bool CManeger::m_bDebug = false;
CResult * CManeger::m_presult = NULL;//���U���g
CGamaClear * CManeger::m_pGameClear = NULL;//�^�C�g��
CGameOver * CManeger::m_pGameOver = NULL;//�^�C�g��

CRanking*CManeger::m_pRanking = NULL;
CFade  *CManeger::m_pfade = NULL;
CManeger*CManeger::m_pManager = NULL;
CManeger::MODE CManeger::m_Mode;
//=============================================================================
//�R���X�g���N�^
//=============================================================================

CManeger::CManeger()
{
	m_pMouse = NULL;
	m_pjoypad = NULL;
	m_pinputKeyboard = NULL;//�L�[�{�[�h
	m_pPlaySound = NULL;//�T�E���h
	m_pRenderer = NULL;//�|���S��
	m_ptitle = NULL;//�^�C�g��
	m_pGame = NULL;//�Q�[��
	m_presult = NULL;//���U���g
	m_pGameClear = NULL;
	m_pGameOver = NULL;
	m_pGameStage2 = NULL;
	m_pfade = NULL;
	m_pManager = NULL;
	m_pRanking = NULL;
	CManeger::m_Mode;

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManeger::~CManeger()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManeger::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	try
	{

	m_pPlaySound = new CSound;

	m_ptitle = new CTitle;
	m_pGame = new CGame;
	m_presult = new CResult;
	m_pfade = new CFade;

	m_Mode = MODE_TITLE;

	switch (m_Mode)
	{
	case	MODE_TITLE:

		if (m_presult != NULL)
		{

			CResult::UnLoad();

			m_presult->Uninit();
			delete m_presult;
			m_presult = NULL;

		}

		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}
		break;
	case	MODE_GAME:
		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}

		if (m_pGame != NULL)
		{

			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

		}
		break;
	case	MODE_GAMESTAGE2:
		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}

		if (m_pGame != NULL)
		{

			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

		}
		if (m_pGameStage2 != NULL)
		{

			m_pGameStage2->Uninit();
			delete m_pGameStage2;
			m_pGameStage2 = NULL;

		}

		break;

	case	MODE_RESULT:

		if (m_pGame != NULL)
		{

			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

		}


		if (m_presult != NULL)
		{

			CResult::UnLoad();

			m_presult->Uninit();
			delete m_presult;
			m_presult = NULL;

		}
		break;
	case	MODE_GAMECLEAR:

		if (m_presult != NULL)
		{

			CResult::UnLoad();

			m_presult->Uninit();
			delete m_presult;
			m_presult = NULL;

		}

		if (m_ptitle != NULL)
		{
			CGamaClear::UnLoad();

			m_pGameClear->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}
		break;
	case	MODE_GAMEOVER:

		if (m_pGameOver != NULL)
		{

			CGameOver::UnLoad();

			m_pGameOver->Uninit();
			delete m_pGameOver;
			m_pGameOver = NULL;

		}

		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}
		break;


	case	MODE_RANKING:
		CRankingGata::UnLoad();
		CRanking::UnLoad();
		CRankes::UnLoad();
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;

		break;
	}
	if (m_pPlaySound != NULL)
	{//�T�E���h
		m_pPlaySound->Init(hWnd);

	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);

	}
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{
		// ����������(�E�B���h�E���쐬���Ă���s��)
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{
			// �I������
			m_pRenderer->Uninit();

			delete m_pRenderer;
			m_pRenderer = NULL;
			return -1;
		}
	}



	if (m_pRenderer != NULL)
	{
		//**********************************
		//BG��LOAD()
		//**********************************
		CBg::Load();
		CFONT::Load();
		CPLESEENTER::Load();
		CTitleUi::Load();
		CNUmber::Load();
		CScore::Load();
		CTime::Load();
		CLevel::Load();
		cLife::Load();
		//**********************************
		//�u���b�N��LOAD()
		//**********************************
		if (m_bDebug == true)
		{

			CDebug::Load();
		}
		Cblock::Load();
		CRogowaku::Load();
		CDice::Load();
		//**********************************
		//�v���C���[��LOAD()
		//**********************************
		CPlayer::Load();
		CPoligon::Load();
		//**********************************
		//�v���C���[��CREATE()
		//**********************************
		CPlayerObj::Load();

		CRobo::Load();
		CCAPSULEENEMY::Load();
		CCapsule::Load();
		//**********************************
		//�G�l�~�[��LOAD()
		//**********************************
		CBUilding::Load();
		CEnemy::Load();
		CBoss::Load();
		//**********************************
		//�I�u�W�F�N�g��LOAD()
		//**********************************
		CObj::Load();
		CWeapons::Load();
		//**********************************
		//�e��LOAD()
		//**********************************
		CBullet::Load();
		CGoal::Load();
		//**********************************
		//������LOAD()
		//**********************************
		CExplosion::Load();
		//**********************************
		//�G�t�F�N�g��LOAD()
		//**********************************
		CEffect::Load();
		//**********************************
		//�X�R�A��LOAD()
		//**********************************
		CBulletNUmber::Load();
		CBulletLife::Load();
		//CLevel::Load();
		CTimer::Load();
	}

	if (m_bPouse == false)
	{
		CPAUSESELECT::Load();

		CPause::Load();
	}
	CManeger::SetMode(m_Mode);


	m_pMouse = new CMouse;

	if (m_pMouse != NULL)
	{//�L�[�{�[�h
		m_pMouse->Init(hInstance, hWnd);

	}
	m_pjoypad = new CJoypad;

	if (m_pjoypad != NULL)
	{//�L�[�{�[�h
		m_pjoypad->Init(hInstance, hWnd);

	}

	m_pinputKeyboard = new CInputKeyboard;

	if (m_pinputKeyboard != NULL)
	{//�L�[�{�[�h
		m_pinputKeyboard->Init(hInstance, hWnd);

	}

	m_bPouse = false;
		}
		catch (const std::exception&)
		{

		}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManeger::Uninit(void)
{
	try
	{

	CScene::ReleaseALL();
	if (m_pfade != NULL)
	{//
		CFade::UnLoad();

		//�I������
		m_pfade->Uninit();
		delete m_pfade;
		m_pfade = NULL;

	}
	else
	{

	}




	if (m_pMouse != NULL)
	{//�L�[�{�[�h
	 // �L�[�{�[�h�̏I������
		delete m_pMouse;
		m_pMouse = NULL;

	}
	else
	{

	}
	if (m_pjoypad != NULL)
	{//�L�[�{�[�h
	 // �L�[�{�[�h�̏I������
		delete m_pjoypad;
		m_pjoypad = NULL;

	}
	else
	{

	}
	if (m_pinputKeyboard != NULL)
	{//�L�[�{�[�h
		// �L�[�{�[�h�̏I������
		delete m_pinputKeyboard;
		m_pinputKeyboard = NULL;

	}
	else
	{

	}

	if (m_pPlaySound != NULL)
	{//�T�E���h
		// �T�E���h�̏I������
		delete m_pPlaySound;
		m_pPlaySound = NULL;

	}
	else
	{

	}



	switch (m_Mode)
	{
	case	MODE_TITLE:
		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}
		break;
	case	MODE_GAME:

		if (m_pGame != NULL)
		{

			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

		}
		break;
	case	MODE_GAMESTAGE2:

		if (m_pGameStage2 != NULL)
		{

			m_pGameStage2->Uninit();
			delete m_pGameStage2;
			m_pGameStage2 = NULL;

		}
		break;

	case	MODE_RESULT:
		if (m_presult != NULL)
		{

			CResult::UnLoad();

			m_presult->Uninit();
			delete m_presult;
			m_presult = NULL;

		}
		break;
	case	MODE_GAMECLEAR:



		if (m_pGameClear != NULL)
		{

			CGamaClear::UnLoad();

			m_pGameClear->Uninit();
			delete m_pGameClear;
			m_pGameClear = NULL;

		}
		break;
	case	MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{

			CGameOver::UnLoad();

			m_pGameOver->Uninit();
			delete m_pGameOver;
			m_pGameOver = NULL;

		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			CRankingGata::UnLoad();
			CRankes::UnLoad();
			CRanking::UnLoad();

			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;

		}
		break;

	}


	if (m_pRenderer != NULL)
	{
		//**********************************
		//BG��LOAD()
		//**********************************
		CBg::UnLoad();
		CFONT::UnLoad();
		CPLESEENTER::UnLoad();
		CTitleUi::UnLoad();
		CNUmber::UnLoad();
		CScore::UnLoad();
		CTime::UnLoad();
		cLife::UnLoad();
		//**********************************
		//�u���b�N��LOAD()
		//**********************************
		if (m_bDebug == true)
		{

			CDebug::UnLoad();
		}
		Cblock::UnLoad();
		CRogowaku::UnLoad();

		CDice::UnLoad();
		//**********************************
		//�v���C���[��LOAD()
		//**********************************
		CPlayer::UnLoad();
		CPoligon::UnLoad();
		//**********************************
		//�v���C���[��CREATE()
		//**********************************
		CPlayerObj::UnLoad();

		CRobo::UnLoad();
		CCAPSULEENEMY::UnLoad();
		CCapsule::UnLoad();
		//**********************************
		//�G�l�~�[��LOAD()
		//**********************************
		CBUilding::UnLoad();
		CEnemy::UnLoad();
		CBoss::UnLoad();
		//**********************************
		//�I�u�W�F�N�g��LOAD()
		//**********************************
		CObj::UnLoad();
		CWeapons::UnLoad();
		//**********************************
		//�e��LOAD()
		//**********************************
		CBullet::UnLoad();
		CGoal::UnLoad();
		//**********************************
		//������LOAD()
		//**********************************
		CExplosion::UnLoad();
		//**********************************
		//�G�t�F�N�g��LOAD()
		//**********************************
		CEffect::UnLoad();
		//**********************************
		//�X�R�A��LOAD()
		//**********************************
		CBulletNUmber::UnLoad();
		CBulletLife::UnLoad();
		CLevel::UnLoad();
		CPAUSESELECT::UnLoad();
		CTimer::UnLoad();
		if (m_bPouse == false)
		{

			CPause::UnLoad();
		}
		m_pRenderer->Uninit();
		// 2D�|���S���̏I������
		delete m_pRenderer;
		m_pRenderer = NULL;

	}
	else
	{

	}
		}
		catch (const std::exception&)
		{

		}

}

//=============================================================================
// �X�V����
//=============================================================================
void CManeger::Update(void)
{
	CManeger::MODE m_mode = CManeger::GetMode();


	if (m_mode == CManeger::MODE_GAME)
	{
		//if (m_pCamera != NULL)
		//{
		//	// �L�[�{�[�h�̍X�V����
		//	//m_pCamera->Update();

		//}
		//if (m_pLight != NULL)
		//{
		//	// �L�[�{�[�h�̍X�V����
		//	m_pLight->Update();

		//}
	}

	if (m_pMouse != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pMouse->Update();

	}
	if (m_pjoypad != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pjoypad->Update();

	}
	if (m_pinputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pinputKeyboard->Update();

	}
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		//PlaySound(SOUND_LABEL_SE_PAUSE);
		m_bPouse = m_bPouse ? false : true;
	}


	if (pInputKeyboard->GetTrigger(DIK_F4) == true)
	{

		m_bDebug = m_bDebug ? false : true;

	}

	if (m_bDebug == false)
	{

		if (m_bPouse == false)
		{

			if (m_pRenderer != NULL)
			{
				// 3D�|���S���̍X�V����
				//m_pRenderer->Update(m_pRenderer->CsceneName_SceneName3D);
				// 2D�|���S���̍X�V����
				m_pRenderer->Update();

			}
		}
	}
	if (m_pfade != NULL)
	{// light�̍X�V����
		m_pfade->Update();
	}
	switch (m_Mode)
	{
	case	MODE_TITLE:
		if (m_ptitle != NULL) { m_ptitle->Update(); }
		break;
	case	MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Update(); }
		break;
	case	MODE_GAMESTAGE2:
		if (m_pGameStage2 != NULL) { m_pGameStage2->Update(); }
		break;
	case	MODE_RESULT:
		if (m_presult != NULL) { m_presult->Update(); }
		break;
	case	MODE_GAMECLEAR:
		if (m_pGameClear != NULL) { m_pGameClear->Update(); }
		break;
	case	MODE_GAMEOVER:
		if (m_pGameOver != NULL) { m_pGameOver->Update(); }
		break;
	case	MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Update(); }
		break;

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CManeger::Draw(void)
{
	switch (m_Mode)
	{
	case	MODE_TITLE:
		if (m_ptitle != NULL) { m_ptitle->Draw(); }
		break;
	case	MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Draw(); }
		break;
	case	MODE_GAMESTAGE2:
		if (m_pGameStage2 != NULL) { m_pGameStage2->Draw(); }
		break;
	case	MODE_RESULT:
		if (m_presult != NULL) { m_presult->Draw(); }
		break;
	case	MODE_GAMECLEAR:
		if (m_pGameClear != NULL) { m_pGameClear->Draw(); }
		break;
	case	MODE_GAMEOVER:
		if (m_pGameOver != NULL) { m_pGameOver->Draw(); }
		break;
	case	MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Draw(); }
		break;

	}
	if (m_pRenderer != NULL)
	{

		// 3D�|���S���̕`�揈��
		//m_pRenderer->Draw(m_pRenderer->CsceneName_SceneName3D);
		// 2D�|���S���̕`�揈��
		m_pRenderer->Draw();

	}
	//�X�V����
	if (m_pfade != NULL){m_pfade->Draw();}
}
HRESULT CManeger::SetMode(MODE mode)
{
	//CSceneNum3D::Release3DALL();

	CScene::ReleaseALL();

	//m_pfade = NULL;

	if (m_pfade != NULL)
	{
		CFade::UnLoad();
		m_pfade->Uninit();
		delete m_pfade;
		m_pfade = NULL;

	}

	m_Mode = mode;

	//m_ptitle = NULL;

	//m_pGame = NULL;

	//m_presult = NULL;




	switch (m_Mode)
	{
	case	MODE_TITLE:
		if (m_ptitle != NULL)
		{
			CTitle::UnLoad();

			m_ptitle->Uninit();
			delete m_ptitle;
			m_ptitle = NULL;

		}
		break;
	case	MODE_GAME:
		if (m_pGame != NULL)
		{

			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

		}
		break;
	case	MODE_GAMESTAGE2:
		if (m_pGameStage2 != NULL)
		{

			m_pGameStage2->Uninit();
			delete m_pGameStage2;
			m_pGameStage2 = NULL;

		}
		break;
	case	MODE_RESULT:


		if (m_presult != NULL)
		{

			CResult::UnLoad();

			m_presult->Uninit();
			delete m_presult;
			m_presult = NULL;

		}

		break;
	case	MODE_GAMECLEAR:



		if (m_pGameClear != NULL)
		{

			CGamaClear::UnLoad();

			m_pGameClear->Uninit();
			delete m_pGameClear;
			m_pGameClear = NULL;

		}
		break;
	case	MODE_GAMEOVER:



		if (m_pGameOver != NULL)
		{

			CGameOver::UnLoad();

			m_pGameOver->Uninit();
			delete m_pGameOver;
			m_pGameOver = NULL;

		}
		break;

	case	MODE_RANKING:



		if (m_pRanking != NULL)
		{
			CRankingGata::UnLoad();
			CRankes::UnLoad();
			CRanking::UnLoad();

			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;

		}
		break;


	}

	m_ptitle = new CTitle;
	m_pGame = new CGame;
	m_pGameStage2 = new CGameStage2;
	m_presult = new CResult;
	m_pGameClear = new CGamaClear;
	m_pGameOver = new CGameOver;
	m_pRanking = new CRanking;
	m_pfade = new CFade;

	switch (mode)
	{
	case	MODE_TITLE:
		if (m_ptitle != NULL) { CTitle::Load(); m_ptitle = CTitle::Create(); }
		break;
	case	MODE_GAME:
		if (m_pGame != NULL) { m_pGame = CGame::Create(); }
		break;
	case	MODE_GAMESTAGE2:
		if (m_pGameStage2 != NULL) { m_pGameStage2 = CGameStage2::Create(); }
		break;
	case	MODE_RESULT:
		if (m_presult != NULL) { CResult::Load(); m_presult = CResult::Create(); }
		break;
	case	MODE_GAMECLEAR:
		if (m_pGameClear != NULL) { CResult::Load(); m_pGameClear = CGamaClear::Create(); }
		break;
	case	MODE_GAMEOVER:
		if (m_pGameOver != NULL) { CGameOver::Load(); m_pGameOver = CGameOver::Create(); }
		break;
	case	MODE_RANKING:
		if (m_pRanking != NULL) { CRankingGata::Load(); CRankes::Load();  CRanking::Load(); m_pRanking = CRanking::Create(); }
		break;


	}
	if (m_pfade != NULL) { m_pfade = CFade::Create(mode); }


	return S_OK;
}