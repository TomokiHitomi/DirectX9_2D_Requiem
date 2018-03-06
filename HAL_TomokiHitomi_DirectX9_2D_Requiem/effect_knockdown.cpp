//=======================================================================Hitcircle======
//
// プレイヤー処理 [effect_knockdown.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "effect_knockdown.h"
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
HRESULT MakeVertexEffect_knockdown(int no);
void SetTextureEffect_knockdown( int no, int cntPattern );	//
void SetVertexEffect_knockdown(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
EFFECT_KNOCKDOWN					effect_knockdownWk[EFFECT_KNOCKDOWN_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEffect_knockdown = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect_knockdown(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_EFFECT_KNOCKDOWN,				// ファイルの名前
			&pD3DTextureEffect_knockdown);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		effect_knockdown->bUse = false;
		effect_knockdown->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		effect_knockdown->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_knockdown->nCountAnim = 0;
		effect_knockdown->nPatternAnim = 0;
		effect_knockdown->nTypeAnim = 0;
		effect_knockdown->Texture = pD3DTextureEffect_knockdown;			// テクスチャへのエネミー
		effect_knockdown->size = D3DXVECTOR2(TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexEffect_knockdown(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect_knockdown(void)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// メモリ解放
	if (pD3DTextureEffect_knockdown != NULL)
	{
		pD3DTextureEffect_knockdown->Release();
		pD3DTextureEffect_knockdown = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect_knockdown(void)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (effect_knockdown->bUse)
		{
			// アニメーション
			effect_knockdown->nCountAnim++;
			if ((effect_knockdown->nCountAnim % TIME_ANIMATION_EFFECT_KNOCKDOWN) == 0)
			{
				// パターンの切り替え
				effect_knockdown->nPatternAnim++;
			}

			// アニメーション終了でfalse
			if (effect_knockdown->nPatternAnim >= TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN * (effect_knockdown->nTypeAnim + 1))
			{
				effect_knockdown->bUse = false;
			}

			// テクスチャ座標を設定
			SetTextureEffect_knockdown(i, effect_knockdown->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEffect_knockdown(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect_knockdown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (effect_knockdown->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, effect_knockdown->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_KNOCKDOWN, effect_knockdown->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect_knockdown(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	// 頂点座標の設定
	effect_knockdown->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_knockdown->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, 100.0f, 0.0f);
	effect_knockdown->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y, 0.0f);
	effect_knockdown->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, 100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y, 0.0f);
	//SetVertexEffect_knockdown();

	// rhwの設定
	effect_knockdown->vertexWk[0].rhw =
	effect_knockdown->vertexWk[1].rhw =
	effect_knockdown->vertexWk[2].rhw =
	effect_knockdown->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect_knockdown->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect_knockdown->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_knockdown->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN, 0.0f );
	effect_knockdown->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN );
	effect_knockdown->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect_knockdown( int no, int cntPattern )
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN;
	effect_knockdown->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_knockdown->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_knockdown->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_knockdown->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEffect_knockdown(int no)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	effect_knockdown->vertexWk[0].vtx.x = effect_knockdown->pos.x - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[0].vtx.y = effect_knockdown->pos.y - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[0].vtx.z = 0.0f;

	effect_knockdown->vertexWk[1].vtx.x = effect_knockdown->pos.x + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[1].vtx.y = effect_knockdown->pos.y - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[1].vtx.z = 0.0f;

	effect_knockdown->vertexWk[2].vtx.x = effect_knockdown->pos.x - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[2].vtx.y = effect_knockdown->pos.y + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[2].vtx.z = 0.0f;

	effect_knockdown->vertexWk[3].vtx.x = effect_knockdown->pos.x + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[3].vtx.y = effect_knockdown->pos.y + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトセット取得関数
//=============================================================================
void SetEffect_knockdown(D3DXVECTOR3 vecPos, int nType)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// 未使用検索
	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (!effect_knockdown->bUse)
		{
			// 有効にする
			effect_knockdown->bUse = true;
			// アニメーションカウンタの初期化
			effect_knockdown->nCountAnim = 0;
			// アニメーションパターンの初期化
			effect_knockdown->nPatternAnim = (TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN * nType);
			// 対象のタイプをセット
			effect_knockdown->nTypeAnim = nType;
			// 対象座標にセット
			effect_knockdown->pos.x = vecPos.x + EFFECT_KNOCKDOWN_ADJUSTMENT_X;
			effect_knockdown->pos.y = vecPos.y + EFFECT_KNOCKDOWN_ADJUSTMENT_Y;
			// テクスチャ座標を設定
			SetTextureEffect_knockdown(i, effect_knockdown->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEffect_knockdown(i);
			return;
		}
	}
}

//=============================================================================
// エフェクト取得関数
//=============================================================================
EFFECT_KNOCKDOWN *GetEffect_knockdown(int no)
{
	return(&effect_knockdownWk[no]);
}

