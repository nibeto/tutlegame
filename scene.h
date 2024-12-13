//=============================================================================
//
// ���C������ [scene.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include"main.h"
//�����_�����O�N���X
class CScene
{
public:

	typedef enum
	{
		OBJECT_TYPE_PLAYER3D = 0,
		OBJECT_TYPE_PLAYER = 0,
		OBJECT_TYPE_PORIGON,
		OBJECT_TYPE_ENENMY,
		OBJECT_TYPE_BOSS,
		OBJECT_TYPE_BUILIDING,
		OBJECT_TYPE_DICE,
		OBJECT_TYPE_BULLET,
		OBJECT_TYPE_BG,
		OBJECT_TYPE_TITLEUI,
		OBJECT_TYPE_DEBUG,
		OBJECT_TYPE_BLOCK,
		OBJECT_TYPE_SCORE,
		OBJECT_TYPE_EFFECT,
		OBJECT_TYPE_WEAPONS,
		OBJECT_TYPE_OBJNIFE,
		OBJECT_TYPE_ROBO,
		OBJECT_TYPE_OBJ,
		OBJECT_TYPE_LIFE,
		OBJECT_TYPE_GOAL,
		OBJECT_TYPE_CAPSULE,
		OBJECT_TYPE_CAPSULEENEMY,
		OBJECT_TYPE_TIMER,
		OBJECT_TYPE_MAX
	}OBJECT_TYPE;
	typedef enum
	{
		SCENE_NUMBER_TYPE_CAMERA = 0,
		SCENE_NUMBER_TYPE_3DPLAYER,
		SCENE_NUMBER_TYPE_BG = 0,
		SCENE_NUMBER_TYPE_FONT,
		SCENE_NUMBER_TYPE_TITLEUI,
		SCENE_NUMBER_TYPE_NUMBER,
		SCENE_NUMBER_TYPE_SCORE,
		SCENE_NUMBER_TYPE_TIME,
		SCENE_NUMBER_TYPE_LEVEL,
		SCENE_NUMBER_TYPE_BULLETLIFE,
		SCENE_NUMBER_TYPE_ROGOWAKU,
		SCENE_NUMBER_TYPE_LIFE,
		SCENE_NUMBER_TYPE_DICE,
		SCENE_NUMBER_TYPE_PLAYER,
		SCENE_NUMBER_TYPE_POLIGON,
		SCENE_NUMBER_TYPE_ENEMY,
		SCENE_NUMBER_TYPE_BOSS,
		SCENE_NUMBER_TYPE_BUILIDING,
		SCENE_NUMBER_TYPE_EFFECT,
		SCENE_NUMBER_TYPE_BULLET,
		SCENE_NUMBER_TYPE_CAPSULE,
		SCENE_NUMBER_TYPE_CAPSULEENEMY,
		SCENE_NUMBER_TYPE_AROUND,
		SCENE_NUMBER_TYPE_EXPROSION,
		SCENE_NUMBER_TYPE_DEBUG,
		SCENE_NUMBER_TYPE_BLOCK,
		SCENE_NUMBER_TYPE_COLLISION,
		SCENE_NUMBER_TYPE_SHIELD,
		SCENE_NUMBER_TYPE_PLAYER_OBJ,
		SCENE_NUMBER_TYPE_WEAPONS,
		SCENE_NUMBER_TYPE_TARGET,
		SCENE_NUMBER_TYPE_ROBO,
		SCENE_NUMBER_TYPE_GOAL,
		SCENE_NUMBER_TYPE_OBJ,
		SCENE_NUMBER_TYPE_TIMER,
		SCENE_NUMBER_TYPE_PAUSE,
		SCENE_NUMBER_TYPE_PAUSE_SERECT,

		SCENE_NUMBER_TYPE_MAX
	}SCENE_NUMBER_TYPE;

	typedef enum
	{//�j���[�����l�b�g���[�N(�O�w)
		LAYER_Input,
		LAYER_Middletier,
		LAYER_Output,
		LAYER_MAX
	}LAYER;

	CScene(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_MAX);//	�f�t�H���g�l
	virtual~CScene();
	virtual	HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseALL(void);
	static void UpdateALL(void);
	static void DrawALL(void);

	static void Road(void);

	inline	static int  GetnNumALL(void) { return m_nNumAll; };

	inline	OBJECT_TYPE GetOBJTYPE(void) { return m_apType; };
	void SetOBJTYPE(OBJECT_TYPE type);

	static CScene * GetCSINE(SCENE_NUMBER_TYPE  m_Number, int m_IDx);


protected:
	int m_nCount;
	void Release(void);
private:
	static CScene *m_apSine[(LAYER)SCENE_NUMBER_TYPE_MAX][MAX_SCENE];//�D�揇��
	OBJECT_TYPE m_apType;
	int m_nID;//�������g�̔ԍ�
	static	int m_nNunberPlayer;
	static int m_nNumAll;
	SCENE_NUMBER_TYPE m_nNumber;
	LAYER m_nLayer;


};


#endif