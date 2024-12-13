//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _LEVEL_H_
#define _LEVEL_H_
#include"main.h"
#include"Scene2D.h"
class CNUmber;
class CScene2D;
#define MAX_LEVEL_TEXTUR (2)
#define MAX_LEVEL_DIGIT (3)
class CLevel : public CScene
{
public:
	CLevel();
	~CLevel();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLevel(int nValue);
	int GetLevel(void);

	static CLevel *Create(void);
private:
	//CNumber * m_apNumBer[1000000];
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LEVEL_TEXTUR];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_apScene2D[2];//�|���S���̐�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
	int nLevel = 0; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	int m_aScoreDigit[1250]; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p

	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	LPDIRECT3DDEVICE9 pDevice;
	CNUmber *m_apNUMber[MAX_LEVEL_DIGIT];
};
#define LEVEL_SIZE (15.0f)//�X�R�A�̃T�C�Y
#define LEVEL_POS_X	(1250)//�X�R�A�̕�
#define LEVEL_POS_Y	(50)//�X�R�A�̍���

#endif