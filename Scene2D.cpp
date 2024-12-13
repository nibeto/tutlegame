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
#include"Scene2D.h"
#include"renderer.h"
#include"input.h"
#include"Player.h"
#include"bullet.h"
#include"Bg.h"
#include"block.h"
#include"Debug.h"
#include"Effect.h"
#include "Time.h"
#include"Timer.h"
#include"Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (1.0f)//赤 (0～255)
#define COLOR_G (1.0f)//緑 (0～255)
#define COLOR_B (1.0f)//青 (0～255)
#define COLOR_A (1.0f)//a =	透明度 (0～255)

bool  g_bDeleate = true;

CScene2D * CScene2D::m_pScene2D = NULL;
//=============================================================================
// メイン関数
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CScene2D::CScene2D(LAYER m_Number = LAYER_MAX) :CScene(m_nNumber)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

CScene2D *CScene2D::Create(void)
{
	//インスタンス
	CScene2D*pScene2D = NULL;

	//
	pScene2D = new CScene2D;
	//初期化
	pScene2D->Init();

	if (pScene2D != NULL)
	{

	}

	//値を返す
	return pScene2D;

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CScene2D::Init(void)
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ポリゴンの位置を初期化
	m_pos = D3DXVECTOR3(50, 610, 0.0f);

	// ポリゴンの移動を初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;


	//頂点バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-mf_pos, -mf_pos, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(mf_pos, -mf_pos, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-mf_pos, mf_pos, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(mf_pos, mf_pos, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_col + D3DXCOLOR(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = m_col + D3DXCOLOR(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = m_col + D3DXCOLOR(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = m_col + D3DXCOLOR(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //色の指定（０～２５５）&透明度（０～２５５)

	 //テクスチャ座標の設定
	pVtx[0].tex = m_tex + D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = m_tex + D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = m_tex + D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = m_tex + D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

	//頂点バッファーをアンロック
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
void CScene2D::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}
	Save();
	//delete this;

	Release();
}
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CScene2D::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	//fSpeedUp = nRecast[nGear] * 1.0f;
	if (g_bDeleate == false)
	{

		Uninit();
		g_bDeleate = true;
	}

	//nCountAnime++;

	if (nCountAnime % 5 == 0)
	{
		nPattenAnime = (nPattenAnime + 1) % 8;


	}
	if (nPattenAnime >= 8 - 1)
	{
		bUse = false;
	}


	else if (m_pos.y <= 0)
	{
		bUse = false;
	}


	//m_fRot = m_nCountRot / m_fRotRand;
#if 0

	//拡縮
	m_fPosSize = 100.0f + sinf((float)m_nCountRot / 15.0f) * 50.0f;

	//移動
	m_pos.x = m_move.x + sinf(m_nCountRot / 30.0f) * 200.0f;
	m_pos.y = m_move.y + cosf(m_nCountRot / 30.0f) * 200.0f;
#endif
#if 0
	//pVtx[0].pos = m_posmove + D3DXVECTOR3(-fPos, -fPos, 0.0f);
	//pVtx[1].pos = m_posmove + D3DXVECTOR3(fPos, -fPos, 0.0f);
	//pVtx[2].pos = m_posmove + D3DXVECTOR3(-fPos, fPos, 0.0f);
	//pVtx[3].pos = m_posmove + D3DXVECTOR3(fPos, fPos, 0.0f);
#endif
#if 0

	////頂点情報の設定
	//pVtx[0].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot), m_fPosSize * cosf(m_fRot), 0.0f);
	//pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * -0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * -0.5f), 0.0f);
	//pVtx[2].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * 0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * 0.5f), 0.0f);
	//pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI), m_fPosSize * cosf(m_fRot + D3DX_PI), 0.0f);
