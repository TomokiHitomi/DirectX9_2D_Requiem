//=============================================================================
//
// TOTAL処理 [total.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "total.h"
#include "totalboard.h"
#include "close.h"
#include "result.h"
#include "pressenter.h"
#include "sound.h"
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTotal(void);
void SetTextureTotal(void);
void AddTotal(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTotal = NULL;					// テクスチャへのポリゴン
VERTEX_2D				g_vertexWkTotal[TOTAL_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				g_posTotal;									// ポリゴンの移動量

int						g_nTotal;									// スコア
int						g_nAddtotal;
bool					g_bTotalStop;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTotal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_TOTAL00,				// ファイルの名前
			&g_pD3DTextureTotal);				// 読み込むメモリのポインタ
	}

	g_posTotal = D3DXVECTOR3((float)TOTAL_POS_X + (float)TOTALBOARD_POS_X, (float)TOTAL_POS_Y + (float)TOTALBOARD_POS_Y, 0.0f);
	g_nTotal = 0;
	g_nAddtotal = 0;
	g_bTotalStop = false;

	// 頂点情報の作成
	MakeVertexTotal();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTotal(void)
{
	if (g_pD3DTextureTotal != NULL)
	{	// テクスチャの開放
		g_pD3DTextureTotal->Release();
		g_pD3DTextureTotal = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTotal(void)
{
	// トータルスコア
	AddTotal();

	SetTextureTotal();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTotal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTotal);

	// スコア
	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TOTAL, g_vertexWkTotal[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTotal(void)
{
	float fWidth = TEXTURE_TOTAL00_SIZE_X;	// 数字の横幅

	// 桁数分処理する
	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// 頂点座標の設定
		g_vertexWkTotal[i][0].vtx.x = -fWidth * i + g_posTotal.x;
		g_vertexWkTotal[i][0].vtx.y = g_posTotal.y;
		g_vertexWkTotal[i][0].vtx.z = 0.0f;
		g_vertexWkTotal[i][1].vtx.x = -fWidth * i + g_posTotal.x + TEXTURE_TOTAL00_SIZE_X;
		g_vertexWkTotal[i][1].vtx.y = g_posTotal.y;
		g_vertexWkTotal[i][1].vtx.z = 0.0f;
		g_vertexWkTotal[i][2].vtx.x = -fWidth * i + g_posTotal.x;
		g_vertexWkTotal[i][2].vtx.y = g_posTotal.y + TEXTURE_TOTAL00_SIZE_Y;
		g_vertexWkTotal[i][2].vtx.z = 0.0f;
		g_vertexWkTotal[i][3].vtx.x = -fWidth * i + g_posTotal.x + TEXTURE_TOTAL00_SIZE_X;
		g_vertexWkTotal[i][3].vtx.y = g_posTotal.y + TEXTURE_TOTAL00_SIZE_Y;
		g_vertexWkTotal[i][3].vtx.z = 0.0f;

		// rhwの設定
		g_vertexWkTotal[i][0].rhw =
		g_vertexWkTotal[i][1].rhw =
		g_vertexWkTotal[i][2].rhw =
		g_vertexWkTotal[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWkTotal[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		g_vertexWkTotal[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkTotal[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWkTotal[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkTotal[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureTotal(void)
{
	int number = g_nTotal;

	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWkTotal[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkTotal[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkTotal[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkTotal[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// スコアの加算処理
//=============================================================================
void AddTotal(void)
{
	PRESSENTER *pressenter = GetPressenter(0);

	if (g_nTotal <= g_nAddtotal)
	{
		g_nTotal += TOTAL_COUNT_UP;
		if (g_nTotal > g_nAddtotal)
		{
			g_nTotal = g_nAddtotal;
			pressenter->bUse = true;
		}
	}

	if (g_nTotal > TOTAL_MAX)
	{
		g_nTotal = TOTAL_MAX;
	}
	else if (g_nTotal < 0)
	{
		g_nTotal = 0;
	}

}
//=============================================================================
// ボーナス値加算
//=============================================================================
void SetTotal(int nType,int nAdd)
{
	switch(nType)
	{
	case 0:
		g_nAddtotal += ((TOTAL_TIME_MAX - nAdd) * TOTAL_TIME_BONUS);
		break;
	case 1:
		g_nAddtotal += nAdd;
		break;
	case 2:
		g_nAddtotal += (nAdd * TOTAL_HP_BONUS);
		break;
	}
}

//=============================================================================
// トータルスコア取得関数
//=============================================================================
int *GetTotal(void)
{
	return(&g_nTotal);
}