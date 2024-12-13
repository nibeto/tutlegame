//=============================================================================
//
// �w�i����[Parturn.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "PLESENTER.h"
#include"manager.h"
//=============================================================================
//�|���S������������
//=============================================================================
LPDIRECT3DTEXTURE9 CPLESEENTER::m_pTexture[MAX_PLESENTER] = {};
LPDIRECT3DVERTEXBUFFER9 CPLESEENTER::m_pVtxBuff = NULL;
//=============================================================================
// Create�֐�
//=============================================================================
CPLESEENTER *CPLESEENTER::Create(D3DXVECTOR3 pos, float Length, int nType)
{
	CPLESEENTER*pPreseenter = NULL;
	pPreseenter = new CPLESEENTER;
	if (pPreseenter != NULL)
	{
		pPreseenter->Init();
	}
	return pPreseenter;

}
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPLESEENTER::CPLESEENTER()
{//clear�i�N���A�j


}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPLESEENTER::~CPLESEENTER()
{

}

HRESULT CPLESEENTER::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�w�i.jpg", &m_pTexture[0]);


	return S_OK;
}
void CPLESEENTER::UnLoad(void)
{//unload//�j��
	try
	{

	for (int nCuntData = 0; nCuntData < MAX_PLESENTER; nCuntData++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nCuntData] != NULL)
		{
			m_pTexture[nCuntData]->Release();
			m_pTexture[nCuntData] = NULL;
		}
	}
	}
	catch (const std::exception&)
	{

	}

}

HRESULT CPLESEENTER::Init()
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//g_nPurturn = 0;
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���āA���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos+D3DXVECTOR3(720, 620, 0.0f);
	pVtx[1].pos = m_pos+D3DXVECTOR3(1120, 620, 0.0f);
	pVtx[2].pos = m_pos+D3DXVECTOR3(720, 725, 0.0f);
	pVtx[3].pos = m_pos+D3DXVECTOR3(1120, 725, 0.0f);

	//rhw�̐ݒ�5
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 250);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)


													  //�e�N�X�`�����W�̐ݒ�
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

void CPLESEENTER::Uninit(void)
{
	try
	{

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		//m_apScene2D->Uninit();
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}
	}
	catch (const std::exception&)
	{

	}


}
void CPLESEENTER::Update(void){}

void CPLESEENTER::Draw(void)
{
	try
	{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCuntData = 0; nCuntData < MAX_PLESENTER; nCuntData++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCuntData]);

		//(D3DPT_TRIANGLELIST�v���~�e�B�u�̎��|1�v���~�e�B�u�̐�|&g_aVertex[0]�擪�A�h���X);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCuntData, 2);



	}

	}
	catch (const std::exception&)
	{

	}

}

