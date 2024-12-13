//=============================================================================
//
// ランキングの処理 [Ranking.cpp]
// Author :
//
//=============================================================================
#include "Ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "Rankes.h"
#include "time.h"
#include "RankGata.h"
#include "title.h"
#include"sound.h"
#include"manager.h"
//#include"bg1.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define POLYGON_POS_X			(20)						//頂点座標Xの移動量
#define POLYGON_POS_Y			(20)						//頂点座標Yの移動量
#define TEX_POS_X_INIT			(1.0f)						//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)						//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)						//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)						//テクスチャ座標U右
#define TEX_TOP					(0.0f)						//テクスチャ座標V上
#define TEX_BOT					(1.0f)						//テクスチャ座標V下

LPDIRECT3DTEXTURE9 CRanking::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRanking::m_pVtxBuff = NULL;

CRankingGata * CRanking::m_pRankingata = NULL;//リザルト
CRankes * CRanking::m_pRankes = NULL;//リザルト
#if 0
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// 頂点バッファへのポインタ
//int						g_nRanking = 0;					// スコア
//int						g_aScore[MAX_RANKING];
//Ranking					g_aRanking[MAX_RANKING];
//D3DXVECTOR3				g_RankingPos(0.0f, 0.0f, 0.0f);
//int						g_nCounterTimer = 0;
//int						g_nRankNum;
//int						g_nCntRankTimer = 0;
//int						g_RankChange = 0;
//=============================================================================
// 初期化処理
//=============================================================================
//void InitRanking(void)
//{
//	InitRankingGata();
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int pScore;
//	int nScoreChange, nScoreChange2;
//
//	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aRanking[nCntRanking].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//スコアの取得
//	//pScore = GetScore();
//
//	g_nRanking = pScore;
//
//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
//	{//ランキングを更新
//		if (g_aScore[nCnt] <= g_nRanking)
//		{
//			if (g_aScore[nCnt + 1] >= g_nRanking)
//			{//ランキングを入れ替え
//			 //値をとっておく
//				nScoreChange = g_aScore[nCnt];
//				//ゲーム後のスコアを代入
//				g_aScore[nCnt] = g_nRanking;
//				g_nRankNum = nCnt;
//				//下のスコアをとっておく
//				nScoreChange2 = g_aScore[nCnt - 1];
//				//下のスコアに塗り替えたスコアを代入
//				g_aScore[nCnt - 1] = nScoreChange;
//				//下のスコアを渡しておく
//				nScoreChange = nScoreChange2;
//				for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
//				{	//渡されたスコアを代入
//					nScoreChange2 = nScoreChange;
//					//さらに下のスコアをとっておく
//					nScoreChange = g_aScore[nCnt - 1];
//					//下のスコアをさらに下のスコアに代入
//					g_aScore[nCnt - 1] = nScoreChange2;
//				}
//				break;
//			}
//			if (nCnt == MAX_RANKING - 1)
//			{
//				if (g_aScore[nCnt] <= g_nRanking)
//				{
//					//値をとっておく
//					nScoreChange = g_aScore[nCnt];
//					//ゲーム後のスコアを代入
//					g_aScore[nCnt] = g_nRanking;
//					g_nRankNum = nCnt;
//					//下のスコアをとっておく
//					nScoreChange2 = g_aScore[nCnt - 1];
//					//下のスコアに塗り替えたスコアを代入
//					g_aScore[nCnt - 1] = nScoreChange;
//					//下のスコアを渡しておく
//					nScoreChange = nScoreChange2;
//					for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
//					{	//渡されたスコアを代入
//						nScoreChange2 = nScoreChange;
//						//さらに下のスコアをとっておく
//						nScoreChange = g_aScore[nCnt - 1];
//						//下のスコアをさらに下のスコアに代入
//						g_aScore[nCnt - 1] = nScoreChange2;
//					}
//					break;
//				}
//			}
//		}
//	}
//
//	g_nCounterTimer = 0;
//	g_nCntRankTimer = 0;
//	g_RankChange = 0;
//
//
//
//	// テクスチャの読み込み
////	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
//	//	TEXTURE_SCORE,							// ファイルの名前
////		&g_pTextureRanking);					// テクスチャへのポインタ
//
//												// 頂点情報の作成
//	//MakeVertexRanking(pDevice);
//
//	InitRankes();
//	//InitPLESENTER();
////	PlaySound(SOUND_LABEL_BGM002);
//	//StopSound(SOUND_LABEL_BGM003);
//	//StopSound(SOUND_LABEL_BGM004);
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void UninitRanking(void)
//{
//	// テクスチャの開放
//	if (g_pTextureRanking != NULL)
//	{
//		g_pTextureRanking->Release();
//		g_pTextureRanking = NULL;
//	}
//
//	// 頂点バッファの開放
//	if (g_pVtxBuffRanking != NULL)
//	{
//		g_pVtxBuffRanking->Release();
//		g_pVtxBuffRanking = NULL;
//	}
//	UninitRankingGata();
//	UninitRankes();
//	//UnInitPLESENTER();
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void UpdateRanking(void)
//{
//	// 頂点情報の作成
//	VERTEX_2D *pVtx;
//	//FADE fade;
//
//	//fade = GetFade();
//
//	//if (fade != FADE_OUT)
//	{
//
//		//エンターキー
//		//if (GetKeyboardTrigger(DIK_RETURN) == true)
//		//{
//		//	PlaySound(SOUND_LABEL_SE_DECIDE);
//		//	StopSound(SOUND_LABEL_BGM002);
//		//	SetFade(MODE_TITLE);
//		//}
//		//g_nCounterTimer++;
//		//if (g_nCounterTimer >= 600)
//		//{
//		////	PlaySound(SOUND_LABEL_SE_DECIDE);
//		//	StopSound(SOUND_LABEL_BGM002);
//
//		//	SetFade(MODE_ENDROOL);
//		//}
//	}
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
//
//
//
//	if (g_nCntRankTimer >= 40)
//	{
//		if (g_RankChange == 0)
//		{
//			g_RankChange = 1;
//
//		}
//		else if (g_RankChange == 1)
//		{
//			g_RankChange = 0;
//
//		}
//		g_nCntRankTimer = 0;
//	}
//	// 頂点バッファをアンロックする
//	g_pVtxBuffRanking->Unlock();
//
//	UpdateRankes();
//	UpdateRankingGata();
//	//UpdatePLESENTER();
//
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void DrawRanking(void)
//{
//	DrawRankingGata();
//
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int nCntScore;
//
//	// 頂点バッファをデータストリームに設定
//	//pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));
//
//	// 頂点フォーマットの設定
//	//pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//// テクスチャの設定
//	//pDevice->SetTexture(0, g_pTextureRanking);
//
//	// ポリゴンの描画
//
//	for (nCntScore = 0; nCntScore < 8 * MAX_RANKING; nCntScore++)
//	{
//		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		//	0 + (4 * nCntScore),	//開始する頂点のインデックス
//		//	2); //描画するプリミティブ数
//	}
//
//	DrawRankes();
//	//DrowPLESENTER();
//}
//
////=============================================================================
//// 頂点情報の作成
////=============================================================================
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
//{
//	// 頂点情報の作成
//	VERTEX_2D *pVtx;
//	int nCntScore;
//	int nPosMove = 0;
//	int nAnswer = 0;
//	int nKeisan = 1;
//	int nCntRanking;
//
//
//	// 頂点バッファを生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_RANKING,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRanking,
//		NULL);
//
//	//頂点情報を設定
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aRanking[nCntRanking].pos.x = SCREEN_WIDTH / 2 + 150;
//		g_aRanking[nCntRanking].pos.y = 550.0f - (100.0f * nCntRanking);
//
//		for (nCntScore = 0; nCntScore < 8; nCntScore++)
//		{
//			nAnswer = g_aScore[nCntRanking] % (nKeisan * 10) / nKeisan;
//
//			//頂点座標
//			pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//
//			//テクスチャ座標
//			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);
//
//			//頂点
//			pVtx[0].rhw = 1.0f;
//			pVtx[1].rhw = 1.0f;
//			pVtx[2].rhw = 1.0f;
//			pVtx[3].rhw = 1.0f;
//
//			//頂点カラー
//			pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//
//			pVtx += 4;	//頂点データのポインタを4つ分進める
//			nKeisan *= 10;
//			g_RankingPos.x -= 40;
//			g_aRanking[nCntRanking].pos.x -= 40;
//		}
//		nKeisan = 1;
//	}
//
//	// 頂点バッファをアンロックする
//	g_pVtxBuffRanking->Unlock();
//}
////=============================================================================
//// ランキングの取得
////=============================================================================
//void SetRanking(int nRanking)
//{
//	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aScore[nCntRanking] = nRanking * (1 + nCntRanking);
//	}
//}
#endif
CRanking::CRanking()
{
}

