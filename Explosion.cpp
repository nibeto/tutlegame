//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = {};
//CInputKeyboard pInput;
bool  g_bDeleateExprosion = true;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
HRESULT CExplosion::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}
void CExplosion::UnLoad(void)
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
CExplosion::CExplosion(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_EXPROSION) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
void CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 tex, int nPattenAnime, float rot, float Length)
{
	CScene2D::Init();
	SetPosition(pos,m_move,rot,m_fPosSizeX,m_fPosSizeX);
	SetAnimation(0.125f, 1.0f);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSizeX = Length;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeX = 55.0f;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeY = 55.0f;//�e�̑傫���̃����o�ϐ�

}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CExplosion::Update(void)
{
	try
	{
	int nLife = 0;
	int nCntAnime = 0;
	nCntAnime++;
	D3DXVECTOR3 pos;
	//move(�ړ���)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	m_nCntExprocion++;
	//pos���擾
	pos = GetPotion();
	//move���擾
	m_move = GetMove();
	bool bRelease = true;

	nCountAnime++;

	if (nCountAnime % 8 == 0)
	{
		nPattenAnime++;

		//nPattenAnime = (nPattenAnime + 1) % 8;

	}

	if (nPattenAnime >= 8)
	{

		nPattenAnime = 0;
		//if (!loop) {
		//	bRelease = true;
		//}
	}
		SetAnimation(0.125f, 1.0f);
		SetPosition(pos,m_move,m_fPosSizeX,m_fPosSizeY, m_fPosSizeX);
		//CSCENE2D���擾
		CScene2D::Update();

		nLife--;
		if (nCntAnime % 15 == 0)
		{
			nLife = 0;
			Uninit();
		}
		else if (nLife == 0)
		{
			Uninit();

		}
		CManeger::MODE m_mode = CManeger::GetMode();

			if (m_mode == CManeger::MODE_RESULT||m_mode == CManeger::MODE_TITLE)
		{
			Uninit();
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
void CExplosion::Draw(void)
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
