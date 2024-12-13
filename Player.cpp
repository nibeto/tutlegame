//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須
#include"block.h"
#include"manager.h"
#include"Player.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"Weapons.h"
#include"Playerobj.h"
#include"robo.h"
#include"Life.h"
#include"Game.h"
#include"Goal.h"
#include"SeedManagement.h"
#include"Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

#define COLOR_A (255)//a =	透明度 (0～255)
#define TEX_FILE1 ("data/TEXTURE/フリーレン.png")//青 (0～255)
#define TEX_FILE2 ("data/TEXTURE/フリーレン.png")//青 (0～255)
#define PLAYER_MOVE_SPEED (5.0f)
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_TEX_PLAYER] = {};

bool  g_bDeleatePlayer = true;
HRESULT CPlayer::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);

	return S_OK;
}
void CPlayer::UnLoad(void)
{//unload//破棄
	try
	{
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
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer::CPlayer(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_PLAYER) :CScene2D(m_layer)
{//clear（クリア）
	try
	{

	}
	catch (const std::exception&)
	{
	m_nLife = 2;
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	nCountBullet = 0;
	fMoveX = 0.0f, fMoveY = 0.0f;
	fRot = 0.0f;
	m_bDisp = true;
	m_bjump = false;
	}

}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float LengshX, float LengshY)
{
	try
	{

	D3DXVECTOR2 tex;

	CScene2D::Init();
	m_bDisp = true;
	m_bjump = false;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//SetRot(pos, m_move,0.0f, m_fPosSizeX);
	m_fPosSizeX = LengshX;
	m_fPosSizeY = LengshY;
	nCountBullet = 0;
	m_nLife = 2;
	Save();
	SetOBJTYPE(OBJECT_TYPE_PLAYER);
	Posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_fRot = D3DX_PI * 0.25f;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CPlayer::Update(void)
{
	try
	{

	nCountBullet++;
	m_nCount++;
	int nCntDAta = 0;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CSeedMAnagenet *Pseed = CSeedMAnagenet::GetSeed();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Out;
	//D3DXVECTOR3 v1(1.0f, 1.0f, 1.0f);
	//D3DXVECTOR3 v2(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 v3;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;

	PLAYER_TYPE type = PLAYER_TYPE_MAX;
	pos = GetPotion();
	Posold = pos;
	move = GetMove();
	tex = GetTex();

	m_fPosSize = GetLength();
	m_fRot = GetfRot();
	fMoveX = Pseed->GetfMoveX();
	fMoveY = Pseed->GetfMoveY();
	fMoveZ = Pseed->GetfMoveZ();
	//pos = v1 + v2;

	CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 20, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

	if (pInputKeyboard->GetPress(DIK_S) == true|| pInputKeyboard->GetPress(DIK_UP) == true) {
		fMoveY = 1.0f; }
	if (pInputKeyboard->GetPress(DIK_W) == true|| pInputKeyboard->GetPress(DIK_DOWN) == true) { fMoveY = -1.0f; }

	Pseed->TheSeedMove(0.0f, fMoveY, fRot,move);
	if (fMoveY != 0.0f)
	{//入力された
		Scene2DMove(fMoveX, fMoveY, fRot,fRot, move,5.0f);
	}
	else if (fMoveX != 0.0f){Scene2DMove(fMoveX, fMoveY, fRot,fRot, move,0.0f);}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		CWeapons::Create(D3DXVECTOR3(pos.x + 85, pos.y - 25, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(fMoveY), 0.0f)*0.5f, CWeapons::WEAPONS_TYPE_2, 0.0f, 25.5f);
	}
	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[PLAYER_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[PLAYER_TYPE_2]); }
	if (type == PLAYER_TYPE_1)
	{
		CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 45, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 15.5f, 5.0f, 5 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

	}
	else
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
			{
				CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
				if (pScene != NULL)
				{
					if (pScene->GetOBJTYPE() == OBJECT_TYPE_EFFECT)
					{//弾発見！
						CEffect *pEffect = (CEffect*)pScene;
						pEffect->Uninit();
					}

				}
			}
		}
	}
	if (pInputKeyboard->GetPress(DIK_W) == true ||pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true) {
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
	if (pos.y + PLAYER_POS_Y2 > SCREEN_HEIGHT_Y_2 + 25)
	{
		pos.y = SCREEN_HEIGHT_Y_2 + 25 - PLAYER_POS_Y2;
	}
	if (pos.x - PLAYER_POS_X2 < 0)
	{
		pos.x = PLAYER_POS_X2;
	}
	if (pos.x + PLAYER_POS_X2 > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - PLAYER_POS_X2;
	}



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
		move.y = -GRAVITY / 2;//* fSpeedUp;

	}
	move.y += 1.75f;

	pos.y += move.y;

	if (pInputKeyboard->GetPress(DIK_Z) == true)//任意のキーが押されたどうか
	{
		CSound *pPlaySound = CManeger::GetSound();
		pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

		if (nCountBullet % 5 == 0)
		{
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER_1);

			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER_2);

			CBullet::Create(pos, D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER);
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_X) == true)//任意のキーが押されたどうか
	{
		CSound *pPlaySound = CManeger::GetSound();
		pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

		if (nCountBullet % 2 == 0)
		{

			CBullet::Create(D3DXVECTOR3(pos.x + 45.0f, pos.y, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_PLAYER_3);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_N) == true)//任意のキーが押されたどうか
	{
		if (nCountBullet % 1 == 0)
		{

			CBullet::Create(pos, D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER);
		}
	}

	pos += move;
	move *= 0.1f;

	int nCntTime = 0;
	Cblock*pBlock = CGame::GetBlock();
	//
	//pBlock->CorisionBlock(&pos, &Posold, &move, bLand,&m_fPosSizeX,&m_fPosSizeY);
	//pBlock->Vec3Cross(&pos, &v1, &v2);
	//pBlock->Vec3Dot(&v1, &v2);

	CScene2D::Update();
	if (nCntTime % 50 == 0)
	{
		m_bjump = false;
	}
	//SetPlayerAnimation(0.25,4.0);
	//SetRot(pos,move,5.0f, m_fPosSizeX);
	SetPosition(pos,move,5.0f, m_fPosSizeX, m_fPosSizeY);

	//当たり判定
	collision();
		}
		catch (const std::exception&)
		{

		}

}

