//=============================================================================
//
// ランクの処理 [Rankes.cpp]
// Author :
//
//=============================================================================
#include "Rankes.h"
#include"manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/rank.png"	// 読み込むテクスチャファイル名
#define POLYGON_POS_X			(50)							//頂点座標Xの移動量
#define POLYGON_POS_Y			(50)							//頂点座標Yの移動量
#define TEX_POS_X_INIT			(1.0f)							//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)							//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)							//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)							//テクスチャ座標U右
#define TEX_TOP					(0.0f)							//テクスチャ座標V上
#define TEX_BOT					(1.0f)							//テクスチャ座標V下
#define MAX_RANK				(5)								//最大順位数

LPDIRECT3DTEXTURE9 CRankes::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRankes::m_pVtxBuff = NULL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice);
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureRank = NULL;		// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		// 頂点バッファへのポインタ
//D3DXVECTOR3				g_RankPos(0.0f, 0.0f, 0.0f);
//LPDIRECT3DTEXTURE9 CRankes::m_pTexture = NULL;
//LPDIRECT3DVERTEXBUFFER9 CRankes::m_pVtxBuff = NULL;


////=============================================================================
//// 初期化処理
////=============================================================================
//void InitRankes(void)
//{
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// テクスチャの読み込み
//	//D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
//	//	TEXTURE_SCORE,		// ファイルの名前
//	//	&g_pTextureRank);	// テクスチャへのポインタ
//
//							// 頂点情報の作成
//	//MakeVertexRankes(pDevice);
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void UninitRankes(void)
//{
//	// テクスチャの開放
//	if (g_pTextureRank != NULL)
//	{
//		g_pTextureRank->Release();
//		g_pTextureRank = NULL;
//	}
//
//	// 頂点バッファの開放
//	if (g_pVtxBuffRank != NULL)
//	{
//		g_pVtxBuffRank->Release();
//		g_pVtxBuffRank = NULL;
//	}
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void UpdateRankes(void)
//{
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void DrawRankes(void)
//{
////	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int nCntScore;
//
//	// 頂点バッファをデータストリームに設定
//	//pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
//
//	//// 頂点フォーマットの設定
//	//pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//// テクスチャの設定
//	//pDevice->SetTexture(0, g_pTextureRank);
//
//	// ポリゴンの描画
//
//	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
//	{
//		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		//	0 + (4 * nCntScore),	//開始する頂点のインデックス
//		//	2); //描画するプリミティブ数
//	}
//}
//
////=============================================================================
//// 頂点情報の作成
////=============================================================================
//void MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice)
//{
//	// 頂点情報の作成
//	VERTEX_2D *pVtx;
//	int nCntScore;
//	int nPosMove = 0;
//	float fTexTop = 0.0f;
//	float fTexBot = 0.2f;
//
//	g_RankPos.x = 400.0f;
//	g_RankPos.y = 150.0f;
//
//	// 頂点バッファを生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRank,
//		NULL);
//
//	//頂点情報を設定
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
//	{
//		//頂点座標
//		pVtx[0].pos = D3DXVECTOR3(g_RankPos.x - POLYGON_POS_X, g_RankPos.y - POLYGON_POS_Y, g_RankPos.z);
//		pVtx[1].pos = D3DXVECTOR3(g_RankPos.x + POLYGON_POS_X, g_RankPos.y - POLYGON_POS_Y, g_RankPos.z);
//		pVtx[2].pos = D3DXVECTOR3(g_RankPos.x - POLYGON_POS_X, g_RankPos.y + POLYGON_POS_Y, g_RankPos.z);
//		pVtx[3].pos = D3DXVECTOR3(g_RankPos.x + POLYGON_POS_X, g_RankPos.y + POLYGON_POS_Y, g_RankPos.z);
//
//		//テクスチャ座標
//		pVtx[0].tex = D3DXVECTOR2(0.0f, fTexTop);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, fTexTop);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, fTexBot);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, fTexBot);
//
//		//頂点
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラー
//		if (nCntScore == 0)
//		{
//			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//		}
//		else if (nCntScore == 1)
//		{
//			//頂点カラー
//			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		}
//		else if (nCntScore == 2)
//		{
//			//頂点カラー
//			pVtx[0].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//		}
//		else
//		{
//			//頂点カラー
//			pVtx[0].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//		}
//		pVtx += 4;	//頂点データのポインタを4つ分進める
//		fTexTop += 0.2f;
//		fTexBot += 0.2f;
//		g_RankPos.y += 100;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffRank->Unlock();
//}

CRankes::CRankes()
{
}

CRankes::~CRankes()
{
}

HRESULT CRankes::Load(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/背景.jpg", &m_pTexture);


	return S_OK;
}

void CRankes::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

HRESULT CRankes::Init()
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
	//	TEXTURE_SCORE,		// ファイルの名前
	//	&g_pTextureRank);	// テクスチャへのポインタ

	// 頂点情報の作成
	//MakeVertexRankes(pDevice);

	return S_OK;
}

void CRankes::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

void CRankes::Update(void)
{
}

void CRankes::Draw(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntScore;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画

	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0 + (4 * nCntScore),	//開始する頂点のインデックス
		2); //描画するプリミティブ数
	}

}
CRankes * CRankes::Create(void)
{
	CRankes*pRankes = NULL;
	pRankes = new CRankes;
	if (pRankes != NULL)
	{
		pRankes->Init();
	}
	return pRankes;

}

void CRankes::MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	float fTexTop = 0.0f;
	float fTexBot = 0.2f;

	m_RankPos.x = 400.0f;
	m_RankPos.y = 150.0f;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報を設定
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(m_RankPos.x - POLYGON_POS_X, m_RankPos.y - POLYGON_POS_Y, m_RankPos.z);
		pVtx[1].pos = D3DXVECTOR3(m_RankPos.x + POLYGON_POS_X, m_RankPos.y - POLYGON_POS_Y, m_RankPos.z);
		pVtx[2].pos = D3DXVECTOR3(m_RankPos.x - POLYGON_POS_X, m_RankPos.y + POLYGON_POS_Y, m_RankPos.z);
		pVtx[3].pos = D3DXVECTOR3(m_RankPos.x + POLYGON_POS_X, m_RankPos.y + POLYGON_POS_Y, m_RankPos.z);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, fTexTop);
		pVtx[1].tex = D3DXVECTOR2(1.0f, fTexTop);
		pVtx[2].tex = D3DXVECTOR2(0.0f, fTexBot);
		pVtx[3].tex = D3DXVECTOR2(1.0f, fTexBot);

		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		if (nCntScore == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else if (nCntScore == 1)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntScore == 2)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
		}
		else
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
		fTexTop += 0.2f;
		fTexBot += 0.2f;
		m_RankPos.y += 100;
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
