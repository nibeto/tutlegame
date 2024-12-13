//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"GameStage2.h"
#include"Scene2D.h"
#include"Player.h"
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
// マクロ定義
//*****************************************************************************
CFONT*CGameStage2::m_pFont = NULL;
CPlayer*CGameStage2::m_pPlayer = NULL;//プレイヤー
cLife*CGameStage2::m_pLife = NULL;
CPlayerObj*CGameStage2::m_pPlayerobj = NULL;//プレイヤー
CRobo*CGameStage2::m_pRobo = NULL;//プレイヤー
CEnemy*CGameStage2::m_Enemy = NULL;
CRogowaku*CGameStage2::m_rogowaku = NULL;
CBg*CGameStage2::m_pBg = NULL;
CBullet*CGameStage2::m_pBullet = NULL;
CEffect*CGameStage2::m_pEffect = NULL;
CGoal*CGameStage2::m_pGoal = NULL;
Cblock*CGameStage2::m_pBlock = NULL;
CDebug*CGameStage2::m_pDebug = NULL;
CPause*CGameStage2::m_pPause = NULL;
CPAUSESELECT*CGameStage2::m_pPauseSerect = NULL;
CManeger*CGameStage2::m_pManagement = NULL;
CTimer*CGameStage2::m_pTimer = NULL;
CTime*CGameStage2::m_pTime = NULL;
CLevel*CGameStage2::m_pLevel = NULL;
CCapsule*CGameStage2::m_pCapsule = NULL;
CCAPSULEENEMY*CGameStage2::m_pCapsuleEnemy = NULL;
CDice*CGameStage2::m_pDice = NULL;
CFontMode*CGameStage2::m_pFontMode = NULL;
CScore*CGameStage2::m_pScore = NULL;
CBUilding*CGameStage2::m_pBuiliding = NULL;
CBoss*CGameStage2::m_pBoss = NULL;
//=============================================================================
// Create関数
//=============================================================================
CGameStage2 *CGameStage2::Create(void)
{
	//インスタンス
	CGameStage2*pgame = NULL;
	pgame = new CGameStage2;
	if (pgame != NULL)
	{
		pgame->Init();
	}
	return pgame;

}
//=============================================================================
//コンストラクタ
//=============================================================================
CGameStage2::CGameStage2()
{//clear（クリア）

}

