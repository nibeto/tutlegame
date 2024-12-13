#ifndef _COLLISION_H_
#define _COLLISION_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//�����_�����O�N���X
class cCollision :public CScene2D
{
public:
	cCollision(SCENE_NUMBER_TYPE m_Number);
	~cCollision();

	void PlayerCollision(void);
	void EnemyCollision(void);
	//���C�̓����蔻��



private:
	int m_nLife = 0;
	int nPattanAnim;
};




#endif // !_COLLISION_H_