#endif
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CScene2D::Draw(void)
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	if (bDraw == false)
	{


		//(D3DPT_TRIANGLELISTプリミティブの種類|1プリミティブの数|&g_aVertex[0]先頭アドレス);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	}
	catch (const std::exception&)
	{

	}

}
void CScene2D::DrawPrimitive(void)
{

}
//******************************************
//スコアのポリゴンの設定処理
//******************************************
void CScene2D::SetPosScore(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	try
	{

	m_pos = pos;
	m_fRot = rot;
	m_fPosSize = Length;
	m_move = move;
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSize, -m_fPosSize, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSize, -m_fPosSize, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSize, m_fPosSize, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSize, m_fPosSize, 0.0f);
	}
	catch (const std::exception&)
	{

	}


}
//******************************************
//ノーマライズの移動
//******************************************
void CScene2D::MoveNormalizeVector(D3DXVECTOR3 move, float fSpeed)
{
	try
	{
	D3DXVECTOR3 vectorNormalize;
	//m_move = move;

	D3DXVec3Normalize(&vectorNormalize, &move);
	vectorNormalize *= fSpeed;


	m_move = vectorNormalize;

	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//ポリゴンの設定処理
//******************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	try
	{

	m_pos = pos;
	m_fRot = rot;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	m_move = move;
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);
	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
void CScene2D::SetNOARMALAnimation(int nPattanAnimation,float fWight, float fHight)
{
	try
	{

	nPattenAnime = nPattanAnimation;
	//if (nPattenAnime <= 8)
	//{
	//	nPattenAnime++;

	//}
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nPattenAnime*fWight), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nPattenAnime * fWight), fHight);
	pVtx[3].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), fHight);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();

	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//ポリゴンの通常の設定処理
