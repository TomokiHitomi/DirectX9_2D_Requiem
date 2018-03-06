//=============================================================================
//
// タイトル処理 [pressenter.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"
#include "close.h"
#include "fade.h"
#include "thank.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPressenter(int no);
void SetTexturePressenter( int no, int cntPattern );	//
void SetVertexPressenter(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PRESSENTER					pressenterWk[PRESSENTER_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTexturePressenter = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPressenter(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PRESSENTER *pressenter = &pressenterWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_PRESSENTER00,				// ファイルの名前
			&pD3DTexturePressenter);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < PRESSENTER_MAX; i++, pressenter++)
	{
		pressenter->bUse = false;
		pressenter->bAlphaFlag = false;

		pressenter->pos = D3DXVECTOR3((float)PRESSENTER_POS_X, (float)PRESSENTER_POS_Y, 0.0f);
		pressenter->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pressenter->nCountAnim = 0;
		pressenter->nPatternAnim = 0;
		pressenter->nAlphaCount = 0;

		pressenter->Texture = pD3DTexturePressenter;			// テクスチャへのエネミー
		pressenter->size = D3DXVECTOR2(TEXTURE_PRESSENTER00_SIZE_X, TEXTURE_PRESSENTER00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexPressenter(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPressenter(void)
{
	PRESSENTER *pressenter = &pressenterWk[0];

	// メモリ解放
	if (pD3DTexturePressenter != NULL)
	{
		pD3DTexturePressenter->Release();
		pD3DTexturePressenter = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePressenter(void)
{
	PRESSENTER *pressenter = &pressenterWk[0];
	FADE *fade = GetFade(0);
	THANK *thank = GetThank(0);

	for (int i = 0; i < PRESSENTER_MAX; i++, pressenter++)
	{
		if (pressenter->bUse)
		{
			// アニメーション
			pressenter->nCountAnim++;
			if ((pressenter->nCountAnim % TIME_ANIMATION_PRESSENTER) == 0)
			{
				// パターンの切り替え
				pressenter->nPatternAnim = (pressenter->nPatternAnim + 1) % ANIM_PATTERN_NUM_PRESSENTER;
			}

			if (pressenter->bAlphaFlag)
			{
				pressenter->nAlphaCount -= PRESSENTER_ALPHA_DOWN_SPEED;
				if (pressenter->nAlphaCount <= PRESSENTER_ALPHA_MIN)
				{
					pressenter->nAlphaCount = PRESSENTER_ALPHA_MIN;
					pressenter->bAlphaFlag = false;
				}
			}
			else
			{
				pressenter->nAlphaCount += PRESSENTER_ALPHA_UP_SPEED;
				if (pressenter->nAlphaCount >= PRESSENTER_ALPHA_MAX)
				{
					pressenter->nAlphaCount = PRESSENTER_ALPHA_MAX;
					pressenter->bAlphaFlag = true;
				}
			}

			// 画面遷移(0)、二週目用初期化処理
			if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_C))
			{
				SetFade(0, 1);
				SetSe(2, E_DS8_FLAG_NONE,false);
			}

			if (fade->nAlphaCount == FADE_ALPHA_MAX && fade->nFadeFlag == 1)
			{
				thank->bUse = true;
			}

			// テクスチャ座標を設定
			SetTexturePressenter(i, pressenter->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexPressenter(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPressenter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PRESSENTER *pressenter = &pressenterWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PRESSENTER_MAX; i++, pressenter++)
	{
		if (pressenter->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, pressenter->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PRESSENTER, pressenter->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPressenter(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PRESSENTER *pressenter = &pressenterWk[no];

	// 頂点座標の設定
	pressenter->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	pressenter->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PRESSENTER00_SIZE_X, 100.0f, 0.0f);
	pressenter->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PRESSENTER00_SIZE_Y, 0.0f);
	pressenter->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PRESSENTER00_SIZE_X, 100.0f+TEXTURE_PRESSENTER00_SIZE_Y, 0.0f);
	//SetVertexPressenter();

	// rhwの設定
	pressenter->vertexWk[0].rhw =
	pressenter->vertexWk[1].rhw =
	pressenter->vertexWk[2].rhw =
	pressenter->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	pressenter->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);

	// テクスチャ座標の設定
	pressenter->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pressenter->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PRESSENTER, 0.0f );
	pressenter->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER );
	pressenter->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PRESSENTER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePressenter( int no, int cntPattern )
{
	PRESSENTER *pressenter = &pressenterWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PRESSENTER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PRESSENTER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PRESSENTER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER;
	pressenter->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	pressenter->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	pressenter->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	pressenter->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexPressenter(int no)
{
	PRESSENTER *pressenter = &pressenterWk[no];

	pressenter->vertexWk[0].vtx.x = pressenter->pos.x - TEXTURE_PRESSENTER00_SIZE_X;
	pressenter->vertexWk[0].vtx.y = pressenter->pos.y - TEXTURE_PRESSENTER00_SIZE_Y;
	pressenter->vertexWk[0].vtx.z = 0.0f;

	pressenter->vertexWk[1].vtx.x = pressenter->pos.x + TEXTURE_PRESSENTER00_SIZE_X;
	pressenter->vertexWk[1].vtx.y = pressenter->pos.y - TEXTURE_PRESSENTER00_SIZE_Y;
	pressenter->vertexWk[1].vtx.z = 0.0f;

	pressenter->vertexWk[2].vtx.x = pressenter->pos.x - TEXTURE_PRESSENTER00_SIZE_X;
	pressenter->vertexWk[2].vtx.y = pressenter->pos.y + TEXTURE_PRESSENTER00_SIZE_Y;
	pressenter->vertexWk[2].vtx.z = 0.0f;

	pressenter->vertexWk[3].vtx.x = pressenter->pos.x + TEXTURE_PRESSENTER00_SIZE_X;
	pressenter->vertexWk[3].vtx.y = pressenter->pos.y + TEXTURE_PRESSENTER00_SIZE_Y;
	pressenter->vertexWk[3].vtx.z = 0.0f;

	// 反射光の設定
	pressenter->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
	pressenter->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, pressenter->nAlphaCount);
}

//=============================================================================
// タイトル取得関数
//=============================================================================
PRESSENTER *GetPressenter(int no)
{
	return(&pressenterWk[no]);
}

