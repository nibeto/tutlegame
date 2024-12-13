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
#include"Dice.h"
#include"score.h"
#include"sound.h"
#include"Playerobj.h"
#include"SeedManagement.h"
#include "Goal.h"
#include"Life.h"
#include"Game.h"
#include"Polygon.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_ENEMY_TYPE (6)//a =	�����x (0�`255)
#define MOVE_ENEMY_SPEED (5.0f)
LPDIRECT3DTEXTURE9 CDice::m_pTexture[MAX_ENEMY_TYPE] = {};

//=============================================================================
// ���C���֐�
//=============================================================================
HRESULT CDice::Load(void)
{//load//�ǂݍ���
	CRenderer* pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��1.png", &m_pTexture[0]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��2.png", &m_pTexture[1]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��3.png", &m_pTexture[2]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��4.png", &m_pTexture[3]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��5.png", &m_pTexture[4]);
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�T�C�R��6.png", &m_pTexture[5]);


	return S_OK;
}
void CDice::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ENEMY_TYPE; nCntEnemyType++)
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
CDice::CDice(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_DICE) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	m_bDisp = true;
	m_bjump = false;
	fMoveX1 = 0.0f, fMoveY1 = 0.0f;

	fMoveX = 0.0f, fMoveY = 0.0f;
	m_nLife = 5;
	fMoveX1 = 0.0f;
	fMoveY1 = 0.0f;
	fMoveX = 0.0f;
	fMoveY = 0.0f;
	fRot = 0.0f;
	nCountBullet = 0;

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDice::~CDice()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CDice::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float f_R, float f_G, float f_B, float f_A)
{
	CScene2D::Init();
	CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
	mf_pos = 5;//pos�̏������̕ϐ�
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);
	SetOBJTYPE(OBJECT_TYPE_DICE);
	SetNOMALDice(pos, move, LengthX, LengthY, f_R, f_G, f_B, f_A);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	m_nLife = 5;
	fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();
	fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();

	return S_OK;

}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CDice::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CDice::Update(void)
{
	try
	{

		CInputKeyboard* pInputKeyboard = CManeger::GetInput();
		CSound* pSound = CManeger::GetSound();
		CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 tex;
		cLife* pLife = CGame::GetLife();

		fMoveX1 = Pseed->GetfMoveX(), fMoveY1 = Pseed->GetfMoveY();

		fMoveX = Pseed->GetfMoveX(), fMoveY = Pseed->GetfMoveY();
		fSpeed = Pseed->fSpped(MOVE_ENEMY_SPEED);
		pos = GetPotion();
		move = GetMove();
		m_fPosSize = GetLength();
		m_fRot = GetfRot();
		nCountBullet++;
		int nCntData;
		DISE_TYPE dice;


		srand((unsigned)time(NULL));   /* �����̎��time ����Ƃ邨�܂��Ȃ� */
		for (nCntData = 0; nCntData < CDice::DISE_TYPE_MAX; nCntData++)
		{
			dice = (DISE_TYPE)(rand() * (double)CDice::DISE_TYPE_MAX / (1.0 + RAND_MAX)); /* �T�C�R���̗���!!! */
			m_nDiseType = dice;

			BindTexture(m_pTexture[dice]);

		}
		if (pInputKeyboard->GetPress(DIK_O))
		{

			BindTexture(m_pTexture[DISE_TYPE_5]);

			//unsigned int sleep(unsigned int nCntData);

		}

		else if (m_nDiseType == DISE_TYPE_5)
		{
			 
			if (pPoligon == NULL)
			{

				if (nCountBullet % 30 == 0)
				{

				CPoligon::Create(D3DXVECTOR3(250, 610, 0.0f), CPoligon::POLIGON_TYPE_2, 55.0f, 55.0f);
				}

				//pPoligon = CPoligon::Create(D3DXVECTOR3(250, 610, 0.0f), CPoligon::POLIGON_TYPE_2, 55.0f, 55.0f);
			}
		}
#if 0
		//else if(m_nDiseType != DISE_TYPE_5)
		//{
		//	if (pPoligon != NULL)
		//	{
		//		CPoligon::TEXTUREDELEATE(pPoligon);
		//		pPoligon = NULL;
		//	}
		//	//CPoligon::DeLeate(pPoligon);
		//}
#endif


		if (m_nDiseType == DISE_TYPE_BASE || m_nDiseType == DISE_TYPE_3 || m_nDiseType == DISE_TYPE_5)
		{

		}
		else if (m_nDiseType == DISE_TYPE_2 || m_nDiseType == DISE_TYPE_4)
		{


		}
		else if (m_nDiseType == DISE_TYPE_1 || m_nDiseType == DISE_TYPE_5)
		{


		}

		if (m_nDiseType == DISE_TYPE_3)
		{
		}
		else	if (m_nDiseType == DISE_TYPE_4)
		{

		}
		else	if (m_nDiseType == DISE_TYPE_5)
		{

		}
		else
		{

		}


		CScene2D::Update();

		SetNOMALDice(pos, move, m_fPosSizeX, m_fPosSizeY, f_R, f_G, f_B, f_A);
	}
	catch (const std::exception&)
	{

	}

}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CDice::Draw(void)
{
	CScene2D::Draw();
}

bool CDice::CntScore(bool score)
{
	return score;
}
