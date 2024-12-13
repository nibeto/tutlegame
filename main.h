//=============================================================================
//
// ���C������ [main.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <stdio.h>//�X�^���_�[�h�A�C�I�[I/O���o�͗p�̃w�b�_�[
#include <stdlib.h>//�X�^���_�[�h���C�u�����[//�����h�Ȃǂ̃��C�u�����[�p�̃w�b�_�[
#include <string.h>//������̊֐����Ăяo�����߂̃w�b�_�[
#include <time.h>
#include <iostream>//I/O stream
#include <fstream>
#include <sstream>
#include <bitset>  // std::bitset<N>
#include <random>//c++�̃����_���w�b�_�[
#include <atlstr.h>
#include <vector>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"
#include "xaudio2.h"				  //�@�T�E���h�����ŕK�v
#include "XInput.h"
#include <vcruntime_exception.h>
#include <list>
#include <utility> // move
#include <cstdlib>
#include <chrono>
#include <deque>
#include <bitset>
#include <array>
//�O���錾
class CRenderer;
class CScene2D;
class CSCENE3D;
using namespace std;//���O��Ԗ�
//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma	comment(lib,"d3d9.lib")
#pragma	comment(lib,"d3dx9.lib")
#pragma	comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment (lib, "xinput.lib")	//���͏����ɕK�v
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�̍ő吔
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define SCREEN_HEIGHT_Y_2	(610)		// �E�C���h�E�̍���
//2D�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//3D�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;//���_���W
	float rhw;//1,0f�ŌŒ�
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}VERTEX_2D;

// 3D�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
} VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//CRenderer *GetRenderer(void);
//CScene2D *GetScense2D(int nNumScene2D);
//CSCENE3D *GetScense3D(int nNumScene3D);

//CSCENE2D **GetScense(void);

#ifdef _DEBUG
int GetFps(void);
#endif // _DEBUG
#define MAX_SCENE       (256)
#define MAX_SCENE3D       (256)
#define MAX_DEFFULT       (3)

#define MAX_SCORE_DIGIT	(5)//�X�R�A�̍ő吔
#define MAX_TIME_DIGIT	(2)//�X�R�A�̍ő吔
#define MAX_BULLETLIFE_DIGIT (5)
#endif