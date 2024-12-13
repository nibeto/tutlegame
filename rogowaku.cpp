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
#include"rogowaku.h"
#include"score.h"
#include"sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

LPDIRECT3DTEXTURE9 CRogowaku::m_pTexture[MAX_ROGOWAKU_TYPE] = {};

//=============================================================================
// Create�֐�
//=============================================================================
CRogowaku *CRogowaku::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, ROGOWAKU_TYPE type, int nType)
{
	//�C���X�^���X
	CRogowaku*pRogowaku = NULL;
	pRogowaku = new CRogowaku(SCENE_NUMBER_TYPE_ROGOWAKU);
	pRogowaku->Init(pos, move,  LengthX, LengthY);
	pRogowaku->m_nType = nType;
	pRogowaku->BindTexture(m_pTexture[type]);
	return pRogowaku;
}

HRESULT CRogowaku::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/rogowakuScore.png", &m_pTexture[0]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/rogo.png", &m_pTexture[1]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�X�e�[�^�X���S.png", &m_pTexture[2]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock.png", &m_pTexture[3]);


	return S_OK;
}
void CRogowaku::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ROGOWAKU_TYPE; nCntEnemyType++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nCntEnemyType] != NULL)
		{
			m_pTexture[nCntEnemyType]->Release();
			m_pTexture[nCntEnemyType] = NULL;
		}
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CRogowaku::CRogowaku(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_ROGOWAKU) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CRogowaku::~CRogowaku()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CRogowaku::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,  float LengthX, float LengthY)
{
	CScene2D::Init();
	SetNOMAL(pos, LengthX, LengthY);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_nLife = 5;
	return S_OK;

}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CRogowaku::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CRogowaku::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	//CSound *pSound = CManeger::GetSound();
	//pSound->Play(CSound::SOUND_LABEL_BGM000);
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;

	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();




	CScene2D::Update();

	GetPotion();
	GetMove();
	GetLength();
	GetfRot();


	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CRogowaku::Draw(void)
{
	CScene2D::Draw();
}
