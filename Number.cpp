//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須
#include"score.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Number.h"
#include"Explosion.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
LPDIRECT3DTEXTURE9 CNUmber::m_pTexture = {};
//=============================================================================
// メイン関数
//=============================================================================
CNUmber *CNUmber::Create(D3DXVECTOR3 pos,   float Length,  int nType)
{
	//インスタンス
	CNUmber*pNumber = NULL;
	//
	pNumber = new CNUmber;
	pNumber->Init(pos,  Length);
	pNumber->m_nNumber = nType;
	return pNumber;

}

//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CNUmber::Load(void)
{//load//読み込み
	if (m_pTexture == NULL)
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		// 頂点情報を設定
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture);
	}
	return S_OK;
}
void CNUmber::UnLoad(void)
{//unload//破棄

 //テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CNUmber::CNUmber()
{//clear（クリア）
}

//=============================================================================
//デストラクタ
//=============================================================================
CNUmber::~CNUmber()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CNUmber::Init(D3DXVECTOR3 pos,  float Length)
{
	//頂点情報生成
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ポリゴンの位置を初期化
	m_pos = pos;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;


	//頂点バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-Length, -Length, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(Length, -Length, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-Length, Length, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(Length, Length, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５)

																	  //テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

												//頂点バッファーをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CNUmber::Uninit(void)
{
	//頂点情報削除
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}

}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CNUmber::Update(void)
{

}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CNUmber::Draw(void)
{
	//描画
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//(D3DPT_TRIANGLELISTプリミティブの種類|1プリミティブの数|&g_aVertex[0]先頭アドレス);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
////=============================================================================
//// ポリゴンの設定処理
////=============================================================================q
void CNUmber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
	//テクスチャー座標更新
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(nNumber*0.1f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2((nNumber*0.1f) + 0.1f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(nNumber*0.1f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2((nNumber*0.1f) + 0.1f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

																//バッファーをアンロック
	m_pVtxBuff->Unlock();
}
