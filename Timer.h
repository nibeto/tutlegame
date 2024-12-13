//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include"main.h"
#include"Scene2D.h"
#define MAX_TIMER_TYPE (2)

//�����_�����O�N���X
class CTimer : public CScene2D
{
public:
	CTimer(SCENE_NUMBER_TYPE m_Number);
	~CTimer();
	typedef enum
	{
		TIMER_TYPE_BASE = 0,
		TIMER_TYPE_1,
		TIMER_TYPE_2,
		TIMER_TYPE_MAX

	}TIMER_TYPE;
	typedef enum
	{
		TIMER_BOX_TYPE_BASE = 0,
		TIMER_BOX_TYPE_1,
		TIMER_BOX_TYPE_2,
		TIMER_BOX_TYPE_MAX

	}TIMER_BOX_TYPE;

	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY, TIMER_TYPE type, TIMER_BOX_TYPE nType);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TIMER_TYPE];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	TIMER_BOX_TYPE m_nType;
	int m_nLife = 5;
	int NcuntRot = 0;
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3 m_move;
	float f_rot;
};
#define TIMER_POLYGON_SIZE (25)
#define TIMER_POS_X			(0)		//�e�̍���X���W
#define TIMER_POS_Y			(0)		//�e�̍���Y���W
#define TIMER_WIDTH			(5)		//�e�̕�
#define TIMER_HEIGHT			(5)		//�e�̍���
#define TIMER_POS_X2			(TIMER_POLYGON_SIZE - TIMER_POS_X / 2)		//�e�̍���X���W
#define TIMER_POS_Y2			(TIMER_POLYGON_SIZE - TIMER_POS_Y / 2)		//�e�̍���X���W


#endif