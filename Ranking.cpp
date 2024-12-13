//=============================================================================
//
// �����L���O�̏��� [Ranking.cpp]
// Author :
//
//=============================================================================
#include "Ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "Rankes.h"
#include "time.h"
#include "RankGata.h"
#include "title.h"
#include"sound.h"
#include"manager.h"
//#include"bg1.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define POLYGON_POS_X			(20)						//���_���WX�̈ړ���
#define POLYGON_POS_Y			(20)						//���_���WY�̈ړ���
#define TEX_POS_X_INIT			(1.0f)						//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)						//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��

LPDIRECT3DTEXTURE9 CRanking::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CRanking::m_pVtxBuff = NULL;

CRankingGata * CRanking::m_pRankingata = NULL;//���U���g
CRankes * CRanking::m_pRankes = NULL;//���U���g
#if 0
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
//int						g_nRanking = 0;					// �X�R�A
//int						g_aScore[MAX_RANKING];
//Ranking					g_aRanking[MAX_RANKING];
//D3DXVECTOR3				g_RankingPos(0.0f, 0.0f, 0.0f);
//int						g_nCounterTimer = 0;
//int						g_nRankNum;
//int						g_nCntRankTimer = 0;
//int						g_RankChange = 0;
//=============================================================================
// ����������
//=============================================================================
//void InitRanking(void)
//{
//	InitRankingGata();
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int pScore;
//	int nScoreChange, nScoreChange2;
//
//	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aRanking[nCntRanking].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//�X�R�A�̎擾
//	//pScore = GetScore();
//
//	g_nRanking = pScore;
//
//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
//	{//�����L���O���X�V
//		if (g_aScore[nCnt] <= g_nRanking)
//		{
//			if (g_aScore[nCnt + 1] >= g_nRanking)
//			{//�����L���O�����ւ�
//			 //�l���Ƃ��Ă���
//				nScoreChange = g_aScore[nCnt];
//				//�Q�[����̃X�R�A����
//				g_aScore[nCnt] = g_nRanking;
//				g_nRankNum = nCnt;
//				//���̃X�R�A���Ƃ��Ă���
//				nScoreChange2 = g_aScore[nCnt - 1];
//				//���̃X�R�A�ɓh��ւ����X�R�A����
//				g_aScore[nCnt - 1] = nScoreChange;
//				//���̃X�R�A��n���Ă���
//				nScoreChange = nScoreChange2;
//				for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
//				{	//�n���ꂽ�X�R�A����
//					nScoreChange2 = nScoreChange;
//					//����ɉ��̃X�R�A���Ƃ��Ă���
//					nScoreChange = g_aScore[nCnt - 1];
//					//���̃X�R�A������ɉ��̃X�R�A�ɑ��
//					g_aScore[nCnt - 1] = nScoreChange2;
//				}
//				break;
//			}
//			if (nCnt == MAX_RANKING - 1)
//			{
//				if (g_aScore[nCnt] <= g_nRanking)
//				{
//					//�l���Ƃ��Ă���
//					nScoreChange = g_aScore[nCnt];
//					//�Q�[����̃X�R�A����
//					g_aScore[nCnt] = g_nRanking;
//					g_nRankNum = nCnt;
//					//���̃X�R�A���Ƃ��Ă���
//					nScoreChange2 = g_aScore[nCnt - 1];
//					//���̃X�R�A�ɓh��ւ����X�R�A����
//					g_aScore[nCnt - 1] = nScoreChange;
//					//���̃X�R�A��n���Ă���
//					nScoreChange = nScoreChange2;
//					for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
//					{	//�n���ꂽ�X�R�A����
//						nScoreChange2 = nScoreChange;
//						//����ɉ��̃X�R�A���Ƃ��Ă���
//						nScoreChange = g_aScore[nCnt - 1];
//						//���̃X�R�A������ɉ��̃X�R�A�ɑ��
//						g_aScore[nCnt - 1] = nScoreChange2;
//					}
//					break;
//				}
//			}
//		}
//	}
//
//	g_nCounterTimer = 0;
//	g_nCntRankTimer = 0;
//	g_RankChange = 0;
//
//
//
//	// �e�N�X�`���̓ǂݍ���
////	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
//	//	TEXTURE_SCORE,							// �t�@�C���̖��O
////		&g_pTextureRanking);					// �e�N�X�`���ւ̃|�C���^
//
//												// ���_���̍쐬
//	//MakeVertexRanking(pDevice);
//
//	InitRankes();
//	//InitPLESENTER();
////	PlaySound(SOUND_LABEL_BGM002);
//	//StopSound(SOUND_LABEL_BGM003);
//	//StopSound(SOUND_LABEL_BGM004);
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void UninitRanking(void)
//{
//	// �e�N�X�`���̊J��
//	if (g_pTextureRanking != NULL)
//	{
//		g_pTextureRanking->Release();
//		g_pTextureRanking = NULL;
//	}
//
//	// ���_�o�b�t�@�̊J��
//	if (g_pVtxBuffRanking != NULL)
//	{
//		g_pVtxBuffRanking->Release();
//		g_pVtxBuffRanking = NULL;
//	}
//	UninitRankingGata();
//	UninitRankes();
//	//UnInitPLESENTER();
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateRanking(void)
//{
//	// ���_���̍쐬
//	VERTEX_2D *pVtx;
//	//FADE fade;
//
//	//fade = GetFade();
//
//	//if (fade != FADE_OUT)
//	{
//
//		//�G���^�[�L�[
//		//if (GetKeyboardTrigger(DIK_RETURN) == true)
//		//{
//		//	PlaySound(SOUND_LABEL_SE_DECIDE);
//		//	StopSound(SOUND_LABEL_BGM002);
//		//	SetFade(MODE_TITLE);
//		//}
//		//g_nCounterTimer++;
//		//if (g_nCounterTimer >= 600)
//		//{
//		////	PlaySound(SOUND_LABEL_SE_DECIDE);
//		//	StopSound(SOUND_LABEL_BGM002);
//
//		//	SetFade(MODE_ENDROOL);
//		//}
//	}
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
//
//
//
//	if (g_nCntRankTimer >= 40)
//	{
//		if (g_RankChange == 0)
//		{
//			g_RankChange = 1;
//
//		}
//		else if (g_RankChange == 1)
//		{
//			g_RankChange = 0;
//
//		}
//		g_nCntRankTimer = 0;
//	}
//	// ���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffRanking->Unlock();
//
//	UpdateRankes();
//	UpdateRankingGata();
//	//UpdatePLESENTER();
//
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawRanking(void)
//{
//	DrawRankingGata();
//
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	int nCntScore;
//
//	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	//pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));
//
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	//pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//// �e�N�X�`���̐ݒ�
//	//pDevice->SetTexture(0, g_pTextureRanking);
//
//	// �|���S���̕`��
//
//	for (nCntScore = 0; nCntScore < 8 * MAX_RANKING; nCntScore++)
//	{
//		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		//	0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
//		//	2); //�`�悷��v���~�e�B�u��
//	}
//
//	DrawRankes();
//	//DrowPLESENTER();
//}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
//{
//	// ���_���̍쐬
//	VERTEX_2D *pVtx;
//	int nCntScore;
//	int nPosMove = 0;
//	int nAnswer = 0;
//	int nKeisan = 1;
//	int nCntRanking;
//
//
//	// ���_�o�b�t�@�𐶐�
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_RANKING,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRanking,
//		NULL);
//
//	//���_����ݒ�
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aRanking[nCntRanking].pos.x = SCREEN_WIDTH / 2 + 150;
//		g_aRanking[nCntRanking].pos.y = 550.0f - (100.0f * nCntRanking);
//
//		for (nCntScore = 0; nCntScore < 8; nCntScore++)
//		{
//			nAnswer = g_aScore[nCntRanking] % (nKeisan * 10) / nKeisan;
//
//			//���_���W
//			pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x - POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//			pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntRanking].pos.x + POLYGON_POS_X, g_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, g_aRanking[nCntRanking].pos.z);
//
//			//�e�N�X�`�����W
//			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);
//
//			//���_
//			pVtx[0].rhw = 1.0f;
//			pVtx[1].rhw = 1.0f;
//			pVtx[2].rhw = 1.0f;
//			pVtx[3].rhw = 1.0f;
//
//			//���_�J���[
//			pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
//
//			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
//			nKeisan *= 10;
//			g_RankingPos.x -= 40;
//			g_aRanking[nCntRanking].pos.x -= 40;
//		}
//		nKeisan = 1;
//	}
//
//	// ���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffRanking->Unlock();
//}
////=============================================================================
//// �����L���O�̎擾
////=============================================================================
//void SetRanking(int nRanking)
//{
//	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
//	{
//		g_aScore[nCntRanking] = nRanking * (1 + nCntRanking);
//	}
//}
#endif
CRanking::CRanking()
{
}

