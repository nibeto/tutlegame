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
#include"Capsule.h"
#include"CapsuleEnemy.h"
#include "Effect.h"
#include"SeedManagement.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLOR_R (255)//�� (0�`255)
#define COLOR_G (255)//�� (0�`255)
#define COLOR_B (255)//�� (0�`255)
#define COLOR_A (255)//a =	�����x (0�`255)
#define MAX_CAPSULE_TYPE (2)//a =	�����x (0�`255)
#define MOVE_CAPSULE_SPEED (5.0f)		//�ړ����x

LPDIRECT3DTEXTURE9 CCapsule::m_pTexture[MAX_CAPSULE_TYPE] = {};
//=============================================================================
// Create�֐�
//=============================================================================
CCapsule *CCapsule::Create(D3DXVECTOR3 pos, float LengthX, float LengthY, CAPSULE_TYPE type, CAPSULE_CLASS_TYPE nType)
{
	//�C���X�^���X
	CCapsule*pRobo = NULL;
	pRobo = new CCapsule(SCENE_NUMBER_TYPE_CAPSULE);
	pRobo->Init(pos, LengthX, LengthY);
	pRobo->BindTexture(m_pTexture[type]);
	pRobo->m_nType = nType;
	return pRobo;
	//�C���X�^���X
}

HRESULT CCapsule::Load(void)
{//load//�ǂݍ���
	CRenderer *pRenderer = CManeger::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/��.png", &m_pTexture[0]);

	// ���_����ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/��.png", &m_pTexture[1]);

	return S_OK;
}
void CCapsule::UnLoad(void)
{//unload//�j��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_CAPSULE_TYPE; nCntEnemyType++)
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
CCapsule::CCapsule(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_CAPSULE) :CScene2D(m_layer)
{//clear�i�N���A�j
	m_nCountRot = 0;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSize = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCapsule::~CCapsule()
{

}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
HRESULT CCapsule::Init(D3DXVECTOR3 pos, float LengthX, float LengthY)
{
	CScene2D::Init();
	SetOBJTYPE(OBJECT_TYPE_CAPSULE);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Length = 5;
	SetNOMAL(pos, LengthX, LengthY);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosSizeX = LengthX;//�e�̑傫���̃����o�ϐ�
	m_fPosSizeY = LengthY;
	return S_OK;

}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
void CCapsule::Uninit(void)
{
	CScene2D::Uninit();
}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
void CCapsule::Update(void)
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
	if (m_nType == CAPSULE_CLASS_TYPE_BASE)
	{
		//MouseTarget();
		if (pInputKeyboard->GetPress(DIK_H))
		{
			CCAPSULEENEMY::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 55.5f, CCAPSULEENEMY::CAPSULEENEMY_TYPE_ENEMY, CCAPSULEENEMY::CAPSULEENEMY_OBJ_TYPE_ENEMY);
		}
		CEffect::Create(D3DXVECTOR3(posPlayer.x + 25, posPlayer.y + 20, posPlayer.z), D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f)*0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 5.0f, 5.5f, 2.0f, 25 * 0.5f, CEffect::EFFECT_TYPE_PLAYER, 1);
		if (nCountBullet % 15 == 0)
		{

			CCAPSULEENEMY::Create(pos, D3DXVECTOR3(sinf(1.5f), cosf(0.5f), 0.0f)*0.5f, -25.0f, 15.5f, CCAPSULEENEMY::CAPSULEENEMY_TYPE_ENEMY, CCAPSULEENEMY::CAPSULEENEMY_OBJ_TYPE_ENEMY);
			std::cout << CCAPSULEENEMY::Create;
		}
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
	//�ړ�����
	MoveNormalizeVector(D3DXVECTOR3(posPlayer.x, posPlayer.y, 0.0f), MOVE_CAPSULE_SPEED / 2.0);
	//player��posX��pos������
	fMoveX = posPlayer.x - pos.x;
	//player��posY��pos������
	fMoveY = posPlayer.y - pos.y;

	//move��Player��Enemy��Playerpos��������move����
	move.x = cos(atan2f(fMoveY, fMoveX))*MOVE_CAPSULE_SPEED;
	move.y = sin(atan2f(fMoveY, fMoveX))*MOVE_CAPSULE_SPEED;



	pos.y += move.y;
	pos.x += move.x;

	move.x += (0.0f - move.x) * MOVE_CAPSULE_SPEED;
	move.y += (0.0f - move.y) * MOVE_CAPSULE_SPEED;


	CScene2D::Update();
	SetNOMAL(pos, m_fPosSizeX, m_fPosSizeY);

	//for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	//{
	//	for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
	//	{
	//		CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
	//		if (pScene != NULL)
	//		{
	//			if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
	//			{//�e�����I
	//				CBullet *pBullet = (CBullet*)pScene;
	//				D3DXVECTOR3 pos = pBullet->GetPotion();
	//				D3DXVECTOR3 move = pBullet->GetMove();


	//				if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
	//				{
	//					if (GetPotion().x > pos.x - CAPSULE_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + CAPSULE_POLYGON_SIZE &&
	//						GetPotion().y > pos.y - BULLET_SIZE - CAPSULE_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + CAPSULE_POLYGON_SIZE)
	//					{
	//						//CExplosion::Create(pos, move, tex, nPattenAnime, -25.0f, m_fPosSize);
	//						pBullet->Uninit();
	//						Uninit();
	//					}
	//				}
	//			}
	//		}

	//	}
	//}
	}
	catch (const std::exception&)
	{

	}

}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================q
void CCapsule::Draw(void)
{
	CScene2D::Draw();
}
