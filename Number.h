//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"

#define NUMBER_SIZE		(10)						//�e�̃T�C�Y
#define MAX_NUMBER_LIFE	(50)						//�e�̎���
#define	MAX_NUMBER				(1250)		// �e�̍ő吔
#define NUMBER_POS_X			(0)		//�e�̍���X���W
#define NUMBER_POS_Y			(0)		//�e�̍���Y���W
#define NUMBER_WIDTH			(5)		//�e�̕�
#define NUMBER_HEIGHT			(5)		//�e�̍���
#define NUMBER_POS_X2			(NUMBER_WIDTH - NUMBER_POS_X / 2)		//�e�̍���X���W
#define NUMBER_POS_Y2			(NUMBER_HEIGHT - NUMBER_POS_Y / 2)		//�e�̍���X���W


#define NUMBER_TEXTURE_SPEED	(0.01f)			//�e�A�j���[�V�����X�s�[�h
#define NUMBER_TEXTURE_UV_U		(1.0f)		//�e�A�j���[�V����U�͈�
#define NUMBER_TEXTURE_UV_V		(1.0f)		//�e�A�j���[�V����V�͈�


//�����_�����O�N���X
class CNUmber
{
public:
	CNUmber();
	~CNUmber();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float Length );
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	static CNUmber *Create(D3DXVECTOR3 pos,   float Length,  int nType);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;

};


#endif
