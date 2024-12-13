//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#define MAX_FADE (1)
#include"main.h"
#include"Scene2D.h"
#include"manager.h"
class CManeger;

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;
	CFade();
	~CFade();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(CManeger::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManeger::MODE modeNext);

	static CFade *Create(CManeger::MODE modeNext);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_apScene2D;//�|���S���̐�
	//CManeger *mManeger;
	D3DXCOLOR m_Fadecol;
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;
	CManeger::MODE					m_modeNext;				// ���̃��[�h
	FADE m_Fade;

};
#endif