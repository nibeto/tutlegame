//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Game.h"
#include"Scene2D.h"
#include"Player.h"
#include"Polygon.h"
#include"input.h"
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
#include"Fade.h"
#include "font.h"
#include "Life.h"
#include"Goal.h"
#include "pauseselect.h"
#include "pause.h"
#include "Timer.h"
#include"Time.h"
#include"level.h"
#include"Capsule.h"
#include"CapsuleEnemy.h"
#include"Scene3D.h"
#include"Title.h"
#include"Dice.h"
#include"Debug.h"
#include"fontMode.h"
#include"Buildings.h"
#include"Boss.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
CFONT*CGame::m_pFont = NULL;
CPlayer*CGame::m_pPlayer = NULL;//�v���C���[
CPoligon*CGame::m_pPoligon = NULL;
cLife*CGame::m_pLife = NULL;
CPlayerObj*CGame::m_pPlayerobj = NULL;//�v���C���[
CRobo*CGame::m_pRobo = NULL;//�v���C���[
CEnemy*CGame::m_Enemy = NULL;
CRogowaku*CGame::m_rogowaku = NULL;
CBg*CGame::m_pBg = NULL;
CBullet*CGame::m_pBullet = NULL;
CEffect*CGame::m_pEffect = NULL;
CGoal*CGame::m_pGoal = NULL;
Cblock*CGame::m_pBlock = NULL;
CDebug*CGame::m_pDebug = NULL;
CPause*CGame::m_pPause = NULL;
CPAUSESELECT*CGame::m_pPauseSerect = NULL;
CManeger*CGame::m_pManagement = NULL;
CTimer*CGame::m_pTimer = NULL;
CTime*CGame::m_pTime = NULL;
CLevel*CGame::m_pLevel = NULL;
CCapsule*CGame::m_pCapsule = NULL;
CCAPSULEENEMY*CGame::m_pCapsuleEnemy = NULL;
CDice*CGame::m_pDice = NULL;
CFontMode*CGame::m_pFontMode = NULL;
CScore*CGame::m_pScore = NULL;
CBUilding*CGame::m_pBuiliding = NULL;
CBoss*CGame::m_pBoss = NULL;
//=============================================================================
// Create�֐�
//=============================================================================
CGame *CGame::Create(void)
{
	//�C���X�^���X
	CGame*pgame = NULL;
	pgame = new CGame;
	if (pgame != NULL)
	{
		pgame->Init();
	}
	return pgame;

}
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGame::CGame()
{//clear�i�N���A�j

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CGame::Init(void)
{

	try
	{
		m_pManagement = CManeger::GetManaher();
		m_bDebug = CManeger::GetDebug();

		CInputKeyboard *pInputGetkey = CManeger::GetInput();

		if (pInputGetkey->GetTrigger(DIK_F4) == true)
		{

			m_bDebug = m_bDebug ? true : false;

		}

		if (m_bDebug == false)
		{

			CSound *pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_BGM001);

			//**********************************
			//BG��CREATE()
			//**********************************
			m_pBg = CBg::Create();
			//m_pScore = CScore::Create();
			m_pTime = CTime::Create();
			m_pFontMode = CFontMode::Create(CManeger::MODE_GAME);
			m_pLife = cLife::Create(D3DXVECTOR3(210.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -125.0f, 25.0f, cLife::LIFE_TYPE_BASE, cLife::LIFE_OBJ_TYPE_LIFE);
			m_pLife = cLife::Create(D3DXVECTOR3(210.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -125.0f, 25.0f, cLife::LIFE_TYPE_BASE, cLife::LIFE_OBJ_TYPE_MP);
			m_pDice = CDice::Create(D3DXVECTOR3(245.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 55.0f, 25.0f, CDice::DISE_TYPE_BASE, CDice::DICE_CLASS_TYPE_BASE, 1.0f, 1.0f, 1.0f, 1.0f);
		}


			CDebug::Loads();
			//**********************************
			//�u���b�N��CREATE()
			//**********************************
			int nNUmBlock = CDebug::GetNumBlock();
			CDebug::Debug *block = CDebug::Getblock();

			if (m_bDebug == false)
			{
					for (int enChanteBlock = 0; enChanteBlock < nNUmBlock; enChanteBlock++)
					{

						m_pDebug =
							CDebug::Create(block[enChanteBlock].pos,
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								block[enChanteBlock].f_rot,
								block[enChanteBlock].f_sizeX,
								block[enChanteBlock].f_sizeY,
								(CDebug::DEBUG_TYPE)block[enChanteBlock].type);

					}
			}
			if (m_bDebug == false)
			{

				//m_rogowaku = CRogowaku::Create(D3DXVECTOR3(1110.0f, 90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 145.0f, CRogowaku::ROGOWAKU_TYPE_BASE, 1);
				//m_rogowaku = CRogowaku::Create(D3DXVECTOR3(1110.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 55.0f, CRogowaku::ROGOWAKU_TYPE_1, 1);
				m_rogowaku = CRogowaku::Create(D3DXVECTOR3(310.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 55.0f, CRogowaku::ROGOWAKU_TYPE_2, 1);
				m_rogowaku = CRogowaku::Create(D3DXVECTOR3(750.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 155.0f, CRogowaku::ROGOWAKU_TYPE_3, 1);



				//**********************************
				//�v���C���[��CREATE()
				//**********************************
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(50, 610, 0.0f), CPlayer::PLAYER_TYPE_2, 55.0f, 55.0f);


				m_pPlayerobj = CPlayerObj::Create(D3DXVECTOR3(150, 620, 0.0f), CPlayerObj::PLAYEROBJ_TYPE_2, 55.0f, 55.0f);
				m_pRobo = CRobo::Create(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 25.0f, 25.0f, CRobo::ROBO_TYPE_1, CRobo::ROBO_CLASS_TYPE_1);

				m_pCapsule = CCapsule::Create(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 35.0f, 35.0f, CCapsule::CAPSULE_TYPE_1, CCapsule::CAPSULE_CLASS_TYPE_BASE);


				CEnemy::Loads();
				//**********************************
				//�G�l�~�[��CREATE()
				//**********************************
				int nNUmEnemy = CEnemy::GetNumEnemy();
				CEnemy::Enemy *enemy = CEnemy::GetEnemy();

				if (m_bDebug == false)
				{
					for (int enChanteEnemy = 0; enChanteEnemy < nNUmEnemy; enChanteEnemy++)
					{

						m_Enemy =
							CEnemy::Create(enemy[enChanteEnemy].pos,
								enemy[enChanteEnemy].move,
								enemy[enChanteEnemy].f_sizeX,
								enemy[enChanteEnemy].f_sizeY,
								(CEnemy::ENEMY_TYPE)enemy[enChanteEnemy].type, (CEnemy::ENEMY_CLASS_TYPE)enemy[enChanteEnemy].ntype,enemy[enChanteEnemy].f_R, enemy[enChanteEnemy].f_G, enemy[enChanteEnemy].f_B, enemy[enChanteEnemy].f_A);

					}
				}




#if 0


				CBUilding::Loads();
				//**********************************
				//��������CREATE()
				//**********************************
				int nNUmBUiliding = CBUilding::GetNumBuilding();
				CBUilding::Building *builiding = CBUilding::GetBuilding();

				if (m_bDebug == false)
				{
					for (int enChanteBUiliding = 0; enChanteBUiliding < nNUmBUiliding; enChanteBUiliding++)
					{
						m_pBuiliding =
							CBUilding::Create(builiding[enChanteBUiliding].pos,
								builiding[enChanteBUiliding].move,
								builiding[enChanteBUiliding].f_sizeX,
								builiding[enChanteBUiliding].f_sizeY,
								(CBUilding::BUILDING_TYPE)builiding[enChanteBUiliding].type, (CBUilding::BUILDING_CLASS_TYPE)builiding[enChanteBUiliding].ntype, builiding[enChanteBUiliding].f_R, builiding[enChanteBUiliding].f_G, builiding[enChanteBUiliding].f_B, builiding[enChanteBUiliding].f_A);

					}
				}
#endif // 0





				CTimer::Create(D3DXVECTOR3(740.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -655.0f, 225.0f, 225.0f, CTimer::TIMER_TYPE_BASE, CTimer::TIMER_BOX_TYPE_BASE);
				CTimer::Create(D3DXVECTOR3(740.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1155.0f, 225.0f, 225.0f, CTimer::TIMER_TYPE_1, CTimer::TIMER_BOX_TYPE_1);
			}
			if (m_bPouse == true)
		{

				CPAUSESELECT::Create(D3DXVECTOR3(550.0f, 50.0f, 0.0f), 500.0f, 0);

		}
		m_bPouse = false;
		m_bDebug = false;
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
void CGame::Uninit(void)
{
	try
	{

	//CSceneNum3D::Release3DALL();
	CScene::ReleaseALL();
	//CSCENE3D::ReleaseALL();
	CScene2D::ReleaseALL();

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
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CGame::Update(void)
{
	try
	{

	CFade *pFade = CManeger::GetFade();
	CFade::FADE  m_fade = pFade->FADE_MAX;
	CManeger::MODE m_mode = CManeger::GetMode();
	CPAUSESELECT *pPauseSerect = CGame::GetPauseSerect();
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();


	//int nValue = -1;

	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
			//PlaySound(SOUND_LABEL_SE_PAUSE);
		m_bPouse = m_bPouse ? false : true;
	}
	m_Pause = pPauseSerect->GetPauseMode();


	if (m_mode == CManeger::MODE_GAME)
	{

		m_pFontMode->Update(CManeger::MODE_GAME);

	if (pInputKeyboard != NULL && pFade != NULL)
	{

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			CSound *pPlaySound = CManeger::GetSound();
			pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM001);


			if (m_fade != pFade->FADE_OUT)
			{
				pFade->SetFade(CManeger::MODE_GAMESTAGE2);
			}
		}


		}//��
	}
	if (pInputKeyboard->GetPress(DIK_P))
	{
		CPAUSESELECT::Create(D3DXVECTOR3(550.0f,50.0f,0.0f),500.0f,0);
	}
	}
	catch (const std::exception&)
	{

	}

}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CGame::Draw(void)
{
	//if (m_pCamera != NULL)
	//{
	//	// light�̍X�V����
	//	m_pCamera->SetCamera();

	//}


}
