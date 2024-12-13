#include"fontMode.h"
#include"manager.h"
#include"font.h"
CFONT* CFontMode::m_pFont = NULL;
CManeger::MODE CFontMode::m_mode;
//***************************************
//コンストラクタ
//***************************************
CFontMode::CFontMode()
{
	m_nTime = 60;

}
//***************************************
//デストラクタ
//***************************************
CFontMode::~CFontMode()
{

}
//***************************************
//初期化処理
//***************************************
void CFontMode::Init(CManeger::MODE mode)
{
	m_nTime = 60;
	m_mode = mode;
	FontMode(mode);
}
//***************************************
//終了処理
//***************************************

void CFontMode::Uninit(void)
{
}
//***************************************
//更新処理
//***************************************
void CFontMode::Update(CManeger::MODE mode)
{
	try
	{
		m_mode = CManeger::GetMode();


		m_mode = mode;

		if (m_mode == CManeger::MODE_TITLE)
		{
			m_nTime += -1;


//***************************************
//文字を順番に表示
//***************************************
#ifdef _DEBUG

			if (m_nTime < 60)
			{
				m_pFont = CFONT::Create(RECT{ 200 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "h ", "", 0, FONT_NUMBER_2, CFONT::FONTSTATE_NONE, true, m_nTime);
			}
			if (m_nTime < 50)
			{
				m_pFont = CFONT::Create(RECT{ 250 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "o", "", 0, FONT_NUMBER_3, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 45)
			{
				m_pFont = CFONT::Create(RECT{ 300 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "g", "", 0, FONT_NUMBER_4, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 40)
			{
				m_pFont = CFONT::Create(RECT{ 350 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "e", "", 0, FONT_NUMBER_5, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 35)
			{
				m_pFont = CFONT::Create(RECT{ 400 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "1", "", 0, FONT_NUMBER_6, CFONT::FONTSTATE_NONE, true, m_nTime);

		}

#else


			if (m_nTime < 60)
			{
				m_pFont = CFONT::Create(RECT{ 300 , 200, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 0.5f, 0.5f , 1.0f }, "タイトル名＞", "%d", 0, FONT_NUMBER_0, CFONT::FONTSTATE_RANKDOWN, true, m_nTime);

				m_pFont = CFONT::Create(RECT{ 200 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "タ", "", 0, FONT_NUMBER_2, CFONT::FONTSTATE_NONE, true, m_nTime);
			}
			if (m_nTime < 50)
			{
				m_pFont = CFONT::Create(RECT{ 450 , 310, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.425f, 0.325f, 0.225f , 1.0f }, "Turtleシューティング", "%d", 0, FONT_NUMBER_0, CFONT::FONTSTATE_RANKSET, true, m_nTime);

				m_pFont = CFONT::Create(RECT{ 400 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "イ", "", 0, FONT_NUMBER_3, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 45)
			{
				m_pFont = CFONT::Create(RECT{ 500 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "ト", "", 0, FONT_NUMBER_4, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 40)
			{
				m_pFont = CFONT::Create(RECT{ 650 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "ル", "", 0, FONT_NUMBER_5, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 35)
			{
				m_pFont = CFONT::Create(RECT{ 700 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "画面", "", 0, FONT_NUMBER_6, CFONT::FONTSTATE_NONE, true, m_nTime);

			}

#endif
		}
#ifdef _DEBUG

#else

		else if (m_mode == CManeger::MODE_GAME)
		{
			m_nTime += -1;

			if (m_nTime < 60)
			{
				m_pFont = CFONT::Create(RECT{ 200 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "ゲ ", "", 0, FONT_NUMBER_7, CFONT::FONTSTATE_NONE, true, m_nTime);
			}
			if (m_nTime < 50)
			{
				m_pFont = CFONT::Create(RECT{ 250 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "ー", "", 0, FONT_NUMBER_8, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 45)
			{
				m_pFont = CFONT::Create(RECT{ 300 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "ム", "", 0, FONT_NUMBER_9, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 40)
			{
				m_pFont = CFONT::Create(RECT{ 350 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "画面", "", 0, FONT_NUMBER_10, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 35)
			{
				m_pFont = CFONT::Create(RECT{ 400 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "", "", 0, FONT_NUMBER_11, CFONT::FONTSTATE_NONE, true, m_nTime);

			}



			m_pFont->BreakFont(FONT_NUMBER_0);
			m_pFont->BreakFont(FONT_NUMBER_2);
			m_pFont->BreakFont(FONT_NUMBER_3);
			m_pFont->BreakFont(FONT_NUMBER_4);
			m_pFont->BreakFont(FONT_NUMBER_5);
			m_pFont->BreakFont(FONT_NUMBER_6);

		}
		else if (m_mode == CManeger::MODE_GAMESTAGE2)
		{
			m_nTime += -1;

			if (m_nTime < 60)
			{
				m_pFont = CFONT::Create(RECT{ 200 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "一 ", "", 0, FONT_NUMBER_12, CFONT::FONTSTATE_NONE, true, m_nTime);
			}
			if (m_nTime < 50)
			{
				m_pFont = CFONT::Create(RECT{ 250 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "の", "", 0, FONT_NUMBER_13, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 45)
			{
				m_pFont = CFONT::Create(RECT{ 300 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "二", "", 0, FONT_NUMBER_14, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 40)
			{
				m_pFont = CFONT::Create(RECT{ 350 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "", "", 0, FONT_NUMBER_15, CFONT::FONTSTATE_NONE, true, m_nTime);

			}
			if (m_nTime < 35)
			{
				m_pFont = CFONT::Create(RECT{ 400 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "", "", 0, FONT_NUMBER_16, CFONT::FONTSTATE_NONE, true, m_nTime);

			}



			m_pFont->BreakFont(FONT_NUMBER_7);
			m_pFont->BreakFont(FONT_NUMBER_8);
			m_pFont->BreakFont(FONT_NUMBER_9);
			m_pFont->BreakFont(FONT_NUMBER_10);
			m_pFont->BreakFont(FONT_NUMBER_11);
		}
		else if (m_mode == CManeger::MODE_RESULT)
		{
			m_pFont->BreakFont(FONT_NUMBER_0);
			m_pFont->BreakFont(FONT_NUMBER_1);
			m_pFont->BreakFont(FONT_NUMBER_2);
			m_pFont->BreakFont(FONT_NUMBER_3);
			m_pFont->BreakFont(FONT_NUMBER_4);
			m_pFont->BreakFont(FONT_NUMBER_5);
			m_pFont->BreakFont(FONT_NUMBER_6);
			m_pFont->BreakFont(FONT_NUMBER_7);
			m_pFont->BreakFont(FONT_NUMBER_8);
			m_pFont->BreakFont(FONT_NUMBER_9);
			m_pFont->BreakFont(FONT_NUMBER_10);
			m_pFont->BreakFont(FONT_NUMBER_11);
			m_pFont->BreakFont(FONT_NUMBER_12);
			m_pFont->BreakFont(FONT_NUMBER_13);
			m_pFont->BreakFont(FONT_NUMBER_14);
			m_pFont->BreakFont(FONT_NUMBER_15);
			m_pFont->BreakFont(FONT_NUMBER_16);

		}
#endif // _DEBUG

	}
	catch (const std::exception&)
	{

	}


}
//***************************************
//モード事に消す処理
//***************************************
void CFontMode::FontMode(CManeger::MODE mode)
{

	try
	{
		m_mode = mode;

		switch (m_mode)
		{
		case CManeger::MODE_TITLE:
			break;
		case CManeger::MODE_GAME:
			m_pFont = CFONT::Create(RECT{ 300 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "通常のステージ > ", "%d", 0, FONT_NUMBER_1, CFONT::FONTSTATE_RANKDOWN, true, m_nTime);
			m_pFont->BreakFont(FONT_NUMBER_0);
			m_pFont->BreakFont(FONT_NUMBER_2);
			m_pFont->BreakFont(FONT_NUMBER_3);
			m_pFont->BreakFont(FONT_NUMBER_4);
			m_pFont->BreakFont(FONT_NUMBER_5);
			m_pFont->BreakFont(FONT_NUMBER_6);
			m_pFont->BreakFont(FONT_NUMBER_12);
			break;
		case CManeger::MODE_GAMESTAGE2:
			m_pFont = CFONT::Create(RECT{ 300 , 100, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR{ 0.5f, 1.0f, 1.0 , 1.0f }, "通常のステージ > ", "%d", 0, FONT_NUMBER_12, CFONT::FONTSTATE_RANKDOWN, true, m_nTime);
			m_pFont->BreakFont(FONT_NUMBER_1);
			m_pFont->BreakFont(FONT_NUMBER_2);
			m_pFont->BreakFont(FONT_NUMBER_3);
			m_pFont->BreakFont(FONT_NUMBER_4);
			m_pFont->BreakFont(FONT_NUMBER_5);
			m_pFont->BreakFont(FONT_NUMBER_6);
			break;
		case CManeger::MODE_RESULT:
			m_pFont->BreakFont(FONT_NUMBER_0);
			m_pFont->BreakFont(FONT_NUMBER_1);
			m_pFont->BreakFont(FONT_NUMBER_2);
			m_pFont->BreakFont(FONT_NUMBER_3);
			m_pFont->BreakFont(FONT_NUMBER_4);
			m_pFont->BreakFont(FONT_NUMBER_5);
			m_pFont->BreakFont(FONT_NUMBER_6);
			m_pFont->BreakFont(FONT_NUMBER_12);
			break;
		default:
			break;
		}

	}
	catch (const std::exception&)
	{

	}

}