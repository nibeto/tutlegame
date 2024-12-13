//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須

#include"manager.h"
#include"Playerobj.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"Weapons.h"
#include "Goal.h"
#include "SeedManagement.h"
#include"Buildings.h"
#include"Fade.h"
#include"Boss.h"
#include"Game.h"
#include"GameStage2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

#define COLOR_A (255)//a =	透明度 (0～255)
#define TEX_FILE1 ("data/TEXTURE/nifer.png")//青 (0～255)
#define TEX_FILE2 ("data/TEXTURE/nifer.png")//青 (0～255)

LPDIRECT3DTEXTURE9 CPlayerObj::m_pTexture[MAX_TEX_PLAYER] = {};


//=============================================================================
// Create関数
//=============================================================================
CPlayerObj *CPlayerObj::Create(D3DXVECTOR3 pos, PLAYEROBJ_TYPE type, float LengshX, float LengshY)
{
	//インスタンス
	CPlayerObj*pPlayerobj = NULL;
	pPlayerobj = new CPlayerObj(SCENE_NUMBER_TYPE_PLAYER_OBJ);
	pPlayerobj->Init(pos,LengshX,LengshY);
	pPlayerobj->BindTexture(m_pTexture[type]);

	return pPlayerobj;

}

HRESULT CPlayerObj::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);

	return S_OK;
}
void CPlayerObj::UnLoad(void)
{//unload//破棄
	for (int nCntPlayer = 0; nCntPlayer < MAX_TEX_PLAYER; nCntPlayer++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntPlayer] != NULL)
		{
			m_pTexture[nCntPlayer]->Release();
			m_pTexture[nCntPlayer] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayerObj::CPlayerObj(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_PLAYER_OBJ) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	nCountBullet = 0;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayerObj::~CPlayerObj()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CPlayerObj::Init(D3DXVECTOR3 pos, float LengshX, float LengshY)
{
	CScene2D::Init();
	try
	{
	SetNOMAL(pos, LengshX, LengshY);
	m_bDisp = true;
	m_bjump = false;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
	m_fPosSizeX = LengshX;
	m_fPosSizeY = LengshY;
	nCountBullet = 0;
	SetOBJTYPE(OBJECT_TYPE_PLAYER);

	m_fRot = D3DX_PI * 0.25f;
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
void CPlayerObj::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CPlayerObj::Update(void)
{
	try
	{

	m_nCount++;
	int nCntDAta = 0;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CSeedMAnagenet *pSeed = CSeedMAnagenet::GetSeed();
	CBoss* pBoss = CGame::GetBoss();
	CBoss* pBoss2 = CGameStage2::GetBoss();


	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	PLAYEROBJ_TYPE type = PLAYEROBJ_TYPE_MAX;
	CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);
	float fMoveX = pSeed->GetfMoveX(), fMoveY = pSeed->GetfMoveY();
	float fRot = pSeed->GetRot();
	f_Speed = pSeed->fSpped(5.0f);
	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();
#if 0
	//if (pInputKeyboard->GetKeyboardPress(DIK_D)==true) { fMoveX = 1.0f; }//↑
	//if (pInputKeyboard->GetKeyboardPress(DIK_A)==true) { fMoveX = -1.0f; }//下
#endif
	if (pInputKeyboard->GetPress(DIK_S) == true) { fMoveY = 1.0f; }
	if (pInputKeyboard->GetPress(DIK_W) == true) { fMoveY = -1.0f; }

	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[PLAYEROBJ_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[PLAYEROBJ_TYPE_2]); }
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true) {
		if (move.x != 0) {}
	}
	else
	{
		if (move.x == 0)
		{

		}

	}


	if (pos.y - PLAYER_POS_Y2 < 0)
	{
		pos.y = PLAYER_POS_Y2;
	}
	if (pos.y + PLAYER_POS_Y2 > SCREEN_HEIGHT_Y_2 + 40)
	{
		pos.y = SCREEN_HEIGHT_Y_2 + 40 - PLAYER_POS_Y2;
	}
	if (pos.x - PLAYER_POS_X2 < 0)
	{
		pos.x = PLAYER_POS_X2;
	}
	if (pos.x + PLAYER_POS_X2 > 550)
	{
		pos.x = 550 - PLAYER_POS_X2;
	}


	pSeed->TheSeedMove(fMoveX, fMoveY, fRot, move);
	Scene2DMove(fMoveX,fMoveY,fRot,fRot, move,f_Speed);

#if 0


	//if (m_pos.y >= SCREEN_HEIGHT)
	//{
	//	m_bjump = false;
	//	pos.y = SCREEN_HEIGHT;
	//	move.y = 0.0f;

	//}

#endif // 0
	if (m_pos.y >= SCREEN_HEIGHT)
	{
		m_bjump = false;
		pos.y = SCREEN_HEIGHT;
		move.y = 0.0f;

	}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bjump == false)//任意のキーが押されたどうか
	{

		m_bjump = true;
		move.y = -25.0f;//* fSpeedUp;
		move.y = -50.0f;//* fSpeedUp;
		move.y = -GRAVITYOBJ / 2;//* fSpeedUp;


	}
	move.y += 1.75f;

	pos.y += move.y;

	if (pInputKeyboard->GetPress(DIK_SPACE) == true)//任意のキーが押されたどうか
	{


		move.x -= cosf(D3DX_PI * 1.0f) * fSpeedUp;
		if (pos.x - 250 < 150 - PLAYEROBJ_SIZE)
		{

			pos.x += 550;


		}

		if (pos.x + PLAYEROBJ_WIDTH > 250 + PLAYEROBJ_SIZE)
		{

			pos.x -= 550;

		}

		pos.x += move.x;


	}




	if (pInputKeyboard->GetPress(DIK_SPACE) == true &&pInputKeyboard->GetPress(DIK_Z) == true)//任意のキーが押されたどうか
	{

		if (m_nCount % 5 == 0)
		{
			{
				CBullet::Create(pos, D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER);
			}
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_N) == true)//任意のキーが押されたどうか
	{
		if (m_nCount % 1 == 0)
		{


			CBullet::Create(pos, D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER);
		}
	}

	pos += move;
	move *= 0.1f;

	int nCntTime = 0;
	CScene2D::Update();
	if (nCntTime % 50 == 0)
	{
		m_bjump = false;
	}

	GetPotion();
	GetMove();
	GetLength();
	GetfRot();
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
				{//弾発見！
					CBullet *pBullet = (CBullet*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (GetPotion().x > pos.x - PLAYEROBJ_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + PLAYEROBJ_SIZE &&
							GetPotion().y > pos.y - BULLET_SIZE - PLAYEROBJ_SIZE && GetPotion().y < pos.y + BULLET_SIZE + PLAYEROBJ_SIZE)
						{
							//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
							pBullet->Uninit();
							//Uninit();
						}
					}
				}
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_ENENMY)
				{//弾発見！
					CEnemy *pEnemy = (CEnemy*)pScene;
					D3DXVECTOR3 pos = pEnemy->GetPotion();
					D3DXVECTOR3 move = pEnemy->GetMove();

					if (GetPotion().x > pos.x - m_fPosSizeX - ENEMY_POLYGON_SIZE && GetPotion().x < pos.x + ENEMY_POLYGON_SIZE + m_fPosSizeX &&
						GetPotion().y > pos.y - ENEMY_POLYGON_SIZE - m_fPosSizeY && GetPotion().y < pos.y + ENEMY_POLYGON_SIZE + m_fPosSizeY)
					{
						CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 50.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);
						CScene2D::SetPattanAnim(nPattanAnim);
						CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, m_fPosSize);
						CBoss::Loads();
						//**********************************
						//ボスのCREATE()
						//**********************************
						int nNUmBoss = CBoss::GetNumBoss();
						CBoss::Boss* boss = CBoss::GetBoss();

						for (int enCanteBoss = 0; enCanteBoss < nNUmBoss; enCanteBoss++)
						{

							pBoss =
								CBoss::Create(boss[enCanteBoss].pos,
									boss[enCanteBoss].move,
									boss[enCanteBoss].f_sizeX,
									boss[enCanteBoss].f_sizeY,
									(CBoss::BOSS_TYPE)boss[enCanteBoss].type, (CBoss::BOSS_CLASS_TYPE)boss[enCanteBoss].ntype, boss[enCanteBoss].f_R, boss[enCanteBoss].f_G, boss[enCanteBoss].f_B, boss[enCanteBoss].f_A);
						}
						int nNUmBoss2 = CBoss::GetNumBoss();
						CBoss::Boss* boss2 = CBoss::GetBoss();

						for (int enCanteBoss = 0; enCanteBoss < nNUmBoss2; enCanteBoss++)
						{

							pBoss2 =
								CBoss::Create(boss2[enCanteBoss].pos,
									boss2[enCanteBoss].move,
									boss2[enCanteBoss].f_sizeX,
									boss2[enCanteBoss].f_sizeY,
									(CBoss::BOSS_TYPE)boss[enCanteBoss].type, (CBoss::BOSS_CLASS_TYPE)boss[enCanteBoss].ntype, boss[enCanteBoss].f_R, boss[enCanteBoss].f_G, boss[enCanteBoss].f_B, boss[enCanteBoss].f_A);
						}


						//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
						pEnemy->Uninit();
