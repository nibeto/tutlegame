//=============================================================================
//
// �����N�̏��� [Rankes.cpp]
// Author :
//
//=============================================================================
#include "Rankes.h"
#include"manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/rank.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_POS_X			(50)							//���_���WX�̈ړ���
#define POLYGON_POS_Y			(50)							//���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��
#define MAX_RANK				(5)								//�ő叇�ʐ�

LPDIRECT3DTEXTURE9 CRankes::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRankes::m_pVtxBuff = NULL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice);
//
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureRank = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3				g_RankPos(0.0f, 0.0f, 0.0f);
//LPDIRECT3DTEXTURE9 CRankes::m_pTexture = NULL;
//LPDIRECT3DVERTEXBUFFER9 CRankes::m_pVtxBuff = NULL;


////=============================================================================
//// ����������
////=============================================================================
//void InitRankes(void)
//{
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// �e�N�X�`���̓ǂݍ���
//	//D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
//	//	TEXTURE_SCORE,		// �t�@�C���̖��O
//	//	&g_pTextureRank);	// �e�N�X�`���ւ̃|�C���^
//
//							// ���_���̍쐬
//	//MakeVertexRankes(pDevice);
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void UninitRankes(void)
//{
//	// �e�N�X�`���̊J��
//	if (g_pTextureRank != NULL)
//	{
//		g_pTextureRank->Release();
//		g_pTextureRank = NULL;
//	}
//
//	// ���_�o�b�t�@�̊J��
//	if (g_pVtxBuffRank != NULL)
//	{
//		g_pVtxBuffRank->Release();
//		g_pVtxBuffRank = NULL;
//	}
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateRankes(void)
//{
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawRankes(void)
//{
////	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int nCntScore;
//
//	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	//pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
//
//	//// ���_�t�H�[�}�b�g�̐ݒ�
//	//pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//// �e�N�X�`���̐ݒ�
//	//pDevice->SetTexture(0, g_pTextureRank);
//
//	// �|���S���̕`��
//
//	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
//	{
//		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		//	0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
//		//	2); //�`�悷��v���~�e�B�u��
//	}
//}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice)
//{
//	// ���_���̍쐬
//	VERTEX_2D *pVtx;
//	int nCntScore;
//	int nPosMove = 0;
//	float fTexTop = 0.0f;
//	float fTexBot = 0.2f;
//
//	g_RankPos.x = 400.0f;
//	g_RankPos.y = 150.0f;
//
//	// ���_�o�b�t�@�𐶐�
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRank,
//		NULL);
//
//	//���_����ݒ�
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
//	{
//		//���_���W
//		pVtx[0].pos = D3DXVECTOR3(g_RankPos.x - POLYGON_POS_X, g_RankPos.y - POLYGON_POS_Y, g_RankPos.z);
//		pVtx[1].pos = D3DXVECTOR3(g_RankPos.x + POLYGON_POS_X, g_RankPos.y - POLYGON_POS_Y, g_RankPos.z);
//		pVtx[2].pos = D3DXVECTOR3(g_RankPos.x - POLYGON_POS_X, g_RankPos.y + POLYGON_POS_Y, g_RankPos.z);
//		pVtx[3].pos = D3DXVECTOR3(g_RankPos.x + POLYGON_POS_X, g_RankPos.y + POLYGON_POS_Y, g_RankPos.z);
//
//		//�e�N�X�`�����W
//		pVtx[0].tex = D3DXVECTOR2(0.0f, fTexTop);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, fTexTop);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, fTexBot);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, fTexBot);
//
//		//���_
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[
//		if (nCntScore == 0)
//		{
//			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
//		}
//		else if (nCntScore == 1)
//		{
//			//���_�J���[
//			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		}
//		else if (nCntScore == 2)
//		{
//			//���_�J���[
//			pVtx[0].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
//		}
//		else
//		{
//			//���_�J���[
//			pVtx[0].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
//		}
//		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
//		fTexTop += 0.2f;
//		fTexBot += 0.2f;
//		g_RankPos.y += 100;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffRank->Unlock();
//}

CRankes::CRankes()
{
}

CRankes::~CRankes()
{
}

HRESULT CRankes::Load(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�w�i.jpg", &m_pTexture);


	return S_OK;
}

void CRankes::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

HRESULT CRankes::Init()
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
	//	TEXTURE_SCORE,		// �t�@�C���̖��O
	//	&g_pTextureRank);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	//MakeVertexRankes(pDevice);

	return S_OK;
}

void CRankes::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

void CRankes::Update(void)
{
}

void CRankes::Draw(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��

	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
	}

}
CRankes * CRankes::Create(void)
{
	CRankes*pRankes = NULL;
	pRankes = new CRankes;
	if (pRankes != NULL)
	{
		pRankes->Init();
	}
	return pRankes;

}

void CRankes::MakeVertexRankes(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	float fTexTop = 0.0f;
	float fTexBot = 0.2f;

	m_RankPos.x = 400.0f;
	m_RankPos.y = 150.0f;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_RankPos.x - POLYGON_POS_X, m_RankPos.y - POLYGON_POS_Y, m_RankPos.z);
		pVtx[1].pos = D3DXVECTOR3(m_RankPos.x + POLYGON_POS_X, m_RankPos.y - POLYGON_POS_Y, m_RankPos.z);
		pVtx[2].pos = D3DXVECTOR3(m_RankPos.x - POLYGON_POS_X, m_RankPos.y + POLYGON_POS_Y, m_RankPos.z);
		pVtx[3].pos = D3DXVECTOR3(m_RankPos.x + POLYGON_POS_X, m_RankPos.y + POLYGON_POS_Y, m_RankPos.z);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, fTexTop);
		pVtx[1].tex = D3DXVECTOR2(1.0f, fTexTop);
		pVtx[2].tex = D3DXVECTOR2(0.0f, fTexBot);
		pVtx[3].tex = D3DXVECTOR2(1.0f, fTexBot);

		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		if (nCntScore == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else if (nCntScore == 1)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntScore == 2)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.7f, 0.2f, 0.2f, 1.0f);
		}
		else
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.3f, 0.3f, 1.0f, 1.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		fTexTop += 0.2f;
		fTexBot += 0.2f;
		m_RankPos.y += 100;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
