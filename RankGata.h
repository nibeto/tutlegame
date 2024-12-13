//=============================================================================
// ���ƍ쐬
// �����N�̔w�i�̏��� [RankGata.h]
// Author :
//
//=============================================================================
#ifndef _RANKGATA_H_
#define _RANKGATA_H_

class CRankingGata
{
public:
	CRankingGata();
	~CRankingGata();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRankingGata *Create(void);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;

};
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//void InitRankingGata(void);
//void UninitRankingGata(void);
//void UpdateRankingGata(void);
//void DrawRankingGata(void);
#endif