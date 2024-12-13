//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Time.h"
#include"Scene2D.h"
#include"Number.h"
#include"Fade.h"
#include"Timer.h"
#include"Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
//=============================================================================
// Create関数
//=============================================================================
CTime *CTime::Create(void)
{
	//インスタンス
	CTime*pScore = NULL;
	pScore = new CTime;
	if (pScore != NULL)
	{
		pScore->Init();
	}
	return pScore;

}

HRESULT CTime::Load(void)
{//load//読み込み
	return S_OK;
}
void CTime::UnLoad(void)
{//unload//破棄

}

//=============================================================================
//コンストラクタ
//=============================================================================
CTime::CTime() :CScene(SCENE_NUMBER_TYPE_TIME)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTime::~CTime()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CTime::Init(void)
{


	for (int nCntNumber = 0; nCntNumber < MAX_TIME_DIGIT; nCntNumber++)
	{


		m_apNUMber[nCntNumber] =
			CNUmber::Create(D3DXVECTOR3(525.0f + nCntNumber * 50, 65.0f, 0.0f), 15.0f, 0);


	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fRot = 0.25f;
	m_nTime = 99;
	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CTime::Uninit(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Uninit();

	}

}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CTime::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

	m_nCntTimer++;
	if (m_nCntTimer == TIME)
	{
		m_nCntTimer = 0;
		AddTIME(-1);
	}
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Update();

	}
}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CTime::Draw(void)
{

	try
	{

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_DIGIT; nCntNumber++)
	{
		m_apNUMber[nCntNumber]->Draw();

	}
	}
	catch (const std::exception&)
	{

	}

}

void CTime::AddTIME(int nValue)
{
	try
	{
	m_nTime += nValue;
	if (m_nTime < 0)
	{

		//CFade *pFade = CManeger::GetFade();
		//CFade::FADE  m_fade = pFade->FADE_MAX;
		//CManeger*m_manager = CManeger::GetManaher();
		//m_manager->MODE_GAME;
		//CInputKeyboard *pInputKeyboard = CManeger::GetInput();
		//if (pInputKeyboard != NULL && pFade != NULL)
		//{
		//		if (m_fade != pFade->FADE_OUT)
		//		{
		//			pFade->SetFade(m_manager->MODE_RESULT);
		//		}
		//}
	}
	else
	{
		m_aScoreDigit[1] = m_nTime;
		m_aScoreDigit[0] = m_nTime / 10;

		for (int nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
		{
			m_apNUMber[nCntTime]->SetNumber(m_aScoreDigit[nCntTime]);
		}
	}

	}
	catch (const std::exception&)
	{

	}

}
int CTime::GetTime(int nTime)
{
	try
	{
		nTime = m_nTime;

	}
	catch (const std::exception&)
	{

	}

	return m_nTime;
}

