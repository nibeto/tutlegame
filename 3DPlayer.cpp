//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"3DPlayer.h"
#include"renderer.h"
#include"input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)

#define COLOR_A (255)//a =	透明度 (0～255)
#define TEX_FILE1 ("data/TEXTURE/Player4.png")//青 (0～255)
#define TEX_FILE2 ("data/TEXTURE/Player9.png")//青 (0～255)
#define PLAYER_NAME0000 ("data/MODEL/01_head.x")				//	プレイヤー(通常)の名前

LPDIRECT3DTEXTURE9 C3DPlayer::m_pTexture[MAX_TEX_PLAYER] = {};
LPD3DXMESH	C3DPlayer:: m_pMesh; 	//メッシュ情報へのポインタ
LPD3DXBUFFER C3DPlayer::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD		C3DPlayer::m_nNumMat;	// マテリアルの情報

//=============================================================================
// Create関数
//=============================================================================
C3DPlayer *C3DPlayer::Create(D3DXVECTOR3 pos, PLAYER3D_TYPE type)
{
	//LPD3DXBUFFER		pBuffMat; DWORD nNumMat; LPD3DXMESH pMesh;
	//インスタンス
	C3DPlayer*pPlayer3D = NULL;
	pPlayer3D = new C3DPlayer(SCENE_NUMBER_TYPE_3DPLAYER);
	pPlayer3D->Init(pos);
	pPlayer3D->BindTexture(m_pTexture[type]);
	pPlayer3D->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
	return pPlayer3D;

}

HRESULT C3DPlayer::Load(void)
{//load//読み込み
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXLoadMeshFromX(PLAYER_NAME0000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);


	return S_OK;
}
void C3DPlayer::UnLoad(void)
{//unload//破棄
	for (int nCntPlayer = 0; nCntPlayer < MAX_TEX_PLAYER; nCntPlayer++)
	{

		//テクスチャの破棄
		if (m_pTexture[nCntPlayer] != NULL)
		{
			m_pTexture[nCntPlayer]->Release();
			m_pTexture[nCntPlayer] = NULL;
		}


	}
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}


}
//=============================================================================
//コンストラクタ
//=============================================================================
C3DPlayer::C3DPlayer(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_3DPLAYER) :CSCENE3D(m_layer3D)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	nCountBullet = 0;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
C3DPlayer::~C3DPlayer()
{

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT C3DPlayer::Init(D3DXVECTOR3 pos)
{
	CSCENE3D::Init();
	m_bDisp = true;
	m_bjump = false;
	m_fPosSizeX = -70.0f;
	m_fPosSizeY = 20.0f;
	m_fPosSizeZ = 0.0f;
	m_pos = D3DXVECTOR3(m_fPosSizeX, m_fPosSizeY, m_fPosSizeZ);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_pos = pos;
	nCountBullet = 0;
	SetOBJTYPE(OBJECT_TYPE_PLAYER3D);

	m_fRot = D3DX_PI * 0.25f;
	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void C3DPlayer::Uninit(void)
{
	CSCENE3D::Uninit();
}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void C3DPlayer::Update(void)
{
	try
	{

	m_nCountRot++;
	nCountBullet++;

	m_fRot = m_nCountRot / m_fRotRand;
	int nCntDAta = 0;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR2 tex;
	PLAYER3D_TYPE type = PLAYER3D_TYPE_MAX;
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;
	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_rot = GetfRot();
#if 0
	//if (pInputKeyboard->GetKeyboardPress(DIK_D)==true) { fMoveX = 1.0f; }//↑
	//if (pInputKeyboard->GetKeyboardPress(DIK_A)==true) { fMoveX = -1.0f; }//下
#endif
	if (pInputKeyboard->GetPress(DIK_D)==true) { fMoveX = 1.0f; }//↑
	if (pInputKeyboard->GetPress(DIK_A)==true) { fMoveX = -1.0f; }//下

	if (pInputKeyboard->GetPress(DIK_S) == true) { fMoveY = 1.0f; }
	if (pInputKeyboard->GetPress(DIK_W) == true) { fMoveY = -1.0f; }
	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//入力された
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}

	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[PLAYER3D_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[PLAYER3D_TYPE_2]); }
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_LEFT) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true) {
		if (move.x != 0) {}
	}
	else
	{
		if (move.x == 0)
		{

		}

	}


	if (pos.y - PLAYER3D_POS_Y2 < 0)
	{
		pos.y = PLAYER3D_POS_Y2;
	}
	if (pos.y + PLAYER3D_POS_Y2 > SCREEN_HEIGHT_Y_2 + 25)
	{
		pos.y = SCREEN_HEIGHT_Y_2 + 25 - PLAYER3D_POS_Y2;
	}
	if (pos.x - PLAYER3D_POS_X2 < 0)
	{
		pos.x = PLAYER3D_POS_X2;
	}
	if (pos.x + PLAYER3D_POS_X2 > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - PLAYER3D_POS_X2;
	}



#if 0


	//if (m_pos.y >= SCREEN_HEIGHT)
	//{
	//	m_bjump = false;
	//	pos.y = SCREEN_HEIGHT;
	//	move.y = 0.0f;

	//}
#endif // 0
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
		move.y = -GRAVITY3D / 2;//* fSpeedUp;

	}
	move.y += 1.75f;


	pos.y += move.y;


	pos += move;
	move *= 0.1f;

	CSCENE3D::Update();

	CSCENE3D::GetPotion();
	CSCENE3D::GetMove();
	CSCENE3D::GetLength();
	CSCENE3D::GetfRot();
	CSCENE3D::SetNOMAL(pos, move, rot, m_mtxWorld);

		}
		catch (const std::exception&)
		{

		}

}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void C3DPlayer::Draw(void)
{
	CSCENE3D::Draw();
}
