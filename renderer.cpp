//=============================================================================
//
// ���C������ [renderer.cpp]
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
// �}�N����`
//*****************************************************************************


//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
//LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;

//===================================================================
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//===================================================================
CRenderer::~CRenderer()
{

}

//===================================================================
//	����������
//===================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	try
	{

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

																	// �f�o�C�X�̐���
																	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
																			// �f�o�b�O���\���p�t�H���g�̐���
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
// �I������
//==================================================================
void CRenderer::Uninit(void)
{
	try
	{

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
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
// �X�V����
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
		//3D�|���S���̍X�V����
		//CSceneNum3D::Update3DALL();
		break;
	case CRenderer::CsceneName_Scene2D:
		//�|���S���̍X�V����
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
// �`�揈��
//==================================================================
void CRenderer::Draw(void)
{

	try
	{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawALL();

		//sceneName = SceneName;
		switch (sceneName)
		{
		case CRenderer::CsceneName_SceneName3D:
			// 3D�|���S���̕`�揈��
			//CSceneNum3D::Draw3DALL();
			break;
		case CRenderer::CsceneName_Scene2D:
			// �|���S���̕`�揈��

			break;
		case CRenderer::CsceneName_MAX:
			break;
		default:
			break;
		}
		CFade*pFade = CManeger::GetFade();

		pFade->Draw();

#ifdef _DEBUG
		// FPS�\��
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
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
	catch (const std::exception&)
	{

	}

}


#ifdef _DEBUG
//==================================================================
// FPS�\��
//==================================================================
void CRenderer::DrawFPS(void)
{
	int nFPS = GetFps();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nFPS);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//==================================================================
// PLayer�̍��W�\��
//==================================================================
void CRenderer::DrawPlayerFps(void)
{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();
	if (bDebug == false)
	{

		//	�v���C���[�̏����擾
		CPlayer *pPlayer = CGame::GetPlayer();;
		//	�v���C���[�̏��(pos)���擾
		D3DXVECTOR3 pos = pPlayer->GetPos();
		//	�v���C���[�̏��(move)���擾
		D3DXVECTOR3 move = pPlayer->GetMove();

		D3DXVECTOR2 tex = pPlayer->GetTex();

		//	�v���C���[�̏��(pos)���擾
		float f_moveX = pPlayer->GetfmoveX();
		float f_moveY = pPlayer->GetfmoveY();
		float f_moveZ = pPlayer->GetfmoveZ();

		int n_PrioTy = pPlayer->GetPrioTy();

	//LPDIRECT3DTEXTURE9 m_apTexture = pPlayer->GetTexTure();



			//(char*)m_apTexture;
			const char cPlayerTest[] = "---------- �v���C���[�̏�� -----------------";
			const char cPlayerTest0[] = "--------------------------------------------";
			const char cPlayerTest1[] = "--\n--\n--\n--\n--\n--\n--\n--\n--\n";
			const char cPlayerTest2[] = "-\n-\n-\n-\n-\n-\n-\n-\n-\n";

			char str[256];


			RECT reccharTest = { 150, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
			//�e�L�X�g����\��
			sprintf(str, "%s\n", cPlayerTest);
			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &reccharTest, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			RECT reccharTest0 = { 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT };
			//�e�L�X�g����\��
			sprintf(str, "\n%s\n", cPlayerTest0);
			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &reccharTest0, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




			RECT reccharTest1 = { 500,50, SCREEN_WIDTH, SCREEN_HEIGHT };
			//�e�L�X�g����\��
			sprintf(str, "%s\n", cPlayerTest1);
			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &reccharTest1, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


			RECT reccharTest2 = { 145,50, SCREEN_WIDTH, SCREEN_HEIGHT };
			//�e�L�X�g����\��
			sprintf(str, "%s\n", cPlayerTest2);
			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &reccharTest2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




			RECT rectpos = { 160, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

			//�v���C���[��(pos)����\��
			sprintf(str, "pos:%.2f:%.2f:%.2f\n", pos.x, pos.y, pos.z);

			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &rectpos, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));



			RECT rectfmove = { 160, 100, SCREEN_WIDTH, SCREEN_HEIGHT };


			//�v���C���[��(move)����\��
			sprintf(str, "move:%.2f:%.2f:%.2f\n", f_moveX, f_moveY, f_moveZ);

			//�e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &rectfmove, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


			RECT rectPrioty = { 180, 200, SCREEN_WIDTH, SCREEN_HEIGHT };


			//�v���C���[��(move)����\��
			sprintf(str, "�`�揇��:%d\n", n_PrioTy);

			//�e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &rectPrioty, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		}
}
void CRenderer::DrawBlockFps(void)
{

	CManeger*pManager = CGame::GetManagement();

	bool bDebug = pManager->GetDebug();
	if (bDebug == false)
	{
		//	�v���C���[�̏����擾
		CDebug *pBlock = CGame::GetDebug();;


		//	�v���C���[�̏��(pos)���擾
		D3DXVECTOR3 pos = pBlock->GetPos();


		//	�v���C���[�̏��(pos)���擾
		float f_sizeX = pBlock->GetSizeX();
		float f_sizeY = pBlock->GetSizeY();



		//(char*)m_apTexture;
		const char cPlayerTest[] = "---------- �n�ʂ̏�� -----------------";
		const char cPlayerTest0[] = "--------------------------------------------";
		const char cPlayerTest1[] = "--\n--\n--\n--\n--\n--\n--\n--\n--\n";
		const char cPlayerTest2[] = "-\n-\n-\n-\n-\n-\n-\n-\n-\n";

		char str[256];


		RECT reccharTest = { 550, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
		//�e�L�X�g����\��
		sprintf(str, "%s\n", cPlayerTest);
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &reccharTest, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		RECT reccharTest0 = { 550, 200, SCREEN_WIDTH, SCREEN_HEIGHT };
		//�e�L�X�g����\��
		sprintf(str, "\n%s\n", cPlayerTest0);
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &reccharTest0, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




		RECT reccharTest1 = { 550,50, SCREEN_WIDTH, SCREEN_HEIGHT };
		//�e�L�X�g����\��
		sprintf(str, "%s\n", cPlayerTest1);
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &reccharTest1, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		RECT reccharTest2 = { 550,50, SCREEN_WIDTH, SCREEN_HEIGHT };
		//�e�L�X�g����\��
		sprintf(str, "%s\n", cPlayerTest2);
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &reccharTest2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		RECT rectSize = { 580, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

		//�v���C���[��(pos)����\��
		sprintf(str, "size:%f:%f\n", f_sizeX, f_sizeY);

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rectSize, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));




		RECT rectpos = { 580, 150, SCREEN_WIDTH, SCREEN_HEIGHT };

		//�v���C���[��(pos)����\��
		sprintf(str, "pos:%.2f:%.2f:%.2f\n", pos.x, pos.y, pos.z);

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rectpos, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

}
#endif
