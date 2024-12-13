//=============================================================================
//
// サウンド処理 [sound.h]
// Author
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//レンダリングクラス
class CSound
{
public:
	CSound();
	~CSound();
	//*************************************
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_BGM004,			// BGM4
		SOUND_LABEL_BGM005,			// BGM5
		SOUND_LABEL_BGM006,			// BGM5


		SOUND_LABEL_SE_HIT000,		// ヒット音0
		SOUND_LABEL_SE_EXPLOSION,	// ジャンプの音
		SOUND_LABEL_SE_EXPLOSION1,	// 爆発音
		SOUND_LABEL_SE_DECIDE,		// 決定音
		SOUND_LABEL_SE_DECIDE1,		// !=決定音
		SOUND_LABEL_SE_DECIDE2,		// 決定音
		SOUND_LABEL_SE_DECIDE3,		// !=決定音
									//SOUND_LABEL_SE_DECIDE4,		// ⇓決定音
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	typedef struct
	{
		const char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void StopSound(SOUND_LABEL label);
	HRESULT Play(SOUND_LABEL label);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};


#endif
