//=============================================================================
//
// タイトル処理 [ground.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "ground.h"
#include "input.h"
#include "sound.h"
#include "close.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGround(int no);
void SetTextureGround( int no, int cntPattern );	//
void SetVertexGround(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
GROUND					groundWk[GROUND_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureGround = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGround(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_GROUND00,				// ファイルの名前
			&pD3DTextureGround);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		ground->bUse = true;
		ground->pos = D3DXVECTOR3(i*((float)TEXTURE_GROUND_SIZE_X * 2) + (float)GROUND_POS_X, (float)GROUND_POS_Y, 0.0f);
		ground->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ground->nCountAnim = 0;
		ground->nPatternAnim = 0;

		ground->Texture = pD3DTextureGround;			// テクスチャへのエネミー
		ground->size = D3DXVECTOR2(TEXTURE_GROUND_SIZE_X, TEXTURE_GROUND_SIZE_Y);

		// 頂点情報の作成
		MakeVertexGround(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGround(void)
{
	GROUND *ground = &groundWk[0];

	// メモリ解放
	if (pD3DTextureGround != NULL)
	{
		pD3DTextureGround->Release();
		pD3DTextureGround = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGround(void)
{
	GROUND *ground = &groundWk[0];

	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		if (ground->bUse)
		{
			// アニメーション
			ground->nCountAnim++;
			if ((ground->nCountAnim % TIME_ANIMATION_GROUND) == 0)
			{
				// パターンの切り替え
				ground->nPatternAnim = (ground->nPatternAnim + 1) % ANIM_PATTERN_NUM_GROUND;
			}

			ground->pos.x -= GROUND_SPEED;

			if (ground->pos.x <= -150)
			{
				ground->pos.x =((GROUND_POS_X*2)*GROUND_MAX) - GROUND_POS_X;
			}


			// テクスチャ座標を設定
			SetTextureGround(i, ground->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexGround(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		if (ground->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, ground->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GROUND, ground->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGround(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[no];

	// 頂点座標の設定
	ground->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	ground->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_GROUND_SIZE_X, 100.0f, 0.0f);
	ground->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_GROUND_SIZE_Y, 0.0f);
	ground->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_GROUND_SIZE_X, 100.0f+TEXTURE_GROUND_SIZE_Y, 0.0f);
	//SetVertexGround();

	// rhwの設定
	ground->vertexWk[0].rhw =
	ground->vertexWk[1].rhw =
	ground->vertexWk[2].rhw =
	ground->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	ground->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);

	// テクスチャ座標の設定
	ground->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	ground->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_GROUND, 0.0f );
	ground->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_GROUND );
	ground->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_GROUND, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_GROUND );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureGround( int no, int cntPattern )
{
	GROUND *ground = &groundWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_GROUND;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_GROUND;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_GROUND;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GROUND;
	ground->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ground->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ground->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ground->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexGround(int no)
{
	GROUND *ground = &groundWk[no];

	ground->vertexWk[0].vtx.x = ground->pos.x - TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[0].vtx.y = ground->pos.y - TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[0].vtx.z = 0.0f;

	ground->vertexWk[1].vtx.x = ground->pos.x + TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[1].vtx.y = ground->pos.y - TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[1].vtx.z = 0.0f;

	ground->vertexWk[2].vtx.x = ground->pos.x - TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[2].vtx.y = ground->pos.y + TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[2].vtx.z = 0.0f;

	ground->vertexWk[3].vtx.x = ground->pos.x + TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[3].vtx.y = ground->pos.y + TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
GROUND *GetGround(int no)
{
	return(&groundWk[no]);
}

