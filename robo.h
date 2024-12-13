//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _ROBO_H_
#define _ROBO_H_
#include"main.h"
#include"Scene2D.h"

//�����_�����O�N���X
class CRobo : public CScene2D
{
public:
	CRobo(SCENE_NUMBER_TYPE m_Number);
	~CRobo();
	typedef enum
	{
		ROBO_TYPE_BASE = 0,
		ROBO_TYPE_1 = 1,
		ROBO_TYPE_2,
		ROBO_TYPE_MAX

	}ROBO_TYPE;
	typedef enum
	{//�^�C�v
		ROBO_CLASS_TYPE_BASE = 0,
		ROBO_CLASS_TYPE_1 = 1,
		ROBO_CLASS_TYPE_2,
		ROBO_CLASS_TYPE_3,
		ROBO_CLASS_TYPE_4,
		ROBO_CLASS_TYPE_5,
		ROBO_CLASS_TYPE_LIFE,
		ROBO_CLASS_TYPE_LIFE_1,
		ROBO_CLASS_TYPE_MAX

	}ROBO_CLASS_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos,  float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CRobo *Create(D3DXVECTOR3 pos, float LengthX, float LengthY, ROBO_TYPE type, ROBO_CLASS_TYPE nType);



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
	ROBO_CLASS_TYPE m_nType;//�^�C�v

};
#define ROBO_POLYGON_SIZE (25)

#define	MAX_TypeROBO			(4)		// �e�̍ő吔

#define	MAX_ROBO			(40)		// �e�̍ő吔
#define ROBO_POS_X			(0)		//�e�̍���X���W
#define ROBO_POS_Y			(0)		//�e�̍���Y���W
#define ROBO_HEIGHT			(55)		//�e�̍���
#define ROBO_WIDTH              (55)
#define ROBO_TEXTURE_SPEED	(0.5f)			//�e�A�j���[�V�����X�s�[�h
#define ROBO_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define ROBO_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�
#define	ROBO_CM				(40)//�ǂƂ̋���
#define	ROBO_POS_X2			(ROBO_WIDTH - ROBO_POS_X / 2)		//�e�̍���X���W
#define ROBO_POS_Y2			(ROBO_HEIGHT - ROBO_POS_Y / 2)		//�e�̍���X���W




#endif