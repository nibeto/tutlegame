//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Dice.h"
#include"score.h"
#include"sound.h"
#include"Playerobj.h"
#include"SeedManagement.h"
#include "Goal.h"
#include"Life.h"
#include"Game.h"
#include"Polygon.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_ENEMY_TYPE (6)//a =	透明度 (0～255)
#define MOVE_ENEMY_SPEED (5.0f)
LPDIRECT3DTEXTURE9 CDice::m_pTexture[MAX_ENEMY_TYPE] = {};

//=============================================================================
// メイン関数
//=============================================================================
HRESULT CDice::Load(void)
{//load//読み込み
	CRenderer* pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ1.png", &m_pTexture[0]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ2.png", &m_pTexture[1]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ3.png", &m_pTexture[2]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ4.png", &m_pTexture[3]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ5.png", &m_pTexture[4]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/サイコロ6.png", &m_pTexture[5]);


	return S_OK;
}
void CDice::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ENEMY_TYPE; nCntEnemyType++)
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
CDice::CDice(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_DICE) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
	fMoveX1 = 0.0f, fMoveY1 = 0.0f;

	fMoveX = 0.0f, fMoveY = 0.0f;
	m_nLife = 5;
	fMoveX1 = 0.0f;
	fMoveY1 = 0.0f;
	fMoveX = 0.0f;
	fMoveY = 0.0f;
	fRot = 0.0f;
	nCountBullet = 0;

}

//=============================================================================
//デストラクタ
//=============================================================================
CDice::~CDice()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CDice::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float f_R, float f_G, float f_B, float f_A)
{
	CScene2D::Init();
	CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
	mf_pos = 5;//posの初期化の変数
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	SetOBJTYPE(OBJECT_TYPE_DICE);
	SetNOMALDice(pos, move, LengthX, LengthY, f_R, f_G, f_B, f_A);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_nLife = 5;
	fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();
	fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();

	return S_OK;

}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CDice::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CDice::Update(void)
{
	try
	{

		CInputKeyboard* pInputKeyboard = CManeger::GetInput();
		CSound* pSound = CManeger::GetSound();
		CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 tex;
		cLife* pLife = CGame::GetLife();

		fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();

		fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();
		fSpeed = Pseed->fSpped(MOVE_ENEMY_SPEED);
		pos = GetPotion();
		move = GetMove();
		m_fPosSize = GetLength();
		m_fRot = GetfRot();
		nCountBullet++;
		int nCntData;
		DISE_TYPE dice;


		srand((unsigned)time(NULL));   /* 乱数の種をtime からとるおまじない */
		for (nCntData = 0; nCntData < CDice::DISE_TYPE_MAX; nCntData++)
		{
			dice = (DISE_TYPE)(rand() * (double)CDice::DISE_TYPE_MAX / (1.0 + RAND_MAX)); /* サイコロの乱数!!! */
			m_nDiseType = dice;

			BindTexture(m_pTexture[dice]);

		}
		if (pInputKeyboard->GetPress(DIK_O))
		{

			BindTexture(m_pTexture[DISE_TYPE_5]);

			//unsigned int sleep(unsigned int nCntData);

		}

		else if (m_nDiseType == DISE_TYPE_5)
		{
			 
			if (pPoligon == NULL)
			{

				if (nCountBullet % 30 == 0)
				{

				CPoligon::Create(D3DXVECTOR3(250, 610, 0.0f), CPoligon::POLIGON_TYPE_2, 55.0f, 55.0f);
				}

				//pPoligon = CPoligon::Create(D3DXVECTOR3(250, 610, 0.0f), CPoligon::POLIGON_TYPE_2, 55.0f, 55.0f);
			}
		}
#if 0
		//else if(m_nDiseType != DISE_TYPE_5)
		//{
		//	if (pPoligon != NULL)
		//	{
		//		CPoligon::TEXTUREDELEATE(pPoligon);
		//		pPoligon = NULL;
		//	}
		//	//CPoligon::DeLeate(pPoligon);
		//}
#endif


		if (m_nDiseType == DISE_TYPE_BASE || m_nDiseType == DISE_TYPE_3 || m_nDiseType == DISE_TYPE_5)
		{

		}
		else if (m_nDiseType == DISE_TYPE_2 || m_nDiseType == DISE_TYPE_4)
		{


		}
		else if (m_nDiseType == DISE_TYPE_1 || m_nDiseType == DISE_TYPE_5)
		{


		}

		if (m_nDiseType == DISE_TYPE_3)
		{
		}
		else	if (m_nDiseType == DISE_TYPE_4)
		{

		}
		else	if (m_nDiseType == DISE_TYPE_5)
		{

		}
		else
		{

		}


		CScene2D::Update();

		SetNOMALDice(pos, move, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);
	}
	catch (const std::exception&)
	{

	}

}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CDice::Draw(void)
{
	CScene2D::Draw();
}

bool CDice::CntScore(bool score)
{
	return score;
}
