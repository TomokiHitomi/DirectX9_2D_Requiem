//=============================================================================
//
// タイトル処理 [scoreboard.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "scoreboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScoreboard(int no);
void SetTextureScoreboard( int no, int cntPattern );	//
void SetVertexScoreboard(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
SCOREBOARD					scoreboardWk[SCOREBOARD_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureScoreboard = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScoreboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_SCOREBOARD00,				// ファイルの名前
			&pD3DTextureScoreboard);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		scoreboard->bUse = true;
		scoreboard->bPosMoveFlag = true;

		scoreboard->pos = D3DXVECTOR3((float)SCOREBOARD_POS_X, (float)SCOREBOARD_POS_Y, 0.0f);
		scoreboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreboard->nCountAnim = 0;
		scoreboard->nPatternAnim = 0;

		scoreboard->Texture = pD3DTextureScoreboard;			// テクスチャへのエネミー
		scoreboard->size = D3DXVECTOR2(TEXTURE_SCOREBOARD00_SIZE_X, TEXTURE_SCOREBOARD00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexScoreboard(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScoreboard(void)
{
	SCOREBOARD *scoreboard = &scoreboardWk[0];

	// メモリ解放
	if (pD3DTextureScoreboard != NULL)
	{
		pD3DTextureScoreboard->Release();
		pD3DTextureScoreboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScoreboard(void)
{
	SCOREBOARD *scoreboard = &scoreboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		if (scoreboard->bUse == true)
		{
			// アニメーション
			scoreboard->nCountAnim++;
			if ((scoreboard->nCountAnim % TIME_ANIMATION_SCOREBOARD) == 0)
			{
				// パターンの切り替え
				scoreboard->nPatternAnim = (scoreboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_SCOREBOARD;
			}

			if (scoreboard->bPosMoveFlag && !result->bPosMoveFlag)
			{
				scoreboard->pos += result->vecPosMove;
				scoreboard->bPosMoveFlag = false;
			}

			// テクスチャ座標を設定
			SetTextureScoreboard(i, scoreboard->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexScoreboard(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScoreboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		if (scoreboard->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, scoreboard->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SCOREBOARD, scoreboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScoreboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	// 頂点座標の設定
	scoreboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	scoreboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_SCOREBOARD00_SIZE_X, 100.0f, 0.0f);
	scoreboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_SCOREBOARD00_SIZE_Y, 0.0f);
	scoreboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_SCOREBOARD00_SIZE_X, 100.0f+TEXTURE_SCOREBOARD00_SIZE_Y, 0.0f);
	//SetVertexScoreboard();

	// rhwの設定
	scoreboard->vertexWk[0].rhw =
	scoreboard->vertexWk[1].rhw =
	scoreboard->vertexWk[2].rhw =
	scoreboard->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	scoreboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	scoreboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	scoreboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD, 0.0f );
	scoreboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD );
	scoreboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScoreboard( int no, int cntPattern )
{
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD;
	scoreboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	scoreboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	scoreboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	scoreboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexScoreboard(int no)
{
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	scoreboard->vertexWk[0].vtx.x = scoreboard->pos.x - TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[0].vtx.y = scoreboard->pos.y - TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[0].vtx.z = 0.0f;

	scoreboard->vertexWk[1].vtx.x = scoreboard->pos.x + TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[1].vtx.y = scoreboard->pos.y - TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[1].vtx.z = 0.0f;

	scoreboard->vertexWk[2].vtx.x = scoreboard->pos.x - TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[2].vtx.y = scoreboard->pos.y + TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[2].vtx.z = 0.0f;

	scoreboard->vertexWk[3].vtx.x = scoreboard->pos.x + TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[3].vtx.y = scoreboard->pos.y + TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
SCOREBOARD *GetScoreboard(int no)
{
	return(&scoreboardWk[no]);
}

