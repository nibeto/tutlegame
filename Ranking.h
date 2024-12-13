//=============================================================================
//
// �����L���O�̏��� [Ranking.h]
// Author :
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#define MAX_RANKING				(5)							//�����L���O�̐�

class CRankes;
class CRankingGata;
class CRankes;

class CRanking
{
public:
	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
							//int nCounterAnim;	//�A�j���[�V�����J�E���^�[
							//int nPatternAnim;	//�A�j���[�V�����p�^�[��No��������
		D3DXCOLOR col;		//�J���[
	}Ranking;
	CRanking();
	~CRanking();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRanking *Create(void);
	void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
	void SetRanking(int nRanking);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	int						m_nRanking = 0;					// �X�R�A
	int						m_aScore[MAX_RANKING];
	Ranking					m_aRanking[MAX_RANKING];
	D3DXVECTOR3				m_RankingPos;
	int						m_nCounterTimer = 0;
	int						m_nRankNum;
	int						m_nCntRankTimer = 0;
	int						m_RankChange = 0;
	static CRankingGata *m_pRankingata;
	static CRankes *m_pRankes;

};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
						//int nCounterAnim;	//�A�j���[�V�����J�E���^�[
						//int nPatternAnim;	//�A�j���[�V�����p�^�[��No��������
	D3DXCOLOR col;		//�J���[
}Ranking;

////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//void InitRanking(void);
//void UninitRanking(void);
//void UpdateRanking(void);
//void DrawRanking(void);
//void SetRanking(int aRanking);
#endif
