//=============================================================================
//
// タイトル処理 [close.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "close.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
#include "motion_result.h"
#include "bg002.h"
#include "bg003.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexClose(int no);
void SetTextureClose( int no, int cntPattern );	//
void SetVertexClose(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CLOSE					closeWk[CLOSE_MAX];
int						g_nCloseCount;
bool					g_bSeFlag;
bool					g_bVoiceFlag;

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureClose = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitClose(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_CLOSE00,				// ファイルの名前
			&pD3DTextureClose);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < CLOSE_MAX; i++, close++)
	{
		close->bUse = false;
		close->bClearFlag = false;
		close->pos = D3DXVECTOR3(CLOSE00_POS_X, CLOSE00_POS_Y, 0.0f);
		close->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		close->nCountAnim = 0;
		close->nPatternAnim = 0;

		close->Texture = pD3DTextureClose;			// テクスチャへのエネミー
		close->size = D3DXVECTOR2(TEXTURE_CLOSE00_SIZE_X, TEXTURE_CLOSE00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexClose(i);
	}

	g_nCloseCount = 0;
	g_bSeFlag = true;
	g_bVoiceFlag = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitClose(void)
{
	CLOSE *close = &closeWk[0];

	// メモリ解放
	if (pD3DTextureClose != NULL)
	{
		pD3DTextureClose->Release();
		pD3DTextureClose = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateClose(void)
{
	CLOSE *close = &closeWk[0];
	FADE *fade = GetFade(0);

	SetBgmVol(0, false);
	SetBgmVol(1, false);
	SetBgmVol(2, false);
	SetBgmVol(3, false);
	SetBgmVol(4, false);

	for (int i = 0; i < CLOSE_MAX; i++,close++)
	{
		if (close->bUse)
		{
			if (g_bSeFlag && g_nCloseCount >= 100)
			{
				// closeサウンド再生
				SetSe(0, E_DS8_FLAG_NONE, false);
				g_bSeFlag = false;
			}

			// アニメーション
			// パターンの切り替え
			if (close->bClearFlag)
			{
				close->nPatternAnim = 0;
				if (g_bVoiceFlag && g_nCloseCount >= 50)
				{
					SetPlayerVoice(4);
					g_bVoiceFlag = false;
				}
				SetBg002();
				SetMotion_result();
			}
			else
			{
				close->nPatternAnim = 1;
				if (g_bVoiceFlag && g_nCloseCount >= 50)
				{
					SetPlayerVoice(2);
					g_bVoiceFlag = false;
				}
				SetBg003();
			}

			g_nCloseCount++;

			int nFadeCount = FADE_COMPLETE;

			if (g_nCloseCount == CLOSE_COUNTMAX - FADE_COMPLETE)
			{
				fade->nFadeFlag = 1;
				fade->bUse = true;
			}
			
			if (g_nCloseCount == CLOSE_COUNTMAX)
			{
				g_nCloseCount = 0;
				SetStage(STAGE_RESULT);
				close->bUse = false;
				g_bSeFlag = true;
				SetSe(7, E_DS8_FLAG_NONE, true);
			}

			// テクスチャ座標を設定
			SetTextureClose(i, close->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexClose(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawClose(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CLOSE_MAX; i++, close++)
	{
		if (close->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, close->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLOSE, close->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexClose(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[no];

	// 頂点座標の設定
	close->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	close->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLOSE00_SIZE_X, 100.0f, 0.0f);
	close->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CLOSE00_SIZE_Y, 0.0f);
	close->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLOSE00_SIZE_X, 100.0f+TEXTURE_CLOSE00_SIZE_Y, 0.0f);
	//SetVertexClose();

	// rhwの設定
	close->vertexWk[0].rhw =
	close->vertexWk[1].rhw =
	close->vertexWk[2].rhw =
	close->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	close->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	close->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	close->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLOSE, 0.0f );
	close->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLOSE );
	close->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLOSE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLOSE );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureClose( int no, int cntPattern )
{
	CLOSE *close = &closeWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CLOSE;
	close->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	close->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	close->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	close->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexClose(int no)
{
	CLOSE *close = &closeWk[no];

	close->vertexWk[0].vtx.x = close->pos.x - TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[0].vtx.y = close->pos.y - TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[0].vtx.z = 0.0f;

	close->vertexWk[1].vtx.x = close->pos.x + TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[1].vtx.y = close->pos.y - TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[1].vtx.z = 0.0f;

	close->vertexWk[2].vtx.x = close->pos.x - TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[2].vtx.y = close->pos.y + TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[2].vtx.z = 0.0f;

	close->vertexWk[3].vtx.x = close->pos.x + TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[3].vtx.y = close->pos.y + TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
CLOSE *GetClose(int no)
{
	return(&closeWk[no]);
}

