//=============================================================================
//
// タイトル処理 [rank.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "rank.h"
#include "input.h"
#include "sound.h"
#include "result.h"
#include "close.h"
#include "total.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRank(int no);
void SetTextureRank( int no, int cntPattern );	//
void SetVertexRank(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
RANK					rankWk[RANK_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureRank = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRank(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK00,				// ファイルの名前
			&pD3DTextureRank);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		rank->bUse = true;

		rank->pos = D3DXVECTOR3((float)RANK_POS_X, (float)RANK_POS_Y, 0.0f);
		rank->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rank->nCountAnim = 0;
		rank->nPatternAnim = 0;

		rank->Texture = pD3DTextureRank;			// テクスチャへのエネミー
		rank->size = D3DXVECTOR2(TEXTURE_RANK00_SIZE_X, TEXTURE_RANK00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexRank(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRank(void)
{
	RANK *rank = &rankWk[0];

	// メモリ解放
	if (pD3DTextureRank != NULL)
	{
		pD3DTextureRank->Release();
		pD3DTextureRank = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRank(void)
{
	RANK *rank = &rankWk[0];
	int *total = GetTotal();

	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		if (rank->bUse )
		{
			// ゲームクリア時のみトータルスコアボーナス
			if (*total >= RANK_S)
			{
				// Sランク表示
				rank->nPatternAnim = 0;
			}
			else if (*total >= RANK_A)
			{
				// Aランク表示
				rank->nPatternAnim = 1;
			}
			else if (*total >= RANK_B)
			{
				// Bランク表示
				rank->nPatternAnim = 2;
			}
			else if (*total >= RANK_C)
			{
				// Cランク表示
				rank->nPatternAnim = 3;
			}
			else
			{
				// Dランク表示
				rank->nPatternAnim = 4;
			}

			// テクスチャ座標を設定
			SetTextureRank(i, rank->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexRank(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		if (rank->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, rank->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RANK, rank->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRank(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[no];

	// 頂点座標の設定
	rank->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	rank->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANK00_SIZE_X, 100.0f, 0.0f);
	rank->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_RANK00_SIZE_Y, 0.0f);
	rank->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANK00_SIZE_X, 100.0f+TEXTURE_RANK00_SIZE_Y, 0.0f);
	//SetVertexRank();

	// rhwの設定
	rank->vertexWk[0].rhw =
	rank->vertexWk[1].rhw =
	rank->vertexWk[2].rhw =
	rank->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	rank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	rank->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	rank->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANK, 0.0f );
	rank->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANK );
	rank->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANK );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRank( int no, int cntPattern )
{
	RANK *rank = &rankWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_RANK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_RANK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_RANK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_RANK;
	rank->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	rank->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	rank->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	rank->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexRank(int no)
{
	RANK *rank = &rankWk[no];

	rank->vertexWk[0].vtx.x = rank->pos.x - TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[0].vtx.y = rank->pos.y - TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[0].vtx.z = 0.0f;

	rank->vertexWk[1].vtx.x = rank->pos.x + TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[1].vtx.y = rank->pos.y - TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[1].vtx.z = 0.0f;

	rank->vertexWk[2].vtx.x = rank->pos.x - TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[2].vtx.y = rank->pos.y + TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[2].vtx.z = 0.0f;

	rank->vertexWk[3].vtx.x = rank->pos.x + TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[3].vtx.y = rank->pos.y + TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
RANK *GetRank(int no)
{
	return(&rankWk[no]);
}