//******************************************
void CScene2D::SetNOMAL(D3DXVECTOR3 pos, float LengthX, float LengthY)
{
	try
	{

	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//エネミーのポリゴンの通常の設定処理
//******************************************
void CScene2D::SetNOMALENEMY(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA)
{
	try
	{

	m_pos = pos;
	m_move = move;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);
	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}


}
void CScene2D::SetNOMALDice(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA)
{
	try
	{

	m_pos = pos;
	m_move = move;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);
	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);


	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//通常のポリゴンの設定処理(2)
//******************************************
void CScene2D::SetNOMALPOS(D3DXVECTOR3 pos, float LengthX, float LengthY)
{
	try
	{

	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	//CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	//if (m_pos.y <= 200)
	//{
	//	m_pos.y += 1.5f;
	//}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	m_pos.y = 200;//キー入力で固定
	//}

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY , 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}


}
//******************************************
//ポリゴンのset
//******************************************
void CScene2D::SetHP(D3DXVECTOR3 pos, float LengthX, float LengthY,  float colR, float colG, float colB, float colA)
{
	try
	{

	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
void CScene2D::SetMagicPoint(D3DXVECTOR3 pos, float LengthX, float LengthY, float colR, float colG, float colB, float colA)
{
	try
	{

	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//フェードの設定処理
//******************************************
void CScene2D::Fade(D3DXVECTOR3 pos, float LengthX, float LengthY, D3DXCOLOR col)
{
	try
	{

	m_pos = pos;
	m_col = col;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;


#ifdef _DEBUG


	//変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = m_col + D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = m_col + D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = m_col + D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);


	//バッファーをアンロック
	m_pVtxBuff->Unlock();
#endif // _DEBUG

	}
	catch (const std::exception&)
	{

	}


}
void CScene2D::SetPattanAnim(int nPattanAnim)
{
	try
	{

	nPattanAnim = nPattenAnime;

	if (nCountAnime % 8 == 0)
	{
		nPattenAnime++;

		nPattenAnime = (nPattenAnime + 1) % 8;

	}

	if (nPattenAnime >= 8)
	{

		nPattenAnime = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}
	}
	catch (const std::exception&)
	{

	}

}

//******************************************
//BGの設定処理
//******************************************
void CScene2D::SetBG(D3DXVECTOR3 pos, float LengthX, float LengthY, OBJECT_TYPE type)
{
	try
	{

	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
void CScene2D::SetPoligon(D3DXVECTOR3 pos, float LengthX, float LengthY, D3DXVECTOR2 tex, float colR, float colG, float colB, float colA)
{
	try
	{

		CInputKeyboard* pInputKeyboard = CManeger::GetInput();


		int nPatternAnim = 0;
		int nDirectionMove = 0;//0右を向いている,1左を向いている
							   // 変数宣言
		m_pos = pos;
		m_fPosSizeX = LengthX;
		m_fPosSizeY = LengthY;
		m_tex = tex;


		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)//任意のキーが押されたどうか
		{
			if (pInputKeyboard->GetPress(DIK_D) != true || pInputKeyboard->GetPress(DIK_RIGHT) != true)
			{

				nDirectionMove = 1;


			}
			if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{
				nDirectionMove = 1;

			}
		}
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) != true || pInputKeyboard->GetPress(DIK_LEFT) != true)
			{
				nDirectionMove = 0;

			}
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)
			{
				nPatternAnim = 0;
			}
		}

		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)//任意のキーが押されたどうか
		{

			if (nPatternAnim % 2 == 0)
			{

				nPatternAnim = (nPatternAnim + 1) % 4;

			}
			nPatternAnim = 1;
		}
		int nCunterAnim = 0;

		nCunterAnim++;
		//nDirectionMove = 1;

		if (nCunterAnim % 8 == 7)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
			{

				nPatternAnim = (nPatternAnim + 1) % 4;
				nCunterAnim = 0;
			}
			else
			{
				nPatternAnim = 0;

			}
		}
		VERTEX_2D* pVtx;
		//バッファーをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		////頂点情報の設定
		pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

		////頂点情報の設定
		pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
		pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
		pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
		pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);


		pVtx[0].tex = D3DXVECTOR2(nPatternAnim * 0.25f, 0.5f * nDirectionMove);//xyの角度
		pVtx[1].tex = D3DXVECTOR2(nPatternAnim * 0.25f + 0.25f, 0.5f * nDirectionMove);//xyの角度
		pVtx[2].tex = D3DXVECTOR2(nPatternAnim * 0.25f, 0.5f * nDirectionMove + 0.5f);//xyの角度
		pVtx[3].tex = D3DXVECTOR2(nPatternAnim * 0.25f + 0.25f, 0.5f * nDirectionMove + 0.5f);//xyの角度

		//バッファーをアンロック
		m_pVtxBuff->Unlock();


	}
	catch (const std::exception&)
	{

	}



}
//******************************************
//回転用
//******************************************
void CScene2D::SetRot(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	try
	{

	m_nCountRot++;
	nCountBullet++;
	m_fRot = m_nCountRot / m_fRotRand;


	m_pos = pos;
	m_fRotRand = rot;
	m_fPosSize = Length;
	m_move = move;
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定

	pVtx[0].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot), m_fPosSize * cosf(m_fRot), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * -0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * -0.5f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * 0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * 0.5f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI), m_fPosSize * cosf(m_fRot + D3DX_PI), 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}



}
//******************************************
//回転タイマーの設定処理
//******************************************
void CScene2D::SetRotTimer(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CTimer *pTimer = CGame::GetTimer();
	if (pTimer->TIMER_BOX_TYPE_MAX)
	{



		int nTimer = 99;
		nTimer--;
		if (nTimer == 98)
		{
			m_nCountRot++;
			nCountBullet++;
			m_fRotTimer = m_nCountRot / m_fRotRand;


		}
	}
	m_pos = pos;
	m_fRotRand = rot;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;

	m_move = move;

	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定

	pVtx[0].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fRotTimer), m_fPosSizeY * cosf(m_fRotTimer), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fRotTimer + D3DX_PI * -0.5f), m_fPosSizeY * cosf(m_fRotTimer + D3DX_PI * -0.5f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fRotTimer + D3DX_PI * 0.5f), m_fPosSizeY * cosf(m_fRotTimer + D3DX_PI * 0.5f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fRotTimer + D3DX_PI), m_fPosSizeY * cosf(m_fRotTimer + D3DX_PI), 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();

	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//拡大縮小の設定処理
