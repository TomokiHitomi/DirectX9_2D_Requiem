//=============================================================================
//
// HOWTOPLAY処理 [howtoplay.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "howtoplay.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexHowtoplay(int no);
void SetTextureHowtoplay( int no, int cntPattern );	//
void SetVertexHowtoplay(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
HOWTOPLAY					howtoplayWk[HOWTOPLAY_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureHowtoplay = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHowtoplay(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_HOWTOPLAY,				// ファイルの名前
			&pD3DTextureHowtoplay);			// 読み込むメモリのポインタ
	}

	// HOWTOPLAYの初期化
	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		howtoplay->bUse = true;
		howtoplay->pos = D3DXVECTOR3((float)HOWTOPLAY_POS_X, (float)HOWTOPLAY_POS_Y, 0.0f);
		howtoplay->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		howtoplay->nCountAnim = 0;
		howtoplay->nPatternAnim = 0;

		howtoplay->Texture = pD3DTextureHowtoplay;			// テクスチャへのHOWTOPLAY
		howtoplay->size = D3DXVECTOR2(TEXTURE_HOWTOPLAY_SIZE_X, TEXTURE_HOWTOPLAY_SIZE_Y);

		// 頂点情報の作成
		MakeVertexHowtoplay(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHowtoplay(void)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	// メモリ解放
	if (pD3DTextureHowtoplay != NULL)
	{
		pD3DTextureHowtoplay->Release();
		pD3DTextureHowtoplay = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHowtoplay(void)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[0];
	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		if (howtoplay->bUse == true)
		{
			// テクスチャ座標を設定
			SetTextureHowtoplay(i, howtoplay->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexHowtoplay(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHowtoplay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		if (howtoplay->bUse)
		{
			// How to playページ切り替え
			if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(0, BUTTON_C))
			{
				if (howtoplay->nPatternAnim)
				{
					howtoplay->nPatternAnim = 0;
				}
				else
				{
					howtoplay->nPatternAnim = 1;
				}
			}
			// テクスチャの設定
			pDevice->SetTexture(0, howtoplay->Texture);

			// HOWTOPLAYの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HOWTOPLAY, howtoplay->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexHowtoplay(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	// 頂点座標の設定
	howtoplay->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	howtoplay->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_SIZE_X, 100.0f, 0.0f);
	howtoplay->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_HOWTOPLAY_SIZE_Y, 0.0f);
	howtoplay->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_SIZE_X, 100.0f+TEXTURE_HOWTOPLAY_SIZE_Y, 0.0f);
	//SetVertexHowtoplay();

	// rhwの設定
	howtoplay->vertexWk[0].rhw =
	howtoplay->vertexWk[1].rhw =
	howtoplay->vertexWk[2].rhw =
	howtoplay->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	howtoplay->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);

	// テクスチャ座標の設定
	howtoplay->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	howtoplay->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY, 0.0f );
	howtoplay->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY );
	howtoplay->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureHowtoplay( int no, int cntPattern )
{
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY;
	howtoplay->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	howtoplay->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	howtoplay->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	howtoplay->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexHowtoplay(int no)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	howtoplay->vertexWk[0].vtx.x = howtoplay->pos.x - TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[0].vtx.y = howtoplay->pos.y - TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[0].vtx.z = 0.0f;

	howtoplay->vertexWk[1].vtx.x = howtoplay->pos.x + TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[1].vtx.y = howtoplay->pos.y - TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[1].vtx.z = 0.0f;

	howtoplay->vertexWk[2].vtx.x = howtoplay->pos.x - TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[2].vtx.y = howtoplay->pos.y + TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[2].vtx.z = 0.0f;

	howtoplay->vertexWk[3].vtx.x = howtoplay->pos.x + TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[3].vtx.y = howtoplay->pos.y + TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// HOWTOPLAY取得関数
//=============================================================================
HOWTOPLAY *GetHowtoplay(int no)
{
	return(&howtoplayWk[no]);
}

