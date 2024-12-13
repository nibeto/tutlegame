//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _3DPLAYER_H_
#define _3DPLAYER_H_
#include"main.h"
#include"Scene3D.h"

//�����_�����O�N���X
class C3DPlayer : public CSCENE3D
{
public:
	C3DPlayer(SCENE_NUMBER_TYPE m_Number);
	~C3DPlayer();
	typedef enum
	{
		PLAYER3D_TYPE_1,
		PLAYER3D_TYPE_2,
		PLAYER3D_TYPE_MAX

	}PLAYER3D_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static C3DPlayer *Create(D3DXVECTOR3 pos, PLAYER3D_TYPE type);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH		m_pMesh;		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;		// �e�N�X�`���ւ̃|�C���^
	static DWORD		m_nNumMat;		// �e�N�X�`���ւ̃|�C���^

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
	int nCountBullet;
	int m_TexType;
	int m_Data = 0;
	char nData[256];

};
#define GRAVITY3D (35.0f)

#define	MAX_PLAYER3D	(1)	// ���@
#define	MAX_TEX_PLAYER3D	(1)	// ���@

#define PLAYER3D_WIDTH			(30)		//�v���C���[�̕�

#define PLAYER3D_HEIGHT			(30)		//�v���C���[�̍���
#define PLAYER3D_POS_X			(0)		//�e�̍���X���W
#define PLAYER3D_POS_Y			(0)		//�e�̍���Y���W
#define	PLAYER3D_POS_X2			(PLAYER3D_WIDTH - PLAYER3D_POS_X / 2)		//�e�̍���X���W
#define PLAYER3D_POS_Y2			(PLAYER3D_HEIGHT - PLAYER3D_POS_Y / 2)		//�e�̍���X���W
#define PLAYER3D_LONG_X			(PLAYER3D_WIDTH/2)
#define PLAYER3D_LONG_Y			(PLAYER3D_HEIGHT/2)


#endif