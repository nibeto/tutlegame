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
#include"obj.h"
#include"score.h"
#include"sound.h"
#include"Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_ENEMY_TYPE (2)//a =	透明度 (0～255)

LPDIRECT3DTEXTURE9 CObj::m_pTexture[MAX_ENEMY_TYPE] = {};

//=============================================================================
// Create関数
//=============================================================================
CObj *CObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, OBJ_TYPE type, OBJ_BOX_TYPE nType)
{
	//インスタンスw
	CObj*pObj = NULL;
	pObj = new CObj(SCENE_NUMBER_TYPE_OBJ);
	pObj->Init(pos, move, rot, Length);
	pObj->m_nType = nType;
	pObj->BindTexture(m_pTexture[type]);
	return pObj;
	//インスタンス
}

HRESULT CObj::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/波.png", &m_pTexture[0]);

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/波.png", &m_pTexture[1]);

	return S_OK;
}
void CObj::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ENEMY_TYPE; nCntEnemyType++)
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
CObj::CObj(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_OBJ) :CScene2D(m_layer)
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
CObj::~CObj()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CObj::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	CScene2D::Init();
	m_pos = pos;
	m_move = move;
	SetOBJTYPE(OBJECT_TYPE_OBJ);
	SetRot(pos, move, 5.0f, m_fPosSizeY);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = Length;
	m_fPosSizeY = Length;
	m_nLife = 5;
	return S_OK;

}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CObj::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CObj::Update(void)
{

	try
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
	m_fRot = GetfRot();
	NcuntRot++;
	if (m_nType == OBJ_BOX_TYPE_BASE)
	{
		move.x += cosf(D3DX_PI * 1.0f) * fSpeedUp / 2;



		fMoveX1 = -1.0f;
		//m_fPosSize = 100.0f + sinf((float)NcuntRot / 15.0f) * 50.0f;

		move += D3DXVECTOR3(sinf(NcuntRot / 50.0f), cosf(NcuntRot / 50.0f), 0.0f) * 5.0f;//1.0
		if (pos.x - SCREEN_WIDTH < 150 - OBJ_POLYGON_SIZE)
		{

			pos.x += SCREEN_WIDTH;


		}

		if (pos.x + PLAYER_WIDTH > SCREEN_WIDTH + OBJ_POLYGON_SIZE)
		{

			pos.x -= SCREEN_WIDTH;

		}

	}
	else if (m_nType == OBJ_BOX_TYPE_2)
	{
		move.x += cosf(D3DX_PI * 1.0f) * fSpeedUp/2;


		pos.x += move.x;


		if (pos.x - SCREEN_WIDTH < 150 - OBJ_POLYGON_SIZE)
		{

			pos.x += SCREEN_WIDTH;


		}

		if (pos.x + PLAYER_WIDTH > SCREEN_WIDTH + OBJ_POLYGON_SIZE)
		{

			pos.x -= SCREEN_WIDTH;

		}

		move.x += (0.5f - move.x);//*0.1f;

	}
	else if (m_nType == OBJ_BOX_TYPE_1)
	{


		move.y += cosf(D3DX_PI * -1.0f) * fSpeedUp;


		pos.y += move.y;



		if (pos.y - SCREEN_HEIGHT < 0 - OBJ_POLYGON_SIZE)
		{

			pos.y += SCREEN_HEIGHT;


		}

		if (pos.y + OBJ_POLYGON_SIZE > SCREEN_HEIGHT_Y_2 + OBJ_POLYGON_SIZE)
		{

			pos.y -= SCREEN_HEIGHT;

		}

		move.y += (0.0f - move.y);//*0.1f;

	}

	if (fMoveX1 != 0.0f || fMoveY1 != 0.0f)
	{//入力された
		fRot = atan2f(fMoveX1, fMoveY1);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 0.5f;//1.0

	}

	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//入力された
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}





	CScene2D::Update();

	pos += move;
	move *= 0.1f;
	GetPotion();
	GetMove();
	GetLength();
	GetfRot();

	//SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);

	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);

		if (m_nType != OBJ_BOX_TYPE_BASE&&pos.x < 15 - m_fPosSize)
		{
			//m_nLife = 0;
			Uninit();
			fMoveX = -1.0f;

		}
	else
	{//当たり判定
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
			{
				CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
				if (pScene != NULL)
				{
					if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
					{//弾発見！
						CBullet *pBullet = (CBullet*)pScene;
						D3DXVECTOR3 pos = pBullet->GetPotion();
						D3DXVECTOR3 move = pBullet->GetMove();
						if (m_nType == OBJ_BOX_TYPE_2)
						{
							if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER)
							{
								if (GetPotion().x > pos.x - OBJ_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + OBJ_POLYGON_SIZE &&
									GetPotion().y > pos.y - BULLET_SIZE - OBJ_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + OBJ_POLYGON_SIZE)
								{
									CScene2D::SetPattanAnim(nPattenAnime);
									CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, 25.0f);
									m_nLife -= 1;

									pBullet->Uninit();
									if (m_nLife == 0)
									{

										Uninit();
									}
								}
							}
						}
					}
				}
			}
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
void CObj::Draw(void)
{
	CScene2D::Draw();
}
