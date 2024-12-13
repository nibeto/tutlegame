//=============================================================================
//// �����N�̔w�i�̏��� [Rankgata.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "RankGata.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURENAME		"data/TEXTURE/block.jpg"//�e�N�X�`���̃t�@�C����
#define POS_X				(0)							//������WX
#define POS_Y				(0)							//������WY
#define BG_WIDTH			(SCREEN_WIDTH)				//�����`�̉������W
#define BG_HEIGHT			(SCREEN_HEIGHT)				//�����`�̏c�����W
#define COUNTER_ANIM_RESET	(200)						//�A�j���[�V�������Z�b�g�J�E���g
#define TEX_POS_X_INIT		(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT		(0.005f)					//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT			(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT			(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT				(1.0f)						//�e�N�X�`�����WV��
LPDIRECT3DTEXTURE9 CRankingGata::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRankingGata::m_pVtxBuff = NULL;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;		//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
////*****************************************************************************
//// �|���S��
////*****************************************************************************
//void InitRankingGata(void)
//{	//���[�J���ϐ�
//	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
//	CRenderer *pRenderer = CManeger::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	////�e�N�X�`���̓ǂݍ���
//	//D3DXCreateTextureFromFile(pDevice,
//	//	BG_TEXTURENAME,
//	//	&g_pTextureRankingBG);
//
//	////���_�o�b�t�@�̐���
//	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
//	//	D3DUSAGE_WRITEONLY,
//	//	FVF_VERTEX_2D,
//	//	D3DPOOL_MANAGED,
//	//	&g_pVtxBuffRankingBG,
//	//	NULL);
//
//	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
//	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);
//	//���_���W
//	pVtx[0].pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, POS_Y, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(POS_X, BG_HEIGHT, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
//	//�e�N�X�`�����W
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//	//���_
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//	//���_�J���[
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffRankingBG->Unlock();
//}
////=============================================================================
//// �I������
////=============================================================================
//void UninitRankingGata(void)
//{	//�e�N�X�`���̔j��
//	if (g_pTextureRankingBG != NULL)
//	{
//		g_pTextureRankingBG->Release();
//		g_pTextureRankingBG = NULL;
//	}
//	//���_�o�b�t�@�̔j���̔j��
//	if (g_pVtxBuffRankingBG != NULL)
//	{
//		g_pVtxBuffRankingBG->Release();
//		g_pVtxBuffRankingBG = NULL;
//	}
//}
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateRankingGata(void)
//{
//}
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawRankingGata(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	////�f�o�C�X���擾����
//	//pDevice = GetDevice();
//	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	//pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));
//	////���_�t�H�[�}�b�g��ݒ�
//	//pDevice->SetFVF(FVF_VERTEX_2D);
//	////�e�N�X�`���̐ݒ�
//	//pDevice->SetTexture(0, g_pTextureRankingBG);
//	////�|���S���̕`��
//	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//	//	0,	//�J�n���钸�_�̃C���f�b�N�X
//	//	2); //�`�悷��v���~�e�B�u��
//}

CRankingGata::CRankingGata()
{
}

CRankingGata::~CRankingGata()
{
}

HRESULT CRankingGata::Load(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�w�i.jpg", &m_pTexture);


	return S_OK;
}

void CRankingGata::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

HRESULT CRankingGata::Init()
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	BG_TEXTURENAME,
	//	&g_pTextureRankingBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(POS_X, POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CRankingGata::Uninit(void)
{
	//���_�o�b�t�@�̔j���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

void CRankingGata::Update(void)
{
}

void CRankingGata::Draw(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

}

CRankingGata * CRankingGata::Create(void)
{
	CRankingGata*pRankingGata = NULL;
	pRankingGata = new CRankingGata;
	if (pRankingGata != NULL)
	{
		pRankingGata->Init();
	}
	return pRankingGata;

}