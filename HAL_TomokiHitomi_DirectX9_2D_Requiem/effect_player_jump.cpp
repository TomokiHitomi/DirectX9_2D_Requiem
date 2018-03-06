//=======================================================================Hitcircle======
//
// プレイヤー処理 [effect_player_jump.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "effect_player_jump.h"
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
HRESULT MakeVertexEffect_player_jump(int no);
void SetTextureEffect_player_jump( int no, int cntPattern );	//
void SetVertexEffect_player_jump(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
EFFECT_PLAYER_JUMP					effect_player_jumpWk[EFFECT_PLAYER_JUMP_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEffect_player_jump = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect_player_jump(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_EFFECT_PLAYER_JUMP,				// ファイルの名前
			&pD3DTextureEffect_player_jump);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < EFFECT_PLAYER_JUMP_MAX; i++, effect_player_jump++)
	{
		effect_player_jump->bUse = false;
		effect_player_jump->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		effect_player_jump->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_player_jump->nCountAnim = 0;
		effect_player_jump->nPatternAnim = 0;
		effect_player_jump->Texture = pD3DTextureEffect_player_jump;			// テクスチャへのエネミー
		effect_player_jump->size = D3DXVECTOR2(TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X, TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexEffect_player_jump(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect_player_jump(void)
{
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[0];

	// メモリ解放
	if (pD3DTextureEffect_player_jump != NULL)
	{
		pD3DTextureEffect_player_jump->Release();
		pD3DTextureEffect_player_jump = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect_player_jump(void)
{
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_PLAYER_JUMP_MAX; i++, effect_player_jump++)
	{
		if (effect_player_jump->bUse)
		{
			// アニメーション
			effect_player_jump->nCountAnim++;
			if ((effect_player_jump->nCountAnim % TIME_ANIMATION_EFFECT_PLAYER_JUMP) == 0)
			{
				// パターンの切り替え
				effect_player_jump->nPatternAnim = (effect_player_jump->nPatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT_PLAYER_JUMP;
			}

			if (effect_player_jump->nCountAnim >= ANIM_PATTERN_NUM_EFFECT_PLAYER_JUMP * TIME_ANIMATION_EFFECT_PLAYER_JUMP)
			{
				effect_player_jump->bUse = false;
			}

			// テクスチャ座標を設定
			SetTextureEffect_player_jump(i, effect_player_jump->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEffect_player_jump(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect_player_jump(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_PLAYER_JUMP_MAX; i++, effect_player_jump++)
	{
		if (effect_player_jump->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, effect_player_jump->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_PLAYER_JUMP, effect_player_jump->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect_player_jump(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[no];

	// 頂点座標の設定
	effect_player_jump->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_player_jump->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X, 100.0f, 0.0f);
	effect_player_jump->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y, 0.0f);
	effect_player_jump->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X, 100.0f+TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y, 0.0f);
	//SetVertexEffect_player_jump();

	// rhwの設定
	effect_player_jump->vertexWk[0].rhw =
	effect_player_jump->vertexWk[1].rhw =
	effect_player_jump->vertexWk[2].rhw =
	effect_player_jump->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect_player_jump->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_jump->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_jump->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_jump->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect_player_jump->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_player_jump->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP, 0.0f );
	effect_player_jump->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP );
	effect_player_jump->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect_player_jump( int no, int cntPattern )
{
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP;
	effect_player_jump->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_player_jump->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_player_jump->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_player_jump->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEffect_player_jump(int no)
{
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[no];

	effect_player_jump->vertexWk[0].vtx.x = effect_player_jump->pos.x - TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X;
	effect_player_jump->vertexWk[0].vtx.y = effect_player_jump->pos.y - TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y;
	effect_player_jump->vertexWk[0].vtx.z = 0.0f;

	effect_player_jump->vertexWk[1].vtx.x = effect_player_jump->pos.x + TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X;
	effect_player_jump->vertexWk[1].vtx.y = effect_player_jump->pos.y - TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y;
	effect_player_jump->vertexWk[1].vtx.z = 0.0f;

	effect_player_jump->vertexWk[2].vtx.x = effect_player_jump->pos.x - TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X;
	effect_player_jump->vertexWk[2].vtx.y = effect_player_jump->pos.y + TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y;
	effect_player_jump->vertexWk[2].vtx.z = 0.0f;

	effect_player_jump->vertexWk[3].vtx.x = effect_player_jump->pos.x + TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X;
	effect_player_jump->vertexWk[3].vtx.y = effect_player_jump->pos.y + TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y;
	effect_player_jump->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトセット取得関数
//=============================================================================
void SetEffect_player_jump(D3DXVECTOR3 vecPos)
{
	EFFECT_PLAYER_JUMP *effect_player_jump = &effect_player_jumpWk[0];

	// 未使用検索
	for (int i = 0; i < EFFECT_PLAYER_JUMP_MAX; i++, effect_player_jump++)
	{
		if (!effect_player_jump->bUse)
		{
			// 有効にする
			effect_player_jump->bUse = true;
			// アニメーションカウンタの初期化
			effect_player_jump->nCountAnim = 0;
			// アニメーションパターンの初期化
			effect_player_jump->nPatternAnim = 0;
			// 対象座標にセット
			effect_player_jump->pos.x = vecPos.x + EFFECT_PLAYER_JUMP_ADJUSTMENT_X;
			effect_player_jump->pos.y = vecPos.y + EFFECT_PLAYER_JUMP_ADJUSTMENT_Y;

			return;
		}
	}
}

//=============================================================================
// エフェクト取得関数
//=============================================================================
EFFECT_PLAYER_JUMP *GetEffect_player_jump(int no)
{
	return(&effect_player_jumpWk[no]);
}

