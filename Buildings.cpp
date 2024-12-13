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
#include"Buildings.h"
#include"score.h"
#include"sound.h"
#include"Playerobj.h"
#include"SeedManagement.h"
#include "Goal.h"
#include"Life.h"
#include"Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define MAX_BUILDING_TYPE (6)//a =	透明度 (0～255)
#define MOVE_BUILDING_SPEED (5.0f)
int CBUilding::nNumBuilding = 0;
CBUilding::Building CBUilding::m_Building[MAX_NUM_BUILDING] = {};
LPDIRECT3DTEXTURE9 CBUilding::m_pTexture[CBUilding::BUILDING_TYPE_MAX] = {};
//=============================================================================
// メイン関数
//=============================================================================
CBUilding *CBUilding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, BUILDING_TYPE type, BUILDING_CLASS_TYPE nType, float colR, float colG, float colB, float colA)
{
	//インスタンスw
	CBUilding*pEnemy = NULL;
	pEnemy = new CBUilding(SCENE_NUMBER_TYPE_BUILIDING);
	pEnemy->Init(pos, move, LengthX, LengthY, colR, colG, colB, colA);
	pEnemy->m_nType = nType;
	pEnemy->BindTexture(m_pTexture[type]);
	return pEnemy;
	//インスタンス

}

