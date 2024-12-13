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
#include"pauseselect.h"
#include"Explosion.h"
#include"Fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define PAUSESELECT_POS_X			(200)						//���_���WX�̈ړ���
#define PAUSESELECT_POS_Y			(50)						//���_���WY�̈ړ���
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
LPDIRECT3DTEXTURE9 CPAUSESELECT::m_pTexture[PAUSESERECT_TEXTURE] = {};
//=============================================================================
// ���C���֐�
//=============================================================================
CPAUSESELECT *CPAUSESELECT::Create(D3DXVECTOR3 pos, float Length, int nType)
{
	//�C���X�^���X
	CPAUSESELECT*pNumber = NULL;
	//
	pNumber = new CPAUSESELECT;
	pNumber->Init(pos, Length);
	pNumber->m_nNumber = nType;
	return pNumber;

}
//=============================================================================
//�R���X�g���N�^
//=============================================================================
HRESULT CPAUSESELECT::Load(void)
{//load//�ǂݍ���
	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{

		if (m_pTexture[nCnt] == NULL)
		{
			CRenderer *pRenderer = CManeger::GetRenderer();
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
			// ���_����ݒ�
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[1]);
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block11.jpg", &m_pTexture[2]);

		}
	}
	return S_OK;
}
void CPAUSESELECT::UnLoad(void)
{//unload//�j��
	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPAUSESELECT::CPAUSESELECT()
{//clear�i�N���A�j
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPAUSESELECT::~CPAUSESELECT()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CPAUSESELECT::Init(D3DXVECTOR3 pos, float Length)
{
	try
	{

	//���_��񐶐�
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �|���S���̈ʒu��������
	m_pos = pos;
	float fMenuPosY = 0;
	m_nSelect = 0;
	m_PauseMenuPos = m_pos+D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SelectMode = SELECTMODE_NONE;

	m_aPauseMenu[0].pos = m_pos+D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
	m_aPauseMenu[0].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	m_aPauseMenu[0].select = SELECTTYPE_SELECT;
	fMenuPosY += 150;
	for (int nCnt = 1; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		m_aPauseMenu[nCnt].pos = m_pos+D3DXVECTOR3(650.0f, 200.0f + (fMenuPosY), 0.0f);
		m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aPauseMenu[nCnt].select = SELECTTYPE_NONE;
		fMenuPosY += 150;
	}


												// ���_���̍쐬
	MakeVertexPauseSelect(pDevice);

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
void CPAUSESELECT::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

	}
}
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CPAUSESELECT::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CFade *pFade = CManeger::GetFade();
	CFade::FADE  m_fade = pFade->FADE_MAX;
	CManeger::MODE m_mode = CManeger::GetMode();

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 1) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;

	}
	if (pInputKeyboard->GetTrigger(DIK_UP) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 2) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;

	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 1) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}
	if (pInputKeyboard->GetTrigger(DIK_W) == true && m_fade == pFade->FADE_NONE)
	{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 2) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}


	//�G���^�[�L�[
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_fade == pFade->FADE_NONE)
	{
		if (m_nSelect == 0)
		{
			//PlaySound(SOUND_LABEL_SE_CANCEL);
			m_SelectMode = SELECTMODE_CONTINUE;
		}
		else if (m_nSelect == 1)
		{
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			m_SelectMode = SELECTMODE_RETRY;
		}
		else if (m_nSelect == 2)
		{
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			m_SelectMode = SELECTMODE_QUIT;
		}


		switch (m_SelectMode)
		{
		case SELECTMODE_CONTINUE:
		{
			break;
		}
		case SELECTMODE_RETRY:
		{
			pFade->SetFade(CManeger::MODE_GAME);
			break;
		}
		case SELECTMODE_QUIT:
		{
			pFade->SetFade(CManeger::MODE_TITLE);
			break;
		}
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_P) == true && m_fade == pFade->FADE_NONE)
	{
			m_nSelect = 0;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
			m_aPauseMenu[1].select = SELECTTYPE_NONE;
			m_aPauseMenu[2].select = SELECTTYPE_NONE;

	}

	for (int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		if (m_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
		{//�I�𒆂̐F
			m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{//���I���̐F
			m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//���_�J���[
		pVtx[0].col = m_aPauseMenu[nCnt].col;
		pVtx[1].col = m_aPauseMenu[nCnt].col;
		pVtx[2].col = m_aPauseMenu[nCnt].col;
		pVtx[3].col = m_aPauseMenu[nCnt].col;
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
		}
		catch (const std::exception&)
		{

		}

}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CPAUSESELECT::Draw(void)
{
	try
	{

	//�`��
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for ( int nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0 + (4 * nCnt),	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
	}
	catch (const std::exception&)
	{

	}

}
void CPAUSESELECT::MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	try
	{

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCnt;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSESERECT_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_����ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//���_���W
		pVtx[0].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = m_aPauseMenu[m_nSelect].col;
		pVtx[1].col = m_aPauseMenu[m_nSelect].col;
		pVtx[2].col = m_aPauseMenu[m_nSelect].col;
		pVtx[3].col = m_aPauseMenu[m_nSelect].col;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}
void CPAUSESELECT::SetPauseSelect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	try
	{

	int nCnt;
	float fMenuPosY = 0;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
					//���_����ݒ�
					//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < PAUSESERECT_TEXTURE; nCnt++)
	{
		//���_���W
		pVtx[0].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[1].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y - PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[2].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x - PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		pVtx[3].pos = m_pos+D3DXVECTOR3(m_aPauseMenu[nCnt].pos.x + PAUSESELECT_POS_X, m_aPauseMenu[nCnt].pos.y + PAUSESELECT_POS_Y, m_aPauseMenu[nCnt].pos.z);
		m_aPauseMenu[nCnt].pos = pos;
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		m_aPauseMenu[nCnt].col = col;

		fMenuPosY += 100;

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	}
	catch (const std::exception&)
	{

	}

}

