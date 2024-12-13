//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須
#include"block.h"
#include"manager.h"
#include "Polygon.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"Weapons.h"
#include"robo.h"
#include"Life.h"
#include"Game.h"
#include"Goal.h"
#include"SeedManagement.h"
#include"Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

#define COLOR_A (255)//a =	透明度 (0～255)
#define TEX_FILE1 ("data/TEXTURE/PlayerTurtle.png")//青 (0～255)
#define TEX_FILE2 ("data/TEXTURE/PlayerTurtle.png")//青 (0～255)
#define POLIGON_MOVE_SPEED (5.0f)
LPDIRECT3DTEXTURE9 CPoligon::m_pTexture[MAX_TEX_POLIGON] = {};

bool  g_bDeleatePoligon = true;
HRESULT CPoligon::Load(void)
{//load//読み込み
	CRenderer* pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);

	return S_OK;
}
void CPoligon::UnLoad(void)
{//unload//破棄
	try
	{
		for (int nCntPOLIGON = 0; nCntPOLIGON < MAX_TEX_POLIGON; nCntPOLIGON++)
		{

			//テクスチャの破棄
			if (m_pTexture[nCntPOLIGON] != NULL)
			{
				m_pTexture[nCntPOLIGON]->Release();
				m_pTexture[nCntPOLIGON] = NULL;
			}
		}

	}
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CPoligon::CPoligon(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_POLIGON) :CScene2D(m_layer)
{//clear（クリア）
	try
	{

	}
	catch (const std::exception&)
	{

		m_nCountRot = 0;
		m_fRot = 0.0f;
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fPosSize = 0.0f;
		nCountBullet = 0;
		fMoveX = 0.0f, fMoveY = 0.0f;
		fRot = 0.0f;
		m_bDisp = true;
		m_bjump = false;
	}

}

//=============================================================================
//デストラクタ
//=============================================================================
CPoligon::~CPoligon()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CPoligon::Init(D3DXVECTOR3 pos, float LengshX, float LengshY)
{
	try
	{

		D3DXVECTOR2 tex;

		CScene2D::Init();
		m_bDisp = true;
		m_bjump = false;
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetPoligon(pos, LengshX, LengshY, tex, f_R, f_G, f_B, f_A);
		m_fPosSizeX = LengshX;
		m_fPosSizeY = LengshY;
		nCountBullet = 0;
		m_nLife = 5;
		Save();
		SetOBJTYPE(OBJECT_TYPE_PORIGON);
		Posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRot = D3DX_PI * 0.25f;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CPoligon::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CPoligon::Update(void)
{
	try
	{
		m_nCountRot++;
		nCountBullet++;
		m_nCount++;
		int nCntDAta = 0;
		CInputKeyboard* pInputKeyboard = CManeger::GetInput();
		CDice* pDice = CGame::GetDice();

		CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
		D3DXVECTOR3 pos;
		D3DXVECTOR3 Out;
		D3DXVECTOR3 v1;
		D3DXVECTOR3 v2;
		D3DXVECTOR3 v3;
		D3DXVECTOR3 move;
		D3DXVECTOR2 tex;
		POLIGON_TYPE type = POLIGON_TYPE_MAX;
		pos = GetPotion();
		tex = GetTex();
		Posold = pos;
		move = GetMove();
		m_fPosSize = GetLength();
		m_fRot = GetfRot();
		fMoveX = Pseed->GetfMoveX();
		fMoveY = Pseed->GetfMoveY();
		fMoveZ = Pseed->GetfMoveZ();
		//pos = v1 + v2;

		fMoveX = 600.0f;
		fMoveY = 400.0f;

		//移動
		pos.x = fMoveX + sinf(m_nCountRot / 2.5f) * 20.0f;
		pos.y = fMoveY + cosf(m_nCountRot / 2.5f) * 20.0f;

		//エフェクト生成
		CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 20, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f) * 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		//移動の移動関数
		Pseed->TheSeedMove(0.0f, fMoveY, fRot, move);
		if (fMoveY != 0.0f)
		{//入力された
			Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 5.0f);
		}
		else if (fMoveX != 0.0f) { Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 0.0f); }

		//任意のキーが押されたどうか
		if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[POLIGON_TYPE_1]); }
		if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[POLIGON_TYPE_2]); }
		if (type == POLIGON_TYPE_1)
		{//エフェクト生成
			CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 45, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f) * 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 15.5f, 5.0f, 5 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		}
		else
		{
			for (int nCount = 0; nCount < MAX_SCENE; nCount++)
			{
				for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
				{
					CScene* pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
					if (pScene != NULL)
					{
						if (pScene->GetOBJTYPE() == OBJECT_TYPE_EFFECT)
						{//弾発見！
							CEffect* pEffect = (CEffect*)pScene;
							pEffect->Uninit();
						}

					}
				}
			}
		}
		//範囲指定
		if (m_pos.y >= SCREEN_HEIGHT)
		{
			m_bjump = false;
			pos.y = SCREEN_HEIGHT;
			move.y = 0.0f;

		}

		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bjump == false)//任意のキーが押されたどうか
		{

			m_bjump = true;
			move.y = -25.0f;//* fSpeedUp;
			move.y = -50.0f;//* fSpeedUp;
			move.y = -GRAVITY / 2;//* fSpeedUp;

		}
		//移動(座標)をずらす
		move.y += 1.75f;

		pos.y += move.y;



			if (nCountBullet % 15 == 0)
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(pos.x + 45.0f, pos.y, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f) * 0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER_3);
			}

			CSound* pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

	//ポジションに移動を加算
		pos += move;
		move *= 0.1f;

		int nCntTime = 0;
		Cblock* pBlock = CGame::GetBlock();
		//更新処理
		CScene2D::Update();
		if (nCntTime % 50 == 0)
		{
			m_bjump = false;
		}
		SetPoligon(pos, m_fPosSizeX, m_fPosSizeY, tex, f_R, f_G, f_B, f_A);
		//終了処理
		if (m_nDiseType != pDice->DISE_TYPE_5)
		{
			if (nCountBullet % 55 == 0)
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
void CPoligon::Draw(void)
{
	CScene2D::Draw();
}
