//=======================================================================Hitcircle======
//
// プレイヤー処理 [effect_close.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "effect_close.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect_close(int no);
void SetTextureEffect_close( int no, int cntPattern );	//
void SetVertexEffect_close(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
EFFECT_CLOSE					effect_closeWk[EFFECT_CLOSE_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEffect_close = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect_close(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_EFFECT_CLOSE,				// ファイルの名前
			&pD3DTextureEffect_close);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		effect_close->bUse = false;
		effect_close->pos = D3DXVECTOR3((float)EFFECT_CLOSE_POS_X, (float)EFFECT_CLOSE_POS_Y, 0.0f);
		effect_close->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_close->nCountAnim = 0;
		effect_close->nPatternAnim = 0;
		effect_close->Texture = pD3DTextureEffect_close;			// テクスチャへのエネミー
		effect_close->size = D3DXVECTOR2(TEXTURE_EFFECT_CLOSE00_SIZE_X, TEXTURE_EFFECT_CLOSE00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexEffect_close(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// メモリ解放
	if (pD3DTextureEffect_close != NULL)
	{
		pD3DTextureEffect_close->Release();
		pD3DTextureEffect_close = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (effect_close->bUse)
		{
			// アニメーション
			effect_close->nCountAnim++;
			if ((effect_close->nCountAnim % TIME_ANIMATION_EFFECT_CLOSE) == 0)
			{
				// パターンの切り替え
				effect_close->nPatternAnim = (effect_close->nPatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT_CLOSE;
				if (effect_close->nPatternAnim == EFFECT_CLOSE_SKIPANIME00 || effect_close->nPatternAnim == EFFECT_CLOSE_SKIPANIME14)
				{
					effect_close->nPatternAnim = 1;
				}
			}

			//if (effect_close->nCountAnim >= ANIM_PATTERN_NUM_EFFECT_CLOSE * TIME_ANIMATION_EFFECT_CLOSE)
			//{
			//	effect_close->bUse = false;
			//}

			// テクスチャ座標を設定
			SetTextureEffect_close(i, effect_close->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEffect_close(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect_close(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (effect_close->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, effect_close->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_CLOSE, effect_close->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect_close(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	// 頂点座標の設定
	effect_close->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_close->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_X, 100.0f, 0.0f);
	effect_close->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_Y, 0.0f);
	effect_close->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_X, 100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_Y, 0.0f);
	//SetVertexEffect_close();

	// rhwの設定
	effect_close->vertexWk[0].rhw =
	effect_close->vertexWk[1].rhw =
	effect_close->vertexWk[2].rhw =
	effect_close->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect_close->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect_close->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_close->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE, 0.0f );
	effect_close->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE );
	effect_close->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect_close( int no, int cntPattern )
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE;
	effect_close->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_close->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_close->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_close->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEffect_close(int no)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	effect_close->vertexWk[0].vtx.x = effect_close->pos.x - TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[0].vtx.y = effect_close->pos.y - TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[0].vtx.z = 0.0f;

	effect_close->vertexWk[1].vtx.x = effect_close->pos.x + TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[1].vtx.y = effect_close->pos.y - TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[1].vtx.z = 0.0f;

	effect_close->vertexWk[2].vtx.x = effect_close->pos.x - TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[2].vtx.y = effect_close->pos.y + TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[2].vtx.z = 0.0f;

	effect_close->vertexWk[3].vtx.x = effect_close->pos.x + TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[3].vtx.y = effect_close->pos.y + TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
void SetEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// 未使用検索
	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (!effect_close->bUse)
		{
			// 有効にする
			effect_close->bUse = true;
			// アニメーションカウンタの初期化
			effect_close->nCountAnim = 0;
			// アニメーションパターンの初期化
			effect_close->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
EFFECT_CLOSE *GetEffect_close(int no)
{
	return(&effect_closeWk[no]);
}

