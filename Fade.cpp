//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Fade.h"
#include"Scene2D.h"
#include"block.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (1.0f)//�� (0�`255)
#define COLOR_G (1.0f)//�� (0�`255)
#define COLOR_B (1.0f)//�� (0�`255)
#define COLOR_A (1.0f)//a =	�����x (0�`255)
#define NUM_POLYGON	(5)

LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;
//=============================================================================
// Create�֐�
//=============================================================================
CFade *CFade::Create(CManeger::MODE modeNext)
{
	CFade*pFade = NULL;
	pFade = new CFade;
	if (pFade != NULL)
	{
		pFade->Init(modeNext);
	}
	return pFade;

}

HRESULT CFade::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�w�i.jpg", &m_pTexture);


	return S_OK;
}
void CFade::UnLoad(void)
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
CFade::CFade()
{//clear�i�N���A�j


}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CFade::Init(CManeger::MODE modeNext)
{
	try
	{

	m_Fade = FADE_IN;
	m_modeNext = modeNext;
	m_Fadecol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);


	m_pos = D3DXVECTOR3(600.0f, 950.0f, 0.0f);

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���āA���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�o�b�t�@�̏���ݒ�

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 190);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)


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
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CFade::Uninit(void)
{
		//���_�o�b�t�@�̔j��
		if (m_pVtxBuff != NULL)
		{
			//m_apScene2D->Uninit();
			m_pVtxBuff->Release();
			m_pVtxBuff = NULL;

		}

}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CFade::Update(void)
{
	try
	{

	// ���_���̍쐬
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	if (m_Fade != FADE_NONE)
	{

		if (m_Fade == FADE_IN)
		{

			m_Fadecol.r = 0.5f;

			m_Fadecol.a -= 0.1f;
			if (m_Fadecol.a <= 0.0f)
			{
				m_Fadecol.r = 0.5f;

				m_Fadecol.a = 0.0f;
				m_Fade = FADE_NONE;

			}
		}
		else if (m_Fade == FADE_OUT)
		{
			//Cblock::Create(D3DXVECTOR3(1150, 600, 0), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f), Cblock::BLOCK_TYPE_TYPE_1, 0.0f, 50.0f, 50.0f);

			m_Fadecol.a += 0.03f;
			if (m_Fadecol.a >= 1.0f)
			{
				m_Fadecol.a = 1.0f;
				m_Fade = FADE_IN;

				CManeger::SetMode(m_modeNext);
			}
		}
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���āA���_�f�[�^�ւ̃|�C���^���擾
													 //���_�J���[�̐ݒ�
		pVtx[0].col = m_Fadecol;
		pVtx[1].col = m_Fadecol;
		pVtx[2].col = m_Fadecol;
		pVtx[3].col = m_Fadecol;

		m_pVtxBuff->Unlock();

	}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CFade::Draw(void)
{

	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//�t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManeger::MODE modeNext)
{
	try
	{

	if (m_Fade == FADE_NONE)
	{
		m_Fade = FADE_OUT;
		m_modeNext = modeNext;
		m_Fadecol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		if (m_modeNext == 0)
		{
			m_Fadecol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f);

		}
		else
		{

			m_Fadecol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);

		}

	}
		}
	catch (const std::exception&)
	{

	}

}
