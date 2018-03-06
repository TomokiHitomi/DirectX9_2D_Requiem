//=============================================================================
//
// タイトル処理 [thank.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "thank.h"
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
HRESULT MakeVertexThank(int no);
void SetTextureThank( int no, int cntPattern );	//
void SetVertexThank(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
THANK					thankWk[THANK_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureThank = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitThank(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_THANK00,				// ファイルの名前
			&pD3DTextureThank);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		thank->bUse = false;
		thank->pos = D3DXVECTOR3((float)THANK_POS_X, (float)THANK_POS_Y, 0.0f);
		thank->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		thank->nCountAnim = 0;
		thank->nPatternAnim = 0;
		thank->nAlphaCount = 0;
		thank->nSceneCount = THANK_SCENE_COUNT;

		thank->Texture = pD3DTextureThank;			// テクスチャへのエネミー
		thank->size = D3DXVECTOR2(TEXTURE_THANK00_SIZE_X, TEXTURE_THANK00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexThank(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitThank(void)
{
	THANK *thank = &thankWk[0];

	// メモリ解放
	if (pD3DTextureThank != NULL)
	{
		pD3DTextureThank->Release();
		pD3DTextureThank = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateThank(void)
{
	THANK *thank = &thankWk[0];

	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		if (thank->bUse)
		{
			// アニメーション
			thank->nCountAnim++;
			if ((thank->nCountAnim % TIME_ANIMATION_THANK) == 0)
			{
				// パターンの切り替え
				thank->nPatternAnim = (thank->nPatternAnim + 1) % ANIM_PATTERN_NUM_THANK;
			}

			thank->nAlphaCount += THANK_ALPHA_SPEED;
			if (thank->nAlphaCount >= THANK_ALPHA_MAX)
			{
				thank->nAlphaCount = THANK_ALPHA_MAX;
			}

			thank->nSceneCount--;
			if (thank->nSceneCount <= 0)
			{
				InitGame(1);
				SetStage(STAGE_TITLE);
			}

			// 画面遷移(0)、二週目用初期化処理
			if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_C))
			{
				InitGame(1);
				SetStage(STAGE_TITLE);
			}


			// テクスチャ座標を設定
			SetTextureThank(i, thank->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexThank(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawThank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		if (thank->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, thank->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_THANK, thank->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexThank(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[no];

	// 頂点座標の設定
	thank->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	thank->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_THANK00_SIZE_X, 100.0f, 0.0f);
	thank->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_THANK00_SIZE_Y, 0.0f);
	thank->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_THANK00_SIZE_X, 100.0f+TEXTURE_THANK00_SIZE_Y, 0.0f);
	//SetVertexThank();

	// rhwの設定
	thank->vertexWk[0].rhw =
	thank->vertexWk[1].rhw =
	thank->vertexWk[2].rhw =
	thank->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	thank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);

	// テクスチャ座標の設定
	thank->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	thank->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_THANK, 0.0f );
	thank->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_THANK );
	thank->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_THANK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_THANK );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureThank( int no, int cntPattern )
{
	THANK *thank = &thankWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_THANK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_THANK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_THANK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_THANK;
	thank->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	thank->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	thank->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	thank->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexThank(int no)
{
	THANK *thank = &thankWk[no];

	thank->vertexWk[0].vtx.x = thank->pos.x - TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[0].vtx.y = thank->pos.y - TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[0].vtx.z = 0.0f;

	thank->vertexWk[1].vtx.x = thank->pos.x + TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[1].vtx.y = thank->pos.y - TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[1].vtx.z = 0.0f;

	thank->vertexWk[2].vtx.x = thank->pos.x - TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[2].vtx.y = thank->pos.y + TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[2].vtx.z = 0.0f;

	thank->vertexWk[3].vtx.x = thank->pos.x + TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[3].vtx.y = thank->pos.y + TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[3].vtx.z = 0.0f;

	// 反射光の設定
	thank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
}

//=============================================================================
// タイトル取得関数
//=============================================================================
THANK *GetThank(int no)
{
	return(&thankWk[no]);
}

