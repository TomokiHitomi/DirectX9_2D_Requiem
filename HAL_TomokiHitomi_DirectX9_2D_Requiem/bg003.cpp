//=============================================================================
//
// BG003処理 [bg003.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "bg003.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBg003(int no);
void SetTextureBg003( int no, int cntPattern );	//
void SetVertexBg003(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BG003					bg003Wk[BG003_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBg003 = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBg003(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BG003,				// ファイルの名前
			&pD3DTextureBg003);			// 読み込むメモリのポインタ
	}

	// BG003の初期化
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		bg003->bUse = false;
		bg003->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		bg003->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg003->nCountAnim = 0;
		bg003->nPatternAnim = 0;

		bg003->Texture = pD3DTextureBg003;			// テクスチャへのBG003
		bg003->size = D3DXVECTOR2(TEXTURE_BG003_SIZE_X, TEXTURE_BG003_SIZE_Y);

		// 頂点情報の作成
		MakeVertexBg003(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];

	// メモリ解放
	if (pD3DTextureBg003 != NULL)
	{
		pD3DTextureBg003->Release();
		pD3DTextureBg003 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (bg003->bUse == true)
		{
			// アニメーション
			bg003->nCountAnim++;
			if ((bg003->nCountAnim % TIME_ANIMATION_BG003) == 0)
			{
				// パターンの切り替え
				bg003->nPatternAnim = (bg003->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG003;
			}

			// テクスチャ座標を設定
			SetTextureBg003(i, bg003->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexBg003(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg003(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (bg003->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bg003->Texture);

			// BG003の描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG003, bg003->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBg003(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[no];

	// 頂点座標の設定
	bg003->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg003->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG003_SIZE_X, 100.0f, 0.0f);
	bg003->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG003_SIZE_Y, 0.0f);
	bg003->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG003_SIZE_X, 100.0f+TEXTURE_BG003_SIZE_Y, 0.0f);
	//SetVertexBg003();

	// rhwの設定
	bg003->vertexWk[0].rhw =
	bg003->vertexWk[1].rhw =
	bg003->vertexWk[2].rhw =
	bg003->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bg003->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);

	// テクスチャ座標の設定
	bg003->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg003->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG003, 0.0f );
	bg003->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG003 );
	bg003->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG003, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG003 );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBg003( int no, int cntPattern )
{
	BG003 *bg003 = &bg003Wk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG003;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG003;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG003;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG003;
	bg003->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg003->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg003->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg003->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBg003(int no)
{
	BG003 *bg003 = &bg003Wk[no];

	bg003->vertexWk[0].vtx.x = bg003->pos.x - TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[0].vtx.y = bg003->pos.y - TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[0].vtx.z = 0.0f;

	bg003->vertexWk[1].vtx.x = bg003->pos.x + TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[1].vtx.y = bg003->pos.y - TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[1].vtx.z = 0.0f;

	bg003->vertexWk[2].vtx.x = bg003->pos.x - TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[2].vtx.y = bg003->pos.y + TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[2].vtx.z = 0.0f;

	bg003->vertexWk[3].vtx.x = bg003->pos.x + TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[3].vtx.y = bg003->pos.y + TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// アクティブ処理
//=============================================================================
void SetBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];

	// 未使用検索
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (!bg003->bUse)
		{
			// 有効にする
			bg003->bUse = true;
			return;
		}
	}
}

//=============================================================================
// BG003取得関数
//=============================================================================
BG003 *GetBg003(int no)
{
	return(&bg003Wk[no]);
}

