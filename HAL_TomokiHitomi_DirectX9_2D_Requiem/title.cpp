//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(int no);
void SetTextureTitle( int no, int cntPattern );	//
void SetVertexTitle(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
TITLE					titleWk[TITLE_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureTitle = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_TITLE00,				// ファイルの名前
			&pD3DTextureTitle);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		title->bUse = true;
		title->pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		title->nCountAnim = 0;
		title->nPatternAnim = 0;

		title->Texture = pD3DTextureTitle;			// テクスチャへのエネミー
		title->size = D3DXVECTOR2(TEXTURE_TITLE00_SIZE_X, TEXTURE_TITLE00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexTitle(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	TITLE *title = &titleWk[0];

	// メモリ解放
	if (pD3DTextureTitle != NULL)
	{
		pD3DTextureTitle->Release();
		pD3DTextureTitle = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	TITLE *title = &titleWk[0];

	SetBgmVol(0, true);
	SetBgmVol(1, false);
	SetBgmVol(2, false);
	SetBgmVol(3, false);
	SetBgmVol(4, false);

	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		if (title->bUse == true)
		{
			// アニメーション
			title->nCountAnim++;
			if ((title->nCountAnim % TIME_ANIMATION_TITLE) == 0)
			{
				// パターンの切り替え
				title->nPatternAnim = (title->nPatternAnim + 1) % ANIM_PATTERN_NUM_TITLE;
			}

			// テクスチャ座標を設定
			SetTextureTitle(i, title->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexTitle(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		if (title->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, title->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TITLE, title->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[no];

	// 頂点座標の設定
	title->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	title->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TITLE00_SIZE_X, 100.0f, 0.0f);
	title->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TITLE00_SIZE_Y, 0.0f);
	title->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TITLE00_SIZE_X, 100.0f+TEXTURE_TITLE00_SIZE_Y, 0.0f);
	//SetVertexTitle();

	// rhwの設定
	title->vertexWk[0].rhw =
	title->vertexWk[1].rhw =
	title->vertexWk[2].rhw =
	title->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	title->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	title->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	title->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TITLE, 0.0f );
	title->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TITLE );
	title->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TITLE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TITLE );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTitle( int no, int cntPattern )
{
	TITLE *title = &titleWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TITLE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TITLE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE;
	title->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	title->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	title->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	title->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexTitle(int no)
{
	TITLE *title = &titleWk[no];

	title->vertexWk[0].vtx.x = title->pos.x - TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[0].vtx.y = title->pos.y - TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[0].vtx.z = 0.0f;

	title->vertexWk[1].vtx.x = title->pos.x + TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[1].vtx.y = title->pos.y - TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[1].vtx.z = 0.0f;

	title->vertexWk[2].vtx.x = title->pos.x - TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[2].vtx.y = title->pos.y + TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[2].vtx.z = 0.0f;

	title->vertexWk[3].vtx.x = title->pos.x + TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[3].vtx.y = title->pos.y + TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
TITLE *GetTitle(int no)
{
	return(&titleWk[no]);
}

