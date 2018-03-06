//=======================================================================Hitcircle======
//
// プレイヤー処理 [effect_player_wing.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "effect_player_wing.h"
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
HRESULT MakeVertexEffect_player_wing(int no);
void SetTextureEffect_player_wing( int no, int cntPattern );
void SetVertexEffect_player_wing(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
EFFECT_PLAYER_WING					effect_player_wingWk[EFFECT_PLAYER_WING_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEffect_player_wing = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect_player_wing(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_EFFECT_PLAYER_WING,				// ファイルの名前
			&pD3DTextureEffect_player_wing);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		effect_player_wing->bUse = false;
		effect_player_wing->bLoop = false;
		effect_player_wing->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		effect_player_wing->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_player_wing->nCountAnim = 0;
		effect_player_wing->nPatternAnim = 0;
		effect_player_wing->nAlpha = EFFECT_PLAYER_WING_ALPHA_MAX;
		effect_player_wing->Texture = pD3DTextureEffect_player_wing;			// テクスチャへのエネミー
		effect_player_wing->size = D3DXVECTOR2(TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexEffect_player_wing(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect_player_wing(void)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// メモリ解放
	if (pD3DTextureEffect_player_wing != NULL)
	{
		pD3DTextureEffect_player_wing->Release();
		pD3DTextureEffect_player_wing = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect_player_wing(void)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		if (effect_player_wing->bUse)
		{
			// アニメーション
			effect_player_wing->nCountAnim++;
			if ((effect_player_wing->nCountAnim % TIME_ANIMATION_EFFECT_PLAYER_WING) == 0)
			{
				// パターンの切り替え
				effect_player_wing->nPatternAnim = (effect_player_wing->nPatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT_PLAYER_WING;
			}

			// パターンループ
			if (effect_player_wing->nPatternAnim >= EFFECT_PLAYER_WING_LOOP_MAX && effect_player_wing->bLoop)
			{
				effect_player_wing->nPatternAnim = EFFECT_PLAYER_WING_LOOP_MIN;
			}

			// ラストパターンで終了
			if (effect_player_wing->nPatternAnim == ANIM_PATTERN_NUM_EFFECT_PLAYER_WING-1)
			{
				effect_player_wing->bUse = false;
			}

			// ウイングの透明度をMP倍率で変更
			effect_player_wing->nAlpha = EFFECT_PLAYER_WING_ALPHA_MAX / (float)PLAYER_MANAMAX * player->fManaPoint;

			effect_player_wing->nAlpha = effect_player_wing->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if(effect_player_wing->nAlpha < 0)
			{
				effect_player_wing->nAlpha = 0;
			}

			// 対象座標にセット
			effect_player_wing->pos.x = player->pos.x + EFFECT_PLAYER_WING_ADJUSTMENT_X;
			effect_player_wing->pos.y = player->pos.y + EFFECT_PLAYER_WING_ADJUSTMENT_Y;

			// テクスチャ座標を設定
			SetTextureEffect_player_wing(i, effect_player_wing->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEffect_player_wing(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect_player_wing(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		if (effect_player_wing->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, effect_player_wing->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_PLAYER_WING, effect_player_wing->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect_player_wing(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];

	// 頂点座標の設定
	effect_player_wing->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_player_wing->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, 100.0f, 0.0f);
	effect_player_wing->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y, 0.0f);
	effect_player_wing->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, 100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y, 0.0f);
	//SetVertexEffect_player_wing();

	// rhwの設定
	effect_player_wing->vertexWk[0].rhw =
	effect_player_wing->vertexWk[1].rhw =
	effect_player_wing->vertexWk[2].rhw =
	effect_player_wing->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect_player_wing->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect_player_wing->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_player_wing->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING, 0.0f );
	effect_player_wing->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING );
	effect_player_wing->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect_player_wing( int no, int cntPattern )
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING;
	effect_player_wing->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_player_wing->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_player_wing->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_player_wing->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEffect_player_wing(int no)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];
	PLAYER *player = GetPlayer(0);

	effect_player_wing->vertexWk[0].vtx.x = effect_player_wing->pos.x - TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[0].vtx.y = effect_player_wing->pos.y - TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[0].vtx.z = 0.0f;

	effect_player_wing->vertexWk[1].vtx.x = effect_player_wing->pos.x + TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[1].vtx.y = effect_player_wing->pos.y - TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[1].vtx.z = 0.0f;

	effect_player_wing->vertexWk[2].vtx.x = effect_player_wing->pos.x - TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[2].vtx.y = effect_player_wing->pos.y + TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[2].vtx.z = 0.0f;

	effect_player_wing->vertexWk[3].vtx.x = effect_player_wing->pos.x + TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[3].vtx.y = effect_player_wing->pos.y + TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[3].vtx.z = 0.0f;

	// 反射光の設定
	effect_player_wing->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
}

//=============================================================================
// セット関数
//=============================================================================
void SetEffect_player_wing()
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// 有効にする
	effect_player_wing->bUse = true;
	// ループフラグを有効にする
	effect_player_wing->bLoop = true;
	// アニメーションカウンタの初期化
	effect_player_wing->nCountAnim = 0;
	// アニメーションパターンの初期化
	effect_player_wing->nPatternAnim = 0;
}

//=============================================================================
// ディセーブル関数
//=============================================================================
void ReleaseEffect_player_wing()
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// ループフラグを無効にする
	effect_player_wing->bLoop = false;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
EFFECT_PLAYER_WING *GetEffect_player_wing(int no)
{
	return(&effect_player_wingWk[no]);
}