CRanking::~CRanking()
{
}

HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�w�i.jpg", &m_pTexture);

	return S_OK;
}

void CRanking::UnLoad(void)
{

		//�e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}

}

HRESULT CRanking::Init()
{
	m_pRankingata->Init();
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int pScore;
	int nScoreChange, nScoreChange2;

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aRanking[nCntRanking].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//�X�R�A�̎擾
	pScore = 0;

	m_nRanking = pScore;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{//�����L���O���X�V
		if (m_aScore[nCnt] <= m_nRanking)
		{
			if (m_aScore[nCnt + 1] >= m_nRanking)
			{//�����L���O�����ւ�
			 //�l���Ƃ��Ă���
				nScoreChange = m_aScore[nCnt];
				//�Q�[����̃X�R�A����
				m_aScore[nCnt] = m_nRanking;
				m_nRankNum = nCnt;
				//���̃X�R�A���Ƃ��Ă���
				nScoreChange2 = m_aScore[nCnt - 1];
				//���̃X�R�A�ɓh��ւ����X�R�A����
				m_aScore[nCnt - 1] = nScoreChange;
				//���̃X�R�A��n���Ă���
				nScoreChange = nScoreChange2;
				for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
				{	//�n���ꂽ�X�R�A����
					nScoreChange2 = nScoreChange;
					//����ɉ��̃X�R�A���Ƃ��Ă���
					nScoreChange = m_aScore[nCnt - 1];
					//���̃X�R�A������ɉ��̃X�R�A�ɑ��
					m_aScore[nCnt - 1] = nScoreChange2;
				}
				break;
			}
			if (nCnt == MAX_RANKING - 1)
			{
				if (m_aScore[nCnt] <= m_nRanking)
				{
					//�l���Ƃ��Ă���
					nScoreChange = m_aScore[nCnt];
					//�Q�[����̃X�R�A����
					m_aScore[nCnt] = m_nRanking;
					m_nRankNum = nCnt;
					//���̃X�R�A���Ƃ��Ă���
					nScoreChange2 = m_aScore[nCnt - 1];
					//���̃X�R�A�ɓh��ւ����X�R�A����
					m_aScore[nCnt - 1] = nScoreChange;
					//���̃X�R�A��n���Ă���
					nScoreChange = nScoreChange2;
					for (nCnt = nCnt - 1; nCnt >= 0; nCnt--)
					{	//�n���ꂽ�X�R�A����
						nScoreChange2 = nScoreChange;
						//����ɉ��̃X�R�A���Ƃ��Ă���
						nScoreChange = m_aScore[nCnt - 1];
						//���̃X�R�A������ɉ��̃X�R�A�ɑ��
						m_aScore[nCnt - 1] = nScoreChange2;
					}
					break;
				}
			}
		}
	}

	m_nCounterTimer = 0;
	m_nCntRankTimer = 0;
	m_RankChange = 0;



	// �e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
	//	TEXTURE_SCORE,							// �t�@�C���̖��O
	//		&m_pTexture);					// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRanking(pDevice);

	m_pRankes->Init();
	//InitPLESENTER();
	//	PlaySound(SOUND_LABEL_BGM002);
	//StopSound(SOUND_LABEL_BGM003);
	//StopSound(SOUND_LABEL_BGM004);

	return S_OK;
}

