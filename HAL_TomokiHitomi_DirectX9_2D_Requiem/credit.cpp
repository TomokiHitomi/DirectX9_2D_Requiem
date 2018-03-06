//=============================================================================
//
// CREDIT処理 [credit.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "credit.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCredit(int no);
void SetTextureCredit( int no, int cntPattern );
void SetVertexCredit(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CREDIT					creditWk[CREDIT_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureCredit = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCredit(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_CREDIT,				// ファイルの名前
			&pD3DTextureCredit);			// 読み込むメモリのポインタ
	}

	// CREDITの初期化
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		credit->bUse = true;
		credit->pos = D3DXVECTOR3((float)CREDIT_POS_X, (float)CREDIT_POS_Y, 0.0f);
		credit->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		credit->nCountAnim = 0;
		credit->nPatternAnim = 0;

		credit->Texture = pD3DTextureCredit;			// テクスチャへのCREDIT
		credit->size = D3DXVECTOR2(TEXTURE_CREDIT_SIZE_X, TEXTURE_CREDIT_SIZE_Y);

		// 頂点情報の作成
		MakeVertexCredit(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCredit(void)
{
	CREDIT *credit = &creditWk[0];

	// メモリ解放
	if (pD3DTextureCredit != NULL)
	{
		pD3DTextureCredit->Release();
		pD3DTextureCredit = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCredit(void)
{
	CREDIT *credit = &creditWk[0];
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (credit->bUse == true)
		{
			// テクスチャ座標を設定
			SetTextureCredit(i, credit->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexCredit(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (credit->bUse)
		{
			if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_START))
			{
				SetSe(3, E_DS8_FLAG_NONE, true);
				InitGame(1);
				SetStage(STAGE_TITLE);
			}

			// テクスチャの設定
			pDevice->SetTexture(0, credit->Texture);

			// CREDITの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CREDIT, credit->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCredit(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[no];

	// 頂点座標の設定
	credit->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	credit->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CREDIT_SIZE_X, 100.0f, 0.0f);
	credit->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CREDIT_SIZE_Y, 0.0f);
	credit->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CREDIT_SIZE_X, 100.0f+TEXTURE_CREDIT_SIZE_Y, 0.0f);
	//SetVertexCredit();

	// rhwの設定
	credit->vertexWk[0].rhw =
	credit->vertexWk[1].rhw =
	credit->vertexWk[2].rhw =
	credit->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	credit->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);

	// テクスチャ座標の設定
	credit->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	credit->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CREDIT, 0.0f );
	credit->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CREDIT );
	credit->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CREDIT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CREDIT );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureCredit( int no, int cntPattern )
{
	CREDIT *credit = &creditWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CREDIT;
	credit->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	credit->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	credit->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	credit->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexCredit(int no)
{
	CREDIT *credit = &creditWk[no];

	credit->vertexWk[0].vtx.x = credit->pos.x - TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[0].vtx.y = credit->pos.y - TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[0].vtx.z = 0.0f;

	credit->vertexWk[1].vtx.x = credit->pos.x + TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[1].vtx.y = credit->pos.y - TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[1].vtx.z = 0.0f;

	credit->vertexWk[2].vtx.x = credit->pos.x - TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[2].vtx.y = credit->pos.y + TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[2].vtx.z = 0.0f;

	credit->vertexWk[3].vtx.x = credit->pos.x + TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[3].vtx.y = credit->pos.y + TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// CREDITセット関数
//=============================================================================
void SetCredit(void)
{
	CREDIT *credit = &creditWk[0];
	// 未使用検索
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (!credit->bUse)
		{
			// 有効にする
			credit->bUse = true;
			return;
		}
	}
}

//=============================================================================
// CREDIT取得関数
//=============================================================================
CREDIT *GetCredit(int no)
{
	return(&creditWk[no]);
}

