//=============================================================================
// ���C������ [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_
#define MAX_TEXTURE_RESULT (3)
#define MAX_POLIGON_RESULT (3)

#include"main.h"
#include"manager.h"
class CManeger;
class CFade;
class CGamaClear
{
public:
	typedef enum
	{
		Result_Type_GameCrear,
		Result_Type_MAX
	}Result_Type;
	CGamaClear();
	~CGamaClear();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);


	static CGamaClear *Create(void);
private:
	CManeger::MODE m_mode;
	CFade *m_apfade;

	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXTURE_RESULT];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	CScene2D *m_apScene2D[MAX_POLIGON_RESULT];//�|���S���̐�

	Result_Type Resulttype;
};
#endif