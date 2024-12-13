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
#include"Timer.h"
#include"score.h"
#include"sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

LPDIRECT3DTEXTURE9 CTimer::m_pTexture[MAX_TIMER_TYPE] = {};

//=============================================================================
// Create関数
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY, TIMER_TYPE type, TIMER_BOX_TYPE nType)
{
	//インスタンスw
	CTimer*pObj = NULL;
	pObj = new CTimer(SCENE_NUMBER_TYPE_TIMER);
	pObj->Init(pos, move, rot, LengthX, LengthY);
	pObj->m_nType = nType;
	pObj->BindTexture(m_pTexture[type]);
	return pObj;
	//インスタンス
}

HRESULT CTimer::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock針.png", &m_pTexture[0]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock針min.png", &m_pTexture[1]);

	return S_OK;
}
void CTimer::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_TIMER_TYPE; nCntEnemyType++)
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
CTimer::CTimer(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_TIMER) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTimer::~CTimer()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	CScene2D::Init();
	m_pos = pos;
	m_move = move;
	SetOBJTYPE(OBJECT_TYPE_TIMER);
	f_rot = rot;
	SetRotTimer(pos, move, rot, LengthX, LengthY);
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
void CTimer::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CTimer::Update(void)
{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;


	float fMoveX1 = 0.0f, fMoveY1 = 0.0f;

	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;


	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRotTimer = GetfTimerRot();
	NcuntRot++;




	pos += move;
	move *= 0.1f;

	CScene2D::Update();

	GetPotion();
	GetMove();
	GetLength();
	GetfTimerRot();
	SetRotTimer(pos, move, f_rot, m_fPosSizeX,m_fPosSizeY);

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CTimer::Draw(void)
{
	CScene2D::Draw();
}
