//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須

#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Effect.h"
#include"Explosion.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = {};
//=============================================================================
// メイン関数
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA, float rot, float LengthX,float LengthY , float Radius, EFFECT_TYPE type, int nType)
{
	//インスタンス
	CEffect*pEffect = NULL;
	//
	pEffect = new CEffect(SCENE_NUMBER_TYPE_EFFECT);
	pEffect->Init(pos, move, colR,colG,colB,colA, rot,LengthX, LengthY, Radius,type);
	pEffect->BindTexture(m_pTexture);
	pEffect->m_TypeEffect = nType;
	return pEffect;

}

//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CEffect::Load(void)
{//load//読み込み
	if (m_pTexture == NULL)
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		// 頂点情報を設定
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture);
	}
	return S_OK;
}
void CEffect::UnLoad(void)
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
CEffect::CEffect(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_EFFECT) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;

	m_bDisp = true;
}

//=============================================================================
//デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA, float rot, float LengthX, float LengthY, float Radius, EFFECT_TYPE type)
{
	try
	{
	CScene2D::Init();
	D3DXVECTOR2 tex;

	mf_pos = 5;//posの初期化の変数
	SetEffect(pos, tex,move, colR, colG, colB, colA,rot, LengthX, LengthY,Radius);   //Length = 5;
	SetPosition(pos, move, rot, LengthX, LengthX);
	m_bDisp = true;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	//m_fPosSize = Length;//弾の大きさのメンバ変数
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_fRadius = Radius;
	SetOBJTYPE(OBJECT_TYPE_BULLET);
	Save();
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
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CEffect::Update(void)
{
	try
	{

	m_nCountEffect++;
	//pos
	D3DXVECTOR3 pos;
	//move(移動量)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	EFFECT_TYPE type = EFFECT_TYPE_MAX;
	D3DXCOLOR col;
	//Xの移動//Yの移動
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot;
	//posを取得
	pos = GetPotion();
	//moveを取得
	move = GetMove();
	//posのサイズを取得
	m_fPosSize = GetLength();
	//アークタンジェント
	fRot = atan2f(fMoveX, fMoveY);
	//moveで移動
	m_fRadius -= 1.0f; //加算
	pos += move;
	move *= 0.1f;
	CScene2D::SetEffect(pos, tex,move,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, m_fPosSizeX, m_fPosSizeX, m_fRadius);

	//posをGet
	GetPotion();
	//MoveをGet
	GetMove();
	//LengthをGet
	GetLength();
	GetCol();

	CManeger::MODE m_mode = CManeger::GetMode();

	if (m_mode == CManeger::MODE_RESULT || m_mode == CManeger::MODE_TITLE)
	{
		Uninit();
	}

	if (m_nCountEffect % 15 == 0)
	{

		Uninit();

	}

	//CSCENE2Dを取得
	CScene2D::Update();
	if (m_TypeEffect == 0)
	{

		if (pos.y - EFFECT_POS_Y2 < 0 || pos.x - EFFECT_POS_X2 <0 || pos.x - EFFECT_POS_X2 > SCREEN_WIDTH || pos.y - EFFECT_POS_Y2 > SCREEN_HEIGHT / 2)
		{

			Uninit();





		}


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
void CEffect::Draw(void)
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CScene2D::Draw();
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	catch (const std::exception&)
	{

	}

}

void CEffect::Loads(void)
{
	try
	{

	FILE *pFile;


	pFile = fopen("Effects.txt", "r");
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
void CEffect::Save(void)
{
	try
	{

	//seve
	FILE *pFile;


	pFile = fopen("Effects.txt", "w");
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
