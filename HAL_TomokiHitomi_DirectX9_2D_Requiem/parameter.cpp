//=============================================================================
//
// パラメータ処理 [parameter.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "parameter.h"
#include "parameterbar.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexParameter(int no);
void SetTextureParameter( int no, int cntPattern );	//
void SetVertexParameter(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PARAMETER					parameterWk[PARAMETER_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureParameter = NULL;
LPDIRECT3DTEXTURE9		pD3DTexturePlayermp = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitParameter(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_PARAMETER00,				// ファイルの名前
			&pD3DTextureParameter);			// 読み込むメモリのポインタ
	}

	// パラメータの初期化
	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		parameter->Texture = pD3DTextureParameter;			// テクスチャへのエネミー
		parameter->size = D3DXVECTOR2(TEXTURE_PARAMETER00_SIZE_X, TEXTURE_PARAMETER00_SIZE_Y);
		parameter->vecChangeSize = D3DXVECTOR3(TEXTURE_CHANGE_PARAMETER_X, TEXTURE_CHANGE_PARAMETER_Y, 0.0f);

		InitStatusParameter(i);

		// 頂点情報の作成
		MakeVertexParameter(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParameter(void)
{
	PARAMETER *parameter = &parameterWk[0];

	// メモリ解放
	if (pD3DTextureParameter != NULL)
	{
		pD3DTextureParameter->Release();
		pD3DTextureParameter = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParameter(void)
{
	PARAMETER *parameter = &parameterWk[0];
	PLAYER *player;
	ENEMY *enemy;

	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (parameter->bUse)
		{
			parameter->nPatternAnim = parameter->nType;
			switch (parameter->nType)
			{
			case 0:
				player = GetPlayer(parameter->nTarget);
				parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)PLAYER_HPMAX * player->fHitPoint;
				parameter->pos.x = player->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
				parameter->pos.y = player->pos.y + (float)PARAMETER_DRAW_HP;
				if (!player->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			case 1:
				player = GetPlayer(parameter->nTarget);
				parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)PLAYER_MANAMAX * player->fManaPoint;
				parameter->pos.x = player->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
				parameter->pos.y = player->pos.y + (float)PARAMETER_DRAW_MP;
				if (!player->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			case 2:
				enemy = GetEnemy(parameter->nTarget);
				if (enemy->nSpec == ENEMY_NORMAL)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)ENEMY_HPMAX * enemy->fHitPoint;
					parameter->pos.x = enemy->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
					parameter->pos.y = enemy->pos.y + (float)PARAMETER_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_STRONG)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)STRONG_ENEMY_HPMAX * enemy->fHitPoint;
					parameter->pos.x = enemy->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
					parameter->pos.y = enemy->pos.y + (float)PARAMETER_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_BOSS)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)BOSS_ENEMY_HPMAX * enemy->fHitPoint;
					parameter->vecChangeSize.x = TEXTURE_CHANGE_BOSS_PARAMETER_X;
					parameter->vecChangeSize.y = TEXTURE_CHANGE_BOSS_PARAMETER_Y;
					parameter->pos.x = BOSS_PARAMETER_POS_X - (float)TEXTURE_PARAMETER00_SIZE_X / 2 * TEXTURE_CHANGE_BOSS_PARAMETER_X;
					parameter->pos.y = BOSS_PARAMETER_POS_Y;
				}
				if (!enemy->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			}

			// テクスチャ座標を設定
			SetTextureParameter(i, parameter->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexParameter(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParameter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (parameter->bUse)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, parameter->Texture);

			// パラメータの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PARAMETER, parameter->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexParameter(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[no];

	// 頂点座標の設定
	parameter->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	parameter->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETER00_SIZE_X, 100.0f, 0.0f);
	parameter->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PARAMETER00_SIZE_Y, 0.0f);
	parameter->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETER00_SIZE_X, 100.0f+TEXTURE_PARAMETER00_SIZE_Y, 0.0f);

	// rhwの設定
	parameter->vertexWk[0].rhw =
	parameter->vertexWk[1].rhw =
	parameter->vertexWk[2].rhw =
	parameter->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	parameter->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	parameter->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	parameter->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETER, 0.0f );
	parameter->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETER );
	parameter->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETER );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureParameter( int no, int cntPattern )
{
	PARAMETER *parameter = &parameterWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PARAMETER;
	parameter->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	parameter->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	parameter->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	parameter->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexParameter(int no)
{
	PARAMETER *parameter = &parameterWk[no];

	parameter->vertexWk[0].vtx.x = parameter->pos.x;
	parameter->vertexWk[0].vtx.y = parameter->pos.y - TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[0].vtx.z = 0.0f;

	parameter->vertexWk[1].vtx.x = parameter->pos.x + parameter->nPointGauge * parameter->vecChangeSize.x;
	parameter->vertexWk[1].vtx.y = parameter->pos.y - TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[1].vtx.z = 0.0f;

	parameter->vertexWk[2].vtx.x = parameter->pos.x;
	parameter->vertexWk[2].vtx.y = parameter->pos.y + TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[2].vtx.z = 0.0f;

	parameter->vertexWk[3].vtx.x = parameter->pos.x + parameter->nPointGauge * parameter->vecChangeSize.x;
	parameter->vertexWk[3].vtx.y = parameter->pos.y + TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// パラメータのセット
//=============================================================================
void SetParameter(int nType, D3DXVECTOR3 vecTargetPos, int nTarget)
{
	PARAMETER *parameter = &parameterWk[0];

	// 未使用のパラメーターを探す
	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (!parameter->bUse)
		{
			// パラメータを有効にする
			parameter->bUse = true;
			// パラメータタイプを設定
			parameter->nType = nType;
			// パラメータ設置対象を記憶
			parameter->vecTargetPos = vecTargetPos;
			// パラメータターゲットを設定
			parameter->nTarget = nTarget;
			// パラメーターフレームを設定
			SetParameterbar(nType, vecTargetPos, nTarget);
			// テクスチャ座標を設定
			SetTextureParameter(i, parameter->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexParameter(i);
			return;
		}
	}
}

//=============================================================================
// 再利用処理
//=============================================================================
void InitStatusParameter(int nParameter)
{
	PARAMETER *parameter = &parameterWk[nParameter];

	// パラメータステータスの初期化
	parameter->bUse = false;

	parameter->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameter->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameter->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	parameter->nCountAnim = 0;
	parameter->nPatternAnim = 0;
	parameter->nPointGauge = 0;
	parameter->nTarget = 0;
	parameter->nType = 0;

	return;
}

//=============================================================================
// パラメータ取得関数
//=============================================================================
PARAMETER *GetParameter(int no)
{
	return(&parameterWk[no]);
}

