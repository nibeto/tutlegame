//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include"main.h"
#include"Scene2D.h"

//�����_�����O�N���X
class CExplosion : public CScene2D
{
public:
	CExplosion(SCENE_NUMBER_TYPE m_Number);
	~CExplosion();

	static HRESULT Load(void);
	static void UnLoad(void);

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 move,float rot, float Length);
	inline static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length) {
		//�C���X�^���X
		CExplosion*pExprosion = NULL;
		//
		pExprosion = new CExplosion(SCENE_NUMBER_TYPE_EXPROSION);
		pExprosion->Init(pos, move, tex, nPattenAnime, rot, Length);
		pExprosion->BindTexture(m_pTexture);
		return pExprosion;

	}
	;

	//void SetTexture(OBJECT_TEXTYPE textype);
private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	int m_nCntExprocion;
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*
	bool m_bjump;
	bool m_bDisp;
	bool bUse;
	int nCountAnime;
	int nPattenAnime;
	D3DXVECTOR3				m_move;						//�ړ���



};

#define	MAX_PLAYER	(1)	// ���@

#define PLAYER_WIDTH			(30)		//�v���C���[�̕�

#define PLAYER_HEIGHT			(30)		//�v���C���[�̍���
#define PLAYER_POS_X			(0)		//�e�̍���X���W
#define PLAYER_POS_Y			(0)		//�e�̍���Y���W
#define	PLAYER_POS_X2			(PLAYER_WIDTH - PLAYER_POS_X / 2)		//�e�̍���X���W
#define PLAYER_POS_Y2			(PLAYER_HEIGHT - PLAYER_POS_Y / 2)		//�e�̍���X���W
#define PLAYER_LONG_X			(PLAYER_WIDTH/2)
#define PLAYER_LONG_Y			(PLAYER_HEIGHT/2)


#endif