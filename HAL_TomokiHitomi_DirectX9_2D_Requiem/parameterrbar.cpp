//=============================================================================
//
// パラメータ処理 [parameterbar.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "parameterbar.h"
#include "parameter.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexParameterbar(int no);
void SetTextureParameterbar( int no, int cntPattern );	//
void SetVertexParameterbar(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PARAMETERBAR					parameterbarWk[PARAMETERBAR_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureParameterbar = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitParameterbar(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_PARAMETERBAR00,				// ファイルの名前
			&pD3DTextureParameterbar);			// 読み込むメモリのポインタ
	}

	// パラメータの初期化
	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		parameterbar->Texture = pD3DTextureParameterbar;			// テクスチャへのエネミー
		parameterbar->size = D3DXVECTOR2(TEXTURE_PARAMETERBAR00_SIZE_X, TEXTURE_PARAMETERBAR00_SIZE_Y);
		parameterbar->vecChangeSize = D3DXVECTOR3(TEXTURE_CHANGE_PARAMETERBAR_X, TEXTURE_CHANGE_PARAMETERBAR_Y, 0.0f);

		InitStatusParameterbar(i);

		// 頂点情報の作成
		MakeVertexParameterbar(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParameterbar(void)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// メモリ解放
	if (pD3DTextureParameterbar != NULL)
	{
		pD3DTextureParameterbar->Release();
		pD3DTextureParameterbar = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParameterbar(void)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];
	PLAYER *player;
	ENEMY *enemy;

	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (parameterbar->bUse)
		{
			parameterbar->nPatternAnim = parameterbar->nType;

			switch (parameterbar->nType)
			{
			case 0:
				player = GetPlayer(parameterbar->nTarget);
				parameterbar->pos.x = player->pos.x;
				parameterbar->pos.y = player->pos.y + (float)PARAMETERBAR_DRAW_HP;
				if (!player->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			case 1:
				player = GetPlayer(parameterbar->nTarget);
				parameterbar->pos.x = player->pos.x;
				parameterbar->pos.y = player->pos.y + (float)PARAMETERBAR_DRAW_MP;
				if (!player->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			case 2:
				enemy = GetEnemy(parameterbar->nTarget);
				if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
				{
					parameterbar->pos.x = enemy->pos.x;
					parameterbar->pos.y = enemy->pos.y + (float)PARAMETERBAR_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_BOSS)
				{
					parameterbar->vecChangeSize.x = TEXTURE_CHANGE_BOSS_PARAMETERBAR_X;
					parameterbar->vecChangeSize.y = TEXTURE_CHANGE_BOSS_PARAMETERBAR_Y;
					parameterbar->pos.x = BOSS_PARAMETERBAR_POS_X;
					parameterbar->pos.y = BOSS_PARAMETERBAR_POS_Y;
				}
				if (!enemy->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			}

			// テクスチャ座標を設定
			SetTextureParameterbar(i, parameterbar->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexParameterbar(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParameterbar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (parameterbar->bUse)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, parameterbar->Texture);

			// パラメータの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PARAMETERBAR, parameterbar->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexParameterbar(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	// 頂点座標の設定
	parameterbar->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	parameterbar->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETERBAR00_SIZE_X, 100.0f, 0.0f);
	parameterbar->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PARAMETERBAR00_SIZE_Y, 0.0f);
	parameterbar->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETERBAR00_SIZE_X, 100.0f+TEXTURE_PARAMETERBAR00_SIZE_Y, 0.0f);

	// rhwの設定
	parameterbar->vertexWk[0].rhw =
	parameterbar->vertexWk[1].rhw =
	parameterbar->vertexWk[2].rhw =
	parameterbar->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	parameterbar->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	parameterbar->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	parameterbar->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR, 0.0f );
	parameterbar->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR );
	parameterbar->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureParameterbar( int no, int cntPattern )
{
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR;
	parameterbar->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	parameterbar->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	parameterbar->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	parameterbar->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexParameterbar(int no)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	parameterbar->vertexWk[0].vtx.x = parameterbar->pos.x - TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[0].vtx.y = parameterbar->pos.y - TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[0].vtx.z = 0.0f;

	parameterbar->vertexWk[1].vtx.x = parameterbar->pos.x + TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[1].vtx.y = parameterbar->pos.y - TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[1].vtx.z = 0.0f;

	parameterbar->vertexWk[2].vtx.x = parameterbar->pos.x - TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[2].vtx.y = parameterbar->pos.y + TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[2].vtx.z = 0.0f;

	parameterbar->vertexWk[3].vtx.x = parameterbar->pos.x + TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[3].vtx.y = parameterbar->pos.y + TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// パラメータのセット
//=============================================================================
void SetParameterbar(int nType, D3DXVECTOR3 vecTargetPos, int nTarget)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// 未使用のパラメーターを探す
	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (!parameterbar->bUse)
		{
			// パラメータを有効にする
			parameterbar->bUse = true;
			// パラメータタイプを設定
			parameterbar->nType = nType;
			// パラメータ設置対象を記憶
			parameterbar->vecTargetPos = vecTargetPos;
			// パラメータターゲットを設定
			parameterbar->nTarget = nTarget;
			return;
		}
	}
}

//=============================================================================
// バレットの再利用処理
//=============================================================================
void InitStatusParameterbar(int nParameterbar)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[nParameterbar];

	// パラメータステータスの初期化
	parameterbar->bUse = false;

	parameterbar->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameterbar->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameterbar->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	parameterbar->nCountAnim = 0;
	parameterbar->nPatternAnim = 0;
	parameterbar->nPointGauge = 0;
	parameterbar->nTarget = 0;
	parameterbar->nType = 0;

	return;
}

//=============================================================================
// パラメータ取得関数
//=============================================================================
PARAMETERBAR *GetParameterbar(int no)
{
	return(&parameterbarWk[no]);
}

