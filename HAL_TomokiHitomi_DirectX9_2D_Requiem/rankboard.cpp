//=============================================================================
//
// タイトル処理 [rankboard.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "rankboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRankboard(int no);
void SetTextureRankboard( int no, int cntPattern );	//
void SetVertexRankboard(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
RANKBOARD					rankboardWk[RANKBOARD_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureRankboard = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRankboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANKBOARD00,				// ファイルの名前
			&pD3DTextureRankboard);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		rankboard->bUse = true;

		rankboard->pos = D3DXVECTOR3((float)RANKBOARD_POS_X, (float)RANKBOARD_POS_Y, 0.0f);
		rankboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rankboard->nCountAnim = 0;
		rankboard->nPatternAnim = 0;

		rankboard->Texture = pD3DTextureRankboard;			// テクスチャへのエネミー
		rankboard->size = D3DXVECTOR2(TEXTURE_RANKBOARD00_SIZE_X, TEXTURE_RANKBOARD00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexRankboard(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankboard(void)
{
	RANKBOARD *rankboard = &rankboardWk[0];

	// メモリ解放
	if (pD3DTextureRankboard != NULL)
	{
		pD3DTextureRankboard->Release();
		pD3DTextureRankboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankboard(void)
{
	RANKBOARD *rankboard = &rankboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		if (rankboard->bUse == true)
		{
			// アニメーション
			rankboard->nCountAnim++;
			if ((rankboard->nCountAnim % TIME_ANIMATION_RANKBOARD) == 0)
			{
				// パターンの切り替え
				rankboard->nPatternAnim = (rankboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_RANKBOARD;
			}

			// テクスチャ座標を設定
			SetTextureRankboard(i, rankboard->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexRankboard(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		if (rankboard->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, rankboard->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RANKBOARD, rankboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRankboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[no];

	// 頂点座標の設定
	rankboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	rankboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANKBOARD00_SIZE_X, 100.0f, 0.0f);
	rankboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_RANKBOARD00_SIZE_Y, 0.0f);
	rankboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANKBOARD00_SIZE_X, 100.0f+TEXTURE_RANKBOARD00_SIZE_Y, 0.0f);
	//SetVertexRankboard();

	// rhwの設定
	rankboard->vertexWk[0].rhw =
	rankboard->vertexWk[1].rhw =
	rankboard->vertexWk[2].rhw =
	rankboard->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	rankboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	rankboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	rankboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANKBOARD, 0.0f );
	rankboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD );
	rankboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANKBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRankboard( int no, int cntPattern )
{
	RANKBOARD *rankboard = &rankboardWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD;
	rankboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	rankboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	rankboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	rankboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexRankboard(int no)
{
	RANKBOARD *rankboard = &rankboardWk[no];

	rankboard->vertexWk[0].vtx.x = rankboard->pos.x - TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[0].vtx.y = rankboard->pos.y - TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[0].vtx.z = 0.0f;

	rankboard->vertexWk[1].vtx.x = rankboard->pos.x + TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[1].vtx.y = rankboard->pos.y - TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[1].vtx.z = 0.0f;

	rankboard->vertexWk[2].vtx.x = rankboard->pos.x - TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[2].vtx.y = rankboard->pos.y + TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[2].vtx.z = 0.0f;

	rankboard->vertexWk[3].vtx.x = rankboard->pos.x + TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[3].vtx.y = rankboard->pos.y + TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
RANKBOARD *GetRankboard(int no)
{
	return(&rankboardWk[no]);
}

