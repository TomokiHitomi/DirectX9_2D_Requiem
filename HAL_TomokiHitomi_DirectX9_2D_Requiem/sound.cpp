//=============================================================================
//
// 入力処理 [sound.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "sound.h"

// おまじない
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

// サウンドファイルのパス（sound.hの通しナンバーと順番を合わせること）
const TCHAR* c_soundFilename[] = {
	_T("data/BGM/BGM000.wav"),
	_T("data/BGM/BGM001.wav"),
	_T("data/BGM/BGM002.wav"),
	_T("data/BGM/BGM003.wav"),
	_T("data/BGM/BGM004.wav"),
	_T("data/SE/close.wav"),
	_T("data/SE/select.wav"),
	_T("data/SE/decision.wav"),
	_T("data/SE/pause.wav"),
	_T("data/SE/nogravity.wav"),
	_T("data/SE/gravity.wav"),
	_T("data/SE/enemybullet00.wav"),
	_T("data/SE/result.wav"),
	_T("data/SE/playerbullet00.wav"),
	_T("data/SE/alert.wav"),
	_T("data/SE/jump.wav"),
	_T("data/SE/hit.wav"),
	_T("data/SE/enemyfalse.wav"),
	_T("data/SE/enemybulletreversal.wav"),
	_T("data/SE/VOICE/healer-damage1.wav"),
	_T("data/SE/VOICE/healer-damage2.wav"),
	_T("data/SE/VOICE/healer-lose1.wav"),
	_T("data/SE/VOICE/healer-start1.wav"),
	_T("data/SE/VOICE/healer-win1.wav")
};

// グローバル変数
IDirectSound8 *g_pDirectSound = NULL;	// サウンドインターフェース

// サウンドの初期化
// hWnd:ウィンドウハンドル
HRESULT InitSound( HWND hWnd )
{
	// DirectSoundオブジェクトの作成
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// 協調レベル設定 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

// 後片付け
void UninitSound()
{
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}
}

// サウンドのロード
// no:サウンドナンバー（ヘッダに定義された列挙型定数）
LPDIRECTSOUNDBUFFER8 LoadSound( int no )
{
	// MMIO = マルチメディア入出力、の略。
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// 曲データの総合バッファ
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// 曲データのバッファ
	DSBUFFERDESC buff;						// バッファ設定構造体

	HMMIO hMmio = NULL;						// MMIOハンドル
	MMIOINFO mmioInfo;						// マルチメディアデータ構造体

	MMRESULT mmRes;								// MM処理結果格納変数
	MMCKINFO riffChunk, formatChunk, dataChunk;	// チャンクデータ構造体
	DWORD size;									// データサイズ格納用
	WAVEFORMATEX pcm;							// 曲データフォーマット構造体

	LPVOID pBlock;				// セカンダリバッファのデータ書き込み先アドレス
	DWORD  dwSize;				// セカンダリバッファのサイズ

	// 1.ハンドルをもとにファイルを開く
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)c_soundFilename[no], &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.ファイル解析�@ RIFFチャンク検索
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// 検索キーワード
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// キーワードをもとに検索
	
	if(mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.ファイル解析�A フォーマットチャンク検索
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// 検索キーワード
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索
	
	if(mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// 検索情報をもとに読み込み
	
	if(size != formatChunk.cksize) 		// 正しく読み込めなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.ファイル解析�B データチャンク検索
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// 検索キーワード
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索
	
	if(mmRes != MMSYSERR_NOERROR) 		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.データ読み込み
	char *pData = new char[dataChunk.cksize];					// 必要な大きさの領域を確保して
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// データを読み込む
	
	if(size != dataChunk.cksize)  		// 正しく読み込めなかったら異常終了
	{
		delete[] pData;
		return NULL;
	}

	// 6.曲を読み込む「セカンダリバッファ」を用意
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// まず初期化
	buff.dwSize = sizeof(DSBUFFERDESC);			// そこから各種設定
	buff.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// 総合バッファを作る
	if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// サウンドバッファを取り出す
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// 取り出したら総合バッファを捨てる
	pBaseBuffer->Release();

	// 7.作られたセカンダリバッファにデータを転送
	// まずは書き込みできるようバッファをロック
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// データ転送
	delete[] pData;					// 元の読み込み領域を消す

	// バッファロック解除
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// セカンダリバッファを返してようやく完了...
	return pBuffer;
}

// 音を鳴らす
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
// flag   :1(E_DS8_FLAG_LOOP)ならループ再生
void PlaySound(  LPDIRECTSOUNDBUFFER8 pBuffer, int flag/*=0*/ )
{	// 続きから鳴らすので、最初から鳴らしたい場合はSetCurrentPosition(0)をすること
	pBuffer->Play(0, 0, flag);
}

void PlayContinuitySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag)
{
	pBuffer->SetCurrentPosition(0);
	PlaySound(pBuffer, flag);
}

// 音を止める
void StopSound( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )	// 鳴っていたら
	{
		pBuffer->Stop();	// 意味的にはPabUseになる。
	}
}

// 再生中かどうか調べる
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )
	{
		return true;
	}
	return false;
}

HRESULT SetVol( LPDIRECTSOUNDBUFFER8 pBuffer, long nVol)
{
	DWORD status;

	pBuffer->GetStatus(&status);
	pBuffer->SetVolume(nVol);
	return DS_OK;
}