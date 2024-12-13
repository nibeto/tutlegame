//=============================================================================
//
// メイン処理 [renderer.cpp]
// Author :moritakamasaya
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"sceneNum3D.h"
#include"Scene2D.h"
#include"Game.h"
#include"Player.h"
#include"Debug.h"
#include"manager.h"
#include"Fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//===================================================================
//	静的メンバ変数宣言
//===================================================================
//LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;

//===================================================================
//	コンストラクタ
//===================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
#ifdef _DEBUG
	m_pFont = NULL;
#endif
}

//===================================================================
//	デストラクタ
//===================================================================
CRenderer::~CRenderer()
{

}

//===================================================================
//	初期化処理
//===================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	try
	{

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

																	// デバイスの生成
																	// ディスプレイアダプタを表すためのデバイスを作成
																	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

#ifdef _DEBUG
																			// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif
	}
	catch (const std::exception&)
	{

	}

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CRenderer::Uninit(void)
{
	try
	{

#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	}
	catch (const std::exception&)
	{

	}

}

//==================================================================
// 更新処理
//==================================================================
void CRenderer::Update(void)
{

	try
	{

	CScene::UpdateALL();

	//sceneName = SceneName;
	switch (sceneName)
	{
	case CRenderer::CsceneName_SceneName3D:
		//3Dポリゴンの更新処理
		//CSceneNum3D::Update3DALL();
		break;
	case CRenderer::CsceneName_Scene2D:
		//ポリゴンの更新処理
		break;
	case CRenderer::CsceneName_MAX:
		break;
	default:
		break;
	}
	}
	catch (const std::exception&)
	{

	}

}

//==================================================================
// 描画処理
//==================================================================
void CRenderer::Draw(void)
{

	try
	{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();

	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawALL();

		//sceneName = SceneName;
		switch (sceneName)
		{
		case CRenderer::CsceneName_SceneName3D:
			// 3Dポリゴンの描画処理
			//CSceneNum3D::Draw3DALL();
			break;
		case CRenderer::CsceneName_Scene2D:
			// ポリゴンの描画処理

			break;
		case CRenderer::CsceneName_MAX:
			break;
		default:
			break;
		}
		CFade*pFade = CManeger::GetFade();

		pFade->Draw();

#ifdef _DEBUG
		// FPS表示
		DrawFPS();

		if (bDebug == false)
		{


			CManeger::MODE m_mode = CManeger::GetMode();
			if (m_mode == CManeger::MODE_GAME)
			{
				DrawBlockFps();
				DrawPlayerFps();

			}
		}
#endif
		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
	catch (const std::exception&)
	{

	}

}


#ifdef _DEBUG
//==================================================================
// FPS表示
//==================================================================
void CRenderer::DrawFPS(void)
{
	int nFPS = GetFps();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nFPS);

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//==================================================================
// PLayerの座標表示
//==================================================================
void CRenderer::DrawPlayerFps(void)
{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();
	if (bDebug == false)
	{

		//	プレイヤーの情報を取得
		CPlayer *pPlayer = CGame::GetPlayer();;
		//	プレイヤーの情報(pos)を取得
		D3DXVECTOR3 pos = pPlayer->GetPos();
		//	プレイヤーの情報(move)を取得
		D3DXVECTOR3 move = pPlayer->GetMove();

		D3DXVECTOR2 tex = pPlayer->GetTex();

		//	プレイヤーの情報(pos)を取得
		float f_moveX = pPlayer->GetfmoveX();
		float f_moveY = pPlayer->GetfmoveY();
		float f_moveZ = pPlayer->GetfmoveZ();

		int n_PrioTy = pPlayer->GetPrioTy();

	//LPDIRECT3DTEXTURE9 m_apTexture = pPlayer->GetTexTure();



			//(char*)m_apTexture;
			const char cPlayerTest[] = "---------- プレイヤーの情報 -----------------";
			const char cPlayerTest0[] = "--------------------------------------------";
			const char cPlayerTest1[] = "--\n--\n--\n--\n--\n--\n--\n--\n--\n";
			const char cPlayerTest2[] = "-\n-\n-\n-\n-\n-\n-\n-\n-\n";

			char str[256];


			RECT reccharTest = { 150, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
			//テキスト情報を表示
			sprintf(str, "%s\n", cPlayerTest);
			// テキスト描画
			m_pFont->DrawText(NULL, str, -1, &reccharTest, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			RECT reccharTest0 = { 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT };
			//テキスト情報を表示
			sprintf(str, "\n%s\n", cPlayerTest0);
			// テキスト描画
			m_pFont->DrawText(NULL, str, -1, &reccharTest0, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




			RECT reccharTest1 = { 500,50, SCREEN_WIDTH, SCREEN_HEIGHT };
			//テキスト情報を表示
			sprintf(str, "%s\n", cPlayerTest1);
			// テキスト描画
			m_pFont->DrawText(NULL, str, -1, &reccharTest1, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


			RECT reccharTest2 = { 145,50, SCREEN_WIDTH, SCREEN_HEIGHT };
			//テキスト情報を表示
			sprintf(str, "%s\n", cPlayerTest2);
			// テキスト描画
			m_pFont->DrawText(NULL, str, -1, &reccharTest2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




			RECT rectpos = { 160, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

			//プレイヤーの(pos)情報を表示
			sprintf(str, "pos:%.2f:%.2f:%.2f\n", pos.x, pos.y, pos.z);

			// テキスト描画
			m_pFont->DrawText(NULL, str, -1, &rectpos, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));



			RECT rectfmove = { 160, 100, SCREEN_WIDTH, SCREEN_HEIGHT };


			//プレイヤーの(move)情報を表示
			sprintf(str, "move:%.2f:%.2f:%.2f\n", f_moveX, f_moveY, f_moveZ);

			//テキスト描画
			m_pFont->DrawText(NULL, str, -1, &rectfmove, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


			RECT rectPrioty = { 180, 200, SCREEN_WIDTH, SCREEN_HEIGHT };


			//プレイヤーの(move)情報を表示
			sprintf(str, "描画順番:%d\n", n_PrioTy);

			//テキスト描画
			m_pFont->DrawText(NULL, str, -1, &rectPrioty, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		}
}
void CRenderer::DrawBlockFps(void)
{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();
	if (bDebug == false)
	{
		//	プレイヤーの情報を取得
		CDebug *pBlock = CGame::GetDebug();;


		//	プレイヤーの情報(pos)を取得
		D3DXVECTOR3 pos = pBlock->GetPos();


		//	プレイヤーの情報(pos)を取得
		float f_sizeX = pBlock->GetSizeX();
		float f_sizeY = pBlock->GetSizeY();



		//(char*)m_apTexture;
		const char cPlayerTest[] = "---------- 地面の情報 -----------------";
		const char cPlayerTest0[] = "--------------------------------------------";
		const char cPlayerTest1[] = "--\n--\n--\n--\n--\n--\n--\n--\n--\n";
		const char cPlayerTest2[] = "-\n-\n-\n-\n-\n-\n-\n-\n-\n";

		char str[256];


		RECT reccharTest = { 550, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
		//テキスト情報を表示
		sprintf(str, "%s\n", cPlayerTest);
		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &reccharTest, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		RECT reccharTest0 = { 550, 200, SCREEN_WIDTH, SCREEN_HEIGHT };
		//テキスト情報を表示
		sprintf(str, "\n%s\n", cPlayerTest0);
		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &reccharTest0, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




		RECT reccharTest1 = { 550,50, SCREEN_WIDTH, SCREEN_HEIGHT };
		//テキスト情報を表示
		sprintf(str, "%s\n", cPlayerTest1);
		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &reccharTest1, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		RECT reccharTest2 = { 550,50, SCREEN_WIDTH, SCREEN_HEIGHT };
		//テキスト情報を表示
		sprintf(str, "%s\n", cPlayerTest2);
		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &reccharTest2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		RECT rectSize = { 580, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

		//プレイヤーの(pos)情報を表示
		sprintf(str, "size:%f:%f\n", f_sizeX, f_sizeY);

		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &rectSize, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




		RECT rectpos = { 580, 150, SCREEN_WIDTH, SCREEN_HEIGHT };

		//プレイヤーの(pos)情報を表示
		sprintf(str, "pos:%.2f:%.2f:%.2f\n", pos.x, pos.y, pos.z);

		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &rectpos, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

}
#endif
