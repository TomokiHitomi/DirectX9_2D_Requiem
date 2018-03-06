//=============================================================================
//
// BG000処理 [bg000.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "bg000.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBg000(int no);
void SetTextureBg000( int no, int cntPattern );	//
void SetVertexBg000(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BG000					bg000Wk[BG000_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBg000 = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBg000(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BG000,				// ファイルの名前
			&pD3DTextureBg000);			// 読み込むメモリのポインタ
	}

	// BG000の初期化
	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		bg000->bUse = true;
		bg000->pos = D3DXVECTOR3(TEXTURE_BG000_SIZE_X, TEXTURE_BG000_SIZE_Y, 0.0f);
		bg000->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg000->nCountAnim = 0;
		bg000->nPatternAnim = 0;

		bg000->Texture = pD3DTextureBg000;			// テクスチャへのBG000
		bg000->size = D3DXVECTOR2(TEXTURE_BG000_SIZE_X, TEXTURE_BG000_SIZE_Y);

		// 頂点情報の作成
		MakeVertexBg000(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg000(void)
{
	BG000 *bg000 = &bg000Wk[0];

	// メモリ解放
	if (pD3DTextureBg000 != NULL)
	{
		pD3DTextureBg000->Release();
		pD3DTextureBg000 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg000(void)
{
	BG000 *bg000 = &bg000Wk[0];
	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		if (bg000->bUse == true)
		{
			// アニメーション
			bg000->nCountAnim++;
			if ((bg000->nCountAnim % TIME_ANIMATION_BG000) == 0)
			{
				// パターンの切り替え
				bg000->nPatternAnim = (bg000->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG000;
			}

			// テクスチャ座標を設定
			SetTextureBg000(i, bg000->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexBg000(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg000(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		if (bg000->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bg000->Texture);

			// BG000の描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG000, bg000->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBg000(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[no];

	// 頂点座標の設定
	bg000->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg000->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG000_SIZE_X, 100.0f, 0.0f);
	bg000->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG000_SIZE_Y, 0.0f);
	bg000->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG000_SIZE_X, 100.0f+TEXTURE_BG000_SIZE_Y, 0.0f);
	//SetVertexBg000();

	// rhwの設定
	bg000->vertexWk[0].rhw =
	bg000->vertexWk[1].rhw =
	bg000->vertexWk[2].rhw =
	bg000->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bg000->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);

	// テクスチャ座標の設定
	bg000->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg000->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG000, 0.0f );
	bg000->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG000 );
	bg000->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG000, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG000 );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBg000( int no, int cntPattern )
{
	BG000 *bg000 = &bg000Wk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG000;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG000;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG000;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG000;
	bg000->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg000->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg000->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg000->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBg000(int no)
{
	BG000 *bg000 = &bg000Wk[no];

	bg000->vertexWk[0].vtx.x = bg000->pos.x - TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[0].vtx.y = bg000->pos.y - TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[0].vtx.z = 0.0f;

	bg000->vertexWk[1].vtx.x = bg000->pos.x + TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[1].vtx.y = bg000->pos.y - TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[1].vtx.z = 0.0f;

	bg000->vertexWk[2].vtx.x = bg000->pos.x - TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[2].vtx.y = bg000->pos.y + TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[2].vtx.z = 0.0f;

	bg000->vertexWk[3].vtx.x = bg000->pos.x + TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[3].vtx.y = bg000->pos.y + TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// BG000取得関数
//=============================================================================
BG000 *GetBg000(int no)
{
	return(&bg000Wk[no]);
}