void CRanking::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		//m_apScene2D->Uninit();
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}

}

void CRanking::Update(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	//FADE fade;

	//fade = GetFade();

	//if (fade != FADE_OUT)
	{

		//�G���^�[�L�[
		//if (GetKeyboardTrigger(DIK_RETURN) == true)
		//{
		//	PlaySound(SOUND_LABEL_SE_DECIDE);
		//	StopSound(SOUND_LABEL_BGM002);
		//	SetFade(MODE_TITLE);
		//}
		//g_nCounterTimer++;
		//if (g_nCounterTimer >= 600)
		//{
		////	PlaySound(SOUND_LABEL_SE_DECIDE);
		//	StopSound(SOUND_LABEL_BGM002);

		//	SetFade(MODE_ENDROOL);
		//}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);



	if (m_nCntRankTimer >= 40)
	{
		if (m_RankChange == 0)
		{
			m_RankChange = 1;

		}
		else if (m_RankChange == 1)
		{
			m_RankChange = 0;

		}
		m_nCntRankTimer = 0;
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_pRankes->Update();
	m_pRankingata->Update();

}

void CRanking::Draw(void)
{
	m_pRankingata->Draw();

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��

	for (nCntScore = 0; nCntScore < 8 * MAX_RANKING; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0 + (4 * nCntScore),	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
	}

	m_pRankes->Draw();

}

CRanking * CRanking::Create(void)
{
	CRanking*pPreseenter = NULL;
	pPreseenter = new CRanking;
	if (pPreseenter != NULL)
	{
		pPreseenter->Init();
	}
	return pPreseenter;

}

void CRanking::MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntScore;
	int nPosMove = 0;
	int nAnswer = 0;
	int nKeisan = 1;
	int nCntRanking;


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aRanking[nCntRanking].pos.x = SCREEN_WIDTH / 2 + 150;
		m_aRanking[nCntRanking].pos.y = 550.0f - (100.0f * nCntRanking);

		for (nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			nAnswer = m_aScore[nCntRanking] % (nKeisan * 10) / nKeisan;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x - POLYGON_POS_X, m_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[1].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x + POLYGON_POS_X, m_aRanking[nCntRanking].pos.y - POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[2].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x - POLYGON_POS_X, m_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);
			pVtx[3].pos = D3DXVECTOR3(m_aRanking[nCntRanking].pos.x + POLYGON_POS_X, m_aRanking[nCntRanking].pos.y + POLYGON_POS_Y, m_aRanking[nCntRanking].pos.z);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (nAnswer * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (nAnswer * 0.1f), 1.0f);

			//���_
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
			nKeisan *= 10;
			m_RankingPos.x -= 40;
			m_aRanking[nCntRanking].pos.x -= 40;
		}
		nKeisan = 1;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

void CRanking::SetRanking(int nRanking)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_aScore[nCntRanking] = nRanking * (1 + nCntRanking);
	}

}
