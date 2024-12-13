//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include "InputKeyboard.h"
#include"Explosion.h"
#include"block.h"
#include "Life.h"
#include "Game.h"
#include"Enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (1.0f)//赤 (0～255)
#define COLOR_G (1.0f)//緑 (0～255)
#define COLOR_B (1.0f)//青 (0～255)
#define COLOR_A (1.0f)//a =	透明度 (0～255)
LPDIRECT3DTEXTURE9 cLife::m_pTexture[MAX_LIFE_TYPE] = {};
//=============================================================================
// Create関数
//=============================================================================
cLife *cLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, LIFE_TYPE type, LIFE_OBJ_TYPE nType)
{
	//インスタンス
	cLife*pBlock = NULL;
	pBlock = new cLife(SCENE_NUMBER_TYPE_LIFE);
	pBlock->Init(pos, move, rot, Length);
	pBlock->BindTexture(m_pTexture[type]);
	pBlock->Type = nType;
	return pBlock;
	//インスタンス
}

HRESULT cLife::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[0]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[1]);

	return S_OK;
}
void cLife::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_LIFE_TYPE; nCntEnemyType++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntEnemyType] != NULL)
		{
			m_pTexture[nCntEnemyType]->Release();
			m_pTexture[nCntEnemyType] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
cLife::cLife(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_LIFE) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_fPosSizeX = 220.0f;//弾の大きさのメンバ変数
	m_fPosSizeY = 20.0f;
	m_bDisp = true;
	m_bjump = false;
	m_nLife = 0;
	f_R = 1.0f;
	f_G = 1.0f;
	f_B = 1.0f;
	f_A = 1.0f;
}

//=============================================================================
//デストラクタ
//=============================================================================
cLife::~cLife()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT cLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	CScene2D::Init();
	mf_pos = 5;//posの初期化の変数
	SetOBJTYPE(OBJECT_TYPE_LIFE);

	SetPosition(pos, move, rot, Length,Length);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = 220.0f;//弾の大きさのメンバ変数
	m_fPosSizeY = 20.0f;
	m_nLife = 0;
	f_R = 1.0f;
	f_G = 1.0f;
	f_B = 1.0f;
	f_A = 1.0f;

	return S_OK;

}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void cLife::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void cLife::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;


	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();
	col = GetCol();


	if (m_fPosSizeX >= 250.0f)
	{
	}
	else
	{
		//m_fPosSizeX--;

	}
	if (m_fPosSizeX > 150)
	{
		f_R = 1.0f;
		f_G = 1.0f;
		f_B = 1.0f;
		f_A = 1.0f;


	}


	CPlayer*pPlayer = CGame::GetPlayer();
	CEnemy*pEnemy = CGame::GetEnemy();

	if (Type == LIFE_OBJ_TYPE_LIFE)
	{
		m_nLife = pPlayer->GetPLayerLife();
		m_nLife = GetLife(m_nLife);
		if (m_nLife <= 4)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 3)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 2)
		{
			m_fPosSizeX -= 20;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 1)
		{
			m_fPosSizeX -= 5;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 0)
		{
			m_fPosSizeX = 0;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		else
		{
			f_R = 0.0f;
			f_G = 1.0f;
			f_B = 0.0f;
			f_A = 1.0f;

		}
	SetHP(pos, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);
	}

	else if (Type == LIFE_OBJ_TYPE_LIFE_ENEMY)
	{
		m_nLife = pEnemy->GetLife();
		m_nLife = GetLife(m_nLife);
		if (m_nLife <= 4)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 3)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 2)
		{
			m_fPosSizeX -= 20;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 1)
		{
			m_fPosSizeX -= 5;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 0)
		{
			m_fPosSizeX = 0;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		else
		{
			f_R = 0.0f;
			f_G = 1.0f;
			f_B = 0.0f;
			f_A = 1.0f;

		}
		SetHP(pos, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);



	}

	else if (Type == LIFE_OBJ_TYPE_MP)
	{

		m_nMagicPoint = pPlayer->GetMagicPoint();
		m_nMagicPoint = GetMagicpoint(m_nMagicPoint);
		if (m_nMagicPoint <= 4)
		{
			m_fPosSizeX = 50;

		}
		if (m_nMagicPoint <= 3)
		{
			m_fPosSizeX = 50;

		}
		if (m_nMagicPoint <= 2)
		{
			m_fPosSizeX -= 20;

		}
		if (m_nMagicPoint <= 1)
		{
			m_fPosSizeX -= 5;
		}
		if (m_nMagicPoint <= 0)
		{
			m_fPosSizeX = 0;

		}
		else
		{
			f_R = 0.0f;
			f_G = 0.0f;
			f_B = 1.0f;
			f_A = 1.0f;

		}
		SetMagicPoint(pos, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);

	}
	CScene2D::Update();
		}
		catch (const std::exception&)
		{

		}

}

////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void cLife::Draw(void)
{
	CScene2D::Draw();
}
int cLife::GetLife(int nLife)
{
	return nLife;
}
int cLife::GetMagicpoint(int nMagicPoint)
{
	return nMagicPoint;
}

