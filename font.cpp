//=========================================================================================================//
//
// �w�i���� [font.cpp]
// Author :moritakamasaya
//
//=========================================================================================================//
#include"font.h"
#include "Manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>//I/O stream
#include <random>
#include "renderer.h"

LPDIRECT3DTEXTURE9 CFONT::m_pTextureFont = NULL;
//=========================================================================================================//
// �R���X�g���N�^
//=========================================================================================================//
CFONT::CFONT() :CScene(SCENE_NUMBER_TYPE_FONT)
{

}
//=========================================================================================================//
// �f�X�g���N�^
//=========================================================================================================//
CFONT::~CFONT()
{

}
HRESULT CFONT::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, Font_TextureName, &m_pTextureFont);


	return S_OK;
}
void CFONT::UnLoad(void)
{//unload//�j��
 //�e�N�X�`���̔j��
	if (m_pTextureFont != NULL)
	{
		m_pTextureFont->Release();
		m_pTextureFont = NULL;
	}

}
//=========================================================================================================//
// ����������
//=========================================================================================================//
HRESULT CFONT::Init(void)
{
	try
	{

	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		//g_Font[nCntFont].rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		m_Font[nCntFont].bUse = false;
	}

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuffFont,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);		//X,Y,0.0f
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);	// A = �����x
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//���_BUFFER���A�����b�N����
	m_pVtxBuffFont->Unlock();

	D3DXCreateFont(pDevice, 40, 12, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont0);
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
//=========================================================================================================//
// �I������
//=========================================================================================================//
void CFONT::Uninit(void)
{
	if (m_pFont0 != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		m_pFont0->Release();
		m_pFont0 = NULL;
	}
}
//=========================================================================================================//
// �X�V����
//=========================================================================================================//
void CFONT::Update(void)
{
	try
	{

	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (m_Font[nCntFont].bUse == true)
		{//�������\����ԂȂ�
			switch (m_Font[nCntFont].state)
			{
			case FONTSTATE_RANKDOWN://������
				m_Font[nCntFont].fCntState += m_fSpeed;
				m_Font[nCntFont].rect.top += 3;
				m_Font[nCntFont].rect.bottom += 3;
				if (m_Font[nCntFont].fCntState >= 1.0f)
				{
					m_Font[nCntFont].fCntState = 0.0f;
					m_Font[nCntFont].state = FONTSTATE_NONE;
				}
				break;

			case FONTSTATE_DELETE://������Ȃ��������
				m_Font[nCntFont].col.a -= 0.028f;
				m_Font[nCntFont].rect.top += 3;
				m_Font[nCntFont].rect.bottom += 3;
				if (m_Font[nCntFont].col.a <= 0.0f)
				{
					m_Font[nCntFont].bUse = false;
				}
				break;

			case FONTSTATE_RANKSET:
				m_Font[nCntFont].col.a += 0.029f;
				m_Font[nCntFont].rect.left -= 5;
				m_Font[nCntFont].rect.right -= 5;
				if (m_Font[nCntFont].col.a >= 1.0f)
				{
					m_Font[nCntFont].col.a = 1.0f;
					m_Font[nCntFont].state = FONTSTATE_NONE;
				}
				break;

			case FONTSTATE_RANKDELETE:
				m_Font[nCntFont].col.a -= 0.029f;
				m_Font[nCntFont].rect.left -= 5;
				m_Font[nCntFont].rect.right -= 5;
				if (m_Font[nCntFont].col.a <= 0.0f)
				{
					m_Font[nCntFont].col.a = 0.0f;
					m_Font[nCntFont].bUse = false;
				}
				break;

			default:
				break;
			}
		}
	}
	}
	catch (const std::exception&)
	{

	}

}

//=========================================================================================================//
// �`�揈��
//=========================================================================================================//
void CFONT::Draw(void)
{
	try
	{

	int nCntFont;

	if (m_nSetFont != 0)
	{//50���\�\��
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, (m_nSetFont - 1.0f) * 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, (m_nSetFont - 1.0f) * 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, m_nSetFont * 0.5f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, m_nSetFont * 0.5f);

		//���_BUFFER���A�����b�N����
		m_pVtxBuffFont->Unlock();

		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


		//���_BUFFER���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuffFont, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

										//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTextureFont);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	try
	{

		//�e�L�X�g�`��
		//hDC      : //�f�o�C�X�R���e�L�X�g�̃n���h��
		//lpString : //�`�悷�镶����ւ̃|�C���^
		//nCount   : //������̕�����
		//lpRect   : //�����`�̈�
		//uFormat  : //�e�L�X�g�̐��`���@���w��
		if (m_pFont0 != NULL)
		{
			for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
			{
				if (m_Font[nCntFont].bUse == true)
				{// ��������� �\��
					m_pFont0->DrawText(NULL, &m_Font[nCntFont].aStr[0], -1, &m_Font[nCntFont].rect, DT_LEFT, m_Font[nCntFont].col);
					//m_pFont0->DrawText(NULL, &m_Font[nCntFont].astr[0], -1, &m_Font[nCntFont].rect, DT_LEFT, m_Font[nCntFont].col);
				}
			}
		}
	}
	catch (const std::exception&)
	{

	}

	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// �����������  Set!!
//=========================================================================================================//
void CFONT::SetFont(RECT rect, D3DXCOLOR col, const char *aStr, const char *astr, int nNumber, FONTSTATE state, int nCntFont)
{//�����Z�b�g
	try
	{

	m_Font[nNumber].bUse = true;
	m_Font[nNumber].state = state;
	m_Font[nNumber].rect = rect;
	strcpy(&m_Font[nNumber].aStr[0], &aStr[0]);
	//strcat(&m_Font[nNumber].astr[nCntFont], &astr[nCntFont]);
	m_Font[nNumber].col = col;
	m_Font[nNumber].fCntState = 0.0f;
	m_Font[nNumber].fWight = 5.0f;
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// �����������  Change!!
//=========================================================================================================//
void CFONT::ChangeFont(bool bUse, const char *aStr, const char *astr,int nNumber, FONTSTATE state)
{//�Z�b�g���ꂽ���̂�ύX
	try
	{

	m_Font[nNumber].bUse = bUse;
	m_Font[nNumber].state = state;
	if (aStr[0] != NULL) { strcpy(&m_Font[nNumber].aStr[0], &aStr[0]); }//NULL����Ȃ���΍X�V
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// ������S�Ĕj��
//=========================================================================================================//
void CFONT::BreakFont(int nNumber)
{//�Z�b�g���ꂽ���������ׂĔj��
	try
	{

	int nCntFont = nNumber;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		m_Font[nCntFont].bUse = false;
	}
	}
	catch (const std::exception&)
	{

	}

}
void CFONT::FontTime(int nNumber)
{
	try
	{

	m_Font[nNumber / 10];
	}
	catch (const std::exception&)
	{

	}

}
void CFONT::FontTimer(int nNumber, int nCntData)
{
	try
	{

	m_Font[nNumber / nCntData];
	}
	catch (const std::exception&)
	{

	}

}
//=========================================================================================================//
// �Z�b�g����Ă���50���̎擾
//=========================================================================================================//
int *CFONT::GetSetFont(void)
{
	try
	{

	return &m_nSetFont;
	}
	catch (const std::exception&)
	{

	}

}