void CBUilding::Save(void)
{
}
//=============================================================================
// ロード
//=============================================================================
void CBUilding::Loads(void)
{
	//変数宣言
	char cEnpty[128];	// 空用（必要のないもの）
	char cLoad[128];	// 読み込む用
	char cComp[128];	// 比較用
	int nNumber = 0;
	int nIndex = 0;
	FILE *pFIle;

	try
	{

	pFIle = fopen("data/Save/Building.txt", "r");

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

				if (strcmp(cComp, "NUM_BUILIDING") == 0)
				{
					sscanf(cLoad, "%s %s %d", &cEnpty, &cEnpty, &nNumBuilding);
					nNumber = nNumBuilding;
				}
				if (strcmp(cComp, "BUILIDINGPOLIGONSET") == 0)
				{
					while (strcmp(cComp, "END_BUILIDINGPOLIGONSET") != 0)
					{
						fgets(cLoad, sizeof(cLoad), pFIle);
						sscanf(cLoad, "%s", &cComp);

						if (strcmp(cComp, "BUILIDINGSET") == 0)
						{
							while (strcmp(cComp, "END_BUILIDINGSET") != 0)
							{
								fgets(cLoad, sizeof(cLoad), pFIle);
								sscanf(cLoad, "%s", &cComp);

								if (strcmp(cComp, "POS") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f ", &cEnpty, &cEnpty, &m_Building[nIndex].pos.x, &m_Building[nIndex].pos.y, &m_Building[nIndex].pos.z);
								}
								if (strcmp(cComp, "MOVE") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f ", &cEnpty, &cEnpty, &m_Building[nIndex].move.x, &m_Building[nIndex].move.y, &m_Building[nIndex].move.z);
								}
								if (strcmp(cComp, "SIZE") == 0)
								{
									sscanf(cLoad, "%s %s %f %f", &cEnpty, &cEnpty, &m_Building[nIndex].f_sizeX, &m_Building[nIndex].f_sizeY);
								}
								if (strcmp(cComp, "TYPE") == 0)
								{
									sscanf(cLoad, "%s %s %d ", &cEnpty, &cEnpty, &m_Building[nIndex].type);
								}
								if (strcmp(cComp, "OBJ_TYPE") == 0)
								{
									sscanf(cLoad, "%s %s %d ", &cEnpty, &cEnpty, &m_Building[nIndex].ntype);
								}
								if (strcmp(cComp, "COLOR") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f %f ", &cEnpty, &cEnpty, &m_Building[nIndex].f_R, &m_Building[nIndex].f_G, &m_Building[nIndex].f_B, &m_Building[nIndex].f_A);
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
int CBUilding::GetNumBuilding(void)
{
	return nNumBuilding;
}
CBUilding::Building *CBUilding::GetBuilding(void)
{
	return &m_Building[0];
}

HRESULT CBUilding::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[0]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[1]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[2]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[3]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[4]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[5]);

#ifdef _DEBUG
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding1.png", &m_pTexture[0]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding2.png", &m_pTexture[1]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding3.png", &m_pTexture[2]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding1.png", &m_pTexture[3]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding2.png", &m_pTexture[4]);
	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Buliding3.png", &m_pTexture[5]);

#endif // _DEBUG
	return S_OK;
}
void CBUilding::UnLoad(void)
{//unload//破棄
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_BUILDING_TYPE; nCntEnemyType++)
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
CBUilding::CBUilding(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_BUILIDING) :CScene2D(m_layer)
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
CBUilding::~CBUilding()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CBUilding::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA)
{
	try
	{

	CScene2D::Init();
	CSeedMAnagenet *Pseed = CSeedMAnagenet::GetSeed();
	mf_pos = 5;//posの初期化の変数
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	f_R = colR;
	f_G = colG;
	f_B = colB;
	f_A = colA;

	//Length = 5;
	SetOBJTYPE(OBJECT_TYPE_BUILIDING);
	SetNOMALENEMY(pos, move, LengthX, LengthY, colR, colG, colB, colA);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = f_posX;
	f_posX = LengthX;
	m_fPosSizeY = f_posY;
	f_posY = LengthY;
	m_nLife = 5;
	fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();
	fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();
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
void CBUilding::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CBUilding::Update(void)
{
	try
	{

	m_nCountRot++;
	//pos
	D3DXVECTOR3 pos;
	//move(移動量)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	D3DXCOLOR col;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	BUILDING_TYPE type = BUILDING_TYPE_MAX;
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




	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[BUILDING_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[BUILDING_TYPE_2]); }

	if (pInputKeyboard->GetPress(DIK_D) == true) { fMoveX = -1.0f; }
	if (pInputKeyboard->GetPress(DIK_A) == true) { fMoveX = 1.0f; }
	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//入力された
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}


	//if (pos.y - BUILIDING_POS_Y2 < 0)
	//{
	//	pos.y = BUILIDING_POS_Y2;
	//}
	//if (pos.y + BUILIDING_POS_Y2 > SCREEN_HEIGHT_Y_2 + 25)
	//{
	//	pos.y = SCREEN_HEIGHT_Y_2 + 25 - BUILIDING_POS_Y2;
	//}
	//if (pos.x - BUILIDING_POS_X2 < 0)
	//{
	//	pos.x = BUILIDING_POS_X2;
	//}
	//if (pos.x + BUILIDING_POS_X2 > SCREEN_WIDTH + 500)
	//{
	//	pos.x = SCREEN_WIDTH + 500 - BUILIDING_POS_X2;
	//}

	if (m_nType == BUILDING_CLASS_TYPE_3)
	{
	}
	else	if (m_nType == BUILDING_CLASS_TYPE_4)
	{


	}
	else	if (m_nType == BUILDING_CLASS_TYPE_5)
	{
	}
	else	if (m_nType == BUILDING_CLASS_TYPE_LIFE || m_nType == BUILDING_CLASS_TYPE_1)
	{
		if (m_nLife <= 4)
		{
			f_posX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 3)
		{
			f_posX = 50;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 2)
		{
			f_posX -= 20;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 1)
		{
			f_posX -= 5;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		if (m_nLife <= 0)
		{
			f_posX = 0;
			f_R = 1.0f;
			f_G = 0.0f;

		}
		else
		{
			f_R = 1.0f;
			f_G = 1.0f;
			f_B = 1.0f;
			f_A = 1.0f;

		}

		SetNOMALENEMY(pos, move, f_posX, f_posY, f_R, f_G, f_B, f_A);
	}


	pos += move;
	move *= 0.1f;

	CScene2D::Update();

	SetNOMALENEMY(pos, move, f_posX, f_posY, f_R, f_G, f_B, f_A);
	CManeger::MODE m_mode = CManeger::GetMode();

	if (m_mode == CManeger::MODE_GAME)
	{
#ifdef _DEBUG


		//当たり判定
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
								if (GetPotion().x > pos.x - BUILIDING_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + BUILIDING_POLYGON_SIZE &&
									GetPotion().y > pos.y - BULLET_SIZE - BUILIDING_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + BUILIDING_POLYGON_SIZE)
								{
									m_nLife -= 1;

									pBullet->Uninit();
									//pScore->AddScore(100);
									if (m_nLife == 0)
									{
										CScene2D::SetPattanAnim(nPattanAnim);
										CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, 25.0f);
										CGoal::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 10.0f, CGoal::GOAL_TYPE_ENEMY, CGoal::GOAL_OBJ_TYPE_ENEMY);

										Uninit();
									}
								}
							}
						}
					}
				}

			}

		}
#endif // DEBUG
	}
		}
		catch (const std::exception&)
		{

		}


}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CBUilding::Draw(void)
{
	CScene2D::Draw();
}

bool CBUilding::CntScore(bool score)
{
	return score;
}

