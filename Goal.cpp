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
#include "Goal.h"
#include"Explosion.h"
#include"Effect.h"
#include "Weapons.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_GOAL_TYPE (3)//a =	透明度 (0～255)
#define MOVE_GOAL_SPEED (5.0f)		//移動速度

LPDIRECT3DTEXTURE9 CGoal::m_pTexture[MAX_GOAL_TYPE] = {};
bool  g_bDeleateGoal = true;
//=============================================================================
// Create関数
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, GOAL_TYPE type, GOAL_OBJ_TYPE nType)
{
	//インスタンス
	CGoal*pBullet = NULL;
	//
	pBullet = new CGoal(SCENE_NUMBER_TYPE_GOAL);
	pBullet->Init(pos, move, rot, Length);
	pBullet->BindTexture(m_pTexture[type]);
	pBullet->Type = nType;
	return pBullet;

}

//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CGoal::Load(void)
{//load//CGoal込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/回復.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/回復.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/回復.png", &m_pTexture[2]);

	return S_OK;
}
void CGoal::UnLoad(void)
{//unload//破棄
	for (int nBulletType = 0; nBulletType < MAX_GOAL_TYPE; nBulletType++)
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
CGoal::CGoal(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_PLAYER) :CScene2D(m_layer)
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
CGoal::~CGoal()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	CScene2D::Init();
	SetNOMAL(pos, Length, Length);
	m_fPosSizeX = Length;//弾の大きさのメンバ変数
	m_fPosSizeY = Length;
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSize = m_fPosx;
	m_fPosSize = Length;//弾の大きさのメンバ変数
	Save();
	SetOBJTYPE(OBJECT_TYPE_GOAL);

	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CGoal::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CGoal::Update(void)
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
	CPlayer *pPLayer = CGame::GetPlayer();
	D3DXVECTOR3 posPlayer = pPLayer->GetPotion();

	GOAL_TYPE type = GOAL_TYPE_MAX;
	//Xの移動//Yの移動

	//posを取得
	pos = GetPotion();
	//moveを取得
	move = GetMove();

	m_fRot = GetfRot();

	//posのサイズを取得
	m_fPosSize = GetLength();



	if (Type == GOAL_OBJ_TYPE_PLAYER)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_ENEMY)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_1)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;


	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_2)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_3)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_ROBO)
	{
		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_AROUND)
	{

		//移動処理
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//playerのposXにposを引く
		fMoveX = posPlayer.x - pos.x;
		//playerのposYにposを引く
		fMoveY = posPlayer.y - pos.y;

		//moveとPlayerのEnemyとPlayerposを引いたmoveを代入
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;


	}
	m_fPosx = m_fPosSizeX;
	m_fPosy = m_fPosSizeY;
	CScene2D::Update();
	SetNOMAL(pos, m_fPosx, m_fPosy);
		}
		catch (const std::exception&)
		{

		}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CGoal::Draw(void)
{
	CScene2D::Draw();
}
void CGoal::Loads(void)
{
	FILE *pFile;


	pFile = fopen("goal.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}
}
void CGoal::Save(void)
{
	//seve
	FILE *pFile;


	pFile = fopen("goal.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}

}
