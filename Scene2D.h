//=============================================================================
// ���C������ [Scene2D.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include"main.h"
#include"scene.h"
//�����_�����O�N���X
class CScene2D : public CScene
{
public:
	//�R���X�g���N�^
	CScene2D(LAYER m_Number);
	//�f�X�g���N�^
	~CScene2D();
	//������
    HRESULT Init(void);
	//�I��
	void Uninit(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);


	void DrawPrimitive(void);
	void SetPosScore(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void MoveNormalizeVector(D3DXVECTOR3 move, float fSpeed);

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot,float LengthX, float LengthY);
	void SetNOARMALAnimation(int nPattanAnimation,float fWight, float fHight);
	void SetAnimation(float fWight, float fHight);
	void SetPlayerAnimation(float fWight, float fHight);
	void SetBgAnimation(D3DXVECTOR2 tex);
	void SetRot(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void SetRotTimer(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float LengthX, float LengthY);
	void SetZoominandoutandRot(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot, float Length);
	void SetNOMAL(D3DXVECTOR3 pos, float LengthX, float LengthY);
	void SetNOMALENEMY(D3DXVECTOR3 pos, D3DXVECTOR3 move,float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void SetNOMALDice(D3DXVECTOR3 pos, D3DXVECTOR3 move, float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void SetNOMALPOS(D3DXVECTOR3 pos, float LengthX, float LengthY);
	void SetHP(D3DXVECTOR3 pos, float LengthX, float LengthY,float colR,float colG,float colB,float colA );
	void SetMagicPoint(D3DXVECTOR3 pos, float LengthX, float LengthY, float colR, float colG, float colB, float colA);
	void SetBG(D3DXVECTOR3 pos, float LengthX, float LengthY, OBJECT_TYPE type);
	void SetPoligon(D3DXVECTOR3 pos, float LengthX, float LengthY, D3DXVECTOR2 tex, float colR, float colG, float colB, float colA);
	void SetPlayer(D3DXVECTOR3 pos, float LengthX, float LengthY,  D3DXVECTOR2 tex,  float colR, float colG, float colB, float colA);
	bool CorisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3	*pMove,bool bLand,float *f_sizeX,float *f_sizeY);
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXVECTOR3 move,  float colR, float colG, float colB, float colA, float rot, float LengthX, float LengthY, float fRadius);
	void SetAround(void);
	void SetMove(D3DXVECTOR3 &move, float fSpeed);
	void Fade(D3DXVECTOR3 pos, float LengthX, float LengthY,D3DXCOLOR col);
	void SetPattanAnim(int nPattanAnim);
	void MakeVertexScore(void);
	void MouseMove(D3DXVECTOR3 &move, float fSpeed);

	void MouseTarget(void);
	void Scene2DMove(float &f_MoveX, float &f_MoveY,float f_Rot, float f_Rot2, D3DXVECTOR3 &move,float m_fSpeed);


	//D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& nomal);
	//D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& nomal);

	LPDIRECT3DDEVICE9 GetMakeVertexScore(void);

	inline D3DXVECTOR3 GetPotion(void) { return m_pos; };
	inline D3DXVECTOR3 GetRot(void){return m_rot; };
	inline D3DXVECTOR2 GetTex(void) { return m_tex; };

	inline D3DXVECTOR3 GetMove(void) { return m_move; };
	inline D3DXCOLOR GetCol(void) { return m_col; };


	inline float GetLength(void) { return m_fPosSize; };
	inline float GetLengthX(void) { return m_fPosSizeX; };
	inline float GetLengthY(void) { return m_fPosSizeY; };

	inline float GetfRot(void) { return m_fRot; };
	inline float GetfRot1(void) { return m_fRot1; };
	inline float GetfTimerRot(void) { return m_fRotTimer; };

	static CScene2D *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);
	void Save(void);
	void Load(void);
	static CScene2D *GetScene2D(void) { return m_pScene2D; };
protected:
	LPDIRECT3DDEVICE9 pDevice;
	int m_nPriority;
	int nNumData = 0;
	int m_nCountRot = 0;			//�J�E���^�ϐ�
	float m_fPosSize = 0.0f;	//�T�C�Y�ύX�p
	float m_fPosSizeX = 0.0f;	//�T�C�Y�ύX�p
	float m_fPosSizeY = 0.0f;	//�T�C�Y�ύX�p
	float m_fRot1 = 0.0f;	//��](float�ϐ�)
	float m_fAroundRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotTimer = D3DX_PI *0.25f;	//��](float�ϐ�)

	float m_fRot = D3DX_PI * 0.25f;	//��](float�ϐ�)
	float m_fRotRand = 0.0f;	//��](float�ϐ�)
	float m_fRotRand1 = 0.0f;	//��](float�ϐ�)
	float fSpeedUp = 6.0f;//�ړ��̑��x*����̓X�s�[�h�A�b�v�ł͂Ȃ�*
	float mf_pos = 0.0f;//(pos�̒����̕ϐ�)
	int nCountAnime;
	int nCountBg;

	bool bUse;
	bool bDraw;
	int nCountBullet;

	bool m_bjump;
	bool m_bDisp;


	float m_fRadius;			// ���a(�傫��)

	static int m_nLife;
	int m_nMagicPoint = 0;
	SCENE_NUMBER_TYPE m_nNumber;//�`�揇��
	LAYER m_layer;


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	static CScene2D *m_pScene2D;
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR2				m_tex;
	D3DXVECTOR3 m_move;
	D3DXCOLOR				m_col;
	D3DXVECTOR3 m_rot;
	bool bLand;
	int nPattenAnime;
	int nPattenAnime2;

};
#endif
