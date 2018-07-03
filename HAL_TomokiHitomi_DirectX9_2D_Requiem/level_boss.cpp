//=============================================================================
//
// タイトル処理 [level_boss.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "level.h"
#include "level_boss.h"
#include "input.h"
#include "sound.h"
#include "menu.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLevel_boss(int no);
void SetTextureLevel_boss( int no, int cntPattern );
void SetVertexLevel_boss(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LEVEL_BOSS					level_bossWk[LEVEL_BOSS_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureLevel_boss = NULL;

int		g_nSelectLevel_boss;
int		g_nSelectLevel_bossCount;
bool	g_bSelectLevel_ReturnFlag;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLevel_boss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_LEVEL_BOSS00,				// ファイルの名前
			&pD3DTextureLevel_boss);			// 読み込むメモリのポインタ
	}

	// タイトルの初期化
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		level_boss->bUse = false;
		level_boss->pos = D3DXVECTOR3((float)LEVEL_BOSS_POS_X, i*(float)LEVEL_BOSS_SPACING + (float)LEVEL_BOSS_POS_Y, 0.0f);
		level_boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		level_boss->nCountAnim = 0;
		level_boss->nPatternAnim = 0;

		level_boss->Texture = pD3DTextureLevel_boss;			// テクスチャへのエネミー
		level_boss->size = D3DXVECTOR2(TEXTURE_LEVEL_BOSS00_SIZE_X, TEXTURE_LEVEL_BOSS00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexLevel_boss(i);
	}

	g_nSelectLevel_boss = 0;
	g_nSelectLevel_bossCount = 0;
	g_bSelectLevel_ReturnFlag = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// メモリ解放
	if (pD3DTextureLevel_boss != NULL)
	{
		pD3DTextureLevel_boss->Release();
		pD3DTextureLevel_boss = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	if(g_bSelectLevel_ReturnFlag)
	{
		ReleaseLevel_boss();
		SetLevel();
		g_bSelectLevel_ReturnFlag = false;
	}

	if (level_boss->bUse)
	{
		// 上移動
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W)
			|| IsButtonTriggered(0, BUTTON_UP) || IsButtonTriggered(0, LSTICK_UP))
		{
			g_nSelectLevel_boss--;
			if (g_nSelectLevel_boss < 0)
			{
				g_nSelectLevel_boss += LEVEL_BOSS_MAX;
			}
			SetSe(1, E_DS8_FLAG_NONE, true);
		}
		// 下移動
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_DOWN) || IsButtonTriggered(0, LSTICK_DOWN))
		{
			g_nSelectLevel_boss++;
			SetSe(1, E_DS8_FLAG_NONE, true);
		}

		// 上移動長押し
		if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)
			|| IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, LSTICK_UP))
		{
			g_nSelectLevel_bossCount++;
			if (g_nSelectLevel_bossCount > LEVEL_BOSS_SELECT_PRESS && g_nSelectLevel_bossCount % LEVEL_BOSS_SELECT_SPEED == 0)
			{
				g_nSelectLevel_boss--;
				if (g_nSelectLevel_boss < 0)
				{
					g_nSelectLevel_boss += LEVEL_BOSS_MAX;
				}
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		// 下移動長押し
		else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, LSTICK_DOWN))
		{
			g_nSelectLevel_bossCount++;
			if (g_nSelectLevel_bossCount > LEVEL_BOSS_SELECT_PRESS && g_nSelectLevel_bossCount  % LEVEL_BOSS_SELECT_SPEED == 0)
			{
				g_nSelectLevel_boss++;
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		else
		{
			g_nSelectLevel_bossCount = 0;
		}

		for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
		{
			if (i == g_nSelectLevel_boss % LEVEL_BOSS_MAX)
			{
				level_boss->nPatternAnim = i + LEVEL_BOSS_MAX;
			}
			else
			{
				level_boss->nPatternAnim = i;
			}
			// テクスチャ座標を設定
			SetTextureLevel_boss(i, level_boss->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexLevel_boss(i);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_C))
		{
			// ステージ設定
			switch ((g_nSelectLevel_boss % LEVEL_MAX) + ONLY_BOSS + 1)
			{
			case BOSS_EASY:
				SetGameLevel(BOSS_EASY);
				break;
			case BOSS_NORMAL:
				SetGameLevel(BOSS_NORMAL);
				break;
			case BOSS_HARD:
				SetGameLevel(BOSS_HARD);
				break;
			case BOSS_ULTIMATE:
				SetGameLevel(BOSS_ULTIMATE);
				break;
			}

			// 決定SE再生
			SetSe(2, E_DS8_FLAG_NONE, true);

			// ステージ遷移:ゲーム
			SetStage(STAGE_GAME);
		}

		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_START))
		{
			g_bSelectLevel_ReturnFlag = true;
			SetSe(3, E_DS8_FLAG_NONE, true);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLevel_boss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (level_boss->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, level_boss->Texture);

			// タイトルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_LEVEL_BOSS, level_boss->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLevel_boss(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	// 頂点座標の設定
	level_boss->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	level_boss->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL_BOSS00_SIZE_X, 100.0f, 0.0f);
	level_boss->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_LEVEL_BOSS00_SIZE_Y, 0.0f);
	level_boss->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL_BOSS00_SIZE_X, 100.0f+TEXTURE_LEVEL_BOSS00_SIZE_Y, 0.0f);
	//SetVertexLevel_boss();

	// rhwの設定
	level_boss->vertexWk[0].rhw =
	level_boss->vertexWk[1].rhw =
	level_boss->vertexWk[2].rhw =
	level_boss->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	level_boss->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	level_boss->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	level_boss->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS, 0.0f );
	level_boss->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS );
	level_boss->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureLevel_boss( int no, int cntPattern )
{
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS;
	level_boss->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	level_boss->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	level_boss->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	level_boss->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexLevel_boss(int no)
{
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	level_boss->vertexWk[0].vtx.x = level_boss->pos.x - TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[0].vtx.y = level_boss->pos.y - TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[0].vtx.z = 0.0f;

	level_boss->vertexWk[1].vtx.x = level_boss->pos.x + TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[1].vtx.y = level_boss->pos.y - TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[1].vtx.z = 0.0f;

	level_boss->vertexWk[2].vtx.x = level_boss->pos.x - TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[2].vtx.y = level_boss->pos.y + TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[2].vtx.z = 0.0f;

	level_boss->vertexWk[3].vtx.x = level_boss->pos.x + TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[3].vtx.y = level_boss->pos.y + TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// アクティブ処理
//=============================================================================
void SetLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// 未使用検索
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (!level_boss->bUse)
		{
			// 有効にする
			level_boss->bUse = true;
			// アニメーションカウンタの初期化
			level_boss->nCountAnim = 0;
			// アニメーションパターンの初期化
			level_boss->nPatternAnim = 0;
			// テクスチャ座標を設定
			SetTextureLevel_boss(i, level_boss->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexLevel_boss(i);
		}
	}
}

//=============================================================================
// ノンアクティブ処理
//=============================================================================
void ReleaseLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// 使用検索
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (level_boss->bUse)
		{
			// 無効にする
			level_boss->bUse = false;
		}
	}
}

//=============================================================================
// タイトル取得関数
//=============================================================================
LEVEL_BOSS *GetLevel_boss(int no)
{
	return(&level_bossWk[no]);
}

