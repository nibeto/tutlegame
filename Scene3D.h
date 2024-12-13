
//=============================================================================
// メイン処理 [Scene2D.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
#include"main.h"
#include"scene.h"
//レンダリングクラス
class CSCENE3D : public CScene
{
public:
	CSCENE3D(LAYER m_Number);
	~CSCENE3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Draw(void);
	void SetCamera(void);

	void SetNOMAL(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXMATRIX mtxWorld);


	D3DXVECTOR3 GetPotion(void);
	D3DXVECTOR3 GetPotionV(void);
	D3DXVECTOR3 GetPotionR(void);
	D3DXVECTOR3 GetPotionU(void);

	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetfRot(void);


	float GetLength(void);
	static CSCENE3D *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);
	void BindModel(LPD3DXBUFFER		pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);

	void Save(void);
	void Load(void);

protected:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	D3DXCOLOR				m_col;

	int m_nCountRot = 0;			//カウンタ変数
	float m_fPosSize = 0.0f;	//サイズ変更用
	float m_fPosSizeX = 0.0f;	//サイズ変更用
	float m_fPosSizeY = 0.0f;	//サイズ変更用
	float m_fPosSizeZ = 0.0f;	//サイズ変更用

	float m_fRot = D3DX_PI * 0.25f;	//回転(float変数)
	float m_fRotRand = 0.0f;	//回転(float変数)
	float m_fRotRand1 = 0.0f;	//回転(float変数)
	float fSpeedUp = 6.0f;//移動の速度*これはスピードアップではない*
	float mf_pos = 0.0f;//(posの長さの変数)
	int nCountAnime;
	int nCountBg;

	int nPattenAnime;
	bool bUse;
	bool bLand;

	bool m_bjump;
	bool m_bDisp;
	int nCountBullet;
	int m_nPriority;


	float m_fRadius;			// 半径(大きさ)


	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;
	D3DXVECTOR2				m_tex;
	D3DXVECTOR3	 m_rot;		// 通常状態 && Pizza状態縦の向き(現在)

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 m_matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *m_pMat;							// マテリアルデータへのポインタ
												// ワールドマトリックスの初期化

	D3DXVECTOR3  m_posOld;	// 過去の位置
	D3DXMATRIX	 m_mtxWorld;	// ワールドマトリックス
	LPD3DXMESH	 m_pMesh = NULL; 	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat = NULL;	// マテリアル情報へのポインタ
	DWORD		m_nNumMat;	// マテリアルの情報
	int		nIdyShadow;		// 影の番号
	float fXaxis;			// X軸
	float fZaxis;			// Z軸

	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注意点
	D3DXVECTOR3 m_vecU;				//上方向ベクトル

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;				//ビューマトリックス

	float m_Bt0 = 43.5f;//拡大縮小
	SCENE_NUMBER_TYPE m_nNumber3D;//描画順番
	LAYER m_layer3D;



private:

};
#endif
