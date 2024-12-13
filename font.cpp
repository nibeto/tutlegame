//=========================================================================================================//
//
// 背景処理 [font.cpp]
// Author :moritakamasaya
//
//=========================================================================================================//
#include"font.h"
#include "Manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>//I/O stream
#include <random>
#include "renderer.h"

LPDIRECT3DTEXTURE9 CFONT::m_pTextureFont = NULL;
//=========================================================================================================//
// コンストラクタ
//=========================================================================================================//
CFONT::CFONT() :CScene(SCENE_NUMBER_TYPE_FONT)
{

}
//=========================================================================================================//
// デストラクタ
//=========================================================================================================//
CFONT::~CFONT()
{

}
HRESULT CFONT::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, Font_TextureName, &m_pTextureFont);


	return S_OK;
}
void CFONT::UnLoad(void)
{//unload//破棄
 //テクスチャの破棄
	if (m_pTextureFont != NULL)
	{
		m_pTextureFont->Release();
		m_pTextureFont = NULL;
	}

}
//=========================================================================================================//
// 初期化処理
//=========================================================================================================//
HRESULT CFONT::Init(void)
{
	try
	{

	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		//g_Font[nCntFont].rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		m_Font[nCntFont].bUse = false;
	}

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuffFont,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);		//X,Y,0.0f
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);	// A = 透明度
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//頂点BUFFERをアンロックする
	m_pVtxBuffFont->Unlock();

	D3DXCreateFont(pDevice, 40, 12, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont0);
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
//=========================================================================================================//
// 終了処理
//=========================================================================================================//
void CFONT::Uninit(void)
{
	if (m_pFont0 != NULL)
	{// デバッグ表示用フォントの開放
		m_pFont0->Release();
		m_pFont0 = NULL;
	}
}
//=========================================================================================================//
// 更新処理
//=========================================================================================================//
void CFONT::Update(void)
{
	try
	{

	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (m_Font[nCntFont].bUse == true)
		{//文字が表示状態なら
			switch (m_Font[nCntFont].state)
			{
			case FONTSTATE_RANKDOWN://下がる
				m_Font[nCntFont].fCntState += m_fSpeed;
				m_Font[nCntFont].rect.top += 3;
				m_Font[nCntFont].rect.bottom += 3;
				if (m_Font[nCntFont].fCntState >= 1.0f)
				{
					m_Font[nCntFont].fCntState = 0.0f;
					m_Font[nCntFont].state = FONTSTATE_NONE;
				}
				break;

			case FONTSTATE_DELETE://下がりながら消える
				m_Font[nCntFont].col.a -= 0.028f;
				m_Font[nCntFont].rect.top += 3;
				m_Font[nCntFont].rect.bottom += 3;
				if (m_Font[nCntFont].col.a <= 0.0f)
				{
					m_Font[nCntFont].bUse = false;
				}
				break;

			case FONTSTATE_RANKSET:
				m_Font[nCntFont].col.a += 0.029f;
				m_Font[nCntFont].rect.left -= 5;
				m_Font[nCntFont].rect.right -= 5;
				if (m_Font[nCntFont].col.a >= 1.0f)
				{
					m_Font[nCntFont].col.a = 1.0f;
					m_Font[nCntFont].state = FONTSTATE_NONE;
				}
				break;

			case FONTSTATE_RANKDELETE:
				m_Font[nCntFont].col.a -= 0.029f;
				m_Font[nCntFont].rect.left -= 5;
				m_Font[nCntFont].rect.right -= 5;
				if (m_Font[nCntFont].col.a <= 0.0f)
				{
					m_Font[nCntFont].col.a = 0.0f;
					m_Font[nCntFont].bUse = false;
				}
				break;

			default:
				break;
			}
		}
	}
	}
	catch (const std::exception&)
	{

	}

}

//=========================================================================================================//
// 描画処理
//=========================================================================================================//
void CFONT::Draw(void)
{
	try
	{

	int nCntFont;

	if (m_nSetFont != 0)
	{//50音表表示
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点BUFFERをロックし、頂点情報へのポインタを取得
		m_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, (m_nSetFont - 1.0f) * 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, (m_nSetFont - 1.0f) * 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, m_nSetFont * 0.5f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, m_nSetFont * 0.5f);

		//頂点BUFFERをアンロックする
		m_pVtxBuffFont->Unlock();

		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


		//頂点BUFFERをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuffFont, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

										//テクスチャの設定
		pDevice->SetTexture(0, m_pTextureFont);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	try
	{

		//テキスト描画
		//hDC      : //デバイスコンテキストのハンドル
		//lpString : //描画する文字列へのポインタ
		//nCount   : //文字列の文字数
		//lpRect   : //長方形領域
		//uFormat  : //テキストの整形方法を指定
		if (m_pFont0 != NULL)
		{
			for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
			{
				if (m_Font[nCntFont].bUse == true)
				{// 文字列を代入 表示
					m_pFont0->DrawText(NULL, &m_Font[nCntFont].aStr[0], -1, &m_Font[nCntFont].rect, DT_LEFT, m_Font[nCntFont].col);
					//m_pFont0->DrawText(NULL, &m_Font[nCntFont].astr[0], -1, &m_Font[nCntFont].rect, DT_LEFT, m_Font[nCntFont].col);
				}
			}
		}
	}
	catch (const std::exception&)
	{

	}

	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// 文字代入処理  Set!!
//=========================================================================================================//
void CFONT::SetFont(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nNumber, FONTSTATE state, int nCntFont)
{//文字セット
	try
	{

	m_Font[nNumber].bUse = true;
	m_Font[nNumber].state = state;
	m_Font[nNumber].rect = rect;
	strcpy(&m_Font[nNumber].aStr[0], &aStr[0]);
	//strcat(&m_Font[nNumber].astr[nCntFont], &astr[nCntFont]);
	m_Font[nNumber].col = col;
	m_Font[nNumber].fCntState = 0.0f;
	m_Font[nNumber].fWight = 5.0f;
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// 文字代入処理  Change!!
//=========================================================================================================//
void CFONT::ChangeFont(bool bUse, const char *aStr, const char *astr,int nNumber, FONTSTATE state)
{//セットされたものを変更
	try
	{

	m_Font[nNumber].bUse = bUse;
	m_Font[nNumber].state = state;
	if (aStr[0] != NULL) { strcpy(&m_Font[nNumber].aStr[0], &aStr[0]); }//NULLじゃなければ更新
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// 文字を全て破壊
//=========================================================================================================//
void CFONT::BreakFont(int nNumber)
{//セットされた文字をすべて破壊
	try
	{

	int nCntFont = nNumber;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		m_Font[nCntFont].bUse = false;
	}
	}
	catch (const std::exception&)
	{

	}

}
void CFONT::FontTime(int nNumber)
{
	try
	{

	m_Font[nNumber / 10];
	}
	catch (const std::exception&)
	{

	}

}
void CFONT::FontTimer(int nNumber, int nCntData)
{
	try
	{

	m_Font[nNumber / nCntData];
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// セットされている50音の取得
//=========================================================================================================//
int *CFONT::GetSetFont(void)
{
	try
	{

	return &m_nSetFont;
	}
	catch (const std::exception&)
	{

	}

}

