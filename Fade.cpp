//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Fade.h"
#include"Scene2D.h"
#include"block.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (1.0f)//赤 (0～255)
#define COLOR_G (1.0f)//緑 (0～255)
#define COLOR_B (1.0f)//青 (0～255)
#define COLOR_A (1.0f)//a =	透明度 (0～255)
#define NUM_POLYGON	(5)

LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;
//=============================================================================
// Create関数
//=============================================================================
CFade *CFade::Create(CManeger::MODE modeNext)
{
	CFade*pFade = NULL;
	pFade = new CFade;
	if (pFade != NULL)
	{
		pFade->Init(modeNext);
	}
	return pFade;

}

HRESULT CFade::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/背景.jpg", &m_pTexture);


	return S_OK;
}
void CFade::UnLoad(void)
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
CFade::CFade()
{//clear（クリア）


}

//=============================================================================
//デストラクタ
//=============================================================================
CFade::~CFade()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CFade::Init(CManeger::MODE modeNext)
{
	try
	{

	m_Fade = FADE_IN;
	m_modeNext = modeNext;
	m_Fadecol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);


	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

							//頂点バッファをロックして、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点バッファの情報を設定

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //色の指定（０～２５５）&透明度（０～２５５)


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
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CFade::Uninit(void)
{
		//頂点バッファの破棄
		if (m_pVtxBuff != NULL)
		{
			//m_apScene2D->Uninit();
			m_pVtxBuff->Release();
			m_pVtxBuff = NULL;

		}

}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CFade::Update(void)
{
	try
	{

	// 頂点情報の作成
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	if (m_Fade != FADE_NONE)
	{

		if (m_Fade == FADE_IN)
		{

			m_Fadecol.r = 0.5f;

			m_Fadecol.a -= 0.1f;
			if (m_Fadecol.a <= 0.0f)
			{
				m_Fadecol.r = 0.5f;

				m_Fadecol.a = 0.0f;
				m_Fade = FADE_NONE;

			}
		}
		else if (m_Fade == FADE_OUT)
		{
			//Cblock::Create(D3DXVECTOR3(1150, 600, 0), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f), Cblock::BLOCK_TYPE_TYPE_1, 0.0f, 50.0f, 50.0f);

			m_Fadecol.a += 0.03f;
			if (m_Fadecol.a >= 1.0f)
			{
				m_Fadecol.a = 1.0f;
				m_Fade = FADE_IN;

				CManeger::SetMode(m_modeNext);
			}
		}
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックして、頂点データへのポインタを取得
													 //頂点カラーの設定
		pVtx[0].col = m_Fadecol;
		pVtx[1].col = m_Fadecol;
		pVtx[2].col = m_Fadecol;
		pVtx[3].col = m_Fadecol;

		m_pVtxBuff->Unlock();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CFade::Draw(void)
{

	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//フェードの設定
//=============================================================================
void CFade::SetFade(CManeger::MODE modeNext)
{
	try
	{

	if (m_Fade == FADE_NONE)
	{
		m_Fade = FADE_OUT;
		m_modeNext = modeNext;
		m_Fadecol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		if (m_modeNext == 0)
		{
			m_Fadecol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f);

		}
		else
		{

			m_Fadecol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);

		}

	}
		}
	catch (const std::exception&)
	{

	}

}
