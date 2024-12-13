//=============================================================================
// ÉÅÉCÉìèàóù [PLayer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _GAMESTAGE2_H_
#define _GAMESTAGE2_H_
#include"main.h"
#include"Scene2D.h"
#include"Scene3D.h"
#include"manager.h"
#include "pauseselect.h"
class CPlayer;
class CBullet;
class cLife;
class CPlayerObj;
class CRobo;
class CEnemy;
class CRogowaku;
class CFade;
class CBg;
class CManeger;
class Cblock;
class CEffect;
class CGoal;
class CPAUSESELECT;
class CPause;
class CTimer;
class CTime;
class CLevel;
class CCAPSULEENEMY;
class CCapsule;
class CDice;
class CDebug;
class CFontMode;
class CScore;
class CFONT;
class CBUilding;
class CBoss;
class CGameStage2
{
public:
	CGameStage2();
	~CGameStage2();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	inline	static CBoss * GetBoss(void) { return m_pBoss; };
	inline	static cLife * GetLife(void) { return m_pLife; };
	inline	static CBUilding * GetBuiliding(void) { return m_pBuiliding; };
	inline static CDice*GetDice(void) { return m_pDice; };
	inline	static CPlayer * GetPlayer(void) { return m_pPlayer; };
	inline	static CPlayerObj * GetPlayerobj(void) { return m_pPlayerobj; };
	inline static CGoal *GetGoal(void) { return m_pGoal; };
	inline static CRobo * GetRobo(void) { return m_pRobo; };
	inline	static CEnemy*GetEnemy(void) { return m_Enemy; };
	inline	static CPause*GetPause(void) { return m_pPause; };
	inline	static CPAUSESELECT*GetPauseSerect(void) { return m_pPauseSerect; };
	inline	static CBullet * GetBullet(void) { return m_pBullet; };
	inline	static CEffect * GetEffect(void) { return m_pEffect; };
	inline	static CRogowaku * GetRogowaku(void) { return m_rogowaku; };
	inline	static CFONT* GetFont(void) { return m_pFont; };
	inline static CFontMode* GetFontMode(void) { return m_pFontMode; };
	inline	static CDebug* GetDebug(void) { return m_pDebug; };
	inline	static Cblock* GetBlock(void) { return m_pBlock; };
	inline	static CBg* GetBg(void) { return m_pBg; };
	inline	static CScore* GetScore(void) { return m_pScore; };
	inline	static CTime *GetTime(void) { return m_pTime; };
	inline	static CTimer *GetTimer(void) { return m_pTimer; };
	inline	static CManeger* GetManagement(void) { return m_pManagement; };
	inline static CLevel* GetLevel(void) { return m_pLevel; };
	inline static CCAPSULEENEMY*GetCapsuleEnemy(void) { return m_pCapsuleEnemy; };
	inline static CCapsule*GetCapSule(void) { return m_pCapsule; };
	static CGameStage2 *Create(void);
private:
	static CFONT *m_pFont;
	static CFontMode *m_pFontMode;
	static cLife *m_pLife;
	static CGoal *m_pGoal;
	static CBUilding *m_pBuiliding;
	static CBoss *m_pBoss;
	static CPause *m_pPause;

	static CPAUSESELECT *m_pPauseSerect;

	static CDice *m_pDice;
	static CScore *m_pScore;

	static CPlayer *m_pPlayer;
	static CBullet*m_pBullet;
	static CEffect*m_pEffect;
	static CPlayerObj *m_pPlayerobj;
	static CRobo *m_pRobo;
	static CEnemy *m_Enemy;
	static CRogowaku *m_rogowaku;
	static CDebug *m_pDebug;
	static Cblock *m_pBlock;
	static CBg *m_pBg;
	static CManeger *m_pManagement;
	static CTime *m_pTime;
	static CLevel *m_pLevel;
	static CTimer *m_pTimer;
	static CCAPSULEENEMY *m_pCapsuleEnemy;
	static CCapsule *m_pCapsule;
	CPAUSESELECT::SELECTMODE	*m_Pause;
	CManeger::MODE m_mode;
	CFade *m_apfade;
	bool m_bPouse;
	bool m_bDebug;

};
#endif