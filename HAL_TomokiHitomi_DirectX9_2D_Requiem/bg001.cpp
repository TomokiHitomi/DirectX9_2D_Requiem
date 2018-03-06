//=============================================================================
//
// BG001処理 [bg001.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "bg001.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBg001(int no);
void SetTextureBg001( int no, int cntPattern );	//
void SetVertexBg001(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BG001					bg001Wk[BG001_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBg001 = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBg001(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG001 *bg001 = &bg001Wk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BG001,				// ファイルの名前
			&pD3DTextureBg001);			// 読み込むメモリのポインタ
	}

	// BG001の初期化
	for (int i = 0; i < BG001_MAX; i++, bg001++)
	{
		bg001->bUse = true;
		bg001->pos = D3DXVECTOR3(i*BG001_POS_X *2 + BG001_POS_X, BG001_POS_Y, 0.0f);
		bg001->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg001->nCountAnim = 0;
		bg001->nPatternAnim = 0;

		bg001->Texture = pD3DTextureBg001;			// テクスチャへのBG001
		bg001->size = D3DXVECTOR2(TEXTURE_BG001_SIZE_X, TEXTURE_BG001_SIZE_Y);

		// 頂点情報の作成
		MakeVertexBg001(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg001(void)
{
	BG001 *bg001 = &bg001Wk[0];

	// メモリ解放
	if (pD3DTextureBg001 != NULL)
	{
		pD3DTextureBg001->Release();
		pD3DTextureBg001 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg001(void)
{
	BG001 *bg001 = &bg001Wk[0];
	for (int i = 0; i < BG001_MAX; i++, bg001++)
	{
		if (bg001->bUse == true)
		{
			// アニメーション
			bg001->nCountAnim++;
			if ((bg001->nCountAnim % TIME_ANIMATION_BG001) == 0)
			{
				// パターンの切り替え
				bg001->nPatternAnim = (bg001->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG001;
			}

			bg001->pos.x -= BG001_SPEED;
			if(bg001->pos.x <= i * TEXTURE_BG001_SIZE_X * 2 - TEXTURE_BG001_SIZE_X)
			{
				bg001->pos.x = i * TEXTURE_BG001_SIZE_X * 2 + TEXTURE_BG001_SIZE_X;
			}
			// テクスチャ座標を設定
			SetTextureBg001(i, bg001->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexBg001(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg001(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG001 *bg001 = &bg001Wk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG001_MAX; i++, bg001++)
	{
		if (bg001->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bg001->Texture);

			// BG001の描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG001, bg001->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBg001(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG001 *bg001 = &bg001Wk[no];

	// 頂点座標の設定
	bg001->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg001->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG001_SIZE_X, 100.0f, 0.0f);
	bg001->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG001_SIZE_Y, 0.0f);
	bg001->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG001_SIZE_X, 100.0f+TEXTURE_BG001_SIZE_Y, 0.0f);
	//SetVertexBg001();

	// rhwの設定
	bg001->vertexWk[0].rhw =
	bg001->vertexWk[1].rhw =
	bg001->vertexWk[2].rhw =
	bg001->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bg001->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG001_R, TEXTURE_BG001_G, TEXTURE_BG001_B, 255);
	bg001->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG001_R, TEXTURE_BG001_G, TEXTURE_BG001_B, 255);
	bg001->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG001_R, TEXTURE_BG001_G, TEXTURE_BG001_B, 255);
	bg001->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG001_R, TEXTURE_BG001_G, TEXTURE_BG001_B, 255);

	// テクスチャ座標の設定
	bg001->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg001->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG001, 0.0f );
	bg001->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG001 );
	bg001->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG001, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG001 );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBg001( int no, int cntPattern )
{
	BG001 *bg001 = &bg001Wk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG001;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG001;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG001;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG001;
	bg001->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg001->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg001->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg001->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBg001(int no)
{
	BG001 *bg001 = &bg001Wk[no];

	bg001->vertexWk[0].vtx.x = bg001->pos.x - TEXTURE_BG001_SIZE_X;
	bg001->vertexWk[0].vtx.y = bg001->pos.y - TEXTURE_BG001_SIZE_Y;
	bg001->vertexWk[0].vtx.z = 0.0f;

	bg001->vertexWk[1].vtx.x = bg001->pos.x + TEXTURE_BG001_SIZE_X;
	bg001->vertexWk[1].vtx.y = bg001->pos.y - TEXTURE_BG001_SIZE_Y;
	bg001->vertexWk[1].vtx.z = 0.0f;

	bg001->vertexWk[2].vtx.x = bg001->pos.x - TEXTURE_BG001_SIZE_X;
	bg001->vertexWk[2].vtx.y = bg001->pos.y + TEXTURE_BG001_SIZE_Y;
	bg001->vertexWk[2].vtx.z = 0.0f;

	bg001->vertexWk[3].vtx.x = bg001->pos.x + TEXTURE_BG001_SIZE_X;
	bg001->vertexWk[3].vtx.y = bg001->pos.y + TEXTURE_BG001_SIZE_Y;
	bg001->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// BG001取得関数
//=============================================================================
BG001 *GetBg001(int no)
{
	return(&bg001Wk[no]);
}

