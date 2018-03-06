//=============================================================================
//
// プレイヤー処理 [motion_result.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "motion_result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMotion_result(int no);
void SetTextureMotion_result( int no, int cntPattern );
void SetVertexMotion_result(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
MOTION_RESULT					motion_resultWk[MOTION_RESULT_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureMotion_result = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMotion_result(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MOTION_RESULT,				// ファイルの名前
			&pD3DTextureMotion_result);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		motion_result->bUse = false;
		motion_result->pos = D3DXVECTOR3((float)MOTION_RESULT_POS_X, (float)MOTION_RESULT_POS_Y, 0.0f);
		motion_result->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		motion_result->nCountAnim = 0;
		motion_result->nPatternAnim = 0;
		motion_result->Texture = pD3DTextureMotion_result;			// テクスチャへのエネミー
		motion_result->size = D3DXVECTOR2(TEXTURE_MOTION_RESULT00_SIZE_X, TEXTURE_MOTION_RESULT00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexMotion_result(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// メモリ解放
	if (pD3DTextureMotion_result != NULL)
	{
		pD3DTextureMotion_result->Release();
		pD3DTextureMotion_result = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (motion_result->bUse)
		{
			// アニメーション
			motion_result->nCountAnim++;
			if (motion_result->nCountAnim % TIME_ANIMATION_MOTION_RESULT == 0)
			{	// パターンの切り替え
				motion_result->nPatternAnim = (motion_result->nPatternAnim + 1) % ANIM_PATTERN_NUM_MOTION_RESULT;
			}

			// テクスチャ座標を設定
			SetTextureMotion_result(i, motion_result->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexMotion_result(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMotion_result(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (motion_result->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, motion_result->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MOTION_RESULT, motion_result->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMotion_result(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	// 頂点座標の設定
	motion_result->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	motion_result->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_RESULT00_SIZE_X, 100.0f, 0.0f);
	motion_result->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MOTION_RESULT00_SIZE_Y, 0.0f);
	motion_result->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_RESULT00_SIZE_X, 100.0f+TEXTURE_MOTION_RESULT00_SIZE_Y, 0.0f);
	//SetVertexMotion_result();

	// rhwの設定
	motion_result->vertexWk[0].rhw =
	motion_result->vertexWk[1].rhw =
	motion_result->vertexWk[2].rhw =
	motion_result->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	motion_result->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	motion_result->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	motion_result->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT, 0.0f );
	motion_result->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT );
	motion_result->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMotion_result( int no, int cntPattern )
{
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT;
	motion_result->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	motion_result->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	motion_result->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	motion_result->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexMotion_result(int no)
{
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	motion_result->vertexWk[0].vtx.x = motion_result->pos.x - TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[0].vtx.y = motion_result->pos.y - TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[0].vtx.z = 0.0f;

	motion_result->vertexWk[1].vtx.x = motion_result->pos.x + TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[1].vtx.y = motion_result->pos.y - TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[1].vtx.z = 0.0f;

	motion_result->vertexWk[2].vtx.x = motion_result->pos.x - TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[2].vtx.y = motion_result->pos.y + TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[2].vtx.z = 0.0f;

	motion_result->vertexWk[3].vtx.x = motion_result->pos.x + TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[3].vtx.y = motion_result->pos.y + TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// アクティブ処理
//=============================================================================
void SetMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// 未使用検索
	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (!motion_result->bUse)
		{
			// 有効にする
			motion_result->bUse = true;
			// アニメーションカウンタの初期化
			motion_result->nCountAnim = 0;
			// アニメーションパターンの初期化
			motion_result->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
MOTION_RESULT *GetMotion_result(int no)
{
	return(&motion_resultWk[no]);
}

