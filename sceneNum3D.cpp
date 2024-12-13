//=============================================================================
//
// メイン処理 [scene.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須


#include"sceneNum3D.h"
#include"renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//静的メンバ変数
CSceneNum3D *CSceneNum3D::m_apSine3D[(LAYER3D)SCENE3D_NUMBER_TYPE_MAX][MAX_SCENE3D] = {};
int CSceneNum3D::m_nNumAll3D = 0;
//=============================================================================
// メイン関数
//=============================================================================





//=============================================================================
// 初期化処理
//=============================================================================
CSceneNum3D::CSceneNum3D(SCENE3D_NUMBER_TYPE m_Number)
{
	//nPrioty = MAX_DEFFULT;
	for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
	{

		if (m_apSine3D[m_Number][nCntScene] == NULL)
		{

			m_apSine3D[m_Number][nCntScene] = this;
			m_nID3D = nCntScene;
			m_nLayer3D = (LAYER3D)m_Number;
			m_nNumAll3D++;
			break;
		}
	}

}
//=============================================================================
//デストラクタ
//=============================================================================
CSceneNum3D::~CSceneNum3D()
{

}
void CSceneNum3D::Release3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < m_nNumAll3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{

				// ポリゴンの終了処理
				m_apSine3D[nCntDeffult][nCntScene]->Uninit();
				delete m_apSine3D[nCntDeffult][nCntScene];
				m_apSine3D[nCntDeffult][nCntScene] = NULL;

			}
		}
	}

}

void CSceneNum3D::Update3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apSine3D[nCntDeffult][nCntScene]->Update();


			}
		}

	}

}

void CSceneNum3D::Draw3DALL(void)
{

	for (int nCntDeffult = 0; nCntDeffult < (SCENE3D_NUMBER_TYPE)LAYER3D_MAX; nCntDeffult++)
	{

		for (int nCntScene = 0; nCntScene < MAX_SCENE3D; nCntScene++)
		{

			if (m_apSine3D[nCntDeffult][nCntScene] != NULL)
			{
				// ポリゴンの終了処理
				m_apSine3D[nCntDeffult][nCntScene]->Draw();

			}
		}

	}

}
void CSceneNum3D::Road(void)
{



}

void CSceneNum3D::Release3D(void)
{

	SCENE3D_NUMBER_TYPE   nNumber3D = (SCENE3D_NUMBER_TYPE)m_nLayer3D;

	int nID3D = m_nID3D;//変数にメンバーに保存

	if (m_apSine3D[nNumber3D][nID3D] != NULL)
	{


		delete m_apSine3D[nNumber3D][nID3D];
		m_apSine3D[nNumber3D][nID3D] = NULL;
		m_nNumAll3D--;


	}

}

//=============================================================================
//オブジェクトの破棄
//=============================================================================
void CSceneNum3D::SetOBJTYPE3D(OBJECT_TYPE3D type)
{
	m_apType3D = type;

}
CSceneNum3D * CSceneNum3D::GetCSINE3D(SCENE3D_NUMBER_TYPE m_Number3D, int m_IDx)
{
	return m_apSine3D[m_Number3D][m_IDx];
}

