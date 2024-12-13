//=============================================================================
//
// �|�[�Y���j���[���� [pauseselect.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include"Scene2D.h"

#define PAUSESERECT_TEXTURE (3)
//�����_�����O�N���X
class CPAUSESELECT
{
public:
	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	typedef enum
	{
		SELECTMODE_NONE = 0,
		SELECTMODE_CONTINUE,		//���s���
		SELECTMODE_RETRY,			//���g���C���
		SELECTMODE_QUIT,			//�I��
		SELECTMODE_MAX				//��Ԃ̑���
	}SELECTMODE;						//�񋓌^

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
		SELECTTYPE_SELECT,		//�I�΂�Ă���	���
		SELECTTYPE_MAX				//��Ԃ̑���
	}SELECT;

	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR	col;		//�J���[
	}PAUSESELECT;

	CPAUSESELECT();
	~CPAUSESELECT();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, float Length);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);
	void SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col);


	static CPAUSESELECT *Create(D3DXVECTOR3 pos, float Length, int nType);
	inline	SELECTMODE *GetPauseMode(void) { return &m_SelectMode; };


private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[PAUSESERECT_TEXTURE];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;
	LPDIRECT3DTEXTURE9		m_pTexturePauseSelect[PAUSESERECT_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPauseSelect = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	PAUSESELECT				m_aPauseMenu[PAUSESERECT_TEXTURE];					// �|�[�Y���j���[
	D3DXVECTOR3				m_PauseMenuPos;
	SELECTMODE				m_SelectMode = SELECTMODE_NONE;
	int						m_nSelect;

};
#endif