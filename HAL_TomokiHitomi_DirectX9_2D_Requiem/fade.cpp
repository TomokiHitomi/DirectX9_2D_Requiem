//=============================================================================
//
// FADE処理 [fade.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexFade(int no);
void SetTextureFade( int no, int cntPattern );
void SetVertexFade(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
FADE					fadeWk[FADE_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureFade = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_FADE,				// ファイルの名前
			&pD3DTextureFade);			// 読み込むメモリのポインタ
	}

	// FADEの初期化
	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		fade->bUse = true;
		fade->nFadeFlag = 0;
		fade->pos = D3DXVECTOR3(i*0.0f + TEXTURE_FADE_SIZE_X, TEXTURE_FADE_SIZE_Y, 0.0f);
		fade->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		fade->nCountAnim = 0;
		fade->nPatternAnim = 0;
		fade->nAlphaCount = FADE_ALPHA_MAX;

		fade->Texture = pD3DTextureFade;			// テクスチャへのFADE
		fade->size = D3DXVECTOR2(TEXTURE_FADE_SIZE_X, TEXTURE_FADE_SIZE_Y);

		// 頂点情報の作成
		MakeVertexFade(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	FADE *fade = &fadeWk[0];

	// メモリ解放
	if (pD3DTextureFade != NULL)
	{
		pD3DTextureFade->Release();
		pD3DTextureFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	FADE *fade = &fadeWk[0];
	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (fade->bUse)
		{
			// アニメーション
			fade->nCountAnim++;
			if ((fade->nCountAnim % TIME_ANIMATION_FADE) == 0)
			{
				// パターンの切り替え
				fade->nPatternAnim = (fade->nPatternAnim + 1) % ANIM_PATTERN_NUM_FADE;
			}

			switch (fade->nFadeFlag)
			{
			case 0:
				fade->nAlphaCount -= FADE_SPEED;
				if (fade->nAlphaCount <= 0)
				{
					fade->nAlphaCount = 0;
					fade->bUse = false;
				}
				break;
			case 1:
				fade->nAlphaCount += FADE_SPEED;
				if (fade->nAlphaCount > FADE_ALPHA_MAX)
				{
					fade->nAlphaCount = FADE_ALPHA_MAX;
				}
				break;
			case 2:
				fade->nAlphaCount += FADE_SPEED;
				if (fade->nAlphaCount > FADE_ALPHA_MID)
				{
					fade->nAlphaCount = FADE_ALPHA_MID;
				}
				break;
			}

			// テクスチャ座標を設定
			SetTextureFade(i, fade->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexFade(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (fade->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, fade->Texture);

			// FADEの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FADE, fade->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexFade(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[no];

	// 頂点座標の設定
	fade->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	fade->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FADE_SIZE_X, 100.0f, 0.0f);
	fade->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FADE_SIZE_Y, 0.0f);
	fade->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FADE_SIZE_X, 100.0f+TEXTURE_FADE_SIZE_Y, 0.0f);

	// rhwの設定
	fade->vertexWk[0].rhw =
	fade->vertexWk[1].rhw =
	fade->vertexWk[2].rhw =
	fade->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	fade->vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);

	// テクスチャ座標の設定
	fade->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	fade->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FADE, 0.0f );
	fade->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FADE );
	fade->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FADE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FADE );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureFade( int no, int cntPattern )
{
	FADE *fade = &fadeWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FADE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FADE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FADE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FADE;
	fade->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	fade->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	fade->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	fade->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexFade(int no)
{
	FADE *fade = &fadeWk[no];

	fade->vertexWk[0].vtx.x = fade->pos.x - TEXTURE_FADE_SIZE_X;
	fade->vertexWk[0].vtx.y = fade->pos.y - TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[0].vtx.z = 0.0f;

	fade->vertexWk[1].vtx.x = fade->pos.x + TEXTURE_FADE_SIZE_X;
	fade->vertexWk[1].vtx.y = fade->pos.y - TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[1].vtx.z = 0.0f;

	fade->vertexWk[2].vtx.x = fade->pos.x - TEXTURE_FADE_SIZE_X;
	fade->vertexWk[2].vtx.y = fade->pos.y + TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[2].vtx.z = 0.0f;

	fade->vertexWk[3].vtx.x = fade->pos.x + TEXTURE_FADE_SIZE_X;
	fade->vertexWk[3].vtx.y = fade->pos.y + TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[3].vtx.z = 0.0f;

	// 反射光の更新
	fade->vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
}

//=============================================================================
// フェード呼出処理
//=============================================================================
void SetFade(int nFade, int nFadeFlag)
{
	FADE *fade = &fadeWk[nFade];

	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (!fade->bUse)
		{
			// フェードを有効にする
			fade->bUse = true;
		}
		// フェードフラグをセット
		fade->nFadeFlag = nFadeFlag;
		return;
	}
}

//=============================================================================
// FADE取得関数
//=============================================================================
FADE *GetFade(int no)
{
	return(&fadeWk[no]);
}

