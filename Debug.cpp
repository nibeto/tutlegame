//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include "InputKeyboard.h"
#include"Explosion.h"
#include"Debug.h"
#include"block.h"
#include"Enemy.h"
#include"Boss.h"
#include"Life.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_BLOCK_TYPE (2)//a =	�����x (0�`255)
#define MOVE_BLOCK_MOVE (5.0f)
//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
int CDebug::nNumBlock = 0;
CDebug::Debug CDebug::m_block[MAX_NUM_DEBUG] = {};
LPDIRECT3DTEXTURE9 CDebug::m_pTexture[CDebug::DEBUG_TYPE_MAX] = {};
//=============================================================================
// �Z�[�u
//=============================================================================
void CDebug::Save(void)
{


}
//=============================================================================
// ���[�h
//=============================================================================
void CDebug::Loads(void)
{
	try
	{

	//�ϐ��錾
	char cEnpty[128];	// ��p�i�K�v�̂Ȃ����́j
	char cLoad[128];	// �ǂݍ��ޗp
	char cComp[128];	// ��r�p
	int nNumber = 0;
	int nIndex = 0;
	FILE *pFIle;

	pFIle = fopen("data/Save/blockDebug.txt", "r");

	if (pFIle != NULL)
	{
		while (strcmp(cComp, "SCRIPT") != 0)
		{
			fgets(cLoad, sizeof(cLoad), pFIle);
			sscanf(cLoad, "%s", &cComp);

		}
		if (strcmp(cComp, "SCRIPT") == 0)
		{
			while (strcmp(cComp, "END_SCRIPT") != 0)
			{
				fgets(cLoad, sizeof(cLoad), pFIle);
				sscanf(cLoad, "%s", &cComp);

				if (strcmp(cComp, "NUM_BLOCK") == 0)
				{
					sscanf(cLoad, "%s %s %d", &cEnpty, &cEnpty, &nNumBlock);
					nNumber = nNumBlock;
				}
				if (strcmp(cComp, "MAPSET") == 0)
				{
					while (strcmp(cComp, "END_MAPSET") != 0)
					{
						fgets(cLoad, sizeof(cLoad), pFIle);
						sscanf(cLoad, "%s", &cComp);

						if (strcmp(cComp, "BLOCKSET") == 0)
						{
							while (strcmp(cComp, "END_BLOCKSET") != 0)
							{
								fgets(cLoad, sizeof(cLoad), pFIle);
								sscanf(cLoad, "%s", &cComp);

								if (strcmp(cComp, "POS") == 0)
								{
									sscanf(cLoad, "%s %s %f %f %f ", &cEnpty, &cEnpty, &m_block[nIndex].pos.x, &m_block[nIndex].pos.y, &m_block[nIndex].pos.z);
								}

								if (strcmp(cComp, "SIZE") == 0)
								{
									sscanf(cLoad, "%s %s %f %f", &cEnpty, &cEnpty, &m_block[nIndex].f_sizeX, &m_block[nIndex].f_sizeY);
								}

								if (strcmp(cComp, "ROT") == 0)
								{
									sscanf(cLoad, "%s %s %f", &cEnpty, &cEnpty, &m_block[nIndex].f_rot);
								}

								if (strcmp(cComp, "TYPE") == 0)
								{
									sscanf(cLoad, "%s %s %d ", &cEnpty, &cEnpty, &m_block[nIndex].type);
								}
							}
							nIndex++;
						}
					}
				}
			}
		}
	}
	/* �t�@�C���̃N���[�Y */
	fclose(pFIle);
	}
	catch (const std::exception&)
	{

	}

}
int CDebug::GetNumBlock(void)
{
	return nNumBlock;
}
CDebug::Debug *CDebug::Getblock(void)
{
	return &m_block[0];
}
HRESULT CDebug::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block.png", &m_pTexture[0]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Skybg.jpg", &m_pTexture[1]);

	return S_OK;
}
void CDebug::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < CDebug::DEBUG_TYPE_MAX; nCntEnemyType++)
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
CDebug::CDebug(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_DEBUG) : CScene2D(m_layer)
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
CDebug::~CDebug()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CDebug::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY)
{
	try
	{

	CScene2D::Init();
	mf_pos = 5;//pos�̏������̕ϐ�
	SetOBJTYPE(OBJECT_TYPE_BLOCK);

	//Length = 5;
	SetPosition(pos, move, rot, LengthX, LengthY);
	m_bDisp = true;
	m_bjump = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(600.0f, 950.0f, 0.0f);
	m_fPosSizeX = LengthX;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeY = LengthY;
	}
	catch (const std::exception&)
	{

	}

	return S_OK;

}
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CDebug::Uninit(void)
{
	CScene2D::Uninit();
}
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CDebug::Update(void)
{
	try
	{

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CMouse *pMouse = CManeger::GetMouse();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;

	float fMoveX = 0.0f, fMoveY = 0.0f;
	float fRot = 0.0f;
	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();
	MouseTarget();
	if (pMouse->GetPress(0))//0or1
	{//�u���b�N�𐶐�����
		Cblock::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(fMoveY), 0.0f), Cblock::BLOCK_TYPE_TYPE_1, 0.0f, m_fPosSizeX, m_fPosSizeY);
		//**********************************
		//�G�l�~�[��CREATE()
		//**********************************
		move.x += sinf(D3DX_PI * -0.75f) * MOVE_BLOCK_MOVE;
		move.y += cosf(D3DX_PI * -0.75f) * MOVE_BLOCK_MOVE;
	}

	if (pMouse->GetPress(1))//0or1
	{
		move.x += sinf(D3DX_PI * -0.25f) * MOVE_BLOCK_MOVE;
		move.y += cosf(D3DX_PI * -0.25f) * MOVE_BLOCK_MOVE;
	}

	if (pInputKeyboard->GetPress(DIK_L) == true) { BindTexture(m_pTexture[0]); }
	if (pInputKeyboard->GetPress(DIK_K) == true) { BindTexture(m_pTexture[1]); }

	if (pInputKeyboard->GetTrigger(DIK_C) == true) {//�{�X�𐶐�����
		CBoss::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(fMoveY), 0.0f), m_fPosSizeX, m_fPosSizeY, CBoss::BOSS_TYPE_1, CBoss::BOSS_CLASS_TYPE_1,1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (pInputKeyboard->GetTrigger(DIK_M) == true) {//�G�l�~�[�𐶐�����
		CEnemy::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(0.0f), cosf(fMoveY), 0.0f), m_fPosSizeX, m_fPosSizeY, CEnemy::ENEMY_TYPE_1, CEnemy::ENEMY_CLASS_TYPE_1, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (pInputKeyboard->GetPress(DIK_U) == true) {//�v���C���[�𐶐�����
	//cLife::Create(D3DXVECTOR3(210.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -125.0f, 25.0f, cLife::LIFE_TYPE_BASE, cLife::LIFE_OBJ_TYPE_LIFE);
	CPlayer::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), CPlayer::PLAYER_TYPE_2, m_fPosSizeX, m_fPosSizeY);
	}
	if (pInputKeyboard->GetPress(DIK_T) == true) { m_fPosSizeX++; }

	if (pInputKeyboard->GetPress(DIK_Y) == true) { m_fPosSizeX--; }


	if (pInputKeyboard->GetPress(DIK_H) == true) { m_fPosSizeY++; }
	if (pInputKeyboard->GetPress(DIK_J) == true) { m_fPosSizeY--; }



	pos += move;
	move *= 0.1f;

	CScene2D::Update();
	SetNOMAL(CScene2D::GetPotion(), m_fPosSizeX, m_fPosSizeY);
	}
	catch (const std::exception&)
	{

	}

}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CDebug::Draw(void)
{
	CScene2D::Draw();
}
bool CDebug::CorisionDebug(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3	*pMove)
{
	D3DXVECTOR3 pos = GetPotion();

	int nCuntBlock;
	bool bLand = false;

	for (nCuntBlock = 0; nCuntBlock < MAX_BLOCK; nCuntBlock++)
	{
		if (bUse == true)
		{
			if (pPos->x + PLAYER_LONG_X >= GetPotion().x&&
				pPos->x - PLAYER_LONG_X <= GetPotion().x + DEBUG_WIDTH)

			{
				//��
				if (pPosold->y <= GetPotion().y &&
					pPos->y >= GetPotion().y)
				{
					bLand = true;
					pPos->y = GetPotion().y;
					pMove->y = 0.0f;
				}

				//��
				if (pPosold->y >= GetPotion().y + DEBUG_HEIGHT&&
					pPos->y - PLAYER_HEIGHT * 2 <= GetPotion().y + DEBUG_HEIGHT)
				{
					pPos->y = GetPotion().y + DEBUG_HEIGHT + PLAYER_HEIGHT * 2;
					pMove->y = 0.0f;
				}
			}

			if (GetPotion().y < pPosold->y
				&& GetPotion().y + DEBUG_HEIGHT + PLAYER_HEIGHT> pPosold->y)
			{//���E�͈͓̔�
				if (GetPotion().x - (PLAYER_LONG_X - 10) >= pPosold->x
					&& GetPotion().x - (PLAYER_LONG_X - 10) <= pPos->x)
				{//��
					pPos->x = GetPotion().x - (PLAYER_LONG_X - 10);
					pMove->x = 0.0f;
				}
				if (GetPotion().x + DEBUG_WIDTH + (PLAYER_LONG_X - 10) <= pPosold->x
					&& GetPotion().x + DEBUG_WIDTH + (PLAYER_LONG_X - 10) >= pPos->x)
				{//�E
					pPos->x = GetPotion().x + DEBUG_WIDTH + (PLAYER_LONG_X - 10);
					pMove->x = 0.0f;
				}
			}
		}
	}

	return bLand;//�Ԃ��l

}