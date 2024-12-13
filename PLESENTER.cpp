//=============================================================================
//
// 背景処理[Parturn.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "PLESENTER.h"
#include"manager.h"
//=============================================================================
//ポリゴン初期化処理
//=============================================================================
LPDIRECT3DTEXTURE9 CPLESEENTER::m_pTexture[MAX_PLESENTER] = {};
LPDIRECT3DVERTEXBUFFER9 CPLESEENTER::m_pVtxBuff = NULL;
//=============================================================================
// Create関数
//=============================================================================
CPLESEENTER *CPLESEENTER::Create(D3DXVECTOR3 pos, float Length, int nType)
{
	CPLESEENTER*pPreseenter = NULL;
	pPreseenter = new CPLESEENTER;
	if (pPreseenter != NULL)
	{
		pPreseenter->Init();
	}
	return pPreseenter;

}
//=============================================================================
//コンストラクタ
//=============================================================================
CPLESEENTER::CPLESEENTER()
{//clear（クリア）


}

//=============================================================================
//デストラクタ
//=============================================================================
CPLESEENTER::~CPLESEENTER()
{

}

HRESULT CPLESEENTER::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/背景.jpg", &m_pTexture[0]);


	return S_OK;
}
void CPLESEENTER::UnLoad(void)
{//unload//破棄
	try
	{

	for (int nCuntData = 0; nCuntData < MAX_PLESENTER; nCuntData++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCuntData] != NULL)
		{
			m_pTexture[nCuntData]->Release();
			m_pTexture[nCuntData] = NULL;
		}
	}
	}
	catch (const std::exception&)
	{

	}

}

HRESULT CPLESEENTER::Init()
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//g_nPurturn = 0;
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

							//頂点バッファをロックして、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos+D3DXVECTOR3(720, 620, 0.0f);
	pVtx[1].pos = m_pos+D3DXVECTOR3(1120, 620, 0.0f);
	pVtx[2].pos = m_pos+D3DXVECTOR3(720, 725, 0.0f);
	pVtx[3].pos = m_pos+D3DXVECTOR3(1120, 725, 0.0f);

	//rhwの設定5
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //色の指定（０～２５５）&透明度（０～２５５)


													  //テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}

void CPLESEENTER::Uninit(void)
{
	try
	{

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		//m_apScene2D->Uninit();
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}
	}
	catch (const std::exception&)
	{

	}


}
void CPLESEENTER::Update(void){}

void CPLESEENTER::Draw(void)
{
	try
	{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCuntData = 0; nCuntData < MAX_PLESENTER; nCuntData++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCuntData]);

		//(D3DPT_TRIANGLELISTプリミティブの種類|1プリミティブの数|&g_aVertex[0]先頭アドレス);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCuntData, 2);



	}

	}
	catch (const std::exception&)
	{

	}

}