//=============================================================================
//デストラクタ
//=============================================================================
CGameStage2::~CGameStage2()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CGameStage2::Init(void)
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
		//BGのCREATE()
		//**********************************
		m_pBg = CBg::Create();
		CBulletLife::Create();
		m_pScore = CScore::Create();
		CTime::Create();
		//	CLevel::Create();
		m_pFontMode = CFontMode::Create(CManeger::MODE_GAMESTAGE2);
		m_pLife = cLife::Create(D3DXVECTOR3(210.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -125.0f, 25.0f, cLife::LIFE_TYPE_BASE, cLife::LIFE_OBJ_TYPE_LIFE);
		m_pLife = cLife::Create(D3DXVECTOR3(210.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -125.0f, 25.0f, cLife::LIFE_TYPE_BASE, cLife::LIFE_OBJ_TYPE_MP);
		m_pDice = CDice::Create(D3DXVECTOR3(245.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 55.0f, 25.0f, CDice::DISE_TYPE_BASE, CDice::DICE_CLASS_TYPE_BASE, 1.0f, 1.0f, 1.0f, 1.0f);
	}


	CDebug::Loads();
	//**********************************
	//ブロックのCREATE()
	//**********************************
	int nNUmBlock = CDebug::GetNumBlock();
	CDebug::Debug *block = CDebug::Getblock();

	if (m_bDebug == false)
	{
		for (int nCntBlock = 0; nCntBlock < nNUmBlock; nCntBlock++)
		{

			m_pDebug =
				CDebug::Create(block[nCntBlock].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					block[nCntBlock].f_rot,
					block[nCntBlock].f_sizeX,
					block[nCntBlock].f_sizeY,
					(CDebug::DEBUG_TYPE)block[nCntBlock].type);

		}
	}
	if (m_bDebug == false)
	{

		m_rogowaku = CRogowaku::Create(D3DXVECTOR3(1110.0f, 90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 145.0f, CRogowaku::ROGOWAKU_TYPE_BASE, 1);
		m_rogowaku = CRogowaku::Create(D3DXVECTOR3(1110.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 55.0f, CRogowaku::ROGOWAKU_TYPE_1, 1);
		m_rogowaku = CRogowaku::Create(D3DXVECTOR3(310.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 55.0f, CRogowaku::ROGOWAKU_TYPE_2, 1);
		m_rogowaku = CRogowaku::Create(D3DXVECTOR3(750.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 155.0f, 155.0f, CRogowaku::ROGOWAKU_TYPE_3, 1);



		//**********************************
		//プレイヤーのCREATE()
		//**********************************
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(50, 610, 0.0f), CPlayer::PLAYER_TYPE_2, 55.0f, 55.0f);

		m_pPlayerobj = CPlayerObj::Create(D3DXVECTOR3(150, 620, 0.0f), CPlayerObj::PLAYEROBJ_TYPE_2, 25.0f, 5.0f);
		//m_pRobo = CRobo::Create(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 55.0f, 55.0f, CRobo::ROBO_TYPE_BASE,CRobo::ROBO_CLASS_TYPE_BASE);
		m_pRobo = CRobo::Create(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 55.0f, 55.0f, CRobo::ROBO_TYPE_1, CRobo::ROBO_CLASS_TYPE_1);

		m_pCapsule = CCapsule::Create(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 55.0f, 55.0f, CCapsule::CAPSULE_TYPE_1, CCapsule::CAPSULE_CLASS_TYPE_BASE);


		CEnemy::Loads();
		//**********************************
		//ブロックのCREATE()
		//**********************************
		int nNUmEnemy = CEnemy::GetNumEnemy();
		CEnemy::Enemy *enemy = CEnemy::GetEnemy();

		if (m_bDebug == false)
		{
			for (int nCntEnemy = 0; nCntEnemy < nNUmEnemy; nCntEnemy++)
			{

				m_Enemy =
					CEnemy::Create(enemy[nCntEnemy].pos,
						enemy[nCntEnemy].move,
						enemy[nCntEnemy].f_sizeX,
						enemy[nCntEnemy].f_sizeY,
						(CEnemy::ENEMY_TYPE)enemy[nCntEnemy].type, (CEnemy::ENEMY_CLASS_TYPE)enemy[nCntEnemy].ntype, enemy[nCntEnemy].f_R, enemy[nCntEnemy].f_G, enemy[nCntEnemy].f_B, enemy[nCntEnemy].f_A);

			}
		}
#if 0
		CBUilding::Loads();
		//**********************************
		//ブロックのCREATE()
		//**********************************
		int nNUmBUiliding = CBUilding::GetNumBuilding();
		CBUilding::Building *builiding = CBUilding::GetBuilding();

		if (m_bDebug == false)
		{
			for (int nCntBUiliding = 0; nCntBUiliding < nNUmBUiliding; nCntBUiliding++)
			{
				m_pBuiliding =
					CBUilding::Create(builiding[nCntBUiliding].pos,
						builiding[nCntBUiliding].move,
						builiding[nCntBUiliding].f_sizeX,
						builiding[nCntBUiliding].f_sizeY,
						(CBUilding::BUILDING_TYPE)builiding[nCntBUiliding].type, (CBUilding::BUILDING_CLASS_TYPE)builiding[nCntBUiliding].ntype, builiding[nCntBUiliding].f_R, builiding[nCntBUiliding].f_G, builiding[nCntBUiliding].f_B, builiding[nCntBUiliding].f_A);

			}
		}
#endif



		//**********************************
		//オブジェクトのCREATE()
		//**********************************
		//*1体目*//
		CObj::Create(D3DXVECTOR3(1245.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_BASE, CObj::OBJ_BOX_TYPE_2);
		////*2体目*//
		CObj::Create(D3DXVECTOR3(1245.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_1, CObj::OBJ_BOX_TYPE_2);
		////*4体目*//
		CObj::Create(D3DXVECTOR3(1645.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_BASE, CObj::OBJ_BOX_TYPE_BASE);
		////*5体目*//
		CObj::Create(D3DXVECTOR3(1645.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_1, CObj::OBJ_BOX_TYPE_2);
		////*6体目*//
		CObj::Create(D3DXVECTOR3(1945.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_BASE, CObj::OBJ_BOX_TYPE_2);
		////*7体目*//
		CObj::Create(D3DXVECTOR3(1945.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_1, CObj::OBJ_BOX_TYPE_BASE);
		////*8体目*//
		CObj::Create(D3DXVECTOR3(2945.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_BASE, CObj::OBJ_BOX_TYPE_2);
		////*9体目*//
		CObj::Create(D3DXVECTOR3(2945.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_1, CObj::OBJ_BOX_TYPE_BASE);
		////*10体目*//
		CObj::Create(D3DXVECTOR3(4945.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 225.0f, 225.0f, CObj::OBJ_TYPE_BASE, CObj::OBJ_BOX_TYPE_2);





		CTimer::Create(D3DXVECTOR3(740.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -655.0f, 225.0f, 225.0f, CTimer::TIMER_TYPE_BASE, CTimer::TIMER_BOX_TYPE_BASE);
		CTimer::Create(D3DXVECTOR3(740.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1155.0f, 225.0f, 225.0f, CTimer::TIMER_TYPE_1, CTimer::TIMER_BOX_TYPE_1);
	}
	if (m_bPouse == true)
	{

		CPause::Create();

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
//// ポリゴンの終了処理
////=============================================================================
void CGameStage2::Uninit(void)
{
	CScene::ReleaseALL();
	CScene2D::ReleaseALL();

	if (m_apfade != NULL)
	{//キーボード
		m_apfade->Uninit();
		// キーボードの終了処理
		delete m_apfade;
		m_apfade = NULL;
	}
	else
	{

	}


}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CGameStage2::Update(void)
{
	CFade *pFade = CManeger::GetFade();
	CFade::FADE  m_fade = pFade->FADE_MAX;
	CManeger::MODE m_mode = CManeger::GetMode();
	CPAUSESELECT *pPauseSerect = CGameStage2::GetPauseSerect();
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();



	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		m_bPouse = m_bPouse ? false : true;
	}
	m_Pause = pPauseSerect->GetPauseMode();


	if (m_mode == CManeger::MODE_GAMESTAGE2)
	{

		m_pFontMode->Update(CManeger::MODE_GAMESTAGE2);

		if (pInputKeyboard != NULL && pFade != NULL)
		{

			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				CSound *pPlaySound = CManeger::GetSound();
				pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM001);


				if (m_fade != pFade->FADE_OUT)
				{
					pFade->SetFade(CManeger::MODE_RESULT);
				}
			}


		}//↑
	}
}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CGameStage2::Draw(void)
{


}