CRanking::~CRanking()
{
}

HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/背景.jpg", &m_pTexture);

	return S_OK;
}

void CRanking::UnLoad(void)
{

		//テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}

}

HRESULT CRanking::Init()
{
	m_pRankingata->Init();
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int pScore;
	int nScoreChange, nScoreChange2;

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aRanking[nCntRanking].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//スコアの取得
	pScore = 0;

	m_nRanking = pScore;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{//ランキングを更新
		if (m_aScore[nCnt] <= m_nRanking)
		{
			if (m_aScore[nCnt + 1] >= m_nRanking)
			{//ランキングを入れ替え
			 //値をとっておく
				nScoreChange = m_aScore[nCnt];
				//ゲーム後のスコアを代入
				m_aScore[nCnt] = m_nRanking;
				m_nRankNum = nCnt;
				//下のスコアをとっておく
				nScoreChange2 = m_aScore[nCnt - 1];
				//下のスコアに塗り替えたスコアを代入
				m_aScore[nCnt - 1] = nScoreChange;
				//下のスコアを渡しておく
				nScoreChange = nScoreChange2;
				for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
				{	//渡されたスコアを代入
					nScoreChange2 = nScoreChange;
					//さらに下のスコアをとっておく
					nScoreChange = m_aScore[nCnt - 1];
					//下のスコアをさらに下のスコアに代入
					m_aScore[nCnt - 1] = nScoreChange2;
				}
				break;
			}
			if (nCnt == MAX_RANKING - 1)
			{
				if (m_aScore[nCnt] <= m_nRanking)
				{
					//値をとっておく
					nScoreChange = m_aScore[nCnt];
					//ゲーム後のスコアを代入
					m_aScore[nCnt] = m_nRanking;
					m_nRankNum = nCnt;
					//下のスコアをとっておく
					nScoreChange2 = m_aScore[nCnt - 1];
					//下のスコアに塗り替えたスコアを代入
					m_aScore[nCnt - 1] = nScoreChange;
					//下のスコアを渡しておく
					nScoreChange = nScoreChange2;
					for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
					{	//渡されたスコアを代入
						nScoreChange2 = nScoreChange;
						//さらに下のスコアをとっておく
						nScoreChange = m_aScore[nCnt - 1];
						//下のスコアをさらに下のスコアに代入
						m_aScore[nCnt - 1] = nScoreChange2;
					}
					break;
				}
			}
		}
	}

	m_nCounterTimer = 0;
	m_nCntRankTimer = 0;
	m_RankChange = 0;



	// テクスチャの読み込み
	//	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
	//	TEXTURE_SCORE,							// ファイルの名前
	//		&m_pTexture);					// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRanking(pDevice);

	m_pRankes->Init();
	//InitPLESENTER();
	//	PlaySound(SOUND_LABEL_BGM002);
	//StopSound(SOUND_LABEL_BGM003);
	//StopSound(SOUND_LABEL_BGM004);

	return S_OK;
}

