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
#include"renderer.h"
#include"input.h"
#include"bullet.h"
#include"Explosion.h"
#include"Effect.h"
#include "Weapons.h"
#include"SeedManagement.h"
#include "Buildings.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_BULLET_TYPE (3)//a =	透明度 (0～255)

LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_BULLET_TYPE] = {};
bool  g_bDeleateBullet = true;
//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CBullet::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ice.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemykaribullet.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/砲弾.png", &m_pTexture[2]);

	return S_OK;
}
void CBullet::UnLoad(void)
{//unload//破棄
	for (int nBulletType = 0; nBulletType < MAX_BULLET_TYPE; nBulletType++)
	{

		//テクスチャの破棄
		if (m_pTexture[nBulletType] != NULL)
		{
			m_pTexture[nBulletType]->Release();
			m_pTexture[nBulletType] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CBullet::CBullet(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_BULLET) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;
	fMoveX = 0.0f, fMoveY = 0.0f;
	fMoveX1 = 0.0f, fMoveY1 = 0.0f;
	fMoveX2 = 0.0f, fMoveY2 = 0.0f;
	fRoboMoveX = 0.0f, fRoboMoveY = 0.0f;
	fAroundMoveX = 0.0f, fAroundMoveY = 0.0f;
	fRot = 0.0f;
	fRot1 = 0.0f;
	fRot2 = 0.0f;
	fRoboRot = 0.0f;
	fAroundRot = D3DX_PI * 0.25f;

	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	CScene2D::Init();
	//mf_pos = 5;//posの初期化の変数
	//Length = 5;
	SetPosition(pos, move, rot, Length,Length);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSize = Length;//弾の大きさのメンバ変数
	Save();
	SetOBJTYPE(OBJECT_TYPE_BULLET);

	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CBullet::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

	m_nCountBullet++;
	//pos
	D3DXVECTOR3 pos;
	//move(移動量)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	BULLET_TYPE type = BULLET_TYPE_MAX;
	//Xの移動//Yの移動
	CSeedMAnagenet *pseed = CSeedMAnagenet::GetSeed();
	//posを取得
	pos = GetPotion();
	//moveを取得
	move = GetMove();
	//posのサイズを取得
	m_fPosSize = GetLength();
	//アークタンジェント
	fRot = pseed->GetRot();
	fRot = atan2f(fMoveX, fMoveY);
	fRot1 = pseed->GetRot();
	fRot2 = pseed->GetRot();
	fRoboRot = pseed->GetRot();
	fAroundRot = pseed->GetRot();
	float f_Speed = 5.0f;
	//moveで移動
	//加算
	if (Type == BULLET_OBJ_TYPE_PLAYER)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveX = 15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_ENEMY)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveX = -15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_ENEMY_1)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveX = -15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_ENEMY_2)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveX = -15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_PLAYER_1)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveY1 = 15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_PLAYER_2)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveY2 = 15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_PLAYER_3)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fMoveX = 15.0f;
	}
	else if (Type == BULLET_OBJ_TYPE_ROBO)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		move.x = fRoboMoveX = 15.0f;
		move.y = fRoboMoveY = 4.5f;

	}
	else if (Type == BULLET_OBJ_TYPE_AROUND)
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);


	}
	else
	{
		move.x = fMoveX = 0.0f;
		move.x = fRoboMoveX = 0.0f;
		move.x = fMoveX1 = 0.0f;
		move.x = fMoveX2 = 0.0f;
	}

	pseed->TheSeedMove(fMoveX, fMoveY, fRot, move);
	Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, f_Speed);

	pseed->TheSeedMove(fMoveX1, fMoveY1, fRot1, move);
	Scene2DMove(fMoveX1, fMoveY1, fRot1, 3.5f, move, f_Speed);

	pseed->TheSeedMove(fMoveX2, fMoveY2, fRot2, move);
	Scene2DMove(fMoveX2, fMoveY2, fRot2, 0.5f, move, f_Speed);

	pseed->TheSeedMove(fRoboMoveX, fRoboMoveY, fRoboMoveX, move);
	Scene2DMove(fRoboMoveX, fRoboMoveY, fRoboMoveX,fRoboMoveX, move, f_Speed);


	pseed->TheSeedMove(fRoboMoveX, fRoboMoveY, fRoboMoveX, move);
	Scene2DMove(fRoboMoveX, fRoboMoveY, fRoboMoveX,fRoboMoveX, move, f_Speed);



	pos += move;
	move *= 0.1f;


	SetPosition(pos, move, 0.0f, m_fPosSize,m_fPosSize);
	CScene2D::Update();
	if (Type == BULLET_OBJ_TYPE_PLAYER_3)
	{

		if (pos.x > 1250 + m_fPosSize)
		{
			//CExplosion::Create(pos, m_move, m_tex, nPattenAnime, 0.0f, 25.0f);

			Uninit();
		}
	}
	if (Type == BULLET_OBJ_TYPE_ROBO)
	{

		if (pos.x > 1250 + m_fPosSize)
		{
			//CExplosion::Create(pos, m_move, m_tex, nPattenAnime, 0.0f, 25.0f);

			Uninit();
		}
	}
	if (Type == BULLET_OBJ_TYPE_AROUND)
	{

		if (pos.x > 50 + m_fPosSizeX)
		{
			//CExplosion::Create(pos, m_move, m_tex, nPattenAnime, 0.0f, 25.0f);

			Uninit();
		}
	}

	if (Type == BULLET_OBJ_TYPE_PLAYER || Type == BULLET_OBJ_TYPE_PLAYER_1 || Type == BULLET_OBJ_TYPE_PLAYER_2)
	{

		if (pos.x > 250 + m_fPosSize)
		{
			//CExplosion::Create(pos, m_move, m_tex, nPattenAnime, 0.0f, 25.0f);

			Uninit();
		}
	}
	//CSCENE2Dを取得
	if (Type == BULLET_OBJ_TYPE_ENEMY)
	{
		if (pos.x < 50 - m_fPosSize)
		{
			//CExplosion::Create(pos, m_move, m_tex, nPattenAnime, 0.0f, 25.0f);

			Uninit();

		}


	}
	CManeger::MODE m_mode = CManeger::GetMode();

#ifdef _DEBUG
	if (m_mode == CManeger::MODE_RESULT ||CManeger::MODE_TITLE)
	{
		Uninit();
	}


	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (Type == BULLET_OBJ_TYPE_PLAYER || Type == BULLET_OBJ_TYPE_PLAYER_1 || Type == BULLET_OBJ_TYPE_PLAYER_2)
				{
					if (Type == BULLET_OBJ_TYPE_PLAYER_3)
					{

						if (pScene->GetOBJTYPE() == OBJECT_TYPE_BUILIDING)
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

								//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
								pBuliding->Uninit();

							}
						}
					}
				}
			}
		}
	}
#else
	if (m_mode == CManeger::MODE_RESULT || m_mode == CManeger::MODE_TITLE)
	{
		Uninit();
	}

#endif // _DEBUG
		}
		catch (const std::exception&)
		{

		}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
void CBullet::Loads(void)
{
	FILE *pFile;


	pFile = fopen("bullets.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}
}
void CBullet::Save(void)
{
	//seve
	FILE *pFile;


	pFile = fopen("bullets.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}

}
