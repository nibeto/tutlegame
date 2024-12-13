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
#include"pauseselect.h"
#include"Explosion.h"
#include"Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define PAUSESELECT_POS_X			(200)						//頂点座標Xの移動量
#define PAUSESELECT_POS_Y			(50)						//頂点座標Yの移動量
#define TEX_LEFT				(0.0f)						//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)						//テクスチャ座標U右
#define TEX_TOP					(0.0f)						//テクスチャ座標V上
#define TEX_BOT					(1.0f)						//テクスチャ座標V下
LPDIRECT3DTEXTURE9 CPAUSESELECT::m_pTexture[PAUSESERECT_TEXTURE] = {};
//=============================================================================
// メイン関数
//=============================================================================
CPAUSESELECT *CPAUSESELECT::Create(D3DXVECTOR3 pos, float Length, int nType)
{
	//インスタンス
	CPAUSESELECT*pNumber = NULL;
	//
	pNumber = new CPAUSESELECT;
	pNumber->Init(pos, Length);
	pNumber->m_nNumber = nType;
	return pNumber;

}
//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CPAUSESELECT::Load(void)
{//load//読み込み
	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{

		if (m_pTexture[nCnt] == NULL)
		{
			CRenderer *pRenderer = CManeger::GetRenderer();
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
			// 頂点情報を設定
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[1]);
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[2]);

		}
	}
	return S_OK;
}
void CPAUSESELECT::UnLoad(void)
{//unload//破棄
	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//コンストラクタ
//=============================================================================
CPAUSESELECT::CPAUSESELECT()
{//clear（クリア）
}

//=============================================================================
//デストラクタ
//=============================================================================
CPAUSESELECT::~CPAUSESELECT()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CPAUSESELECT::Init(D3DXVECTOR3 pos, float Length)
{
	try
	{

	//頂点情報生成
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ポリゴンの位置を初期化
	m_pos = pos;
	float fMenuPosY = 0;
	m_nSelect = 0;
	m_PauseMenuPos = m_pos+D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SelectMode = SELECTMODE_NONE;

	m_aPauseMenu[0].pos = m_pos+D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
	m_aPauseMenu[0].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	m_aPauseMenu[0].select = SELECTTYPE_SELECT;
	fMenuPosY += 150;
	for (int nCnt = 1; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		m_aPauseMenu[nCnt].pos = m_pos+D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
		m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aPauseMenu[nCnt].select = SELECTTYPE_NONE;
		fMenuPosY += 150;
	}


												// 頂点情報の作成
	MakeVertexPauseSelect(pDevice);

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
void CPAUSESELECT::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}
}
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CPAUSESELECT::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CFade *pFade = CManeger::GetFade();
	CFade::FADE  m_fade = pFade->FADE_MAX;
	CManeger::MODE m_mode = CManeger::GetMode();

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 1) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;

	}
	if (pInputKeyboard->GetTrigger(DIK_UP) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 2) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;

	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 1) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}
	if (pInputKeyboard->GetTrigger(DIK_W) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 2) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}


	//エンターキー
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_fade == pFade->FADE_NONE)
	{
		if (m_nSelect == 0)
		{
			//PlaySound(SOUND_LABEL_SE_CANCEL);
			m_SelectMode = SELECTMODE_CONTINUE;
		}
		else if (m_nSelect == 1)
		{
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			m_SelectMode = SELECTMODE_RETRY;
		}
		else if (m_nSelect == 2)
		{
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			m_SelectMode = SELECTMODE_QUIT;
		}


		switch (m_SelectMode)
		{
		case SELECTMODE_CONTINUE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			pFade->SetFade(CManeger::MODE_GAME);
			break;
		}
		case SELECTMODE_QUIT:
		{
			pFade->SetFade(CManeger::MODE_TITLE);
			break;
		}
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_P) == true && m_fade == pFade->FADE_NONE)
	{
			m_nSelect = 0;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
			m_aPauseMenu[1].select = SELECTTYPE_NONE;
			m_aPauseMenu[2].select = SELECTTYPE_NONE;

	}

	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		if (m_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
		{//選択中の色
			m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{//未選択の色
			m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//頂点カラー
		pVtx[0].col = m_aPauseMenu[nCnt].col;
		pVtx[1].col = m_aPauseMenu[nCnt].col;
		pVtx[2].col = m_aPauseMenu[nCnt].col;
		pVtx[3].col = m_aPauseMenu[nCnt].col;
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
		}
		catch (const std::exception&)
		{

		}

}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CPAUSESELECT::Draw(void)
{
	try
	{

	//描画
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for ( int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCnt),	//開始する頂点のインデックス
			2); //描画するプリミティブ数
	}
	}
	catch (const std::exception&)
	{

	}

}
void CPAUSESELECT::MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	try
	{

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCnt;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSESERECT_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報を設定
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//頂点座標
		pVtx[0].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー
		pVtx[0].col = m_aPauseMenu[m_nSelect].col;
		pVtx[1].col = m_aPauseMenu[m_nSelect].col;
		pVtx[2].col = m_aPauseMenu[m_nSelect].col;
		pVtx[3].col = m_aPauseMenu[m_nSelect].col;

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
void CPAUSESELECT::SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	try
	{

	int nCnt;
	float fMenuPosY = 0;
	VERTEX_2D *pVtx;//頂点情報へのポインタ
					//頂点情報を設定
					//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//頂点座標
		pVtx[0].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		m_aPauseMenu[nCnt].pos = pos;
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		m_aPauseMenu[nCnt].col = col;

		fMenuPosY += 100;

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}

