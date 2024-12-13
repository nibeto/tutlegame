//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _CAPSULE_H_
#define _CAPSULE_H_
#include"main.h"
#include"Scene2D.h"

//�����_�����O�N���X
class CCapsule : public CScene2D
{
public:
	CCapsule(SCENE_NUMBER_TYPE m_Number);
	~CCapsule();
	typedef enum
	{
		CAPSULE_TYPE_BASE = 0,
		CAPSULE_TYPE_1 = 1,
		CAPSULE_TYPE_2,
		CAPSULE_TYPE_MAX

	}CAPSULE_TYPE;
	typedef enum
	{//�^�C�v
		CAPSULE_CLASS_TYPE_BASE = 0,
		CAPSULE_CLASS_TYPE_1 = 1,
		CAPSULE_CLASS_TYPE_2,
		CAPSULE_CLASS_TYPE_3,
		CAPSULE_CLASS_TYPE_4,
		CAPSULE_CLASS_TYPE_5,
		CAPSULE_CLASS_TYPE_LIFE,
		CAPSULE_CLASS_TYPE_LIFE_1,
		CAPSULE_CLASS_TYPE_MAX

	}CAPSULE_CLASS_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCapsule *Create(D3DXVECTOR3 pos, float LengthX, float LengthY, CAPSULE_TYPE type, CAPSULE_CLASS_TYPE nType);



private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
									//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*
	bool m_bjump;
	bool m_bDisp;
	int nCountBullet;
	CAPSULE_CLASS_TYPE m_nType;//�^�C�v
	float m_posx;
	float m_posy;
};
#define CAPSULE_POLYGON_SIZE (25)

#define	MAX_TypeCAPSULE			(4)		// �e�̍ő吔

#define	MAX_CAPSULE			(40)		// �e�̍ő吔
#define CAPSULE_POS_X			(0)		//�e�̍���X���W
#define CAPSULE_POS_Y			(0)		//�e�̍���Y���W
#define CAPSULE_HEIGHT			(55)		//�e�̍���
#define CAPSULE_WIDTH              (55)
#define CAPSULE_TEXTURE_SPEED	(0.5f)			//�e�A�j���[�V�����X�s�[�h
#define CAPSULE_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define CAPSULE_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�
#define	CAPSULE_CM				(40)//�ǂƂ̋���
#define	CAPSULE_POS_X2			(CAPSULE_WIDTH - CAPSULE_POS_X / 2)		//�e�̍���X���W
#define CAPSULE_POS_Y2			(CAPSULE_HEIGHT - CAPSULE_POS_Y / 2)		//�e�̍���X���W




#endif