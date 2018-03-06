//=============================================================================
//
// プレイヤー処理 [motion_title.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "motion_title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMotion_title(int no);
void SetTextureMotion_title( int no, int cntPattern );
void SetVertexMotion_title(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
MOTION_TITLE					motion_titleWk[MOTION_TITLE_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureMotion_title = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMotion_title(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MOTION_TITLE,				// ファイルの名前
			&pD3DTextureMotion_title);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		motion_title->bUse = true;
		motion_title->bFlap = false;
		motion_title->pos = D3DXVECTOR3((float)MOTION_TITLE_POS_X, (float)MOTION_TITLE_POS_Y, 0.0f);
		motion_title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		motion_title->nCountAnim = 0;
		motion_title->nPatternAnim = 0;
		motion_title->Texture = pD3DTextureMotion_title;			// テクスチャへのエネミー
		motion_title->size = D3DXVECTOR2(TEXTURE_MOTION_TITLE00_SIZE_X, TEXTURE_MOTION_TITLE00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexMotion_title(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// メモリ解放
	if (pD3DTextureMotion_title != NULL)
	{
		pD3DTextureMotion_title->Release();
		pD3DTextureMotion_title = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (motion_title->bUse)
		{
			// アニメーション
			motion_title->nCountAnim++;
			if (motion_title->nCountAnim % TIME_ANIMATION_MOTION_TITLE == 0)
			{	// パターンの切り替え
				if (!motion_title->bFlap)
				{
					motion_title->nPatternAnim = (motion_title->nPatternAnim + 1) % ANIM_PATTERN_NUM_MOTION_TITLE;
					if (motion_title->nPatternAnim >= ANIM_PATTERN_NUM_MOTION_TITLE-1)
					{
						motion_title->bFlap = true;
					}
				}
				else
				{
					motion_title->nPatternAnim = (motion_title->nPatternAnim - 1) % ANIM_PATTERN_NUM_MOTION_TITLE;
					if (motion_title->nPatternAnim <= 0)
					{
						motion_title->bFlap = false;
					}
				}
			}

			// テクスチャ座標を設定
			SetTextureMotion_title(i, motion_title->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexMotion_title(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMotion_title(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (motion_title->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, motion_title->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MOTION_TITLE, motion_title->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMotion_title(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	// 頂点座標の設定
	motion_title->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	motion_title->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_TITLE00_SIZE_X, 100.0f, 0.0f);
	motion_title->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MOTION_TITLE00_SIZE_Y, 0.0f);
	motion_title->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_TITLE00_SIZE_X, 100.0f+TEXTURE_MOTION_TITLE00_SIZE_Y, 0.0f);
	//SetVertexMotion_title();

	// rhwの設定
	motion_title->vertexWk[0].rhw =
	motion_title->vertexWk[1].rhw =
	motion_title->vertexWk[2].rhw =
	motion_title->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	motion_title->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	motion_title->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	motion_title->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE, 0.0f );
	motion_title->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE );
	motion_title->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMotion_title( int no, int cntPattern )
{
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE;
	motion_title->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	motion_title->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	motion_title->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	motion_title->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexMotion_title(int no)
{
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	motion_title->vertexWk[0].vtx.x = motion_title->pos.x - TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[0].vtx.y = motion_title->pos.y - TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[0].vtx.z = 0.0f;

	motion_title->vertexWk[1].vtx.x = motion_title->pos.x + TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[1].vtx.y = motion_title->pos.y - TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[1].vtx.z = 0.0f;

	motion_title->vertexWk[2].vtx.x = motion_title->pos.x - TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[2].vtx.y = motion_title->pos.y + TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[2].vtx.z = 0.0f;

	motion_title->vertexWk[3].vtx.x = motion_title->pos.x + TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[3].vtx.y = motion_title->pos.y + TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
void SetMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// 未使用検索
	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (!motion_title->bUse)
		{
			// 有効にする
			motion_title->bUse = true;
			// アニメーションカウンタの初期化
			motion_title->nCountAnim = 0;
			// アニメーションパターンの初期化
			motion_title->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
MOTION_TITLE *GetMotion_title(int no)
{
	return(&motion_titleWk[no]);
}

