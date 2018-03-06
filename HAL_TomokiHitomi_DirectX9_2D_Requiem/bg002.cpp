//=============================================================================
//
// BG002処理 [bg002.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "bg002.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBg002(int no);
void SetTextureBg002( int no, int cntPattern );	//
void SetVertexBg002(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BG002					bg002Wk[BG002_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBg002 = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBg002(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BG002,				// ファイルの名前
			&pD3DTextureBg002);			// 読み込むメモリのポインタ
	}

	// BG002の初期化
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		bg002->bUse = true;
		bg002->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		bg002->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg002->nCountAnim = 0;
		bg002->nPatternAnim = 0;

		bg002->Texture = pD3DTextureBg002;			// テクスチャへのBG002
		bg002->size = D3DXVECTOR2(TEXTURE_BG002_SIZE_X, TEXTURE_BG002_SIZE_Y);

		// 頂点情報の作成
		MakeVertexBg002(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];

	// メモリ解放
	if (pD3DTextureBg002 != NULL)
	{
		pD3DTextureBg002->Release();
		pD3DTextureBg002 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (bg002->bUse == true)
		{
			// アニメーション
			bg002->nCountAnim++;
			if ((bg002->nCountAnim % TIME_ANIMATION_BG002) == 0)
			{
				// パターンの切り替え
				bg002->nPatternAnim = (bg002->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG002;
			}

			// テクスチャ座標を設定
			SetTextureBg002(i, bg002->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexBg002(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg002(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (bg002->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bg002->Texture);

			// BG002の描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG002, bg002->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBg002(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[no];

	// 頂点座標の設定
	bg002->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg002->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG002_SIZE_X, 100.0f, 0.0f);
	bg002->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG002_SIZE_Y, 0.0f);
	bg002->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG002_SIZE_X, 100.0f+TEXTURE_BG002_SIZE_Y, 0.0f);
	//SetVertexBg002();

	// rhwの設定
	bg002->vertexWk[0].rhw =
	bg002->vertexWk[1].rhw =
	bg002->vertexWk[2].rhw =
	bg002->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bg002->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);

	// テクスチャ座標の設定
	bg002->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg002->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG002, 0.0f );
	bg002->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG002 );
	bg002->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG002, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG002 );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBg002( int no, int cntPattern )
{
	BG002 *bg002 = &bg002Wk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG002;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG002;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG002;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG002;
	bg002->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg002->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg002->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg002->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBg002(int no)
{
	BG002 *bg002 = &bg002Wk[no];

	bg002->vertexWk[0].vtx.x = bg002->pos.x - TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[0].vtx.y = bg002->pos.y - TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[0].vtx.z = 0.0f;

	bg002->vertexWk[1].vtx.x = bg002->pos.x + TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[1].vtx.y = bg002->pos.y - TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[1].vtx.z = 0.0f;

	bg002->vertexWk[2].vtx.x = bg002->pos.x - TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[2].vtx.y = bg002->pos.y + TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[2].vtx.z = 0.0f;

	bg002->vertexWk[3].vtx.x = bg002->pos.x + TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[3].vtx.y = bg002->pos.y + TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// アクティブ処理
//=============================================================================
void SetBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];

	// 未使用検索
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (!bg002->bUse)
		{
			// 有効にする
			bg002->bUse = true;
			return;
		}
	}
}

//=============================================================================
// BG002取得関数
//=============================================================================
BG002 *GetBg002(int no)
{
	return(&bg002Wk[no]);
}

