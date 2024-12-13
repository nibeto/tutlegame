//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"manager.h"
#include"Game.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"robo.h"
#include "Effect.h"
#include"SeedManagement.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_ROBO_TYPE (2)//a =	�����x (0�`255)
#define MOVE_ROBO_SPEED (5.0f)		//�ړ����x

LPDIRECT3DTEXTURE9 CRobo::m_pTexture[MAX_ROBO_TYPE] = {};
//=============================================================================
// Create�֐�
//=============================================================================
CRobo *CRobo::Create(D3DXVECTOR3 pos, float LengthX, float LengthY, ROBO_TYPE type, ROBO_CLASS_TYPE nType)
{
	//�C���X�^���X
	CRobo*pRobo = NULL;
	pRobo = new CRobo(SCENE_NUMBER_TYPE_ROBO);
	pRobo->Init(pos, LengthX, LengthY);
	pRobo->BindTexture(m_pTexture[type]);
	pRobo->m_nType = nType;
	return pRobo;
	//�C���X�^���X
}

HRESULT CRobo::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mousetarget01.png", &m_pTexture[0]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mousetarget01.png", &m_pTexture[1]);

	return S_OK;
}
void CRobo::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ROBO_TYPE; nCntEnemyType++)
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
CRobo::CRobo(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_ROBO) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CRobo::~CRobo()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CRobo::Init(D3DXVECTOR3 pos, float LengthX, float LengthY)
{
	CScene2D::Init();
	SetOBJTYPE(OBJECT_TYPE_BLOCK);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Length = 5;
	SetRot(pos, m_move, 5.0f, m_fPosSizeY);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSizeX = LengthX;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeY = LengthY;
	return S_OK;

}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CRobo::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CRobo::Update(void)
{
	try
	{

	nCountBullet++;
	CSeedMAnagenet *Pseed = CSeedMAnagenet::GetSeed();

	CInputKeyboard *pInputKeyboard = CManeger::GetInput();
	CPlayer *pPLayer = CGame::GetPlayer();
	//ROBO_TYPE type = ROBO_TYPE_MAX;
	D3DXVECTOR3 posPlayer = pPLayer->GetPotion();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 tex;
	if (m_nType == ROBO_CLASS_TYPE_BASE)
	{
		MouseTarget();
		//CEffect::Create(D3DXVECTOR3(posPlayer.x + 25, posPlayer.y + 20, posPlayer.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);

	}
	float fMoveX = 0.0f, fMoveY = 0.0f;
	pos = GetPotion();
	move = GetMove();
	m_fPosSize = GetLength();
	m_fRot = GetfRot();

	m_nCount++;

	m_fRot = m_nCount / m_fRotRand;

	if (nCountBullet % 15 == 0)
	{
		//CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(sinf(0.5f), cosf(0.5f), 0.0f), m_fRot, m_fPosSize, CBullet::BULLET_TYPE_ROBO, CBullet::BULLET_OBJ_TYPE_ROBO);

	}

	//SetZoominandoutandRot(D3DXVECTOR3(250.0f, 550.0f, 0.0f), move, m_fRotRand, m_fPosSizeY);
	//�ړ�����
	MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_ROBO_SPEED / 2.0);
	//player��posX��pos������
	fMoveX = posPlayer.x - pos.x;
	//player��posY��pos������
	fMoveY = posPlayer.y - pos.y;

	//move��Player��Enemy��Playerpos��������move����
	move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_ROBO_SPEED;
	move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_ROBO_SPEED;



	pos.y += move.y;
	pos.x += move.x;

	move.x += (0.0f - move.x) * MOVE_ROBO_SPEED;
	move.y += (0.0f - move.y) * MOVE_ROBO_SPEED;


	CScene2D::Update();
	SetRot(pos, move, 5.0f, m_fPosSizeY);

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


					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (GetPotion().x > pos.x - ROBO_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + ROBO_POLYGON_SIZE &&
							GetPotion().y > pos.y - BULLET_SIZE - ROBO_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + ROBO_POLYGON_SIZE)
						{
							//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
							pBullet->Uninit();
							Release();
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
void CRobo::Draw(void)
{
	try
	{
		CScene2D::Draw();

	}
	catch (const std::exception&)
	{

	}
}
