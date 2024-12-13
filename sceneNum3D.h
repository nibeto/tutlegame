//=============================================================================
//
// メイン処理 [scene.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCENENUM3D_H_
#define _SCENENUM3D_H_
#include"main.h"
//レンダリングクラス
class CSceneNum3D
{
public:

	typedef enum
	{
		OBJECT_TYPE3D_PLAYER = 0,
		OBJECT_TYPE3D_ENENMY,
		OBJECT_TYPE3D_BULLET,
		OBJECT_TYPE3D_BG,
		OBJECT_TYPE3D_BG1,
		OBJECT_TYPE3D_BLOCK,
		OBJECT_TYPE3D_SCORE,
		OBJECT_TYPE3D_EFFECT,
		OBJECT_TYPE3D_WEAPONS,
		OBJECT_TYPE3D_OBJNIFE,
		OBJECT_TYPE3D_ROBO,
		OBJECT_TYPE3D_OBJ,
		OBJECT_TYPE3D_LIFE,
		OBJECT_TYPE3D_GOAL,
		OBJECT_TYPE3D_CAPSULE,
		OBJECT_TYPE3D_CAPSULEENEMY,
		OBJECT_TYPE3D_MAX
	}OBJECT_TYPE3D;


	typedef enum
	{

		SCENE3D_NUMBER_TYPE_CAMERA = 0,
		SCENE3D_NUMBER_TYPE_PLAYER_3D,
		SCENE3D_NUMBER_TYPE_MAX

	}SCENE3D_NUMBER_TYPE;
	typedef enum
	{//ニューラルネットワーク3D(三層)
		LAYER3D_Input,
		LAYER3D_Middletier,
		LAYER3D_Output,
		LAYER3D_MAX
	}LAYER3D;

	CSceneNum3D(SCENE3D_NUMBER_TYPE m_Number = SCENE3D_NUMBER_TYPE_MAX);//	デフォルト値
	virtual~CSceneNum3D();
	virtual	HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void Release3DALL(void);
	static void Update3DALL(void);
	static void Draw3DALL(void);



	static void Road(void);

	inline static int  GetnNumALL3D(void) { return m_nNumAll3D; };

	inline OBJECT_TYPE3D GetOBJTYPE3D(void) { return m_apType3D; };
	void SetOBJTYPE3D(OBJECT_TYPE3D type);


	static CSceneNum3D * GetCSINE3D(SCENE3D_NUMBER_TYPE  m_Number3D, int m_IDx);

protected:
	int m_nCount;
	void Release3D(void);
private:
	static CSceneNum3D *m_apSine3D[(LAYER3D)SCENE3D_NUMBER_TYPE_MAX][MAX_SCENE3D];//優先順位
	OBJECT_TYPE3D m_apType3D;
	int m_nID3D;//自分自身の番号
	static int m_nNumAll3D;
	SCENE3D_NUMBER_TYPE m_nNumber3D;
	LAYER3D m_nLayer3D;


};


#endif