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
#include"Weapons.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"font.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

#define COLOR_A (255)//a =	�����x (0�`255)
#define TEX_FILE1 ("data/TEXTURE/�V�[���h.png")//�� (0�`255)
#define TEX_FILE2 ("data/TEXTURE/�C�e.png")//�� (0�`255)

LPDIRECT3DTEXTURE9 CWeapons::m_pTexture[MAX_TEX_WEAPONS] = {};


//=============================================================================
// Create�֐�
//=============================================================================
CWeapons *CWeapons::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, WEAPONS_TYPE type, float rot, float Length)
{
	//�C���X�^���X
	CWeapons*pWeapons = NULL;
	pWeapons = new CWeapons(SCENE_NUMBER_TYPE_WEAPONS);
	pWeapons->Init(pos,move,rot,Length);
	pWeapons->BindTexture(m_pTexture[type]);

	return pWeapons;

}

HRESULT CWeapons::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);

	return S_OK;
}
void CWeapons::UnLoad(void)
{//unload//�j��
	for (int nCntPlayer = 0; nCntPlayer < MAX_TEX_PLAYER; nCntPlayer++)
	{

		//�e�N�X�`���̔j��
		if (m_pTexture[nCntPlayer] != NULL)
		{
			m_pTexture[nCntPlayer]->Release();
			m_pTexture[nCntPlayer] = NULL;
		}
	}

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CWeapons::CWeapons(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_BLOCK) : CScene2D(m_layer)
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
CWeapons::~CWeapons()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CWeapons::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,  float rot,float Length)
{
	CScene2D::Init();
	SetPosition(pos, move, rot, Length,Length);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSize = Length;
	nCountBullet = 0;
	Save();
	SetOBJTYPE(OBJECT_TYPE_PLAYER);

	m_fRot = D3DX_PI * 0.25f;

	return S_OK;
}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CWeapons::Uninit(void)
{
	CScene2D::Uninit();
	Loads();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CWeapons::Update(void)
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
	WEAPONS_TYPE type = WEAPONS_TYPE_MAX;
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

	int nCntData, dice;
	srand((unsigned)time(NULL));   /* �����̎��time ����Ƃ邨�܂��Ȃ� */

	for (nCntData = 0; nCntData < CWeapons::WEAPONS_TYPE_MAX; nCntData++)
	{
		dice = (int)(rand()*(double)CWeapons::WEAPONS_TYPE_MAX / (1.0 + RAND_MAX)); /* �T�C�R���̗���!!! */
		BindTexture(m_pTexture[dice]);
	}

	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[WEAPONS_TYPE_1]); }
	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[WEAPONS_TYPE_2]); }

	if (fMoveX != 0.0f || fMoveY != 0.0f)
	{//���͂��ꂽ
		fRot = atan2f(fMoveX, fMoveY);
	}
		CWeapons::WEAPONS_TYPE Weponstype = CWeapons::WEAPONS_TYPE_MAX;

	if (m_pTexture[Weponstype] == m_pTexture[WEAPONS_TYPE_1])
	{
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);


	}
	else if (m_pTexture[Weponstype] == m_pTexture[WEAPONS_TYPE_2])
	{

		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 25.5f, 2.0f, 55 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);


	}


	//move�ňړ�
	//���Z
	pos += move;
	move *= 0.1f;

	move.y += 1.75f;
	//SetPosition(pos, move, 5.0f, m_fPosSize);
	SetRot(pos,move, 5.0f, m_fPosSize);
	//pos��Get
	GetPotion();
	//Move��Get
	GetMove();
	//Length��Get
	GetLength();

	//CSCENE2D���擾
	CScene2D::Update();

	if (m_nCountRot % 15 == 0)
	{

		Uninit();

	}


	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_WEAPONS)
				{//�e�����I
					CBullet *pBullet = (CBullet*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (GetPotion().x > pos.x - WEAPONS_WIDTH - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + PLAYER_WIDTH &&
							GetPotion().y > pos.y - BULLET_SIZE - WEAPONS_HEIGHT && GetPotion().y < pos.y + BULLET_SIZE + PLAYER_HEIGHT)
						{
							SetPattanAnim(nPattenAnime);
							CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, 25.0f);
							pBullet->Uninit();
						}
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
void CWeapons::Draw(void)
{
	CScene2D::Draw();
}
void CWeapons::Loads(void)
{
	FILE *pFile;

	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pFile = fopen("Wepons.txt", "r");
	if (pFile != NULL)
	{

		fscanf(pFile, "%f\n", &m_fPosSizeX);
		fscanf(pFile, "%f\n", &m_fPosSizeY);

		fscanf(pFile, "data/TEXTURE/block.png");
		fscanf(pFile, "data/TEXTURE/block.png");


		fclose(pFile);

	}
}
void CWeapons::Save(void)
{
	//seve
	FILE *pFile;

	pFile = fopen("Wepons.txt", "w");
	if (pFile != NULL)
	{

		fprintf(pFile, "%f\n", m_fPosSizeX);
		fprintf(pFile, "%f\n", m_fPosSizeY);

		fprintf(pFile, TEX_FILE1);
		fprintf(pFile, TEX_FILE2);

		fclose(pFile);

	}
}