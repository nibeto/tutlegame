//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"BulletLife.h"
#include"Scene2D.h"
#include"bulletNumber.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_BULLET_LIFE_TEX (2)
LPDIRECT3DTEXTURE9 CBulletLife::m_pTexture[MAX_BULLET_LIFE_TEX] = {};

//=============================================================================
// Create関数
//=============================================================================
CBulletLife *CBulletLife::Create(void)
{
	//インスタンス
	CBulletLife*pBulletlife = NULL;
	pBulletlife = new CBulletLife;
	if (pBulletlife != NULL)
	{
		pBulletlife->Init();
	}
	return pBulletlife;

}

HRESULT CBulletLife::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	return S_OK;
}
void CBulletLife::UnLoad(void)
{//unload//破棄

}

//=============================================================================
//コンストラクタ
//=============================================================================
CBulletLife::CBulletLife():CScene(SCENE_NUMBER_TYPE_BULLETLIFE)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCount = 0;

}

//=============================================================================
//デストラクタ
//=============================================================================
CBulletLife::~CBulletLife()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CBulletLife::Init(void)
{
	m_nCount = 0;

	for (int nCntNumberBULLET = 0; nCntNumberBULLET < MAX_BULLETLIFE_DIGIT; nCntNumberBULLET++)
	{

		m_apBulletNUMber[nCntNumberBULLET] =
			CBulletNUmber::Create(D3DXVECTOR3(1025.0f + nCntNumberBULLET * 50, 655.0f, 0.0f), 15.0f, nCntNumberBULLET);
	}
	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CBulletLife::Uninit(void)
{
	for (int nCntNumberBULLET = 0; nCntNumberBULLET < MAX_BULLETLIFE_DIGIT; nCntNumberBULLET++)
	{
		m_apBulletNUMber[nCntNumberBULLET]->Uninit();

	}
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CBulletLife::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	m_nCount++;


		for (int nCntNumberBULLET = 0; nCntNumberBULLET < MAX_BULLETLIFE_DIGIT; nCntNumberBULLET++)
		{

			if (pInputKeyboard->GetTrigger(DIK_X) == true)//任意のキーが押されたどうか
			{
				if (m_nCount % 6 == 5)
				{
					if (nCntNumberBULLET == 4)
					{

						m_apBulletNUMber[nCntNumberBULLET]->Uninit();
					}
				}

				if (m_nCount % 6 == 4)
				{

					if (nCntNumberBULLET == 3)
					{
						m_apBulletNUMber[nCntNumberBULLET]->Uninit();
					}
				}
					if (m_nCount % 6 == 3)
					{

						if (nCntNumberBULLET == 2)
						{
							m_apBulletNUMber[nCntNumberBULLET]->Uninit();
						}
					}
					if (m_nCount % 6 == 2)
					{

						if (nCntNumberBULLET == 1)
						{
							m_apBulletNUMber[nCntNumberBULLET]->Uninit();
						}
					}
					if (m_nCount % 6 == 1)
					{

						if (nCntNumberBULLET == 0)
						{
							m_apBulletNUMber[nCntNumberBULLET]->Uninit();
						}
					}
		}
			if (nCntNumberBULLET == 4|| nCntNumberBULLET == 3|| nCntNumberBULLET == 2|| nCntNumberBULLET == 1|| nCntNumberBULLET == 0)
			{

				if (m_nCount % 160 == 0)
				{
					m_apBulletNUMber[nCntNumberBULLET] =
						CBulletNUmber::Create(D3DXVECTOR3(1025.0f + nCntNumberBULLET * 50, 655.0f, 0.0f), 15.0f, 0);

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
////=============================================================================
void CBulletLife::Draw(void)
{
	try
	{

	for (int nCntNumberBULLET = 0; nCntNumberBULLET < MAX_BULLETLIFE_DIGIT; nCntNumberBULLET++)
	{
		m_apBulletNUMber[nCntNumberBULLET]->Draw();

	}
	}
	catch (const std::exception&)
	{

	}

}

void CBulletLife::AddBulletLife(int nValue)
{
	try
	{

	nScore += nValue;
	m_aScoreDigit[0] = nScore % 100000 / 10000;
	m_aScoreDigit[1] = nScore % 10000 / 1000;
	m_aScoreDigit[2] = nScore % 1000 / 100;
	m_aScoreDigit[3] = nScore % 100 / 10;
	m_aScoreDigit[4] = nScore % 10 / 1;
	}
	catch (const std::exception&)
	{

	}

	//for (nScore = 0; nScore < MAX_BULLETLIFE_DIGIT; nScore++)
	//{
	//	m_apBulletNUMber[nScore]->SetNumber(m_aScoreDigit[nScore]);

	//}

}
int CBulletLife::GetScoer(void)
{


	return nScore;
}