//#ifdef _DEBUG
//
//
//						CFade *pFade = CManeger::GetFade();
//
//						CFade::FADE  m_fade = pFade->FADE_MAX;
//
//						if (m_fade != pFade->FADE_OUT)
//						{
//							pFade->SetFade(CManeger::MODE_RESULT);
//						}
//#endif // _DEBUG
//
					}
				}
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BOSS)
				{//弾発見！
					CBoss *pBoss = (CBoss*)pScene;
					D3DXVECTOR3 pos = pBoss->GetPotion();
					D3DXVECTOR3 move = pBoss->GetMove();

					if (GetPotion().x > pos.x - m_fPosSizeX - BOSS_POLYGON_SIZE && GetPotion().x < pos.x + BOSS_POLYGON_SIZE + m_fPosSizeX &&
						GetPotion().y > pos.y - BOSS_POLYGON_SIZE - m_fPosSizeY && GetPotion().y < pos.y + BOSS_POLYGON_SIZE + m_fPosSizeY)
					{
						CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 10.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);
						nCountAnime++;
						CScene2D::SetPattanAnim(nPattanAnim);
						CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, m_fPosSize);

						//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
						pBoss->Uninit();

						CSound *pPlaySound = CManeger::GetSound();
						pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM001);


						CFade *pFade = CManeger::GetFade();

						CFade::FADE  m_fade = pFade->FADE_MAX;

						if (m_fade != pFade->FADE_OUT)
						{
							pFade->SetFade(CManeger::MODE_RESULT);
						}

					}
				}
				else	if (pScene->GetOBJTYPE() == OBJECT_TYPE_BUILIDING)
				{//弾発見！
					CBUilding *pBuliding = (CBUilding*)pScene;
					D3DXVECTOR3 pos = pBuliding->GetPotion();
					D3DXVECTOR3 move = pBuliding->GetMove();
					float m_fSixe_X = pBuliding->GetBulidingSizeX();
					float m_fSixe_Y = pBuliding->GetBulidingSizeY();
					if (GetPotion().x > pos.x - m_fPosSizeX - m_fSixe_X && GetPotion().x < pos.x + m_fSixe_X + m_fPosSizeX &&
						GetPotion().y > pos.y - m_fSixe_Y - m_fPosSizeY && GetPotion().y < pos.y + m_fSixe_Y + m_fPosSizeY)
					{

						//CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 10.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);
						pBuliding->Uninit();

					}
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
//// ポリゴンの描画処理
////=============================================================================q
void CPlayerObj::Draw(void)
{
	CScene2D::Draw();
}
