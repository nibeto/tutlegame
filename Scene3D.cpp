//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//ヘッダーファイル//必須
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//必須
#include"score.h"
#include"manager.h"
#include"Scene3D.h"
#include"renderer.h"
#include"input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR_R (255)//赤 (0～255)
#define COLOR_G (255)//緑 (0～255)
#define COLOR_B (255)//青 (0～255)
#define COLOR_A (255)//a =	透明度 (0～255)
#define SCREEN_WHIDH_VIEWPORT (1280)
#define SCREEN_HIGHT_VIEWPORT (720)


//=============================================================================
// メイン関数
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CSCENE3D::CSCENE3D(LAYER m_Number = LAYER_MAX) :CScene(m_nNumber3D)
{//clear（クリア）
	m_nCountRot = 0;
	m_fRot = 0.0f;
}

//=============================================================================
//デストラクタ
//=============================================================================
CSCENE3D::~CSCENE3D()
{

}

CSCENE3D *CSCENE3D::Create(void)
{
	//インスタンス
	CSCENE3D*pScene3D = NULL;

	//
	pScene3D = new CSCENE3D;
	//初期化
	pScene3D->Init();

	if (pScene3D != NULL)
	{

	}

	//値を返す
	return pScene3D;

}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
HRESULT CSCENE3D::Init(void)
{
	// 位置・向きの初期設定
	m_pos = D3DXVECTOR3(-70.0f, 20.0f, 0.0f);		//位置の初期設定
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			//向きの初期セxyz
	return S_OK;
}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
void CSCENE3D::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
		// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh = NULL;
	}

		// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat = NULL;
	}

	Save();
	//delete this;

	Release();
}
void CSCENE3D::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{

	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;
}
void CSCENE3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{

	m_pTexture = pTexture;

}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
void CSCENE3D::Update(void)
{


}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================q
void CSCENE3D::Draw(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&m_matDef);

	// マテリアルデータへのポインタを取得
	//m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//
	for (int nCntMat1 = 0; nCntMat1 < (int)m_nNumMat; nCntMat1++)
	{
		// マテリアルの設定
		//pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);
		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat1);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&m_matDef);

}
void CSCENE3D::SetCamera(void)
{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_Bt0),								//光
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//画面比率
		10.0f,												//カメラから見た手前の位置
		1000.0f);											//カメラから見た奥行きの位置

															// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV,
		&m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//******************************************
//ポリゴンのset
//******************************************

void CSCENE3D::SetNOMAL(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXMATRIX mtxWorld)
{

	m_pos = pos;
	m_move = move;
	m_rot = rot;
	m_mtxWorld = mtxWorld;
}
//******************************************
//ポリゴンをGET
//******************************************

D3DXVECTOR3 CSCENE3D::GetPotion(void)
{

	return m_pos;

}
D3DXVECTOR3 CSCENE3D::GetPotionV(void)
{

	return m_posV;

}
D3DXVECTOR3 CSCENE3D::GetPotionR(void)
{

	return m_posR;

}
D3DXVECTOR3 CSCENE3D::GetPotionU(void)
{

	return m_vecU;


}
//******************************************
//移動をGET
//******************************************

D3DXVECTOR3 CSCENE3D::GetMove(void)
{

	return m_move;

}
//******************************************
//ポリゴンのサイズをGET
//******************************************

float CSCENE3D::GetLength(void)
{

	return m_fPosSize;

}
//******************************************
//ポリゴンの回転をGET
//******************************************

D3DXVECTOR3 CSCENE3D::GetfRot(void)
{

	return m_rot;


}
//******************************************
//posの初期化サイズをSAVE
//******************************************

void CSCENE3D::Save(void)
{


	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}

}
//******************************************
//posの初期化サイズをLOAD
//******************************************

void CSCENE3D::Load(void)
{


	//seve
	FILE *pFile;


	pFile = fopen("pos.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}

}