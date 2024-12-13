//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"

#define POLYGON_POS_X			(20)							//���_���WX�̈ړ���
#define POLYGON_POS_Y			(20)							//���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define TIME					(60)							//�^�C��


//�����_�����O�N���X
class CNUmber;
class CScene2D;

class CTime : public CScene
{
public:
	CTime();
	~CTime();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTIME(int nValue);
	inline	int GetTime(int nTime);

	static CTime *Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_apScene2D[2];//�|���S���̐�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
	int nScore = 0; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	int m_aScoreDigit[50]; 						//float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p

	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	LPDIRECT3DDEVICE9 pDevice;
	CNUmber *m_apNUMber[MAX_SCORE_DIGIT];
	int	m_nTime;				// �^�C��
	int m_nAnswer = 0;
	int m_nCntTimer;
};
#endif
