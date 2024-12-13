//=============================================================================
//
// 入力処理 [input.cpp]
// Author :
//
//=============================================================================
#include"light.h"
#include"manager.h"
#include"renderer.h"
//*************************************************************************************************************************
CLIGHT *CLIGHT::Create(void)
{
	//インスタンス
	CLIGHT*plight = NULL;
	plight = new CLIGHT;
	if (plight != NULL)
	{
		plight->Init();
	}
	return plight;



}

CLIGHT::CLIGHT()
{

	m_pDevice = NULL;

}
CLIGHT::~CLIGHT()
{

}


HRESULT  CLIGHT::Init(void)
{



		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		D3DXVECTOR3 vecDir;

		// ライトをクリアする
		ZeroMemory(&m_light, sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light.Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.2f, -0.5f, 0.4f);

		D3DXVec3Normalize(&vecDir, &vecDir);			//正規化する
		m_light.Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(0, &m_light);

		// ライトを有効にする
		pDevice->LightEnable(0, TRUE);

		return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLIGHT::Uninit(void)
{

}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLIGHT::Update(void)
{
}

