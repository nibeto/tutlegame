//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{
#include"score.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bulletNumber.h"
#include"Explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
LPDIRECT3DTEXTURE9 CBulletNUmber::m_pTexture = {};
//=============================================================================
// Create�֐�
//=============================================================================
CBulletNUmber *CBulletNUmber::Create(D3DXVECTOR3 pos, float Length, int nType)
{
	//�C���X�^���X
	CBulletNUmber*pBulletNumber = NULL;

	pBulletNumber = new CBulletNUmber;
	pBulletNumber->Init(pos, Length);
	pBulletNumber->m_nNumber = nType;
	return pBulletNumber;

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
HRESULT CBulletNUmber::Load(void)
{//load//�ǂݍ���
	//if (m_pTexture == NULL)
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		// ���_����ݒ�
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�epoint1.png", &m_pTexture);
	}
	return S_OK;
}
void CBulletNUmber::UnLoad(void)
{//unload//�j��

 //�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBulletNUmber::CBulletNUmber()
{//clear�i�N���A�j
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBulletNUmber::~CBulletNUmber()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CBulletNUmber::Init(D3DXVECTOR3 pos, float Length)
{
	try
	{

	//���_��񐶐�
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �|���S���̈ʒu��������
	m_pos = pos;
	//Length = 0.0f;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�[�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-Length, -Length, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(Length, -Length, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-Length, Length, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(Length, Length, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_R, COLOR_G, COLOR_B, COLOR_A);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j

	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CBulletNUmber::Uninit(void)
{
	//���_���폜
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CBulletNUmber::Update(void)
{

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CBulletNUmber::Draw(void)
{
	try
	{

	//�`��
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//(D3DPT_TRIANGLELIST�v���~�e�B�u�̎��|1�v���~�e�B�u�̐�|&g_aVertex[0]�擪�A�h���X);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	catch (const std::exception&)
	{

	}

}
void CBulletNUmber::SetNumber(int nNumber)
{
	try
	{

	m_nNumber = nNumber;
	//�e�N�X�`���[���W�X�V
	VERTEX_2D* pVtx;
	//�o�b�t�@�[�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(nNumber*0.1f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2((nNumber*0.1f) + 0.1f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(nNumber*0.1f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2((nNumber*0.1f) + 0.1f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j

																//�o�b�t�@�[���A�����b�N
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}


}
