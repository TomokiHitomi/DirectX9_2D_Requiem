//=============================================================================
//
// タイトル処理 [timeboard.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "timeboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTimeboard(int no);
void SetTextureTimeboard( int no, int cntPattern );	//
void SetVertexTimeboard(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
TIMEBOARD					timeboardWk[TIMEBOARD_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureTimeboard = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTimeboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[0];


	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_TIMEBOARD00,				// ファイルの名前
			&pD3DTextureTimeboard);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		timeboard->bUse = true;
		timeboard->bPosMoveFlag = true;

		timeboard->pos = D3DXVECTOR3((float)TIMEBOARD_POS_X, (float)TIMEBOARD_POS_Y, 0.0f);
		timeboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeboard->nCountAnim = 0;
		timeboard->nPatternAnim = 0;

		timeboard->Texture = pD3DTextureTimeboard;			// テクスチャへのエネミー
		timeboard->size = D3DXVECTOR2(TEXTURE_TIMEBOARD00_SIZE_X, TEXTURE_TIMEBOARD00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexTimeboard(i);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimeboard(void)
{
	TIMEBOARD *timeboard = &timeboardWk[0];

	// メモリ解放
	if (pD3DTextureTimeboard != NULL)
	{
		pD3DTextureTimeboard->Release();
		pD3DTextureTimeboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimeboard(void)
{
	TIMEBOARD *timeboard = &timeboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		if (timeboard->bUse == true)
		{
			// アニメーション
			timeboard->nCountAnim++;
			if ((timeboard->nCountAnim % TIME_ANIMATION_TIMEBOARD) == 0)
			{
				// パターンの切り替え
				timeboard->nPatternAnim = (timeboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_TIMEBOARD;
			}

			if (timeboard->bPosMoveFlag && !result->bPosMoveFlag)
			{
				timeboard->pos += result->vecPosMove;
				timeboard->bPosMoveFlag = false;
			}

			// テクスチャ座標を設定
			SetTextureTimeboard(i, timeboard->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexTimeboard(i);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimeboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		if (timeboard->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, timeboard->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TIMEBOARD, timeboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTimeboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[no];

	// 頂点座標の設定
	timeboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	timeboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TIMEBOARD00_SIZE_X, 100.0f, 0.0f);
	timeboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TIMEBOARD00_SIZE_Y, 0.0f);
	timeboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TIMEBOARD00_SIZE_X, 100.0f+TEXTURE_TIMEBOARD00_SIZE_Y, 0.0f);
	//SetVertexTimeboard();

	// rhwの設定
	timeboard->vertexWk[0].rhw =
	timeboard->vertexWk[1].rhw =
	timeboard->vertexWk[2].rhw =
	timeboard->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	timeboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	timeboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	timeboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD, 0.0f );
	timeboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD );
	timeboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTimeboard( int no, int cntPattern )
{
	TIMEBOARD *timeboard = &timeboardWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD;
	timeboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	timeboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	timeboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	timeboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexTimeboard(int no)
{
	TIMEBOARD *timeboard = &timeboardWk[no];

	timeboard->vertexWk[0].vtx.x = timeboard->pos.x - TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[0].vtx.y = timeboard->pos.y - TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[0].vtx.z = 0.0f;

	timeboard->vertexWk[1].vtx.x = timeboard->pos.x + TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[1].vtx.y = timeboard->pos.y - TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[1].vtx.z = 0.0f;

	timeboard->vertexWk[2].vtx.x = timeboard->pos.x - TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[2].vtx.y = timeboard->pos.y + TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[2].vtx.z = 0.0f;

	timeboard->vertexWk[3].vtx.x = timeboard->pos.x + TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[3].vtx.y = timeboard->pos.y + TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイトル取得関数
//=============================================================================
TIMEBOARD *GetTimeboard(int no)
{
	return(&timeboardWk[no]);
}

