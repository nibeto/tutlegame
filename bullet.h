//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//�����_�����O�N���X
class CBullet : public CScene2D
{
public:
	CBullet(SCENE_NUMBER_TYPE m_Number);
	~CBullet();
	typedef enum
	{//�e�N�X�`���[�^�C�v
		BULLET_TYPE_PLAYER = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_ROBO,
		BULLET_TYPE_MAX

	}BULLET_TYPE;
	typedef enum
	{//�^�C�v
		BULLET_OBJ_TYPE_PLAYER = 0,
		BULLET_OBJ_TYPE_PLAYER_1,
		BULLET_OBJ_TYPE_PLAYER_2,
		BULLET_OBJ_TYPE_PLAYER_3,
		BULLET_OBJ_TYPE_PLAYER_4,
		BULLET_OBJ_TYPE_ENEMY,
		BULLET_OBJ_TYPE_ENEMY_1,
		BULLET_OBJ_TYPE_ENEMY_2,
		BULLET_OBJ_TYPE_ROBO,
		BULLET_OBJ_TYPE_AROUND,
		BULLET_OBJ_TYPE_MAX

	}BULLET_OBJ_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	//�N���G�C�g
	inline static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, BULLET_TYPE type, BULLET_OBJ_TYPE nType) {
		//�C���X�^���X
		CBullet*pBullet = NULL;
		pBullet = new CBullet(SCENE_NUMBER_TYPE_BULLET);
		pBullet->Init(pos, move, rot, Length);
		pBullet->BindTexture(m_pTexture[type]);
		pBullet->Type = nType;
		return pBullet;

	};

	BULLET_OBJ_TYPE Type;//�^�C�v

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

};
#define BULLET_SIZE		(10)						//�e�̃T�C�Y
#define MAX_BULLET_LIFE	(50)						//�e�̎���
#define	MAX_BULLET				(1250)		// �e�̍ő吔
#define BULLET_POS_X			(0)		//�e�̍���X���W
#define BULLET_POS_Y			(0)		//�e�̍���Y���W
#define BULLET_WIDTH			(5)		//�e�̕�
#define BULLET_HEIGHT			(5)		//�e�̍���
#define BULLET_POS_X2			(BULLET_WIDTH - BULLET_POS_X / 2)		//�e�̍���X���W
#define BULLET_POS_Y2			(BULLET_HEIGHT - BULLET_POS_Y / 2)		//�e�̍���X���W


#define BULLET_TEXTURE_SPEED	(0.01f)			//�e�A�j���[�V�����X�s�[�h
#define BULLET_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define BULLET_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�



#endif