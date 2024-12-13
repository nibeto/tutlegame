//=============================================================================
//
// �t�H���g���� [font.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

#include"main.h"
#include "scene2D.h"

//*************************************
// �}�N��
//*************************************
#define MAX_FONT			(256)
#define SETFONT_WIDE		(SCREEN_WIDTH * 0.35)
#define SETFONT_HEIGHT		(SCREEN_HEIGHT * 0.4)
#define Font_TextureName	"data/TEXTURE/50��.png"		//50���\
class CManeger;

class CFONT: public CScene
{
public:
	//*************************************
	// �t�H���g�̏��
	//*************************************
	typedef enum
	{//�����̏��
		FONTSTATE_NONE = 0,
		FONTSTATE_DELETE,
		FONTSTATE_RANKDOWN,
		FONTSTATE_RANKSET,		//�����L���O���̃Z�b�g
		FONTSTATE_RANKDELETE,	//�����L���O���̃f���[�g

	}FONTSTATE;

	typedef struct
	{
		FONTSTATE	state;		//�����̏��
		D3DXCOLOR	col;		//�J���[
		RECT		rect;		//�����̕\���͈�
		float		fCntState;	//��ԊǗ��p
		char		aStr[25];	//�����̗�
		char		astr[25];	//�����̗�
		bool		bUse;		//�g�por���g�p
		float fWight;
	}Font;
	CFONT();
	~CFONT();
	static HRESULT Load(void);
	static void UnLoad(void);
	//*****************************************************************************
	// �v���g�^�C�v�錾
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFont(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nNumber, FONTSTATE state,int nCntFont);
	void ChangeFont(bool bUse, const char *aStr, const char *astr, int nNumber, FONTSTATE state);
	void BreakFont(int nNumber);
	void FontTime(int nNumber);
	void FontTimer(int nNumber,int nCntData);
	int *GetSetFont(void);
	static CFONT* Create(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nCntData,int nNumber, FONTSTATE state,bool buse, int nCntFont) {
		//int nAll = m_nNumAll;
		CFONT* PFont = NULL;
		PFont = new CFONT;
		PFont->Init();
		PFont->SetFont(rect, col, aStr, astr, nNumber, state, nCntFont);
		PFont->ChangeFont(buse, aStr, astr, nNumber, state);
		return PFont;
	};

private:
	static	LPDIRECT3DTEXTURE9 m_pTextureFont;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFont = NULL;	//���_BUFFER�ւ̃|�C���^
	LPD3DXFONT			m_pFont0 = NULL;			// �t�H���g�ւ̃|�C���^
	Font				m_Font[MAX_FONT];
	int					m_nSetFont = 0;
	float m_fSpeed = 0.028f;
};



#endif
