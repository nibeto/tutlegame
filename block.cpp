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
#include"block.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"font.h"
#include"Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

#define COLOR_A (255)//a =	�����x (0�`255)
#define TEX_FILE1 ("data/TEXTURE/block.png")//�� (0�`255)
#define TEX_FILE2 ("data/TEXTURE/Skybg.jpg")//�� (0�`255)

LPDIRECT3DTEXTURE9 Cblock::m_pTexture[MAX_TEX_BLOCK] = {};

D3DXVECTOR3 Cblock::GetBlock(void)
{
	Cblock*pBlock = CGame::GetBlock();

	D3DXVECTOR3 pos = pBlock->GetPotion();

	try
	{


	}
	catch (const std::exception&)
	{

	}		
return pos;

}

HRESULT Cblock::Load(void)
{//load//�ǂݍ���
	try
	{
		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		// ���_����ݒ�
		D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);


	}
	catch (const std::exception&)
	{

	}
	return S_OK;

}
void Cblock::UnLoad(void)
{//unload//�j��
	try
	{
		for (int nCntBLOCK = 0; nCntBLOCK < MAX_TEX_BLOCK; nCntBLOCK++)
		{

			//�e�N�X�`���̔j��
			if (m_pTexture[nCntBLOCK] != NULL)
			{
				m_pTexture[nCntBLOCK]->Release();
				m_pTexture[nCntBLOCK] = NULL;
			}
		}

	}
	catch (const std::exception&)
	{

	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
Cblock::Cblock(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_BLOCK) : CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
	nCountBullet = 0;
	m_bDisp = true;
	m_bjump = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
Cblock::~Cblock()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT Cblock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	CScene2D::Init();
	SetPosition(pos, move, rot, LengthX, LengthY);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;
	m_fPosSizeY = LengthY;
	nCountBullet = 0;
	Save();
	SetOBJTYPE(OBJECT_TYPE_BLOCK);

	m_fRot = D3DX_PI * 0.25f;

	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void Cblock::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void Cblock::Update(void)
{
	try
	{

	m_nCountRot++;
	//pos
	D3DXVECTOR3 pos;
	//move(�ړ���)
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	D3DXCOLOR col;
	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	BLOCK_TYPE type = BLOCK_TYPE_TYPE_MAX;
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




	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[BLOCK_TYPE_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[BLOCK_TYPE_TYPE_2]); }

	if (pInputKeyboard->GetPress(DIK_D) == true) { fMoveX = -1.0f; }
	if (pInputKeyboard->GetPress(DIK_A) == true) { fMoveX = 1.0f; }
	if (pInputKeyboard->GetPress(DIK_W) == true) { fMoveY = -1.0f; }
	if (pInputKeyboard->GetPress(DIK_S) == true) { fMoveY = 1.0f; }

	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//���͂��ꂽ
		fRot = atan2f(fMoveX, fMoveY);
		move += D3DXVECTOR3(sinf(fRot), cosf(fRot), 0.0f) * 5.0f;//1.0
	}

	pos.x += move.x;
	pos.y += move.y;



	//move�ňړ�
	//���Z
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);

	//CSCENE2D���擾
	CScene2D::Update();


	if (pInputKeyboard->GetPress(DIK_V) == true) { Uninit(); }
	//�u���b�N�̓����蔻��
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
				{//�e�����I
					CBullet *pBullet = (CBullet*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER || pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER_3|| pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
							if (GetPotion().x > pos.x - m_fPosSizeX - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + m_fPosSizeX &&
							GetPotion().y > pos.y - BULLET_SIZE - m_fPosSizeY && GetPotion().y < pos.y + BULLET_SIZE + m_fPosSizeY)
						{
							pBullet->Uninit();
						}
					}
				}
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_PLAYER)
				{//�e�����I
					CPlayer* pPlayer = (CPlayer*)pScene;
					D3DXVECTOR3 pos = pPlayer->GetPotion();
					D3DXVECTOR3 move = pPlayer->GetMove();

						if (GetPotion().x > pos.x - m_fPosSizeX - PLAYER_HEIGHT && GetPotion().x < pos.x + PLAYER_HEIGHT + m_fPosSizeX &&
							GetPotion().y > pos.y - PLAYER_WIDTH - m_fPosSizeY && GetPotion().y < pos.y + PLAYER_WIDTH + m_fPosSizeY)
						{

						}
				}

			}
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
void Cblock::Draw(void)
{
	try
	{
		CScene2D::Draw();

	}
	catch (const std::exception&)
	{

	}
}
void Cblock::Loads(void)
{
	try
	{

	FILE *pFile;

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pFile = fopen("Block.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSizeX);
		fscanf(pFile, "%f\n", &m_fPosSizeY);

		fscanf(pFile, "data/TEXTURE/block.png");
		fscanf(pFile, "data/TEXTURE/block.png");


		fclose(pFile);

	}
	}
	catch (const std::exception&)
	{

	}

}
//------------------------------------
//
//�x�N�g���̓���
//
//------------------------------------
float Cblock::Vec3Dot(D3DXVECTOR3 * pV1, D3DXVECTOR3 * pV2)
{
	try
	{
		return ((pV1->x)*(pV2->x) + (pV1->y)*(pV2->y) + (pV1->z)*(pV2->z));

	}
	catch (const std::exception&)
	{

	}
}
//------------------------------------
//
//�x�N�g���̊O��
//
//------------------------------------
void Cblock::Vec3Cross(D3DXVECTOR3 * pOut, D3DXVECTOR3 * pV1, D3DXVECTOR3 *pV2)
{
	try
	{
		CManeger *pMAnager = CGame::GetManagement();

		CManeger::MODE mode = pMAnager->GetMode();

		if (mode == CManeger::MODE_GAME)
		{
			//Cblock* pBlock = CGame::GetBlock();
			//D3DXVECTOR3 vec = pBlock->GetPotion();
			D3DXVECTOR3 vec;
			double x1, y1, z1, x2, y2, z2;

			x1 = (double)(pV1->x);
			y1 = (double)(pV1->y);
			z1 = (double)(pV1->z);
			x2 = (double)(pV2->x);
			y2 = (double)(pV1->y);
			z2 = (double)(pV1->z);

			vec.x = (float)(y1 * z2 - y1 *y2);
			vec.y = (float)(z1 * x2 - z1 *y2);
			vec.z = (float)(x1 * y2 - x1 *y2);

			*pOut = vec;
		}

	}
	catch (const std::exception&)
	{

	}
}
void Cblock::Save(void)
{
	try
	{
		//seve
		FILE *pFile;

		pFile = fopen("Block.txt", "w");
		if (pFile != NULL)
		{

			fprintf(pFile, "%f\n", m_fPosSizeX);
			fprintf(pFile, "%f\n", m_fPosSizeY);

			fprintf(pFile, TEX_FILE1);
			fprintf(pFile, TEX_FILE2);

			fclose(pFile);

		}

	}
	catch (const std::exception&)
	{

	}
}