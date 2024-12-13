//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#include"main.h"
#include"Scene2D.h"

class CBg : public CScene
{
public:
	CBg();
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	static CBg *Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_apScene2D[2];//�|���S���̐�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
									//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*


};


#define	MAX_PLAYER	(1)	// ���@
#define	MAX_BG_TEX	(2)	// ���@

#define PLAYER_WIDTH			(30)		//�v���C���[�̕�

#define PLAYER_HEIGHT			(30)		//�v���C���[�̍���
#define PLAYER_POS_X			(0)		//�e�̍���X���W
#define PLAYER_POS_Y			(0)		//�e�̍���Y���W
#define	PLAYER_POS_X2			(PLAYER_WIDTH - PLAYER_POS_X / 2)		//�e�̍���X���W
#define PLAYER_POS_Y2			(PLAYER_HEIGHT - PLAYER_POS_Y / 2)		//�e�̍���X���W
#define PLAYER_LONG_X			(PLAYER_WIDTH/2)
#define PLAYER_LONG_Y			(PLAYER_HEIGHT/2)


#endif