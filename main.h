//=============================================================================
//
// メイン処理 [main.h]
// Author :moritakamasaya
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include <stdio.h>//スタンダードアイオーI/O入出力用のヘッダー
#include <stdlib.h>//スタンダードライブラリー//ランドなどのライブラリー用のヘッダー
#include <string.h>//文字列の関数を呼び出すためのヘッダー
#include <time.h>
#include <iostream>//I/O stream
#include <fstream>
#include <sstream>
#include <bitset>  // std::bitset<N>
#include <random>//c++のランダムヘッダー
#include <atlstr.h>
#include <vector>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"
#include "xaudio2.h"				  //　サウンド処理で必要
#include "XInput.h"
#include <vcruntime_exception.h>
#include <list>
#include <utility> // move
#include <cstdlib>
#include <chrono>
#include <deque>
#include <bitset>
#include <array>
//前方宣言
class CRenderer;
class CScene2D;
class CSCENE3D;
using namespace std;//名前空間名
//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma	comment(lib,"d3d9.lib")
#pragma	comment(lib,"d3dx9.lib")
#pragma	comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻取得
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment (lib, "xinput.lib")	//入力処理に必要
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// キーの最大数
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ
#define SCREEN_HEIGHT_Y_2	(610)		// ウインドウの高さ
//2Dポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//3Dポリゴン頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 頂点カラー / テクスチャ座標 )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;//頂点座標
	float rhw;//1,0fで固定
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}VERTEX_2D;

// 3Dポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ
} VERTEX_3D;

//*****************************************************************************
// プロトタイプ宣言
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

#define MAX_SCORE_DIGIT	(5)//スコアの最大数
#define MAX_TIME_DIGIT	(2)//スコアの最大数
#define MAX_BULLETLIFE_DIGIT (5)
#endif