#ifndef _COLLISION_H_
#define _COLLISION_H_
#include"main.h"
#include"Scene2D.h"
#include"Player.h"
//レンダリングクラス
class cCollision :public CScene2D
{
public:
	cCollision(SCENE_NUMBER_TYPE m_Number);
	~cCollision();

	void PlayerCollision(void);
	void EnemyCollision(void);
	//レイの当たり判定



private:
	int m_nLife = 0;
	int nPattanAnim;
};




#endif // !_COLLISION_H_
