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
#include "Goal.h"
#include"Explosion.h"
#include"Effect.h"
#include "Weapons.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_GOAL_TYPE (3)//a =	�����x (0�`255)
#define MOVE_GOAL_SPEED (5.0f)		//�ړ����x

LPDIRECT3DTEXTURE9 CGoal::m_pTexture[MAX_GOAL_TYPE] = {};
bool  g_bDeleateGoal = true;
//=============================================================================
// Create�֐�
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length, GOAL_TYPE type, GOAL_OBJ_TYPE nType)
{
	//�C���X�^���X
	CGoal*pBullet = NULL;
	//
	pBullet = new CGoal(SCENE_NUMBER_TYPE_GOAL);
	pBullet->Init(pos, move, rot, Length);
	pBullet->BindTexture(m_pTexture[type]);
	pBullet->Type = nType;
	return pBullet;

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
HRESULT CGoal::Load(void)
{//load//CGoal����
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/��.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/��.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/��.png", &m_pTexture[2]);

	return S_OK;
}
void CGoal::UnLoad(void)
{//unload//�j��
	for (int nBulletType = 0; nBulletType < MAX_GOAL_TYPE; nBulletType++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nBulletType] != NULL)
		{
			m_pTexture[nBulletType]->Release();
			m_pTexture[nBulletType] = NULL;
		}
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGoal::CGoal(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_PLAYER) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_fPosSize = 0.0f;
	fMoveX = 0.0f, fMoveY = 0.0f;
	fMoveX1 = 0.0f, fMoveY1 = 0.0f;
	fMoveX2 = 0.0f, fMoveY2 = 0.0f;
	fRoboMoveX = 0.0f, fRoboMoveY = 0.0f;
	fAroundMoveX = 0.0f, fAroundMoveY = 0.0f;
	fRot = 0.0f;
	fRot1 = 0.0f;
	fRot2 = 0.0f;
	fRoboRot = 0.0f;
	fAroundRot = D3DX_PI * 0.25f;

	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length)
{
	CScene2D::Init();
	SetNOMAL(pos, Length, Length);
	m_fPosSizeX = Length;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeY = Length;
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSize = m_fPosx;
	m_fPosSize = Length;//�e�̑傫���̃����o�ϐ�
	Save();
	SetOBJTYPE(OBJECT_TYPE_GOAL);

	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CGoal::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CGoal::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();

	m_nCountBullet++;
	//pos
	D3DXVECTOR3 pos;
	//move(�ړ���)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	CPlayer *pPLayer = CGame::GetPlayer();
	D3DXVECTOR3 posPlayer = pPLayer->GetPotion();

	GOAL_TYPE type = GOAL_TYPE_MAX;
	//X�̈ړ�//Y�̈ړ�

	//pos���擾
	pos = GetPotion();
	//move���擾
	move = GetMove();

	m_fRot = GetfRot();

	//pos�̃T�C�Y���擾
	m_fPosSize = GetLength();



	if (Type == GOAL_OBJ_TYPE_PLAYER)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_ENEMY)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_1)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;


	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_2)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_PLAYER_3)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_ROBO)
	{
		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;



	}
	else if (Type == GOAL_OBJ_TYPE_AROUND)
	{

		//�ړ�����
		MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_GOAL_SPEED / 2.0);
		//player��posX��pos������
		fMoveX = posPlayer.x - pos.x;
		//player��posY��pos������
		fMoveY = posPlayer.y - pos.y;

		//move��Player��Enemy��Playerpos��������move����
		move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;
		move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_GOAL_SPEED;



		pos.y += move.y;
		pos.x += move.x;

		move.x += (0.0f - move.x) * MOVE_GOAL_SPEED;
		move.y += (0.0f - move.y) * MOVE_GOAL_SPEED;


	}
	m_fPosx = m_fPosSizeX;
	m_fPosy = m_fPosSizeY;
	CScene2D::Update();
	SetNOMAL(pos, m_fPosx, m_fPosy);
		}
		catch (const std::exception&)
		{

		}

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CGoal::Draw(void)
{
	CScene2D::Draw();
}
void CGoal::Loads(void)
{
	FILE *pFile;


	pFile = fopen("goal.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSize);

		fclose(pFile);

	}
}
void CGoal::Save(void)
{
	//seve
	FILE *pFile;


	pFile = fopen("goal.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSize);

		fclose(pFile);

	}

}
