//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _CAPSULEENEMY_H_
#define _CAPSULEENEMY_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//�����_�����O�N���X
class CCAPSULEENEMY : public CScene2D
{
public:
	CCAPSULEENEMY(SCENE_NUMBER_TYPE m_Number);
	~CCAPSULEENEMY();
	typedef enum
	{//�e�N�X�`���[�^�C�v
		CAPSULEENEMY_TYPE_PLAYER = 0,
		CAPSULEENEMY_TYPE_ENEMY,
		CAPSULEENEMY_TYPE_ROBO,
		CAPSULEENEMY_TYPE_MAX

	}CAPSULEENEMY_TYPE;
	typedef enum
	{//�^�C�v
		CAPSULEENEMY_OBJ_TYPE_PLAYER = 0,
		CAPSULEENEMY_OBJ_TYPE_PLAYER_1,
		CAPSULEENEMY_OBJ_TYPE_PLAYER_2,
		CAPSULEENEMY_OBJ_TYPE_PLAYER_3,
		CAPSULEENEMY_OBJ_TYPE_PLAYER_4,
		CAPSULEENEMY_OBJ_TYPE_ENEMY,
		CAPSULEENEMY_OBJ_TYPE_ROBO,
		CAPSULEENEMY_OBJ_TYPE_AROUND,
		CAPSULEENEMY_OBJ_TYPE_MAX

	}CAPSULEENEMY_OBJ_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	inline	float	GetPosX(void) { return m_f_posX; };
	inline	float	GetPosY(void) { return m_f_posY; };

	static CCAPSULEENEMY *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, CAPSULEENEMY_TYPE type, CAPSULEENEMY_OBJ_TYPE nType);

	CAPSULEENEMY_OBJ_TYPE Type;//�^�C�v

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
	float m_f_posX;
	float m_f_posY;

};
#define CAPSULEENEMY_SIZE		(10)						//�e�̃T�C�Y
#define MAX_CAPSULEENEMY_LIFE	(50)						//�e�̎���
#define	MAX_CAPSULEENEMY				(1250)		// �e�̍ő吔
#define CAPSULEENEMY_POS_X			(0)		//�e�̍���X���W
#define CAPSULEENEMY_POS_Y			(0)		//�e�̍���Y���W
#define CAPSULEENEMY_WIDTH			(5)		//�e�̕�
#define CAPSULEENEMY_HEIGHT			(5)		//�e�̍���
#define CAPSULEENEMY_POS_X2			(CAPSULEENEMY_WIDTH - CAPSULEENEMY_POS_X / 2)		//�e�̍���X���W
#define CAPSULEENEMY_POS_Y2			(CAPSULEENEMY_HEIGHT - CAPSULEENEMY_POS_Y / 2)		//�e�̍���X���W


#define CAPSULEENEMY_TEXTURE_SPEED	(0.01f)			//�e�A�j���[�V�����X�s�[�h
#define CAPSULEENEMY_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define CAPSULEENEMY_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�



#endif