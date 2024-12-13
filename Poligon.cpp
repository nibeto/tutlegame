//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
//�w�b�_�[�t�@�C��//�K�{
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>//�K�{
#include"block.h"
#include"manager.h"
#include "Polygon.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"block.h"
#include"Effect.h"
#include"Weapons.h"
#include"robo.h"
#include"Life.h"
#include"Game.h"
#include"Goal.h"
#include"SeedManagement.h"
#include"Fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)

#define COLOR_A (255)//a =	�����x (0�`255)
#define TEX_FILE1 ("data/TEXTURE/PlayerTurtle.png")//�� (0�`255)
#define TEX_FILE2 ("data/TEXTURE/PlayerTurtle.png")//�� (0�`255)
#define POLIGON_MOVE_SPEED (5.0f)
LPDIRECT3DTEXTURE9 CPoligon::m_pTexture[MAX_TEX_POLIGON] = {};

bool  g_bDeleatePoligon = true;
HRESULT CPoligon::Load(void)
{//load//�ǂݍ���
	CRenderer* pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, TEX_FILE1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEX_FILE2, &m_pTexture[1]);

	return S_OK;
}
void CPoligon::UnLoad(void)
{//unload//�j��
	try
	{
		for (int nCntPOLIGON = 0; nCntPOLIGON < MAX_TEX_POLIGON; nCntPOLIGON++)
		{

			//�e�N�X�`���̔j��
			if (m_pTexture[nCntPOLIGON] != NULL)
			{
				m_pTexture[nCntPOLIGON]->Release();
				m_pTexture[nCntPOLIGON] = NULL;
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
CPoligon::CPoligon(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_POLIGON) :CScene2D(m_layer)
{//clear�i�N���A�j
	try
	{

	}
	catch (const std::exception&)
	{

		m_nCountRot = 0;
		m_fRot = 0.0f;
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fPosSize = 0.0f;
		nCountBullet = 0;
		fMoveX = 0.0f, fMoveY = 0.0f;
		fRot = 0.0f;
		m_bDisp = true;
		m_bjump = false;
	}

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPoligon::~CPoligon()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CPoligon::Init(D3DXVECTOR3 pos, float LengshX, float LengshY)
{
	try
	{

		D3DXVECTOR2 tex;

		CScene2D::Init();
		m_bDisp = true;
		m_bjump = false;
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetPoligon(pos, LengshX, LengshY, tex, f_R, f_G, f_B, f_A);
		m_fPosSizeX = LengshX;
		m_fPosSizeY = LengshY;
		nCountBullet = 0;
		m_nLife = 5;
		Save();
		SetOBJTYPE(OBJECT_TYPE_PORIGON);
		Posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRot = D3DX_PI * 0.25f;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CPoligon::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CPoligon::Update(void)
{
	try
	{
		m_nCountRot++;
		nCountBullet++;
		m_nCount++;
		int nCntDAta = 0;
		CInputKeyboard* pInputKeyboard = CManeger::GetInput();
		CDice* pDice = CGame::GetDice();

		CSeedMAnagenet* Pseed = CSeedMAnagenet::GetSeed();
		D3DXVECTOR3 pos;
		D3DXVECTOR3 Out;
		D3DXVECTOR3 v1;
		D3DXVECTOR3 v2;
		D3DXVECTOR3 v3;
		D3DXVECTOR3 move;
		D3DXVECTOR2 tex;
		POLIGON_TYPE type = POLIGON_TYPE_MAX;
		pos = GetPotion();
		tex = GetTex();
		Posold = pos;
		move = GetMove();
		m_fPosSize = GetLength();
		m_fRot = GetfRot();
		fMoveX = Pseed->GetfMoveX();
		fMoveY = Pseed->GetfMoveY();
		fMoveZ = Pseed->GetfMoveZ();
		//pos = v1 + v2;

		fMoveX = 600.0f;
		fMoveY = 400.0f;

		//�ړ�
		pos.x = fMoveX + sinf(m_nCountRot / 2.5f) * 20.0f;
		pos.y = fMoveY + cosf(m_nCountRot / 2.5f) * 20.0f;

		//�G�t�F�N�g����
		CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 20, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f) * 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		//�ړ��̈ړ��֐�
		Pseed->TheSeedMove(0.0f, fMoveY, fRot, move);
		if (fMoveY != 0.0f)
		{//���͂��ꂽ
			Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 5.0f);
		}
		else if (fMoveX != 0.0f) { Scene2DMove(fMoveX, fMoveY, fRot, fRot, move, 0.0f); }

		//�C�ӂ̃L�[�������ꂽ�ǂ���
		if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[POLIGON_TYPE_1]); }
		if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[POLIGON_TYPE_2]); }
		if (type == POLIGON_TYPE_1)
		{//�G�t�F�N�g����
			CEffect::Create(D3DXVECTOR3(pos.x + 25, pos.y + 45, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f) * 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 15.5f, 5.0f, 5 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

		}
		else
		{
			for (int nCount = 0; nCount < MAX_SCENE; nCount++)
			{
				for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
				{
					CScene* pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
					if (pScene != NULL)
					{
						if (pScene->GetOBJTYPE() == OBJECT_TYPE_EFFECT)
						{//�e�����I
							CEffect* pEffect = (CEffect*)pScene;
							pEffect->Uninit();
						}

					}
				}
			}
		}
		//�͈͎w��
		if (m_pos.y >= SCREEN_HEIGHT)
		{
			m_bjump = false;
			pos.y = SCREEN_HEIGHT;
			move.y = 0.0f;

		}

		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bjump == false)//�C�ӂ̃L�[�������ꂽ�ǂ���
		{

			m_bjump = true;
			move.y = -25.0f;//* fSpeedUp;
			move.y = -50.0f;//* fSpeedUp;
			move.y = -GRAVITY / 2;//* fSpeedUp;

		}
		//�ړ�(���W)�����炷
		move.y += 1.75f;

		pos.y += move.y;



			if (nCountBullet % 15 == 0)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x + 45.0f, pos.y, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f) * 0.5f, -25.0f, 15.5f, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_OBJ_TYPE_PLAYER_3);
			}

			CSound* pPlaySound = CManeger::GetSound();
			pPlaySound->Play(pPlaySound->SOUND_LABEL_SE_DECIDE);

	//�|�W�V�����Ɉړ������Z
		pos += move;
		move *= 0.1f;

		int nCntTime = 0;
		Cblock* pBlock = CGame::GetBlock();
		//�X�V����
		CScene2D::Update();
		if (nCntTime % 50 == 0)
		{
			m_bjump = false;
		}
		SetPoligon(pos, m_fPosSizeX, m_fPosSizeY, tex, f_R, f_G, f_B, f_A);
		//�I������
		if (m_nDiseType != pDice->DISE_TYPE_5)
		{
			if (nCountBullet % 55 == 0)
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
void CPoligon::Draw(void)
{
	CScene2D::Draw();
}