//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}
////=============================================================================
//// ポリゴンの当たり判定
////=============================================================================
void CPlayer::collision(void)
{
	D3DXVECTOR2 tex;
	tex = GetTex();

	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene* pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
				{//弾発見！
					CBullet* pBullet = (CBullet*)pScene;
					CPlayerObj* pPlayerobj = (CPlayerObj*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (m_nCount % 160 == 0)
						{
							pBullet->Uninit();
						}

					}

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (GetPotion().x > pos.x - PLAYER_WIDTH - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + PLAYER_WIDTH &&
							GetPotion().y > pos.y - BULLET_SIZE - PLAYER_HEIGHT && GetPotion().y < pos.y + BULLET_SIZE + PLAYER_HEIGHT)
						{
							f_R = 1.0f;
							f_G = 0.0f;
							f_B = 0.0f;
							f_A = 1.0f;
							cLife* pLife = CGame::GetLife();

							pLife->GetLife(m_nLife);
							//m_nLife = 2;
							m_nLife -= 1;

						 if (m_nLife == 0)
							{
								pBullet->Uninit();
								CScene2D::SetPattanAnim(nPattanAnim);
								CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, 25.0f);
								Uninit();
								CFade* pFade = CManeger::GetFade();
								CFade::FADE  m_fade = pFade->FADE_MAX;

								if (m_fade != pFade->FADE_OUT)
								{
									CSound* pPlaySound = CManeger::GetSound();
									pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM001);

									pFade->SetFade(CManeger::MODE_GAMEOVER);
								}
							}
						}
						else
						{
							f_R = 1.0f;
							f_G = 1.0f;
							f_B = 1.0f;
							f_A = 1.0f;
						}
					}
				}
				else if (pScene->GetOBJTYPE() == OBJECT_TYPE_GOAL)
				{//弾発見！
					CGoal* pGOAl = (CGoal*)pScene;
					D3DXVECTOR3 pos = pGOAl->GetPotion();
					D3DXVECTOR3 move = pGOAl->GetMove();

					if (GetPotion().x > pos.x - m_fPosSizeX - GOAL_WIDTH && GetPotion().x < pos.x + GOAL_WIDTH + m_fPosSizeX &&
						GetPotion().y > pos.y - GOAL_HEIGHT - m_fPosSizeY && GetPotion().y < pos.y + GOAL_HEIGHT + m_fPosSizeY)
					{
						CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f) * 0.5f, -25.0f, 10.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);

						cLife* pLife = CGame::GetLife();

						pLife->GetLife(m_nLife);
						if (m_nLife < 2)
						{
							m_nLife += 1;
						}
						//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
						pGOAl->Uninit();

					}
				}
			}


		}
	}

}
void CPlayer::Loads(void)
{
	FILE *pFile;

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pFile = fopen("Player.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSizeX);
		fscanf(pFile, "%f\n", &m_fPosSizeY);

		fscanf(pFile, "data/TEXTURE/block.png");
		fscanf(pFile, "data/TEXTURE/block.png");


		fclose(pFile);

	}
}
void CPlayer::Save(void)
{
	//seve
	FILE *pFile;

	pFile = fopen("Player.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSizeX);
		fprintf(pFile, "%f\n", m_fPosSizeY);

		fprintf(pFile, TEX_FILE1);
		fprintf(pFile, TEX_FILE2);

		fclose(pFile);

	}
}