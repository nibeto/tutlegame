
//=============================================================================
// ���C������ [Scene2D.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
#include"main.h"
#include"scene.h"
//�����_�����O�N���X
class CSCENE3D : public CScene
{
public:
	CSCENE3D(LAYER m_Number);
	~CSCENE3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Draw(void);
	void SetCamera(void);

	void SetNOMAL(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXMATRIX mtxWorld);


	D3DXVECTOR3 GetPotion(void);
	D3DXVECTOR3 GetPotionV(void);
	D3DXVECTOR3 GetPotionR(void);
	D3DXVECTOR3 GetPotionU(void);

	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetfRot(void);


	float GetLength(void);
	static CSCENE3D *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);
	void BindModel(LPD3DXBUFFER		pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);

	void Save(void);
	void Load(void);

protected:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	D3DXCOLOR				m_col;

	int m_nCountRot = 0;			//�J�E���^�ϐ�
	float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	float m_fPosSizeX = 0.0f;	//�T�C�Y�ύX�p
	float m_fPosSizeY = 0.0f;	//�T�C�Y�ύX�p
	float m_fPosSizeZ = 0.0f;	//�T�C�Y�ύX�p

	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	int nCountAnime;
	int nCountBg;

	int nPattenAnime;
	bool bUse;
	bool bLand;

	bool m_bjump;
	bool m_bDisp;
	int nCountBullet;
	int m_nPriority;


	float m_fRadius;			// ���a(�傫��)


	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	D3DXVECTOR2				m_tex;
	D3DXVECTOR3	 m_rot;		// �ʏ��� && Pizza��ԏc�̌���(����)

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 m_matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *m_pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
												// ���[���h�}�g���b�N�X�̏�����

	D3DXVECTOR3  m_posOld;	// �ߋ��̈ʒu
	D3DXMATRIX	 m_mtxWorld;	// ���[���h�}�g���b�N�X
	LPD3DXMESH	 m_pMesh = NULL; 	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	DWORD		m_nNumMat;	// �}�e���A���̏��
	int		nIdyShadow;		// �e�̔ԍ�
	float fXaxis;			// X��
	float fZaxis;			// Z��

	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//���ӓ_
	D3DXVECTOR3 m_vecU;				//������x�N�g��

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;				//�r���[�}�g���b�N�X

	float m_Bt0 = 43.5f;//�g��k��
	SCENE_NUMBER_TYPE m_nNumber3D;//�`�揇��
	LAYER m_layer3D;



private:

};
#endif
