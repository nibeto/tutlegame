//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = {};
//CInputKeyboard pInput;
bool  g_bDeleateExprosion = true;
//=============================================================================
//コンストラクタ
//=============================================================================
HRESULT CExplosion::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}
void CExplosion::UnLoad(void)
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
CExplosion::CExplosion(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_EXPROSION) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
void CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length)
{
	CScene2D::Init();
	SetPosition(pos,m_move,rot,m_fPosSizeX,m_fPosSizeX);
	SetAnimation(0.125f, 1.0f);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSizeX = Length;//弾の大きさのメンバ変数
	m_fPosSizeX = 55.0f;//弾の大きさのメンバ変数
	m_fPosSizeY = 55.0f;//弾の大きさのメンバ変数

}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CExplosion::Update(void)
{
	try
	{
	int nLife = 0;
	int nCntAnime = 0;
	nCntAnime++;
	D3DXVECTOR3 pos;
	//move(移動量)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	m_nCntExprocion++;
	//posを取得
	pos = GetPotion();
	//moveを取得
	m_move = GetMove();
	bool bRelease = true;

	nCountAnime++;

	if (nCountAnime % 8 == 0)
	{
		nPattenAnime++;

		//nPattenAnime = (nPattenAnime + 1) % 8;

	}

	if (nPattenAnime >= 8)
	{

		nPattenAnime = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}
		SetAnimation(0.125f, 1.0f);
		SetPosition(pos,m_move,m_fPosSizeX,m_fPosSizeY, m_fPosSizeX);
		//CSCENE2Dを取得
		CScene2D::Update();

		nLife--;
		if (nCntAnime % 15 == 0)
		{
			nLife = 0;
			Uninit();
		}
		else if (nLife == 0)
		{
			Uninit();

		}
		CManeger::MODE m_mode = CManeger::GetMode();

			if (m_mode == CManeger::MODE_RESULT||m_mode == CManeger::MODE_TITLE)
		{
			Uninit();
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
void CExplosion::Draw(void)
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
