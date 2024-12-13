//=============================================================================
//
// メイン処理 [renderer.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include"renderer.h"
#include "InputKeyboard.h"
#include "joypad.h"
#include"mouse.h"
#include"bullet.h"
#include"sound.h"
class CTitle;
class CGame;
class CGameStage2;
class CResult;
class CGamaClear;
class CGameOver;
class CPlayerObj;
class CFontMode;
class CFade;
class CRanking;
//レンダリングクラス
class CManeger
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_GAMESTAGE2,
		MODE_RESULT,
		MODE_GAMECLEAR,
		MODE_GAMEOVER,
		MODE_RANKING,
        MODE_MAX
	}MODE;

	CManeger();
	~CManeger();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT SetMode(MODE mode);

	inline	static CRenderer * GetRenderer(void) { return m_pRenderer; };
	inline static CRanking * GetRanking(void) { return m_pRanking; };

	inline 	static CJoypad * GetJoypad(void) { return m_pjoypad; };
	inline static CMouse * GetMouse(void) { return m_pMouse; };

	inline static CInputKeyboard * GetInput(void) { return m_pinputKeyboard; };
	inline	static CSound * GetSound(void) {return m_pPlaySound; };

	inline	static CFade * GetFade(void) { return m_pfade; };


	inline	static CTitle * GetTitle(void) { return m_ptitle; };
	inline	static CGame * GetGame(void) { return m_pGame; };
	inline	static CGameStage2 * GetGameStage(void) { return m_pGameStage2; };
	inline	static CResult * GetResult(void) { return m_presult; };
	inline	static bool  GetDebug(void) { return m_bDebug; };
	inline	static MODE GetMode(void) { return m_Mode; };
	inline static CManeger *GetManaher(void) { return m_pManager; };
	inline static CFontMode *GetFintMode(void) { return m_pFontMode; };
	inline static CGamaClear *GetGameClear(void) { return m_pGameClear; };
	inline static CGameOver *GetGameOver(void) { return m_pGameOver; };

protected:
	static CRenderer *m_pRenderer;
	static CManeger *m_pManager;

	static MODE m_Mode;
	static bool m_bDebug;

private:
	static CJoypad *m_pjoypad;
	static CMouse *m_pMouse;
	static CInputKeyboard *m_pinputKeyboard;
	static CSound *m_pPlaySound;
	static CRanking *m_pRanking;
	static CPlayerObj *m_pPlayerobj;
	static CFade *m_pfade;
	static CFontMode *m_pFontMode;

	static CTitle *m_ptitle;
	static CGame *m_pGame;
	static CGameStage2 *m_pGameStage2;
	static CResult *m_presult;
	static CGamaClear *m_pGameClear;
	static CGameOver *m_pGameOver;

	bool m_bPouse;

};


#endif