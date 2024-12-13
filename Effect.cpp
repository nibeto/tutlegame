//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{

#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Effect.h"
#include"Explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = {};
//=============================================================================
// ���C���֐�
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA, float rot, float LengthX,float LengthY , float Radius, EFFECT_TYPE type, int nType)
{
	//�C���X�^���X
	CEffect*pEffect = NULL;
	//
	pEffect = new CEffect(SCENE_NUMBER_TYPE_EFFECT);
	pEffect->Init(pos, move, colR,colG,colB,colA, rot,LengthX, LengthY, Radius,type);
	pEffect->BindTexture(m_pTexture);
	pEffect->m_TypeEffect = nType;
	return pEffect;

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
HRESULT CEffect::Load(void)
{//load//�ǂݍ���
	if (m_pTexture == NULL)
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		// ���_����ݒ�
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture);
	}
	return S_OK;
}
void CEffect::UnLoad(void)
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
CEffect::CEffect(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_EFFECT) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;

	m_bDisp = true;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float colR, float colG, float colB, float colA, float rot, float LengthX, float LengthY, float Radius, EFFECT_TYPE type)
{
	try
	{
	CScene2D::Init();
	D3DXVECTOR2 tex;

	mf_pos = 5;//pos�̏������̕ϐ�
	SetEffect(pos, tex,move, colR, colG, colB, colA,rot, LengthX, LengthY,Radius);   //Length = 5;
	SetPosition(pos, move, rot, LengthX, LengthX);
	m_bDisp = true;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	//m_fPosSize = Length;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_fRadius = Radius;
	SetOBJTYPE(OBJECT_TYPE_BULLET);
	Save();
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
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CEffect::Update(void)
{
	try
	{

	m_nCountEffect++;
	//pos
	D3DXVECTOR3 pos;
	//move(�ړ���)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	EFFECT_TYPE type = EFFECT_TYPE_MAX;
	D3DXCOLOR col;
	//X�̈ړ�//Y�̈ړ�
	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot;
	//pos���擾
	pos = GetPotion();
	//move���擾
	move = GetMove();
	//pos�̃T�C�Y���擾
	m_fPosSize = GetLength();
	//�A�[�N�^���W�F���g
	fRot = atan2f(fMoveX, fMoveY);
	//move�ňړ�
	m_fRadius -= 1.0f; //���Z
	pos += move;
	move *= 0.1f;
	CScene2D::SetEffect(pos, tex,move,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, m_fPosSizeX, m_fPosSizeX, m_fRadius);

	//pos��Get
	GetPotion();
	//Move��Get
	GetMove();
	//Length��Get
	GetLength();
	GetCol();

	CManeger::MODE m_mode = CManeger::GetMode();

	if (m_mode == CManeger::MODE_RESULT || m_mode == CManeger::MODE_TITLE)
	{
		Uninit();
	}

	if (m_nCountEffect % 15 == 0)
	{

		Uninit();

	}

	//CSCENE2D���擾
	CScene2D::Update();
	if (m_TypeEffect == 0)
	{

		if (pos.y - EFFECT_POS_Y2 < 0 || pos.x - EFFECT_POS_X2 <0 || pos.x - EFFECT_POS_X2 > SCREEN_WIDTH || pos.y - EFFECT_POS_Y2 > SCREEN_HEIGHT / 2)
		{

			Uninit();





		}


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
void CEffect::Draw(void)
{
	try
	{

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CScene2D::Draw();
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	catch (const std::exception&)
	{

	}

}

void CEffect::Loads(void)
{
	try
	{

	FILE *pFile;


	pFile = fopen("Effects.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}
	}
	catch (const std::exception&)
	{

	}

}
void CEffect::Save(void)
{
	try
	{

	//seve
	FILE *pFile;


	pFile = fopen("Effects.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}
	}
	catch (const std::exception&)
	{

	}

}
