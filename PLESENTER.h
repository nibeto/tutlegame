//=============================================================================
//
// �w�i���� [Parturn.h]
// Author :
//
//=============================================================================
#ifndef _PLESENTER_H_
#define _PLESENTER_H_
#include"main.h"
#include"Scene2D.h"
class CManeger;

#define MAX_PLESENTER	(1)
//�����_�����O�N���X
class CPLESEENTER
{
public:
	CPLESEENTER();
	~CPLESEENTER();
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPLESEENTER *Create(D3DXVECTOR3 pos, float Length, int nType);

private:
	static 	LPDIRECT3DTEXTURE9		m_pTexture[1];		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	float m_fLength;
	int m_nNumber;
	LPDIRECT3DDEVICE9 m_pDevice;
	int nCountBullet;

};
#endif //  _PLESENTER_H
