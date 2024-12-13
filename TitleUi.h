//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_
#include"main.h"
#include"Scene2D.h"

class CTitleUi : public CScene
{
public:
	CTitleUi();
	~CTitleUi();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	static CTitleUi *Create(void);
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


#define	MAX_TITLEUI	(1)	// ���@
#define	MAX_TITLEUI_TEX	(2)	// ���@

#define TITLEUI_WIDTH			(30)		//�v���C���[�̕�
#define TITLEUI_HEIGHT			(30)		//�v���C���[�̍���
#define TITLEUI_POS_X			(0)		//�e�̍���X���W
#define TITLEUI_POS_Y			(0)		//�e�̍���Y���W
#define	TITLEUI_POS_X2			(TITLEUI_WIDTH - TITLEUI_POS_X / 2)		//�e�̍���X���W
#define TITLEUI_POS_Y2			(TITLEUI_HEIGHT - TITLEUI_POS_Y / 2)		//�e�̍���X���W
#define TITLEUI_LONG_X			(TITLEUI_WIDTH/2)
#define TITLEUI_LONG_Y			(TITLEUI_HEIGHT/2)


#endif