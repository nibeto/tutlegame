#include "collision.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Explosion.h"
#include"Enemy.h"
#include"score.h"
#include"sound.h"
#include"Playerobj.h"
#include "Life.h"
#include "block.h"
cCollision::cCollision(SCENE_NUMBER_TYPE m_Number = SCENE_NUMBER_TYPE_COLLISION) : CScene2D(m_layer)
{
}

cCollision::~cCollision()
{
}

void cCollision::PlayerCollision(void)
{
	D3DXVECTOR2 tex;
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
				{//’e”­Œ©I
					CBullet *pBullet = (CBullet*)pScene;
					CPlayerObj*pPlayerobj = (CPlayerObj*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();
					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER_3)
					{
						if (m_nCount % 160 == 0)
						{
							pBullet->Uninit();
						}

					}

					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_ENEMY)
					{
						if (GetPotion().x > pos.x - PLAYER_WIDTH - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + PLAYER_WIDTH &&
							GetPotion().y > pos.y - BULLET_SIZE - PLAYER_HEIGHT && GetPotion().y < pos.y + BULLET_SIZE + PLAYER_HEIGHT)
						{
							CScene2D::SetPattanAnim(nPattanAnim);
							CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, 25.0f);
							pBullet->Uninit();
							Uninit();
						}
					}
				}
			}

		}
	}
}
void cCollision::EnemyCollision(void)
{
	D3DXVECTOR2 tex;
	cLife*pLife = NULL;

	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		for (int nDeffult = 0; nDeffult < SCENE_NUMBER_TYPE_MAX; nDeffult++)
		{
			CScene *pScene = GetCSINE((SCENE_NUMBER_TYPE)nDeffult, nCount);
			if (pScene != NULL)
			{
				if (pScene->GetOBJTYPE() == OBJECT_TYPE_BULLET)
				{//’e”­Œ©I
					CBullet *pBullet = (CBullet*)pScene;
					D3DXVECTOR3 pos = pBullet->GetPotion();
					D3DXVECTOR3 move = pBullet->GetMove();


					if (pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER || pBullet->Type == pBullet->BULLET_OBJ_TYPE_PLAYER_3)
					{
						if (GetPotion().x > pos.x - ENEMY_POLYGON_SIZE - BULLET_SIZE && GetPotion().x < pos.x + BULLET_SIZE + ENEMY_POLYGON_SIZE &&
							GetPotion().y > pos.y - BULLET_SIZE - ENEMY_POLYGON_SIZE && GetPotion().y < pos.y + BULLET_SIZE + ENEMY_POLYGON_SIZE)
						{
							CScene2D::SetPattanAnim(nPattanAnim);
							CExplosion::Create(pos, move, tex, nPattanAnim, -25.0f, 25.0f);
							m_nLife = 	pLife->GetLife(m_nLife);
							m_nLife -= 1;

							pBullet->Uninit();
							//pScore->AddScore(1);
							if (m_nLife == 0)
							{
								Uninit();
							}
						}
					}

				}
			}
		}
	}
}