void CRanking::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		//m_apScene2D->Uninit();
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}

}

void CRanking::Update(void)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	//FADE fade;

	//fade = GetFade();

	//if (fade != FADE_OUT)
	{

		//エンターキー
		//if (GetKeyboardTrigger(DIK_RETURN) == true)
		//{
		//	PlaySound(SOUND_LABEL_SE_DECIDE);
		//	StopSound(SOUND_LABEL_BGM002);
		//	SetFade(MODE_TITLE);
		//}
		//g_nCounterTimer++;
		//if (g_nCounterTimer >= 600)
		//{
		////	PlaySound(SOUND_LABEL_SE_DECIDE);
		//	StopSound(SOUND_LABEL_BGM002);

		//	SetFade(MODE_ENDROOL);
		//}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);



	if (m_nCntRankTimer >= 40)
	{
		if (m_RankChange == 0)
		{
			m_RankChange = 1;

		}
		else if (m_RankChange == 1)
		{
			m_RankChange = 0;

		}
		m_nCntRankTimer = 0;
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_pRankes->Update();
	m_pRankingata->Update();

}

void CRanking::Draw(void)
{
	m_pRankingata->Draw();

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntScore;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画

	for (nCntScore = 0; nCntScore < 8 * MAX_RANKING; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0 + (4 * nCntScore),	//開始する頂点のインデックス
		2); //描画するプリミティブ数
	}

	m_pRankes->Draw();

}

CRanking * CRanking::Create(void)
{
	CRanking*pPreseenter = NULL;
	pPreseenter = new CRanking;
	if (pPreseenter != NULL)
	{
		pPreseenter->Init();
	}
	return pPreseenter;

}

void CRanking::MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	int nAnswer = 0;
	int nKeisan = 1;
	int nCntRanking;


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報を設定
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aRanking[nCntRanking].pos.x = SCREEN_WIDTH / 2 + 150;
		m_aRanking[nCntRanking].pos.y = 550.0f - (100.0f * nCntRanking);

		for (nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			nAnswer = m_aScore[nCntRanking] % (nKeisan * 10) / nKeisan;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x - POLYGON_POS_X, m_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[1].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x + POLYGON_POS_X, m_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[2].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x - POLYGON_POS_X, m_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[3].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x + POLYGON_POS_X, m_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);

			//頂点
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);

			pVtx += 4;	//頂点データのポインタを4つ分進める
			nKeisan *= 10;
			m_RankingPos.x -= 40;
			m_aRanking[nCntRanking].pos.x -= 40;
		}
		nKeisan = 1;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

void CRanking::SetRanking(int nRanking)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aScore[nCntRanking] = nRanking * (1 + nCntRanking);
	}

}
