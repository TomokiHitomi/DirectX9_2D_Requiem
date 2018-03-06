//=============================================================================
//
// タイトル処理 [totalboard.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "totalboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTotalboard(int no);
void SetTextureTotalboard( int no, int cntPattern );	//
void SetVertexTotalboard(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
TOTALBOARD					totalboardWk[TOTALBOARD_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureTotalboard = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTotalboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_TOTALBOARD00,				// ファイルの名前
			&pD3DTextureTotalboard);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		totalboard->bUse = true;

		totalboard->pos = D3DXVECTOR3((float)TOTALBOARD_POS_X, (float)TOTALBOARD_POS_Y, 0.0f);
		totalboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		totalboard->nCountAnim = 0;
		totalboard->nPatternAnim = 0;

		totalboard->Texture = pD3DTextureTotalboard;			// テクスチャへのエネミー
		totalboard->size = D3DXVECTOR2(TEXTURE_TOTALBOARD00_SIZE_X, TEXTURE_TOTALBOARD00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexTotalboard(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTotalboard(void)
{
	TOTALBOARD *totalboard = &totalboardWk[0];

	// メモリ解放
	if (pD3DTextureTotalboard != NULL)
	{
		pD3DTextureTotalboard->Release();
		pD3DTextureTotalboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTotalboard(void)
{
	TOTALBOARD *totalboard = &totalboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		if (totalboard->bUse == true)
		{
			// アニメーション
			totalboard->nCountAnim++;
			if ((totalboard->nCountAnim % TIME_ANIMATION_TOTALBOARD) == 0)
			{
				// パターンの切り替え
				totalboard->nPatternAnim = (totalboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_TOTALBOARD;
			}

			// テクスチャ座標を設定
			SetTextureTotalboard(i, totalboard->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexTotalboard(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTotalboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		if (totalboard->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, totalboard->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TOTALBOARD, totalboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTotalboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[no];

	// 頂点座標の設定
	totalboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	totalboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TOTALBOARD00_SIZE_X, 100.0f, 0.0f);
	totalboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TOTALBOARD00_SIZE_Y, 0.0f);
	totalboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TOTALBOARD00_SIZE_X, 100.0f+TEXTURE_TOTALBOARD00_SIZE_Y, 0.0f);
	//SetVertexTotalboard();

	// rhwの設定
	totalboard->vertexWk[0].rhw =
	totalboard->vertexWk[1].rhw =
	totalboard->vertexWk[2].rhw =
	totalboard->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	totalboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	totalboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	totalboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD, 0.0f );
	totalboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD );
	totalboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTotalboard( int no, int cntPattern )
{
	TOTALBOARD *totalboard = &totalboardWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD;
	totalboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	totalboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	totalboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	totalboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexTotalboard(int no)
{
	TOTALBOARD *totalboard = &totalboardWk[no];

	totalboard->vertexWk[0].vtx.x = totalboard->pos.x - TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[0].vtx.y = totalboard->pos.y - TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[0].vtx.z = 0.0f;

	totalboard->vertexWk[1].vtx.x = totalboard->pos.x + TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[1].vtx.y = totalboard->pos.y - TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[1].vtx.z = 0.0f;

	totalboard->vertexWk[2].vtx.x = totalboard->pos.x - TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[2].vtx.y = totalboard->pos.y + TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[2].vtx.z = 0.0f;

	totalboard->vertexWk[3].vtx.x = totalboard->pos.x + TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[3].vtx.y = totalboard->pos.y + TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
TOTALBOARD *GetTotalboard(int no)
{
	return(&totalboardWk[no]);
}

