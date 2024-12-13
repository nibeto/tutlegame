//=============================================================================
//
// ���͏��� [input.cpp]
// Author :
//
//=============================================================================
#include"light.h"
#include"manager.h"
#include"renderer.h"
//*************************************************************************************************************************
CLIGHT *CLIGHT::Create(void)
{
	//�C���X�^���X
	CLIGHT*plight = NULL;
	plight = new CLIGHT;
	if (plight != NULL)
	{
		plight->Init();
	}
	return plight;



}

CLIGHT::CLIGHT()
{

	m_pDevice = NULL;

}
CLIGHT::~CLIGHT()
{

}


HRESULT  CLIGHT::Init(void)
{



		CRenderer *pRenderer = CManeger::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		D3DXVECTOR3 vecDir;

		// ���C�g���N���A����
		ZeroMemory(&m_light, sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light.Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.2f, -0.5f, 0.4f);

		D3DXVec3Normalize(&vecDir, &vecDir);			//���K������
		m_light.Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(0, &m_light);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(0, TRUE);

		return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLIGHT::Uninit(void)
{

}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLIGHT::Update(void)
{
}

