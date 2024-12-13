//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _WEAPONS_H_
#define _WEAPONS_H_
#include"main.h"
#include"Scene2D.h"

//�����_�����O�N���X
class CWeapons : public CScene2D
{
public:
	CWeapons(SCENE_NUMBER_TYPE m_Number);
	~CWeapons();
	typedef enum
	{
		WEAPONS_TYPE_1 = 0,
		WEAPONS_TYPE_2,
		WEAPONS_TYPE_MAX

	}WEAPONS_TYPE;
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Loads(void);

	static CWeapons *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,WEAPONS_TYPE type, float rot, float Length);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 Posold;//�O��̈ʒu
	D3DXVECTOR3 pMovee;//�ړ��̗�


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
	D3DXVECTOR3 m_move;
	int nPattenAnime;

};

#define	MAX_WEAPONS	(1)	// ���@
#define	MAX_TEX_WEAPONS	(2)	// ���@

#define WEAPONS_WIDTH			(30)		//�v���C���[�̕�

#define WEAPONS_HEIGHT			(30)		//�v���C���[�̍���
#define WEAPONS_POS_X			(0)		//�e�̍���X���W
#define WEAPONS_POS_Y			(0)		//�e�̍���Y���W
#define	WEAPONS_POS_X2			(WEAPONS_WIDTH - WEAPONS_POS_X / 2)		//�e�̍���X���W
#define WEAPONS_POS_Y2			(WEAPONS_HEIGHT - WEAPONS_POS_Y / 2)		//�e�̍���X���W
#define WEAPONS_LONG_X			(WEAPONS_WIDTH/2)
#define WEAPONS_LONG_Y			(WEAPONS_HEIGHT/2)


#endif