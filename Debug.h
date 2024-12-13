//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include"main.h"
#include"Scene2D.h"

#define MAX_NUM_DEBUG (20)
//�����_�����O�N���X
class CDebug : public CScene2D
{
public:
	CDebug(SCENE_NUMBER_TYPE m_Number);
	~CDebug();
	typedef enum
	{
		DEBUG_TYPE_BASE = 0,
		DEBUG_TYPE_1,
		DEBUG_TYPE_MAX
	}DEBUG_TYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		float f_sizeX;
		float f_sizeY;
		float f_rot;
		int  type;
	}Debug;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CorisionDebug(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3	*pMove);
	D3DXVECTOR3	GetPos(void) { return m_pos; };
	float GetSizeX(void) { return CScene2D::GetLengthX(); };
	float GetSizeY(void) { return CScene2D::GetLengthY(); };

	void Save(void);
	static void Loads(void);

	static int GetNumBlock(void);

	static Debug *Getblock(void);

	static CDebug *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY, DEBUG_TYPE type) {
		//�C���X�^���X
		CDebug*pBlock = NULL;
		pBlock = new CDebug(SCENE_NUMBER_TYPE_DEBUG);
		pBlock->Init(pos, move, rot, LengthX, LengthY);
		pBlock->BindTexture(m_pTexture[type]);

		return pBlock;
		//�C���X�^���X
	};


private:
	static LPDIRECT3DTEXTURE9		m_pTexture[DEBUG_TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
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
	static int nNumBlock;
	static Debug m_block[MAX_NUM_DEBUG];
};

#define DEBUG_POLYGON_SIZE (25)
#define	MAX_TypeDEBUG			(4)		// �e�̍ő吔
#define	MAX_DEBUG			(40)		// �e�̍ő吔
#define DEBUG_POS_X			(0)		//�e�̍���X���W
#define DEBUG_POS_Y			(0)		//�e�̍���Y���W
#define DEBUG_HEIGHT			(40)		//�e�̍���
#define DEBUG_WIDTH              (150)
#define DEBUGN_TEXTURE_SPEED	(0.5f)			//�e�A�j���[�V�����X�s�[�h
#define DEBUG_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define DEBUG_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�
#define	DEBUG_CM				(40)//�ǂƂ̋���




#endif