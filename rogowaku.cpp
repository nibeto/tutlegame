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
#include"rogowaku.h"
#include"score.h"
#include"sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

LPDIRECT3DTEXTURE9 CRogowaku::m_pTexture[MAX_ROGOWAKU_TYPE] = {};

//=============================================================================
// Create関数
//=============================================================================
CRogowaku *CRogowaku::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, ROGOWAKU_TYPE type, int nType)
{
	//インスタンス
	CRogowaku*pRogowaku = NULL;
	pRogowaku = new CRogowaku(SCENE_NUMBER_TYPE_ROGOWAKU);
	pRogowaku->Init(pos, move,  LengthX, LengthY);
	pRogowaku->m_nType = nType;
	pRogowaku->BindTexture(m_pTexture[type]);
	return pRogowaku;
}

HRESULT CRogowaku::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/rogowakuScore.png", &m_pTexture[0]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/rogo.png", &m_pTexture[1]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ステータスロゴ.png", &m_pTexture[2]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock.png", &m_pTexture[3]);


	return S_OK;
}
void CRogowaku::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ROGOWAKU_TYPE; nCntEnemyType++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntEnemyType] != NULL)
		{
			m_pTexture[nCntEnemyType]->Release();
			m_pTexture[nCntEnemyType] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CRogowaku::CRogowaku(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_ROGOWAKU) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
}

//=============================================================================
//デストラクタ
//=============================================================================
CRogowaku::~CRogowaku()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CRogowaku::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,  float LengthX, float LengthY)
{
	CScene2D::Init();
	SetNOMAL(pos, LengthX, LengthY);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_nLife = 5;
	return S_OK;

}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CRogowaku::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CRogowaku::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	//CSound *pSound = CManeger::GetSound();
	//pSound->Play(CSound::SOUND_LABEL_BGM000);
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;

	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();




	CScene2D::Update();

	GetPotion();
	GetMove();
	GetLength();
	GetfRot();


	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CRogowaku::Draw(void)
{
	CScene2D::Draw();
}
