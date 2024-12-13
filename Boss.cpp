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
#include"Boss.h"
#include"score.h"
#include"sound.h"
#include"Playerobj.h"
#include"SeedManagement.h"
#include "Goal.h"
#include"Life.h"
#include"Game.h"
#include"Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_ENEMY_TYPE (6)//a =	透明度 (0～255)
#define MOVE_ENEMY_SPEED (5.0f)
int CBoss::nNumBoss = 0;
CBoss::Boss CBoss::m_Boss[MAX_NUM_BOSS] = {};
LPDIRECT3DTEXTURE9 CBoss::m_pTexture[CBoss::BOSS_TYPE_MAX] = {};
//=============================================================================
// メイン関数
//=============================================================================
void CBoss::Save(void)
{
}
//=============================================================================
// ロード
//=============================================================================
void CBoss::Loads(void)
{
	try
	{

	//変数宣言
	char cEnpty[128];	// 空用（必要のないもの）
	char cLoad[128];	// 読み込む用
	char cComp[128];	// 比較用
	int nNumber = 0;
	int nIndex = 0;
	FILE *pFIle;

	pFIle = fopen("data/Save/Boss.txt", "r");

	if (pFIle != NULL)
	{
		while (strcmp(cComp, "SCRIPT") != 0)
		{
			fgets(cLoad, sizeof(cLoad), pFIle);
			sscanf(cLoad, "%s", &cComp);

		}
		if (strcmp(cComp, "SCRIPT") == 0)
		{
			while (strcmp(cComp, "END_SCRIPT") != 0)
			{
				fgets(cLoad, sizeof(cLoad), pFIle);
				sscanf(cLoad, "%s", &cComp);

				if (strcmp(cComp, "NUM_BOSS") == 0)
				{
					sscanf(cLoad, "%s %s %d", &cEnpty, &cEnpty, &nNumBoss);
					nNumber = nNumBoss;
				}
				if (strcmp(cComp, "BOSSPOLIGONSET") == 0)
				{
					while (strcmp(cComp, "END_BOSSPOLIGONSET") != 0)
					{
						fgets(cLoad, sizeof(cLoad), pFIle);
						sscanf(cLoad, "%s", &cComp);

						if (strcmp(cComp, "BOSSSET") == 0)
						{
							while (strcmp(cComp, "END_BOSSSET") != 0)
							{
								fgets(cLoad, sizeof(cLoad), pFIle);
								sscanf(cLoad, "%s", &cComp);

								if (strcmp(cComp, "POS") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f ", &cEnpty, &cEnpty, &m_Boss[nIndex].pos.x, &m_Boss[nIndex].pos.y, &m_Boss[nIndex].pos.z);
								}
								if (strcmp(cComp, "MOVE") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f ", &cEnpty, &cEnpty, &m_Boss[nIndex].move.x, &m_Boss[nIndex].move.y, &m_Boss[nIndex].move.z);
								}
								if (strcmp(cComp, "SIZE") == 0)
								{
									sscanf(cLoad, "%s %s %f %f", &cEnpty, &cEnpty, &m_Boss[nIndex].f_sizeX, &m_Boss[nIndex].f_sizeY);
								}
								if (strcmp(cComp, "TYPE") == 0)
								{
									sscanf(cLoad, "%s %s %d ", &cEnpty, &cEnpty, &m_Boss[nIndex].type);
								}
								if (strcmp(cComp, "OBJ_TYPE") == 0)
								{
									sscanf(cLoad, "%s %s %d ", &cEnpty, &cEnpty, &m_Boss[nIndex].ntype);
								}
								if (strcmp(cComp, "COLOR") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f %f ", &cEnpty, &cEnpty, &m_Boss[nIndex].f_R, &m_Boss[nIndex].f_G, &m_Boss[nIndex].f_B, &m_Boss[nIndex].f_A);
								}
							}
							nIndex++;
						}
					}
				}
			}
		}
	}
	/* ファイルのクローズ */
	fclose(pFIle);
	}
	catch (const std::exception&)
	{

	}


}
int CBoss::GetNumBoss(void)
{
	return nNumBoss;
}
CBoss::Boss *CBoss::GetBoss(void)
{
	return &m_Boss[0];
}

HRESULT CBoss::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[0]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[1]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[2]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[3]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[4]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TurtleBoss.png", &m_pTexture[5]);


	return S_OK;
}
void CBoss::UnLoad(void)
{//unload//破棄
	for (int nCntBossType = 0; nCntBossType < CBoss::BOSS_TYPE_MAX; nCntBossType++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntBossType] != NULL)
		{
			m_pTexture[nCntBossType]->Release();
			m_pTexture[nCntBossType] = NULL;
		}
	}

}

//=============================================================================
//コンストラクタ
//=============================================================================
CBoss::CBoss(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_BOSS) :CScene2D(m_layer)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
	fMoveX1 = 0.0f, fMoveY1 = 0.0f;

	fMoveX = 0.0f, fMoveY = 0.0f;
	m_nLife = 5;
	fMoveX1 = 0.0f;
	fMoveY1 = 0.0f;
	fMoveX = 0.0f;
	fMoveY = 0.0f;
	fRot = 0.0f;
	nCountBullet = 0;

}

