#ifndef _LIFE_H_
#define _LIFE_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_LIFE_TYPE (2)//a =	�����x (0�`255)

//�����_�����O�N���X
class cLife : public CScene2D
{
public:
	cLife(SCENE_NUMBER_TYPE m_Number);
	~cLife();
	typedef enum
	{
		LIFE_TYPE_BASE = 0,
		LIFE_TYPE_1 = 1,
		LIFE_TYPE_2,
		LIFE_TYPE_MAX

	}LIFE_TYPE;
	typedef enum
	{//�^�C�v
		LIFE_OBJ_TYPE_LIFE = 0,
		LIFE_OBJ_TYPE_LIFE_ENEMY,
		LIFE_OBJ_TYPE_MP,
		LIFE_OBJ_TYPE_MAX
	}LIFE_OBJ_TYPE;


	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int  GetLife(int nLife);
	int  GetMagicpoint(int nMagicPoint);

	static cLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, LIFE_TYPE type, LIFE_OBJ_TYPE nType);
	LIFE_OBJ_TYPE Type;//�^�C�v


private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LIFE_TYPE];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 Oldpos;
	D3DXCOLOR col;
	D3DXVECTOR3 pPos;//���݂̈ʒu
	D3DXVECTOR3 pPosold;//�O��̈ʒu
	D3DXVECTOR3 pMove;//�ړ��̗�

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
	int m_nLife = 0;
	float f_R = 1.0f;
	float f_G = 1.0f;
	float f_B = 1.0f;
	float f_A = 1.0f;

};
#define LIFE_POLYGON_SIZE (25)

#define	MAX_LIFE_BOX			(4)		// �e�̍ő吔

#define	MAX_LIFE			(40)		// �e�̍ő吔
#define LIFE_POS_X			(0)		//�e�̍���X���W
#define LIFE_POS_Y			(0)		//�e�̍���Y���W
#define LIFE_HEIGHT			(40)		//�e�̍���
#define LIFE_WIDTH              (150)
#define LIFEN_TEXTURE_SPEED	(0.5f)			//�e�A�j���[�V�����X�s�[�h
#define LIFE_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define LIFE_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�
#define	LIFE_CM				(40)//�ǂƂ̋���




#endif // !_COLLISION_H_
