//=============================================================================
//
// タイトル処理 [menu.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "menu.h"
#include "input.h"
#include "sound.h"
#include "credit.h"
#include "level.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMenu(int no);
void SetTextureMenu( int no, int cntPattern );
void SetVertexMenu(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
MENU					menuWk[MENU_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureMenu = NULL;

int g_nSelectMenu;
int g_nSelectMenuCount;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMenu(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MENU00,				// ファイルの名前
			&pD3DTextureMenu);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		menu->bUse = true;
		menu->pos = D3DXVECTOR3((float)MENU_POS_X, i*(float)MENU_SPACING + (float)MENU_POS_Y, 0.0f);
		menu->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		menu->nCountAnim = 0;
		menu->nPatternAnim = 0;

		menu->Texture = pD3DTextureMenu;			// テクスチャへのエネミー
		menu->size = D3DXVECTOR2(TEXTURE_MENU00_SIZE_X, TEXTURE_MENU00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexMenu(i);
	}

	g_nSelectMenu = 0;
	g_nSelectMenuCount = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMenu(void)
{
	MENU *menu = &menuWk[0];

	// メモリ解放
	if (pD3DTextureMenu != NULL)
	{
		pD3DTextureMenu->Release();
		pD3DTextureMenu = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMenu(void)
{
	MENU *menu = &menuWk[0];

	if (menu->bUse)
	{
		// 上移動
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W)
			|| IsButtonTriggered(0, BUTTON_UP) || IsButtonTriggered(0, LSTICK_UP))
		{
			g_nSelectMenu--;
			if (g_nSelectMenu < 0)
			{
				g_nSelectMenu += MENU_MAX;
			}
			SetSe(1, E_DS8_FLAG_NONE, true);
		}
		// 下移動
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_DOWN) || IsButtonTriggered(0, LSTICK_DOWN))
		{
			g_nSelectMenu++;
			SetSe(1, E_DS8_FLAG_NONE, true);
		}

		// 上移動長押し
		if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)
			|| IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, LSTICK_UP))
		{
			g_nSelectMenuCount++;
			if (g_nSelectMenuCount > MENU_SELECT_PRESS && g_nSelectMenuCount % MENU_SELECT_SPEED == 0)
			{
				g_nSelectMenu--;
				if (g_nSelectMenu < 0)
				{
					g_nSelectMenu += MENU_MAX;
				}
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		// 下移動長押し
		else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, LSTICK_DOWN))
		{
			g_nSelectMenuCount++;
			if (g_nSelectMenuCount > MENU_SELECT_PRESS && g_nSelectMenuCount  % MENU_SELECT_SPEED == 0)
			{
				g_nSelectMenu++;
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		else
		{
			g_nSelectMenuCount = 0;
		}


		for (int i = 0; i < MENU_MAX; i++, menu++)
		{
			if (i == g_nSelectMenu % MENU_MAX)
			{
				menu->nPatternAnim = i + MENU_MAX;
			}
			else
			{
				menu->nPatternAnim = i;
			}
			// テクスチャ座標を設定
			SetTextureMenu(i, menu->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexMenu(i);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_C))
		{
			switch (g_nSelectMenu % MENU_MAX)
			{
			case 0:
				ReleaseMenu();
				SetLevel();
				break;
			case 1:
				InitGame(1);
				SetStage(STAGE_TUTORIAL);
				break;
			case 2:
				InitGame(1);
				SetStage(STAGE_CREDIT);
				break;
			case 3:
				SetEndFlag();
				break;
			}
			SetSe(2, E_DS8_FLAG_NONE, true);
		}
		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B))
		{
			SetSe(3, E_DS8_FLAG_NONE, true);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (menu->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, menu->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MENU, menu->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMenu(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[no];

	// 頂点座標の設定
	menu->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	menu->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MENU00_SIZE_X, 100.0f, 0.0f);
	menu->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MENU00_SIZE_Y, 0.0f);
	menu->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MENU00_SIZE_X, 100.0f+TEXTURE_MENU00_SIZE_Y, 0.0f);
	//SetVertexMenu();

	// rhwの設定
	menu->vertexWk[0].rhw =
	menu->vertexWk[1].rhw =
	menu->vertexWk[2].rhw =
	menu->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	menu->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	menu->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	menu->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MENU, 0.0f );
	menu->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MENU );
	menu->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MENU, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MENU );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMenu( int no, int cntPattern )
{
	MENU *menu = &menuWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MENU;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MENU;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MENU;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MENU;
	menu->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	menu->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	menu->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	menu->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexMenu(int no)
{
	MENU *menu = &menuWk[no];

	menu->vertexWk[0].vtx.x = menu->pos.x - TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[0].vtx.y = menu->pos.y - TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[0].vtx.z = 0.0f;

	menu->vertexWk[1].vtx.x = menu->pos.x + TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[1].vtx.y = menu->pos.y - TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[1].vtx.z = 0.0f;

	menu->vertexWk[2].vtx.x = menu->pos.x - TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[2].vtx.y = menu->pos.y + TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[2].vtx.z = 0.0f;

	menu->vertexWk[3].vtx.x = menu->pos.x + TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[3].vtx.y = menu->pos.y + TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// アクティブ処理
//=============================================================================
void SetMenu(void)
{
	MENU *menu = &menuWk[0];

	// 未使用検索
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (!menu->bUse)
		{
			// 有効にする
			menu->bUse = true;
			// アニメーションカウンタの初期化
			menu->nCountAnim = 0;
			// アニメーションパターンの初期化
			menu->nPatternAnim = 0;
		}
	}
}

//=============================================================================
// ノンアクティブ処理
//=============================================================================
void ReleaseMenu(void)
{
	MENU *menu = &menuWk[0];

	// 使用検索
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (menu->bUse)
		{
			// 無効にする
			menu->bUse = false;
		}
	}
}

//=============================================================================
// タイトル取得関数
//=============================================================================
MENU *GetMenu(int no)
{
	return(&menuWk[no]);
}

