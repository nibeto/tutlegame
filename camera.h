//=============================================================================
//
// 入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include"Scene3D.h"
#define MAX_CAMERA (4)
//レンダリングクラス
class CCAMERA
{
public:
	//*****************************************************************************
	// カメラの構造体
	//*****************************************************************************
	typedef struct
	{
		D3DXVECTOR3 posV;			//視点
		D3DXVECTOR3 posR;			//注視点
		D3DXVECTOR3 posU;			//上方向ベクトル
		D3DXVECTOR3 posVDest;
		D3DXVECTOR3 posRDest;
		D3DXVECTOR3 rotCamera;		//向き
		D3DXVECTOR3 rotDest;
		D3DXVECTOR3 DiffAngle;
		D3DXMATRIX mtxProjection;	//プロジェクションマトリックス(テレビ)
		D3DXMATRIX mtxView;			//ビューマトリックス(カメラマン)
		float nCounterAngle;			//カメラアングルが変わるカウンター
		D3DVIEWPORT9 Viewport;		//ビューポート
	}Camera;
	CCAMERA();
	~CCAMERA();
	static CCAMERA *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(int nIdxCamera);
	void cameraPos(void);
	void CameraGame(float fMove, float fSpeedMove, float fMovePos);
	void CameraTutorial(float fMove, float fSpeedMove, float fMovePos);
	void CameraTitle(void);
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;				// 入力デバイスへのポインタ

private:
	Camera m_Camera[MAX_CAMERA];	//カメラの情報
	float fLength;

	float fAngle = 0.0f;					//角度
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 posV;				//視点
	D3DXVECTOR3 posR;				//注意点
	D3DXVECTOR3 vecU;				//上方向ベクトル


};

#endif
