
//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _PLAYEROBJ_H_
#define _PLAYEROBJ_H_
#include"main.h"
#include"Scene2D.h"

//�����_�����O�N���X
class CPlayerObj : public CScene2D
{
public:
	CPlayerObj(SCENE_NUMBER_TYPE m_Number);
	~CPlayerObj();
	typedef enum
	{
		PLAYEROBJ_TYPE_1,
		PLAYEROBJ_TYPE_2,
		PLAYEROBJ_TYPE_MAX

	}PLAYEROBJ_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos ,float LengshX,float LengshY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CPlayerObj *Create(D3DXVECTOR3 pos, PLAYEROBJ_TYPE type,float LengshX, float LengshY);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 Posold;//�O��̈ʒu
	D3DXVECTOR3 pMovee;//�ړ��̗�


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
	int m_TexType;
	int m_Data = 0;
	char nData[256];
	int nCountBullet;
	float f_Speed;
	int nPattanAnim;
};
#define GRAVITYOBJ (35.0f)

#define	MAX_PLAYEROBJ	(1)	// ���@
#define	MAX_TEX_PLAYEROBJ	(2)	// ���@

#define PLAYEROBJ_WIDTH			(30)		//�v���C���[�̕�
#define PLAYEROBJ_SIZE			(30)		//�v���C���[�̕�

#define PLAYEROBJ_HEIGHT			(30)		//�v���C���[�̍���
#define PLAYEROBJ_POS_X			(0)		//�e�̍���X���W
#define PLAYEROBJ_POS_Y			(0)		//�e�̍���Y���W
#define	PLAYEROBJ_POS_X2			(PLAYEROBJ_WIDTH - PLAYEROBJ_POS_X / 2)		//�e�̍���X���W
#define PLAYEROBJ_POS_Y2			(PLAYEROBJ_HEIGHT - PLAYEROBJ_POS_Y / 2)		//�e�̍���X���W
#define PLAYEROBJ_LONG_X			(PLAYEROBJ_WIDTH/2)
#define PLAYEROBJ_LONG_Y			(PLAYEROBJ_HEIGHT/2)


#endif