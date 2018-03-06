//=============================================================================
//
// タイトル処理 [clearbonus.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "clearbonus.h"
#include "input.h"
#include "sound.h"
#include "result.h"
#include "close.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexClearbonus(int no);
void SetTextureClearbonus( int no, int cntPattern );	//
void SetVertexClearbonus(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CLEARBONUS					clearbonusWk[CLEARBONUS_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureClearbonus = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitClearbonus(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_CLEARBONUS00,				// ファイルの名前
			&pD3DTextureClearbonus);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		clearbonus->bUse = true;

		clearbonus->pos = D3DXVECTOR3((float)CLEARBONUS_POS_X, (float)CLEARBONUS_POS_Y, 0.0f);
		clearbonus->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		clearbonus->nCountAnim = 0;
		clearbonus->nPatternAnim = 0;

		clearbonus->Texture = pD3DTextureClearbonus;			// テクスチャへのエネミー
		clearbonus->size = D3DXVECTOR2(TEXTURE_CLEARBONUS00_SIZE_X, TEXTURE_CLEARBONUS00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexClearbonus(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitClearbonus(void)
{
	CLEARBONUS *clearbonus = &clearbonusWk[0];

	// メモリ解放
	if (pD3DTextureClearbonus != NULL)
	{
		pD3DTextureClearbonus->Release();
		pD3DTextureClearbonus = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateClearbonus(void)
{
	CLEARBONUS *clearbonus = &clearbonusWk[0];
	CLOSE *close = GetClose(0);

	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		if (clearbonus->bUse )
		{
			// ゲームクリア時のみトータルスコアボーナス
			if (close->bClearFlag)
			{
				clearbonus->nPatternAnim = 0;
			}
			else
			{
				clearbonus->nPatternAnim = 1;
			}

			// テクスチャ座標を設定
			SetTextureClearbonus(i, clearbonus->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexClearbonus(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawClearbonus(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		if (clearbonus->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, clearbonus->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLEARBONUS, clearbonus->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexClearbonus(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	// 頂点座標の設定
	clearbonus->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	clearbonus->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLEARBONUS00_SIZE_X, 100.0f, 0.0f);
	clearbonus->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CLEARBONUS00_SIZE_Y, 0.0f);
	clearbonus->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLEARBONUS00_SIZE_X, 100.0f+TEXTURE_CLEARBONUS00_SIZE_Y, 0.0f);
	//SetVertexClearbonus();

	// rhwの設定
	clearbonus->vertexWk[0].rhw =
	clearbonus->vertexWk[1].rhw =
	clearbonus->vertexWk[2].rhw =
	clearbonus->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	clearbonus->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	clearbonus->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	clearbonus->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS, 0.0f );
	clearbonus->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS );
	clearbonus->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureClearbonus( int no, int cntPattern )
{
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS;
	clearbonus->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	clearbonus->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	clearbonus->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	clearbonus->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexClearbonus(int no)
{
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	clearbonus->vertexWk[0].vtx.x = clearbonus->pos.x - TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[0].vtx.y = clearbonus->pos.y - TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[0].vtx.z = 0.0f;

	clearbonus->vertexWk[1].vtx.x = clearbonus->pos.x + TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[1].vtx.y = clearbonus->pos.y - TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[1].vtx.z = 0.0f;

	clearbonus->vertexWk[2].vtx.x = clearbonus->pos.x - TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[2].vtx.y = clearbonus->pos.y + TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[2].vtx.z = 0.0f;

	clearbonus->vertexWk[3].vtx.x = clearbonus->pos.x + TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[3].vtx.y = clearbonus->pos.y + TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
CLEARBONUS *GetClearbonus(int no)
{
	return(&clearbonusWk[no]);
}

