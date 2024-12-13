//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _BULLETLIFE_H_
#define _BULLETLIFE_H_
#include"main.h"
#include"Scene2D.h"
class CBulletNUmber;
class CScene2D;

class CBulletLife : public CScene
{
public:
	CBulletLife();
	~CBulletLife();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddBulletLife(int nValue);
	int GetScoer(void);

	static CBulletLife *Create(void);
private:
	//CNumber * m_apNumBer[1000000];
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_apScene2D[2];//�|���S���̐�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
	int nScore = 0; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	int m_aScoreDigit[1250]; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p

	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	LPDIRECT3DDEVICE9 pDevice;
	CBulletNUmber *m_apBulletNUMber[MAX_BULLETLIFE_DIGIT];
};
#define SCORE_SIZE (15.0f)//�X�R�A�̃T�C�Y
#define SCORE_POS_X	(1250)//�X�R�A�̕�
#define SCORE_POS_Y	(50)//�X�R�A�̍���

#endif