//******************************************
void CScene2D::SetZoominandoutandRot(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	try
	{

	m_nCountRot++;
	m_fRot = m_nCountRot / m_fRotRand;

	//拡縮
	m_fPosSize = 100.0f + sinf((float)m_nCountRot / 15.0f) * 50.0f;

	m_pos = pos;
	m_fRotRand = rot;
	m_fPosSize = Length;
	m_move = move;
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot), m_fPosSize * cosf(m_fRot), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * -0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * -0.5f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI * 0.5f), m_fPosSize * cosf(m_fRot + D3DX_PI * 0.5f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSize * sinf(m_fRot + D3DX_PI), m_fPosSize * cosf(m_fRot + D3DX_PI), 0.0f);
	//バッファーをアンロック
	m_pVtxBuff->Unlock();

	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//爆発のTEXTUREANIMATION
//******************************************
void CScene2D::SetAnimation(float fWight, float fHight)
{
	try
	{

	// 変数宣言
	bool bRelease = false;
	nCountAnime++;

	if (nCountAnime % 8 == 0)
	{
		nPattenAnime++;

		nPattenAnime = (nPattenAnime + 1) %8;

	}

	if (nPattenAnime >= 8)
	{

		nPattenAnime = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}

	//if (nPattenAnime <= 8)
	//{
	//	nPattenAnime++;

	//}
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nPattenAnime*fWight), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nPattenAnime * fWight), fHight);
	pVtx[3].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), fHight);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();

	//return bRelease;
	}
	catch (const std::exception&)
	{

	}

}
void CScene2D::SetPlayerAnimation(float fWight, float fHight)
{
	try
	{

	nCountAnime++;

	if (nCountAnime % 3 == 0)
	{
		nPattenAnime++;

		nPattenAnime = (nPattenAnime + 1) % 3;

	}

	if (nPattenAnime >= 3)
	{

		nPattenAnime = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}
	if (nCountAnime % 4 == 0)
	{
		nPattenAnime2++;

		nPattenAnime2 = (nPattenAnime2 + 1) % 4;

	}

	if (nPattenAnime2 >= 4)
	{

		nPattenAnime2 = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}


	//if (nPattenAnime <= 8)
	//{
	//	nPattenAnime++;

	//}
	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nPattenAnime*fWight), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nPattenAnime * fWight), nPattenAnime2+ fHight);
	pVtx[3].tex = D3DXVECTOR2(fWight + (nPattenAnime * fWight), nPattenAnime2+fHight);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}


}
//******************************************
//BGのTEXTURE移動
//******************************************
void CScene2D::SetBgAnimation(D3DXVECTOR2 tex)
{
	try
	{

	m_tex = tex;
	nCountBg++;



	// 変数宣言
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.001f*nCountBg + 0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(0.001f*nCountBg + 1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.001f*nCountBg + 0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(0.001f*nCountBg + 1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）


	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//2D用のプレイヤーのTEXTURE更新
//******************************************
void CScene2D::SetPlayer(D3DXVECTOR3 pos, float LengthX, float LengthY, D3DXVECTOR2 tex,  float colR, float colG, float colB, float colA)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();


	int nPatternAnim = 0;
	int nDirectionMove = 0;//0右を向いている,1左を向いている
						   // 変数宣言
	m_pos = pos;
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_tex = tex;


	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)//任意のキーが押されたどうか
	{
		if (pInputKeyboard->GetPress(DIK_D) != true || pInputKeyboard->GetPress(DIK_RIGHT) != true)
		{

			nDirectionMove = 1;


		}
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			nDirectionMove = 1;

		}
	}
	if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		if (pInputKeyboard->GetPress(DIK_A) != true || pInputKeyboard->GetPress(DIK_LEFT) != true)
		{
			nDirectionMove = 0;

		}
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			nPatternAnim = 0;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)//任意のキーが押されたどうか
	{

		if (nPatternAnim % 2 == 0)
		{

			nPatternAnim = (nPatternAnim + 1) % 4;

		}
		nPatternAnim = 1;
	}
	int nCunterAnim = 0;

	nCunterAnim++;
	//nDirectionMove = 1;

	if (nCunterAnim % 8 == 7)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{

			nPatternAnim = (nPatternAnim + 1) % 4;
			nCunterAnim = 0;
		}
		else
		{
			nPatternAnim = 0;

		}
	}
	VERTEX_2D* pVtx;
	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点情報の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, -m_fPosSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX, m_fPosSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, 0.0f);

	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);


	pVtx[0].tex = D3DXVECTOR2(nPatternAnim *0.25f, 0.5f * nDirectionMove);//xyの角度
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim	*0.25f + 0.25f, 0.5f * nDirectionMove);//xyの角度
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*0.25f, 0.5f * nDirectionMove + 0.5f);//xyの角度
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim	*0.25f + 0.25f, 0.5f * nDirectionMove + 0.5f);//xyの角度

	//バッファーをアンロック
	m_pVtxBuff->Unlock();


	}
	catch (const std::exception&)
	{

	}


}
//******************************************
//スコア
//******************************************
void CScene2D::MakeVertexScore(void)
{
	try
	{

	int nCntScore;


	// 頂点情報の作成
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックして、頂点データへのポインタを取得
												  //頂点情報の設定
	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		pVtx[0].pos = D3DXVECTOR3((SCORE_POS_X - (25 * nCntScore)) - SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((SCORE_POS_X - (25 * nCntScore)) + SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((SCORE_POS_X - (25 * nCntScore)) - SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((SCORE_POS_X - (25 * nCntScore)) + SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);


	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();


	}
	catch (const std::exception&)
	{

	}


}
void CScene2D::MouseMove(D3DXVECTOR3 & move, float fSpeed)
{
	try
	{

	CMouse* pMouse = CManeger::GetMouse();
	if (pMouse->GetPress(0))//0or1
	{
		move.x += sinf(D3DX_PI * -0.75f) * fSpeed;
		move.y += cosf(D3DX_PI * -0.75f) * fSpeed;
	}

	if (pMouse->GetPress(1))//0or1
	{
		move.x += sinf(D3DX_PI * -0.25f) * fSpeed;
		move.y += cosf(D3DX_PI * -0.25f) * fSpeed;
	}

	//int n_X;
	//int n_Y;


	//pJoypad->GetGamepadStickLeft(&n_X, &n_Y);

	//if (n_X != 0 || n_Y != 0)
	//{
	//	move.x += sinf((float)atan2(n_X, n_Y)) * fSpeed;//(float) = cast型
	//	move.y -= cosf((float)atan2(n_X, n_Y)) * fSpeed;

	//}
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//ブロックの当たり判定
//******************************************
bool CScene2D::CorisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3	*pMove, bool bLand, float *f_sizeX, float* f_sizeY)
{
	try
	{

	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{

			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				bLand = false;

				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BLOCK)
				{//弾発見！
					CDebug *pBlock = (CDebug*)pScene;
					int nCuntBlock;
					CPlayer*pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 posPlayer = pPlayer->GetPotion();
					D3DXVECTOR3 pos = pBlock->GetPotion();
					float f_Wight = pPlayer->GetLengthX();
					float f_Hight = pPlayer->GetLengthY();
					f_Wight = *f_sizeX;
					f_Hight = *f_sizeY;
					for (nCuntBlock = 0; nCuntBlock < MAX_BLOCK; nCuntBlock++)
					{
						//*calcWallScratchVector(pPos,*pPosold,*pMove);
						if (pBlock->bUse == true)
						{
							if (pPos->x + f_Wight/2 >= pos.x&&
								pPos->x - f_Wight/2 <= pos.x + BLOCK_WIDTH)

							{
								//上
								if (pPosold->y <= pos.y &&
									pPos->y >= pos.y)
								{
									bLand = true;
									pPos->y = pos.y;
									pMove->y = 0.0f;
								}

								//下
								if (pPosold->y >= pos.y + BLOCK_HEIGHT&&
									pPos->y - f_Hight * 2 <= pos.y + BLOCK_HEIGHT)
								{
									pPos->y = pos.y + BLOCK_HEIGHT + f_Hight * 2;
									pMove->y = 0.0f;
								}
							}
							if (pos.y < pPosold->y
								&& pos.y + BLOCK_HEIGHT + f_Hight> pPosold->y)
							{//左右の範囲内
								if (pos.x - (f_Wight / 2 - 10) >= pPosold->x
									&& pos.x - (f_Wight / 2 - 10) <= pPos->x)
								{//左
									pPos->x = pos.x - (f_Wight / 2 - 10);
									pMove->x = 0.0f;
								}
								if (pos.x + BLOCK_WIDTH + (f_Wight / 2 - 10) <= pPosold->x
									&& pos.x + BLOCK_WIDTH + (f_Wight / 2 - 10) >= pPos->x)
								{//右
									pPos->x = pos.x + BLOCK_WIDTH + (f_Wight / 2 - 10);
									pMove->x = 0.0f;
								}
							}
						}
					}

					return bLand;//返す値

				}

			}

		}
	}

	}
	catch (const std::exception&)
	{

	}

	return bLand;

}
//******************************************
//エフェクトの設定処理
//******************************************
void CScene2D::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXVECTOR3 move,  float colR, float colG, float colB, float colA, float rot, float LengthX, float LengthY, float fRadius)
{
	try
	{

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点データへのポインタを取得
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_pos = pos;
	m_fRadius = fRadius;
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX - fRadius, -m_fPosSizeY - fRadius, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX + fRadius, -m_fPosSizeY - fRadius, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fPosSizeX - fRadius, m_fPosSizeY + fRadius, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX + fRadius, m_fPosSizeY + fRadius, 0.0f);

	////頂点情報の設定
	pVtx[0].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[1].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[2].col = m_col + D3DXCOLOR(colR, colG, colB, colA);
	pVtx[3].col = m_col + D3DXCOLOR(colR, colG, colB, colA);


	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//回転設定
//******************************************
void CScene2D::SetAround(void)
{
	try
	{

	// 変数宣言
	VERTEX_2D* pVtx;

	//バッファーをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	////頂点情報の設定

	pVtx[0].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fAroundRot), m_fPosSizeY * cosf(m_fAroundRot), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fAroundRot + D3DX_PI * -0.5f), m_fPosSizeY * cosf(m_fAroundRot + D3DX_PI * -0.5f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fAroundRot + D3DX_PI * 0.5f), m_fPosSizeY * cosf(m_fAroundRot + D3DX_PI * 0.5f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fPosSizeX * sinf(m_fAroundRot + D3DX_PI), m_fPosSizeY * cosf(m_fAroundRot + D3DX_PI), 0.0f);

	//バッファーをアンロック
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//ジョイパッドの移動処理
//******************************************
void CScene2D::SetMove(D3DXVECTOR3 & move, float fSpeed)
{
	try
	{

	CJoypad* pJoypad = CManeger::GetJoypad();

	if (pJoypad->GetPress(pJoypad->JOYPADKEY_LEFT))//引数はCJoypad::JOYPADKEY_X(joypadのクラスとenumの構造体の中身)でもよい。
	{
		if (pJoypad->GetPress(pJoypad->JOYPADKEY_RIGHT))
		{
			move.x += sinf(D3DX_PI * -0.75f) * fSpeed;
			move.y += cosf(D3DX_PI * -0.75f) * fSpeed;
		}
		else if (pJoypad->GetPress(pJoypad->JOYPADKEY_DOWN))
		{
			move.x += sinf(D3DX_PI * -0.25f) * fSpeed;
			move.y += cosf(D3DX_PI * -0.25f) * fSpeed;
		}
		else
		{
			move.x += sinf(D3DX_PI * -0.5f) * fSpeed;
			move.y += cosf(D3DX_PI * -0.5f) * fSpeed;
		}
	}
	else if (pJoypad->GetPress(pJoypad->JOYPADKEY_RIGHT))
	{
		if (pJoypad->GetPress(pJoypad->JOYPADKEY_LEFT))
		{
			move.x += sinf(D3DX_PI * 0.75f) * fSpeed;
			move.y += cosf(D3DX_PI * 0.75f) * fSpeed;
		}
		else if (pJoypad->GetPress(pJoypad->JOYPADKEY_DOWN))
		{
			move.x += sinf(D3DX_PI * 0.25f) * fSpeed;
			move.y += cosf(D3DX_PI * 0.25f) * fSpeed;
		}
		else
		{
			move.x += sinf(D3DX_PI * 0.5f) * fSpeed;
			move.y += cosf(D3DX_PI * 0.5f) * fSpeed;
		}
	}
	else if (pJoypad->GetPress(pJoypad->JOYPADKEY_DOWN))
	{
		move.x += sinf(D3DX_PI * 0.0f) * fSpeed;
		move.y += cosf(D3DX_PI * 0.0f) * fSpeed;
	}
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//マウスの移動処理
//******************************************
void CScene2D::MouseTarget(void)
{
	try
	{

	CMouse* pMouse = CManeger::GetMouse();
	m_pos.x = (float)pMouse->GetMouseX();
	m_pos.y = (float)pMouse->GetMouseY();

	if (m_pos.x + m_fPosSizeX >= SCREEN_WIDTH - 130 && m_move.x > 0.0f ||
		m_pos.x - m_fPosSizeX <= SCREEN_WIDTH - 1150 && m_move.x < 0.0f)
	{

		m_move.x = 0.0f;
	}
	if (m_pos.y + m_fPosSizeY >= SCREEN_HEIGHT && m_move.y > 0.0f ||
		m_pos.y - m_fPosSizeY <= 0 && m_move.y < 0.0f)
	{
		m_move.y = 0.0f;
	}
	}
	catch (const std::exception&)
	{

	}

}

void CScene2D::Scene2DMove(float &f_MoveX, float &f_MoveY, float f_Rot,float f_Rot2,D3DXVECTOR3 &move, float m_fSpeed)
{
	try
	{

	if (f_MoveX != 0.0f || f_MoveY != 0.0f)
	{//入力された
		f_Rot = atan2f(f_MoveX, f_MoveY);
		//f_Rot2 = atan2f(f_MoveX, f_MoveY);
		move += D3DXVECTOR3(sinf(f_Rot), cosf(f_Rot), 0.0f) * m_fSpeed;//1.0
	}
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//壁ずりベクトル
//******************************************
//D3DXVECTOR3 * CScene2D::calcWallScratchVector(D3DXVECTOR3 * out, const D3DXVECTOR3 & front, const D3DXVECTOR3 & nomal)
//{
//	D3DXVECTOR3 normal_n;
//	D3DXVec3Normalize(&normal_n, &nomal);
//
//	try
//	{
//
//
//	}
//	catch (const std::exception&)
//	{
//
//	}
//	return D3DXVec3Normalize(out, &(front - D3DXVec3Dot(&front, &normal_n)*normal_n));
//
//}
//******************************************
//反射ベクトル
//******************************************
//D3DXVECTOR3 * CScene2D::calcReflectVector(D3DXVECTOR3 * out, const D3DXVECTOR3 & front, const D3DXVECTOR3 & nomal)
//{
//	D3DXVECTOR3 normal_n;
//
//	D3DXVec3Normalize(&normal_n, &nomal);
//
//	try
//	{
//
//
//	}
//
//	catch (const std::exception&)
//	{
//
//	}
//	return D3DXVec3Normalize(out, &(front - 2.0f* D3DXVec3Dot(&front, &normal_n)*normal_n));
//
//
//}
//******************************************
//スコアをGET
//******************************************
LPDIRECT3DDEVICE9 CScene2D::GetMakeVertexScore(void)
{
	try
	{

	}
	catch (const std::exception&)
	{

	}
	return pDevice;

}
//
//******************************************
//posの初期化サイズをSAVE
//******************************************

void CScene2D::Save(void)
{

	try
	{

	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}
	}
	catch (const std::exception&)
	{

	}

}
//******************************************
//posの初期化サイズをLOAD
//******************************************

void CScene2D::Load(void)
{

	try
	{

	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}
	}
	catch (const std::exception&)
	{

	}

}