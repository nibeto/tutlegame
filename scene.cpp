//=============================================================================
//
// メイン処理 [scene.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須


#include"scene.h"
#include"renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//静的メンバ変数
CScene *CScene::m_apSine[(LAYER)SCENE_NUMBER_TYPE_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;
//=============================================================================
// メイン関数
//=============================================================================





//=============================================================================
//コンストラクタ
//=============================================================================
CScene::CScene(SCENE_NUMBER_TYPE nNumber)
{

		//nPrioty = MAX_DEFFULT;
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apSine[nNumber][nCntScene] == NULL)
			{

				m_apSine[nNumber][nCntScene] = this;
				m_nID = nCntScene;
				m_nLayer = (LAYER)nNumber;
				m_nNumAll++;
				break;
			}
		}
}
//=============================================================================
//デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//リリース処理
//=============================================================================
void CScene::ReleaseALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < m_nNumAll; nCntScene++)
		{

			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{

				// ポリゴンの終了処理
				m_apSine[nCntDeffult][nCntScene]->Uninit();
				delete m_apSine[nCntDeffult][nCntScene];
				m_apSine[nCntDeffult][nCntScene] = NULL;

			}
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CScene::UpdateALL(void)
{


	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{


				// ポリゴンの更新処理
				m_apSine[nCntDeffult][nCntScene]->Update();


			}
		}

	}
}
//=============================================================================
//描画処理
//=============================================================================
void CScene::DrawALL(void)
{


	for (int nCntDeffult = 0; nCntDeffult < (SCENE_NUMBER_TYPE)LAYER_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apSine[nCntDeffult][nCntScene] != NULL)
			{
				// ポリゴンの終了処理
				m_apSine[nCntDeffult][nCntScene]->Draw();

			}
		}

	}



}

void CScene::Road(void)
{



}


//=============================================================================
//オブジェクトの破棄
//=============================================================================
void CScene::Release(void)
{



	SCENE_NUMBER_TYPE   nNumber = (SCENE_NUMBER_TYPE)m_nLayer;

	int nID = m_nID;//変数にメンバーに保存

	if (m_apSine[nNumber][nID] != NULL)
	{


			delete m_apSine[nNumber][nID];
			m_apSine[nNumber][nID] = NULL;
			m_nNumAll--;


		}





}
//=============================================================================
//オブジェクトの破棄
//=============================================================================
void CScene::SetOBJTYPE(OBJECT_TYPE type)

{
	m_apType = type;

}
CScene * CScene::GetCSINE(SCENE_NUMBER_TYPE  m_Number,int m_IDX)
{

	return m_apSine[m_Number][m_IDX];



}