//=============================================================================
//デストラクタ
//=============================================================================
CBoss::~CBoss()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA)
{
	try
	{

	CScene2D::Init();
	CSeedMAnagenet *Pseed = CSeedMAnagenet::GetSeed();
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	mf_pos = 5;//posの初期化の変数
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	f_R = colR;
	f_G = colG;
	f_B = colB;
	f_A = colA;

	//Length = 5;
	SetOBJTYPE(OBJECT_TYPE_BOSS);
	SetNOMALENEMY(pos, move, LengthX, LengthY, colR, colG, colB, colA);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_nLife = 5;
	fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();
	fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();
	if (pInputKeyboard->GetPress(DIK_V) == true) { Uninit(); }

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
void CBoss::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CBoss::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CSound *pSound = CManeger::GetSound();
	CSeedMAnagenet *Pseed = CSeedMAnagenet::GetSeed();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	D3DXCOLOR col = GetCol();
	cLife*pLife = CGame::GetLife();
	m_nCountRot++;
	fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();

	fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();
	fSpeed = Pseed->fSpped(MOVE_ENEMY_SPEED);
	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();
	nCountBullet++;


	if (pInputKeyboard->GetPress(DIK_D) == true) { fMoveX = -1.0f; }
	if (pInputKeyboard->GetPress(DIK_A) == true) { fMoveX = 1.0f; }
	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//入力された
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}


	fMoveX = 800.0f;
	fMoveY = 300.0f;

	//移動
	pos.x = fMoveX + sinf(m_nCountRot / 50.5f) * 300.0f;
	pos.y = fMoveY + cosf(m_nCountRot / 50.5f) * 300.0f;

	//エフェクト生成

	//移動の移動関数
	Pseed->TheSeedMove(0.0f, fMoveY, fRot, move);
	if (fMoveY != 0.0f)
	{//入力された
		Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 5.0f);
	}
	else if (fMoveX != 0.0f) { Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 0.0f); }
	pos += move;
	move *= 0.1f;


	if (m_nType == BOSS_CLASS_TYPE_3)
	{
		if (nCountBullet % 15 == 0)
		{
			CSound *pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

			CBullet::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_ENEMY);



		}

	}
	else	if (m_nType == BOSS_CLASS_TYPE_4)
	{

		if (nCountBullet % 155 == 0)
		{
			CSound *pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

			CBullet::Create(pos, D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_ENEMY);
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_ENEMY);
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_ENEMY);

		}

	}
	else	if (m_nType == BOSS_CLASS_TYPE_5)
	{

		if (nCountBullet % 55 == 0)
		{
			CSound *pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

			CBullet::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_OBJ_TYPE_ENEMY);

		}

	}
	else	if (m_nType == BOSS_CLASS_TYPE_LIFE || m_nType == BOSS_CLASS_TYPE_LIFE_1)
	{
		if (m_nLife <= 4)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 3)
		{
			m_fPosSizeX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 2)
		{
			m_fPosSizeX -= 20;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 1)
		{
			m_fPosSizeX -= 5;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 0)
		{
			m_fPosSizeX = 0;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		else
		{
			f_R = 0.0f;
			f_G = 1.0f;
			f_B = 0.0f;
			f_A = 1.0f;

		}

		SetNOMALENEMY(pos, move, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);
	}


	pos += move;
	move *= 0.1f;

	CScene2D::Update();

	SetNOMALENEMY(pos, move, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);
	CManeger::MODE m_mode = CManeger::GetMode();
	if (pInputKeyboard->GetPress(DIK_V) == true) { Uninit(); }

	if (m_mode == CManeger::MODE_GAME)
	{

		if (pos.x < 50 - m_fPosSize)
		{
			m_nLife = 0;
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
							CScore *pScore = (CScore*)pScene;
							//if (m_nType == ENEMY_CLASS_TYPE_BASE || m_nType == ENEMY_CLASS_TYPE_1 || m_nType == ENEMY_CLASS_TYPE_2 || m_nType == ENEMY_CLASS_TYPE_3 || m_nType == ENEMY_CLASS_TYPE_4 || m_nType == ENEMY_CLASS_TYPE_5)
							{
								if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER || pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER_3)
								{
									if (GetPotion().x > pos.x - BOSS_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + BOSS_POLYGON_SIZE &&
										GetPotion().y > pos.y - BULLET_SIZE - BOSS_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + BOSS_POLYGON_SIZE)
									{
										m_nLife -= 1;

										pBullet->Uninit();
										//pScore->AddScore(100);
										if (m_nLife == 0)
										{
											CScene2D::SetPattanAnim(nPattanAnim);
											CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, 25.0f);
											CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 50.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);
											Uninit();
											CFade *pFade = CManeger::GetFade();
											CFade::FADE  m_fade = pFade->FADE_MAX;

											if (m_fade != pFade->FADE_OUT)
											{
												CSound *pPlaySound = CManeger::GetSound();
												pPlaySound->StopSound(pPlaySound->SOUND_LABEL_BGM001);
												pFade->SetFade(CManeger::MODE_RESULT);
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
	}
		}
		catch (const std::exception&)
		{

		}

}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CBoss::Draw(void)
{
	CScene2D::Draw();
}

bool CBoss::CntScore(bool score)
{
	return score;
}