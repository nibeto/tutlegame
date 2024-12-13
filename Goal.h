//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//�����_�����O�N���X
class CGoal : public CScene2D
{
public:
	CGoal(SCENE_NUMBER_TYPE m_Number);
	~CGoal();
	typedef enum
	{//�e�N�X�`���[�^�C�v
		GOAL_TYPE_PLAYER = 0,
		GOAL_TYPE_ENEMY,
		GOAL_TYPE_ROBO,
		GOAL_TYPE_MAX

	}GOAL_TYPE;
	typedef enum
	{//�^�C�v
		GOAL_OBJ_TYPE_PLAYER = 0,
		GOAL_OBJ_TYPE_PLAYER_1,
		GOAL_OBJ_TYPE_PLAYER_2,
		GOAL_OBJ_TYPE_PLAYER_3,
		GOAL_OBJ_TYPE_PLAYER_4,
		GOAL_OBJ_TYPE_ENEMY,
		GOAL_OBJ_TYPE_ROBO,
		GOAL_OBJ_TYPE_AROUND,
		GOAL_OBJ_TYPE_MAX

	}GOAL_OBJ_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	inline	float	GetPosX(void) { return m_fPosx; };
	inline	float	GetPosY(void) { return m_fPosy; };

	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, GOAL_TYPE type, GOAL_OBJ_TYPE nType);

	GOAL_OBJ_TYPE Type;//�^�C�v

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[3];		// �e�N�X�`���ւ̃|�C���^
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*
	bool m_bDisp;
	bool bUse;
	int m_nCountBullet;
	int m_Tex;

	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fMoveX1 = 0.0f, fMoveY1 = 0.0f;
	float fMoveX2 = 0.0f, fMoveY2 = 0.0f;

	float fRoboMoveX = 0.0f, fRoboMoveY = 0.0f;
	float fAroundMoveX = 0.0f, fAroundMoveY = 0.0f;


	float fRot;
	float fRot1;
	float fRot2;
	float fRoboRot;
	float fAroundRot = D3DX_PI * 0.25f;
	float m_fPosx;
	float m_fPosy;
};
#define BULLET_SIZE		(10)						//�e�̃T�C�Y
#define MAX_GOA_LIFE	(50)						//�e�̎���
#define	MAX_GOAL				(1250)		// �e�̍ő吔
#define GOAL_POS_X			(0)		//�e�̍���X���W
#define GOAL_POS_Y			(0)		//�e�̍���Y���W
#define GOAL_WIDTH			(5)		//�e�̕�
#define GOAL_HEIGHT			(5)		//�e�̍���
#define GOAL_POS_X2			(GOAL_WIDTH - GOAL_POS_X / 2)		//�e�̍���X���W
#define GOAL_POS_Y2			(GOAL_HEIGHT - GOAL_POS_Y / 2)		//�e�̍���X���W


#define GOAL_TEXTURE_SPEED	(0.01f)			//�e�A�j���[�V�����X�s�[�h
#define GOAL_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define GOAL_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�



#endif