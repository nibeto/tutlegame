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
#include"Timer.h"
#include"score.h"
#include"sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

LPDIRECT3DTEXTURE9 CTimer::m_pTexture[MAX_TIMER_TYPE] = {};

//=============================================================================
// Create�֐�
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY, TIMER_TYPE type, TIMER_BOX_TYPE nType)
{
	//�C���X�^���Xw
	CTimer*pObj = NULL;
	pObj = new CTimer(SCENE_NUMBER_TYPE_TIMER);
	pObj->Init(pos, move, rot, LengthX, LengthY);
	pObj->m_nType = nType;
	pObj->BindTexture(m_pTexture[type]);
	return pObj;
	//�C���X�^���X
}

HRESULT CTimer::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock�j.png", &m_pTexture[0]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/clock�jmin.png", &m_pTexture[1]);

	return S_OK;
}
void CTimer::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_TIMER_TYPE; nCntEnemyType++)
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
CTimer::CTimer(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_TIMER) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	CScene2D::Init();
	m_pos = pos;
	m_move = move;
	SetOBJTYPE(OBJECT_TYPE_TIMER);
	f_rot = rot;
	SetRotTimer(pos, move, rot, LengthX, LengthY);
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
void CTimer::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CTimer::Update(void)
{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;


	float fMoveX1 = 0.0f, fMoveY1 = 0.0f;

	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;


	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRotTimer = GetfTimerRot();
	NcuntRot++;




	pos += move;
	move *= 0.1f;

	CScene2D::Update();

	GetPotion();
	GetMove();
	GetLength();
	GetfTimerRot();
	SetRotTimer(pos, move, f_rot, m_fPosSizeX,m_fPosSizeY);

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CTimer::Draw(void)
{
	CScene2D::Draw();
}
