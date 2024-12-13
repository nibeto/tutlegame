//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include "level.h"
#include"Scene2D.h"
#include"Number.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

LPDIRECT3DTEXTURE9 CLevel::m_pTexture[MAX_LEVEL_TEXTUR] = {};

//=============================================================================
// Create関数
//=============================================================================
CLevel *CLevel::Create(void)
{
	//インスタンス
	CLevel*pScore = NULL;
	pScore = new CLevel;
	if (pScore != NULL)
	{
		pScore->Init();
	}
	return pScore;

}

HRESULT CLevel::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture[0]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_pTexture[1]);

	return S_OK;
}
void CLevel::UnLoad(void)
{//unload//破棄
	for (int nCntBg = 0; nCntBg < MAX_LEVEL_TEXTUR; nCntBg++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CLevel::CLevel() :CScene(SCENE_NUMBER_TYPE_LEVEL)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CLevel::~CLevel()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CLevel::Init(void)
{

	try
	{
	for (int nCntNumber = 0; nCntNumber < MAX_LEVEL_DIGIT; nCntNumber++)
	{


		m_apNUMber[nCntNumber] =
			CNUmber::Create(D3DXVECTOR3(225.0f + nCntNumber * 50, 355.0f, 0.0f), 15.0f, 0);


	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fRot = 0.25f;

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
void CLevel::Uninit(void)
{
	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_LEVEL_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Uninit();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CLevel::Update(void)
{
	try
	{

	AddLevel(5);
	for (int nCntNumber = 0; nCntNumber < MAX_LEVEL_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Update();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================
void CLevel::Draw(void)
{
	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_LEVEL_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Draw();

	}
	}
	catch (const std::exception&)
	{

	}

}

void CLevel::AddLevel(int nValue)
{
	try
	{

	nLevel += nValue;
	m_aScoreDigit[0] = nLevel % 100000 / 10000;
	m_aScoreDigit[1] = nLevel % 10000 / 1000;
	m_aScoreDigit[2] = nLevel % 1000 / 100;
	m_aScoreDigit[3] = nLevel % 100 / 10;
	m_aScoreDigit[4] = nLevel % 10 / 1;

	for (nLevel = 0; nLevel < MAX_LEVEL_DIGIT; nLevel++)
	{
		m_apNUMber[nLevel]->SetNumber(m_aScoreDigit[nLevel]);

	}

	}
	catch (const std::exception&)
	{

	}
}
int CLevel::GetLevel(void)
{

	try
	{

	}
	catch (const std::exception&)
	{

	}	
	return nLevel;

}

