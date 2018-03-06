
//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
//#include "main.h"
#include "enemy.h"
#include "enemybullet.h"
#include "input.h"
#include "parameter.h"
#include "close.h"
#include "player.h"
#include "game.h"
#include "sound.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy(int no);
void SetMoveEnemy(int nEnemy, int nMoveType);
void SetMovePosEnemy(int nEnemy, float fPosX, float fPosY);
void SetMoveStopEnemy(int nEnemy);
void SetMoveStopPosEnemy(int nEnemy);

void SetBulletTypeEnemy(int nEnemy);
void SetBulletTypeBossEnemy(int nEnemy);
void SetBulletTypeEnemy00(int nEnemy);
void SetBulletTypeEnemy01(int nEnemy);
void SetBulletTypeEnemy02(int nEnemy);
void SetBulletTypeEnemy03(int nEnemy);
void SetBulletTypeEnemy04(int nEnemy);
void SetBulletTypeEnemy05(int nEnemy);
void SetBulletTypeEnemy06(int nEnemy);
void SetBulletTypeEnemy07(int nEnemy);
void SetBulletTypeEnemy08(int nEnemy);

void SetMoveTypeEnemy(int nEnemy, int nMoveType);
void SetMoveCalculationEnemy(int nEnemy);

void SetMovePatternEnemy00(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy01(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy02(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy03(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy04(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy05(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy06(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy07(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy08(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy09(int nEnemy, int nMoveFlag);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY					enemyWk[ENEMY_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEnemy = NULL;

int g_nEnemyCount;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY00,			// ファイルの名前
			&pD3DTextureEnemy);				// 読み込むメモリのポインタ
	}

	// エネミーの初期化
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->Texture = pD3DTextureEnemy;			// テクスチャへのエネミー
		enemy->size = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X, TEXTURE_ENEMY00_SIZE_Y);

		// 各ステータスの初期化
		InitStatusEnemy(i);

		// 頂点情報の作成
		MakeVertexEnemy(i);
	}

	g_nEnemyCount = 1;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	// メモリ解放
	if (pD3DTextureEnemy != NULL)
	{
		pD3DTextureEnemy->Release();
		pD3DTextureEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	CLOSE *close = GetClose(0);
	int *count = GetCount();

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// クールダウン（ホーミングバレットの再追尾防止）
		if (enemy->nCoolDown > 0)
		{
			enemy->nCoolDown--;
			if (enemy->nCoolDown <= 0)
			{
				enemy->nCoolDown = 0;
			}
		}

		// ファイル取り込み用（運用中止）
		//if (enemy->nPopCount == *count && *count > 0)
		//{
		//	enemy->bUse = true;
		//}

		if (enemy->bUse)
		{
			// アニメーション
			enemy->nCountAnim++;
			if ((enemy->nCountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// パターンの切り替え
				enemy->nPatternAnim = (enemy->nPatternAnim + 1) % TEXTURE_PATTERN_DIVIDE_X_ENEMY + (TEXTURE_PATTERN_DIVIDE_X_ENEMY * enemy->nType);

			}

			// HP・MPゲージの設定
			if (!enemy->bParameterUse)
			{
				SetParameter(2, enemy->pos, i);
				enemy->bParameterUse = true;
			}

			// 移動処理
			SetMoveEnemy(i,enemy->nMoveType);

			if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
			{
				// ショット処理
				SetBulletTypeEnemy(i);
			}
			else if (enemy->nSpec == ENEMY_BOSS)
			{
				if (!close->bUse && enemy->bBossReversal)
				{
					SetBgmVol(2, true);
				}
				// ショット処理
				SetBulletTypeBossEnemy(i);
			}

			// 回転処理
			enemy->rot.z += ENEMY_ROTATION;
			if (enemy->rot.z >= D3DX_PI * 2.0f)
			{
				// 360度を超えたら360度を引く
				enemy->rot.z -= D3DX_PI * 2.0f;
			}

			// テクスチャ座標を設定
			SetTextureEnemy(i, enemy->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEnemy(i);
			enemy->nActionCount++;
		}
	}
	if (g_nEnemyCount == 0)
	{
		close->bUse = true;
		close->bClearFlag = true;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, enemy->Texture);

			// エネミーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];

	// 角度を求める
	enemy->fBaseAngle = atan2f(TEXTURE_ENEMY00_SIZE_Y, TEXTURE_ENEMY00_SIZE_X);

	// 半径を求める
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X, TEXTURE_ENEMY00_SIZE_Y);
	enemy->fRadius = D3DXVec2Length(&temp);

	// 頂点座標の設定
	enemy->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	enemy->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMY00_SIZE_X, 100.0f, 0.0f);
	enemy->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_ENEMY00_SIZE_Y, 0.0f);
	enemy->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMY00_SIZE_X, 100.0f+TEXTURE_ENEMY00_SIZE_Y, 0.0f);

	// rhwの設定
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	enemy->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f );
	enemy->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy( int no, int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	//// 頂点0:回転あり
	//enemy->vertexWk[0].vtx.x = (enemy->pos.x - cosf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[0].vtx.y = (enemy->pos.y - sinf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[0].vtx.z = 0.0f;

	//// 頂点1:回転あり
	//enemy->vertexWk[1].vtx.x = (enemy->pos.x + cosf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[1].vtx.y = (enemy->pos.y - sinf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[1].vtx.z = 0.0f;

	//// 頂点2:回転あり
	//enemy->vertexWk[2].vtx.x = (enemy->pos.x - cosf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[2].vtx.y = (enemy->pos.y + sinf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[2].vtx.z = 0.0f;

	//// 頂点3:回転あり
	//enemy->vertexWk[3].vtx.x = (enemy->pos.x + cosf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[3].vtx.y = (enemy->pos.y + sinf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[3].vtx.z = 0.0f;

	enemy->vertexWk[0].vtx.x = enemy->pos.x - (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[0].vtx.y = enemy->pos.y - (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[1].vtx.y = enemy->pos.y - (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[2].vtx.y = enemy->pos.y + (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[3].vtx.y = enemy->pos.y + (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミーショットタイプ
//=============================================================================
void SetBulletTypeEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (enemy->nBulletType)
	{
	case 0:
		SetBulletTypeEnemy00(nEnemy);
		break;
	case 1:
		SetBulletTypeEnemy01(nEnemy);
		break;
	case 2:
		SetBulletTypeEnemy02(nEnemy);
		break;
	case 3:
		SetBulletTypeEnemy03(nEnemy);
		break;
	case 4:
		SetBulletTypeEnemy04(nEnemy);
		break;
	case 5:
		SetBulletTypeEnemy05(nEnemy);
		break;
	case 6:
		SetBulletTypeEnemy06(nEnemy);
		break;
	case 7:
		SetBulletTypeEnemy07(nEnemy);
		break;
	case 8:
		SetBulletTypeEnemy08(nEnemy);
		break;
	}

	enemy->nBulletTime[enemy->nBulletType]--;
	if (enemy->nBulletTime[enemy->nBulletType] <= 0)
	{
		enemy->nBulletTime[enemy->nBulletType] = 0;
	}
}

//=============================================================================
// ボスエネミーショットタイプ
//=============================================================================
void SetBulletTypeBossEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->nBulletType = BTYPE00;
	SetBulletTypeEnemy00(nEnemy);

	enemy->nBulletType = BTYPE01;
	SetBulletTypeEnemy01(nEnemy);

	enemy->nBulletType = BTYPE02;
	SetBulletTypeEnemy02(nEnemy);

	enemy->nBulletType = BTYPE03;
	SetBulletTypeEnemy03(nEnemy);

	enemy->nBulletType = BTYPE04;
	SetBulletTypeEnemy04(nEnemy);

	enemy->nBulletType = BTYPE05;
	SetBulletTypeEnemy05(nEnemy);

	enemy->nBulletType = BTYPE06;
	SetBulletTypeEnemy06(nEnemy);

	enemy->nBulletType = BTYPE07;
	SetBulletTypeEnemy07(nEnemy);

	enemy->nBulletType = BTYPE08;
	SetBulletTypeEnemy07(nEnemy);

	for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
	{
		enemy->nBulletTime[i]--;
		if (enemy->nBulletTime[i] <= 0)
		{
			enemy->nBulletTime[i] = 0;
		}
	}
}

//=============================================================================
// エネミーショットタイプ00
//=============================================================================
void SetBulletTypeEnemy00(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
	}
}

//=============================================================================
// エネミーショットタイプ01
//=============================================================================
void SetBulletTypeEnemy01(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// エネミーショットタイプ02
//=============================================================================
void SetBulletTypeEnemy02(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// エネミーショットタイプ03
//=============================================================================
void SetBulletTypeEnemy03(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// エネミーショットタイプ04
//=============================================================================
void SetBulletTypeEnemy04(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// エネミーショットタイプ05
//=============================================================================
void SetBulletTypeEnemy05(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// エネミーショットタイプ06
//=============================================================================
void SetBulletTypeEnemy06(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// エネミーショットタイプ07
//=============================================================================
void SetBulletTypeEnemy07(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// エネミーショットタイプ08
//=============================================================================
void SetBulletTypeEnemy08(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// エネミーの設定処理（不具合のため運用中止）
//=============================================================================
void SetEnemyLevel(int nLevel)
{
	//ENEMY *enemy = &enemyWk[0];

	//FILE *fp;
	//char *fname;
	//int data[FILE_DATA_MAX];

	//// レベルに応じたファイルを選択
	//switch (nLevel)
	//{
	//case EASY:
	//	fname = FILE_ENEMY_EASY;
	//	break;
	//case NORMAL:
	//	fname = FILE_ENEMY_NORMAL;
	//	break;
	//case HARD:
	//	fname = FILE_ENEMY_HARD;
	//	break;
	//}

	//// ファイルオープンエラー処理
	//fp = fopen(fname, "r");
	//if (fp == NULL) {
	//	return;
	//}

	//// エネミーステータス設定
	//while (fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11]) != EOF)
	//{
	//	if (data[0] <= 0)
	//	{
	//		break;
	//	}
	//	enemy->nPopCount = data[0];
	//	enemy->nType = data[1];
	//	if (data[1] >= TYPE_S_WH)
	//	{
	//		enemy->nSpec = ENEMY_STRONG;
	//		enemy->fHitPoint = STRONG_ENEMY_HPMAX;
	//	}
	//	enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, data[2] * ENEMY_POP_POS_X + (ENEMY_POP_POS_X / 2), 0.0f);
	//	enemy->nMoveType = data[3];
	//	enemy->nBulletType = data[4];					// バレットタイプを設定
	//	enemy->nBulletTexture[data[1]] = data[5];		// バレットテクスチャーを設定
	//	enemy->nBulletSpeed[data[1]] = data[6];			// バレットのスピードを設定
	//	enemy->nBulletSetTime[data[1]] = data[7];		// バレットの発射時間を設定
	//	enemy->nBulletAction[data[1]] = data[8];		// バレットの連射速度を設定
	//	enemy->nBulletSplit[data[1]] = data[9];			// バレットの射角分割を設定
	//	enemy->nBulletSpeedChange[data[1]] = data[10];	// バレットのスピードチェンジを設定
	//	enemy->nBulletOption[data[1]] = data[11];		// バレットのオプションを設定
	//	enemy++;
	//}

	//fclose(fp);
}


//=============================================================================
// エネミーの出現処理
//=============================================================================
void SetEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption)
{
	ENEMY *enemy = &enemyWk[0];

	// 未使用のエネミーを探す
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (!enemy->bUse && enemy->nCoolDown == 0)
		{
			// エネミーを有効にする
			enemy->bUse = true;
			// エネミーの初期テクスチャを設定
			enemy->nPatternAnim = TEXTURE_PATTERN_DIVIDE_X_ENEMY * nType;
			// エネミーのタイプを設定
			enemy->nType = nType;
			if (nType >= TYPE_S_WH)
			{
				enemy->nSpec = ENEMY_STRONG;
				enemy->fHitPoint = STRONG_ENEMY_HPMAX;
			}

			// 出現座標・移動・離脱の設定
			enemy->nMoveType = nMoveType;
			// 出現座標の設定
			enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, nPopType*ENEMY_POP_POS_X + (ENEMY_POP_POS_X/2), 0.0f);
			// バレットタイプを設定
			enemy->nBulletType = nBulletType;
			// バレットテクスチャーを設定
			enemy->nBulletTexture[nBulletType] = nBulletTexture;
			// バレットのスピードを設定
			enemy->nBulletSpeed[nBulletType] = nBulletSpeed;
			// バレットの発射時間を設定
			enemy->nBulletSetTime[nBulletType] = nBulletSetTime;
			// バレットの連射速度を設定
			enemy->nBulletAction[nBulletType] = nBulletAction;
			// バレットの射角分割を設定
			enemy->nBulletSplit[nBulletType] = nBulletSplit;
			// バレットのスピードチェンジを設定
			enemy->nBulletSpeedChange[nBulletType] = nBulletSpeedChange;
			// バレットのオプションを設定
			enemy->nBulletOption[nBulletType] = nBulletOption;

			return;
		}
	}
}

//=============================================================================
// ボスエネミーの出現処理
//=============================================================================
void SetBossEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption)
{
	ENEMY *enemy = &enemyWk[0];

	// 未使用のエネミーを探す
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (!enemy->bUse && enemy->nCoolDown == 0)
		{
			// エネミーを有効にする
			enemy->bUse = true;
			// エネミーの初期テクスチャを設定
			enemy->nPatternAnim = TEXTURE_PATTERN_DIVIDE_X_ENEMY * nType;
			// エネミーのタイプを設定
			enemy->nType = nType;
			// 出現座標・移動・離脱の設定
			enemy->nMoveType = nMoveType;
			// 出現座標の設定
			enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, nPopType*ENEMY_POP_POS_X + (ENEMY_POP_POS_X / 2), 0.0f);
			// バレットタイプを設定
			enemy->nBulletType = nBulletType;

			// ボスバレットのステータス設定
			SetGameLevelBossSpec(i);
			// ボスフラグを設定
			enemy->nSpec = ENEMY_BOSS;
			// ボスHPを設定
			enemy->fHitPoint = BOSS_ENEMY_HPMAX;
			// ボス用サイズ変更
			enemy->size = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X*TEXTURE_CHANGE_BOSS_ENEMY_X, TEXTURE_ENEMY00_SIZE_Y*TEXTURE_CHANGE_BOSS_ENEMY_Y);
			// 頂点座標変更
			enemy->vecChangeSize = D3DXVECTOR2(TEXTURE_CHANGE_BOSS_ENEMY_X, TEXTURE_CHANGE_BOSS_ENEMY_Y);
			return;
		}
	}
}

//=============================================================================
// エネミーの再利用処理
//=============================================================================
void InitStatusEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// エネミーステータスの初期化
	enemy->bUse = false;
	enemy->bCalculation = false;
	enemy->bParameterUse = false;
	enemy->bBossReversal = false;

	enemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecChangeSize = D3DXVECTOR2((float)TEXTURE_CHANGE_ENEMY_X, (float)TEXTURE_CHANGE_ENEMY_Y);

	for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
	{
		enemy->bBulletStandby[i] = false;
		enemy->bBulletFlag[i] = false;
		enemy->nBulletTexture[i] = 0;
		enemy->nBulletCount[i] = 0;
		enemy->nBulletSpeed[i] = 0;
		enemy->nBulletSetTime[i] = 0;
		enemy->nBulletTime[i] = 0;
		enemy->nBulletAction[i] = 0;
		enemy->nBulletSplit[i] = 0;
		enemy->nBulletSpeedChange[i] = 0;
		enemy->nBulletOption[i] = 0;
	}

	enemy->nCountAnim = 0;
	enemy->nPatternAnim = 0;
	enemy->nType = 0;
	enemy->nMoveType = 0;
	enemy->nBulletType = 0;
	enemy->nBulletPattern = 0;
	enemy->nBulletShiftAngle = 0;

	enemy->nBulletTime[enemy->nBulletType] = 0;
	enemy->nMoveCount = 0;
	enemy->nMoveFlag = 0;
	enemy->nStopFlag = 0;
	enemy->nActionCount = 0;
	enemy->nActionFlag = 0;
	enemy->nCoolDown = ENEMY_COOLDOWN;
	enemy->nSpec = ENEMY_NORMAL;
	enemy->nPopCount = 0;

	enemy->fHitPoint = ENEMY_HPMAX;
	enemy->fAngle = 0.0f;
	return;
}

//=============================================================================
// エネミーの移動処理
//=============================================================================
void SetMoveEnemy(int nEnemy, int nMoveType)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// 移動処理
	if (enemy->nActionCount % ENEMY_ACTION == 0)
	{
		SetMoveTypeEnemy(nEnemy, nMoveType);
	}

	// 移動量計算
	if (enemy->bCalculation)
	{
		SetMoveCalculationEnemy(nEnemy);
	}

	// 移動停止処理
	SetMoveStopEnemy(nEnemy);

	// 移動量適用
	enemy->pos.x += enemy->vecMove.x;
	enemy->pos.y += enemy->vecMove.y;

	return;
}

//=============================================================================
// エネミーの移動タイプ設定
//=============================================================================
void SetMoveTypeEnemy(int nEnemy, int nMoveType)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// タイプに応じた移動処理
	switch (nMoveType)
	{
	case 0:
		SetMovePatternEnemy00(nEnemy, enemy->nMoveFlag);
		break;
	case 1:
		SetMovePatternEnemy01(nEnemy, enemy->nMoveFlag);
		break;
	case 2:
		SetMovePatternEnemy02(nEnemy, enemy->nMoveFlag);
		break;
	case 3:
		SetMovePatternEnemy03(nEnemy, enemy->nMoveFlag);
		break;
	case 4:
		SetMovePatternEnemy04(nEnemy, enemy->nMoveFlag);
		break;
	case 5:
		SetMovePatternEnemy05(nEnemy, enemy->nMoveFlag);
		break;
	case 6:
		SetMovePatternEnemy06(nEnemy, enemy->nMoveFlag);
		break;
	case 7:
		SetMovePatternEnemy07(nEnemy, enemy->nMoveFlag);
		break;
	case 8:
		SetMovePatternEnemy08(nEnemy, enemy->nMoveFlag);
		break;
	case 9:
		SetMovePatternEnemy09(nEnemy, enemy->nMoveFlag);
		break;
	}
	enemy->bCalculation = true;
	return;
}

//=============================================================================
// エネミーの移動パターン00
//=============================================================================
void SetMovePatternEnemy00(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, +100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, +300.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, +200.0f * SCREEN_SCALING, +100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}


//=============================================================================
// エネミーの移動パターン01
//=============================================================================
void SetMovePatternEnemy01(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, -100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, -300.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, +200.0f * SCREEN_SCALING, -100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン02
//=============================================================================
void SetMovePatternEnemy02(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン03
//=============================================================================
void SetMovePatternEnemy03(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン04
//=============================================================================
void SetMovePatternEnemy04(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, -400.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, -500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, -500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン05
//=============================================================================
void SetMovePatternEnemy05(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン06
//=============================================================================
void SetMovePatternEnemy06(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン07
//=============================================================================
void SetMovePatternEnemy07(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン08
//=============================================================================
void SetMovePatternEnemy08(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// エネミーの移動パターン09 ボス用
//=============================================================================
void SetMovePatternEnemy09(int nEnemy, int nMoveFlag)
{

	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 8:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 9:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 10:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 11:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 12:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 13:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 14:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 15:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 16:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 17:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 18:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 19:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 20:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 21:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 22:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 23:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 24:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 25:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	}

	SetGameBossAction(nEnemy, nMoveFlag);

	if (enemy->fHitPoint <= BOSS_ENEMY_HPMAX / 2 && !enemy->bBossReversal)
	{
		AddScore(100000000);
		enemy->nBulletSpeedChange[BTYPE00] = BSPD_UP;
		enemy->nBulletSpeedChange[BTYPE01] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE02] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE03] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE04] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE05] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE06] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE07] = BSPD_DOWN;
		SetSe(13, E_DS8_FLAG_NONE, CONTINUITY_OFF);
		enemy->bBossReversal = true;
	}
	return;
}

//=============================================================================
// エネミーの移動座標設定
//=============================================================================
void SetMovePosEnemy(int nEnemy, float fPosX, float fPosY)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecDestination.x = enemy->pos.x + fPosX;
	enemy->vecDestination.y = enemy->pos.y + fPosY;

	// 移動停止フラグ
	if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
	{
		enemy->nStopFlag = 0;
	}
	else if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
	{
		enemy->nStopFlag = 1;
	}
	else if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
	{
		enemy->nStopFlag = 2;
	}
	else if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
	{
		enemy->nStopFlag = 3;
	}
	enemy->nMoveFlag++;
	return;
}

//=============================================================================
// エネミーの移動座標設定
//=============================================================================
void SetMoveCalculationEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecTa.x = enemy->vecDestination.x - enemy->pos.x;
	enemy->vecTa.y = enemy->vecDestination.y - enemy->pos.y;

	// atan2のエラー防止
	if (enemy->vecTa.x == 0 && enemy->vecTa.y == 0)
	{
		enemy->vecTa.x += 0.00001;
	}

	// 角度計算
	enemy->fAngle = atan2(enemy->vecTa.y, enemy->vecTa.x);

	//// 射角変更
	//enemy->fAngle = -1.570;

	// 移動量計算
	enemy->vecMove.x = cos(enemy->fAngle) * ENEMY_MOVE_SPEED;
	enemy->vecMove.y = sin(enemy->fAngle) * ENEMY_MOVE_SPEED;
	enemy->bCalculation = false;
	return;
}

//=============================================================================
// エネミーの移動座標設定
//=============================================================================
void SetMoveStopEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// 指定座標到着で移動停止
	switch (enemy->nStopFlag)
	{
	case 0:		// 左上
		if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 1:		// 右上
		if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 2:		// 左下
		if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 3:		// 右下
		if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	}
	return;
}

//=============================================================================
// エネミーのストップ座標＋バレットフラグ
//=============================================================================
void SetMoveStopPosEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecMove.x = 0.0f;
	enemy->vecMove.y = 0.0f;
	if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
	{
		if (enemy->bBulletStandby[enemy->nBulletType])
		{
			enemy->bBulletFlag[enemy->nBulletType] = true;
			enemy->bBulletStandby[enemy->nBulletType] = false;
		}
	}
	else if (enemy->nSpec == ENEMY_BOSS)
	{
		for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
		{
			if (enemy->bBulletStandby[i])
			{
				enemy->bBulletFlag[i] = true;
				enemy->bBulletStandby[i] = false;
			}
		}
	}
}


//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

