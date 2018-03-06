//=============================================================================
//
// エネミーバレット処理 [enemybullet.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
//#include "main.h"
#include "enemy.h"
#include "enemybullet.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemybullet(int no);
void SetTextureEnemybullet( int no, int cntPattern );
void SetVertexEnemybullet(int no);

void SetSearchPlayer(int nBullet);
void SetEnemyBulletType(int nBullet);
void SetEnemyBulletSpeedChange(int nBullet, int nBulletType);

void SetEnemyBulletType00(int nBullet);
void SetEnemyBulletType01(int nBullet);
void SetEnemyBulletType02(int nBullet);
void SetEnemyBulletType03(int nBullet);
void SetEnemyBulletType04(int nBullet);
void SetEnemyBulletType05(int nBullet);
void SetEnemyBulletType06(int nBullet);
void SetEnemyBulletType07(int nBullet);
void SetEnemyBulletType08(int nBullet);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMYBULLET				enemybulletWk[ENEMYBULLET_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureEnemybullet = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemybullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_ENEMYBULLET,				// ファイルの名前
			&pD3DTextureEnemybullet);			// 読み込むメモリのポインタ
	}

	// エネミーバレットの初期化
	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		enemybullet->Texture = pD3DTextureEnemybullet;			// テクスチャへのエネミーバレット
		enemybullet->size = D3DXVECTOR2(ENEMYBULLET_CUSTOM_SIZE_NORMAL_X, ENEMYBULLET_CUSTOM_SIZE_NORMAL_Y);

		enemybullet->fBaseAngle = 0.0f;
		enemybullet->fRadius = 0.0f;

		InitStatusEnemyBullet(i);
		// 頂点情報の作成
		MakeVertexEnemybullet(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemybullet(void)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];
	// メモリ解放
	if (pD3DTextureEnemybullet != NULL)
	{
		pD3DTextureEnemybullet->Release();
		pD3DTextureEnemybullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemybullet(void)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (enemybullet->bUse == true)
		{
			// テクスチャを設定
			if (enemybullet->bTextureUse == false)
			{
				enemybullet->nPatternAnim = enemybullet->nBulletTexture;
				enemybullet->bTextureUse = true;
			}

			SetEnemyBulletType(i);

			// フィールド外で未使用化（画面外弾道調整）
			if (enemybullet->pos.y < 0 - (TEXTURE_ENEMYBULLET_SIZE_Y + SCREEN_MARGIN_BULLET)
				|| enemybullet->pos.y > SCREEN_HEIGHT + (TEXTURE_ENEMYBULLET_SIZE_Y + SCREEN_MARGIN_BULLET)
				|| enemybullet->pos.x < 0 - (TEXTURE_ENEMYBULLET_SIZE_X + SCREEN_MARGIN)
				|| enemybullet->pos.x > SCREEN_WIDTH + (TEXTURE_ENEMYBULLET_SIZE_X + SCREEN_MARGIN_BULLET) )
			{
				InitStatusEnemyBullet(i);
			}
			
			// テクスチャ座標を設定
			SetTextureEnemybullet(i, enemybullet->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexEnemybullet(i);
			// 回転処理
			enemybullet->rot.z = enemybullet->fAngle;

			enemybullet->nBulletTime++;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemybullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (enemybullet->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, enemybullet->Texture);

			// エネミーバレットの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET, enemybullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemybullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[no];

	// 角度と半径を求める
	enemybullet->fBaseAngle = atan2f(TEXTURE_ENEMYBULLET_SIZE_Y, TEXTURE_ENEMYBULLET_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMYBULLET_SIZE_X, TEXTURE_ENEMYBULLET_SIZE_Y);
	enemybullet->fRadius = D3DXVec2Length(&temp);

	// 頂点座標の設定
	enemybullet->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	enemybullet->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMYBULLET_SIZE_X, 100.0f, 0.0f);
	enemybullet->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_ENEMYBULLET_SIZE_Y, 0.0f);
	enemybullet->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMYBULLET_SIZE_X, 100.0f+TEXTURE_ENEMYBULLET_SIZE_Y, 0.0f);
	//SetVertexEnemybullet();

	// rhwの設定
	enemybullet->vertexWk[0].rhw =
	enemybullet->vertexWk[1].rhw =
	enemybullet->vertexWk[2].rhw =
	enemybullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemybullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemybullet->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	enemybullet->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 0.0f );
	enemybullet->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET );
	enemybullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemybullet( int no, int cntPattern )
{
	ENEMYBULLET *enemybullet = &enemybulletWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET;
	enemybullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemybullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemybullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemybullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexEnemybullet(int no)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[no];
	// 頂点0:回転あり
	enemybullet->vertexWk[0].vtx.x = enemybullet->pos.x - cosf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[0].vtx.y = enemybullet->pos.y - sinf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[0].vtx.z = 0.0f;

	// 頂点1:回転あり
	enemybullet->vertexWk[1].vtx.x = enemybullet->pos.x + cosf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[1].vtx.y = enemybullet->pos.y - sinf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[1].vtx.z = 0.0f;

	// 頂点2:回転あり
	enemybullet->vertexWk[2].vtx.x = enemybullet->pos.x - cosf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[2].vtx.y = enemybullet->pos.y + sinf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[2].vtx.z = 0.0f;

	// 頂点3:回転あり
	enemybullet->vertexWk[3].vtx.x = enemybullet->pos.x + cosf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[3].vtx.y = enemybullet->pos.y + sinf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// エネミーバレットパターン
//=============================================================================
void SetEnemyBulletType(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];

	switch (enemybullet->nBulletType)
	{
	case 0:
		SetEnemyBulletType00(nBullet);
		break;
	case 1:
		SetEnemyBulletType01(nBullet);
		break;
	case 2:
		SetEnemyBulletType02(nBullet);
		break;
	case 3:
		SetEnemyBulletType03(nBullet);
		break;
	case 4:
		SetEnemyBulletType04(nBullet);
		break;
	case 5:
		SetEnemyBulletType05(nBullet);
		break;
	case 6:
		SetEnemyBulletType06(nBullet);
		break;
	case 7:
		SetEnemyBulletType07(nBullet);
		break;
	case 8:
		SetEnemyBulletType08(nBullet);
		break;
	}
}

//=============================================================================
// エネミーバレットをエネミーに設置
//=============================================================================
void SetEnemybullet(int nEnemy, int nBulletSplit)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];
	ENEMY *enemy = GetEnemy(nEnemy);

	int nEnemyBulletWay = enemy->nBulletSplit[BTYPE00];
	int nEnemyBulletSplit05 = enemy->nBulletSplit[BTYPE05];
	int nEnemyBulletSplit06 = enemy->nBulletSplit[BTYPE06];
	int nEnemyBulletSplit07 = enemy->nBulletSplit[BTYPE07];
	int nEnemyBulletSplit08 = enemy->nBulletSplit[BTYPE08];

	// 未使用の弾を探す
	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (!enemybullet->bUse)
		{
			SetSe(6, E_DS8_FLAG_NONE, false);
			// セットするエネミーを記憶
			enemybullet->nSetEnemy = nEnemy;
			// posを自分にセット
			enemybullet->pos = enemy->pos;
			// バレットタイプをセット
			enemybullet->nBulletType = enemy->nBulletType;
			// バレットテクスチャーをセット
			enemybullet->nBulletTexture = enemy->nBulletTexture[enemy->nBulletType];

			if (enemybullet->nBulletTexture >= ENEMYBULLET_SIZE_SMALL_NUM)
			{
				enemybullet->size = D3DXVECTOR2(ENEMYBULLET_CUSTOM_SIZE_SMALL_X, ENEMYBULLET_CUSTOM_SIZE_SMALL_Y);
			}

			// 未使用の弾があったら使用に変更
			enemybullet->bUse = true;
			// ターゲット座標を設定
			enemybullet->vecTargetPos = enemy->vecTargetPos;
			// 総発射数をカウント
			switch(enemy->nBulletType)
			{
			case 0:
				// ホーミングパターン設置
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % nBulletSplit;
				if (nEnemyBulletWay == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletWay--;
				}
				enemy->nBulletCount[BTYPE00]++;
				break;
			case 1:
				enemy->nBulletCount[BTYPE01]++;
				return;
				break;
			case 2:
				enemy->nBulletCount[BTYPE02]++;
				return;
				break;
			case 3:
				enemy->nBulletCount[BTYPE03]++;
				return;
				break;
			case 4:
				enemy->nBulletCount[BTYPE04]++;
				return;
				break;
			case 5:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit05 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit05--;
				}
				enemy->nBulletCount[BTYPE05]++;
				break;
			case 6:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit06 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit06--;
				}
				enemy->nBulletCount[BTYPE06]++;
				break;
			case 7:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit07 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit07--;
				}
				enemy->nBulletCount[BTYPE07]++;
				break;
			case 8:
				enemybullet->vecOldEnemyPos = enemy->pos;
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit08 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit08--;
				}
				enemy->nBulletCount[BTYPE08]++;
				break;
			}
		}
	}
}

//=============================================================================
// エネミーバレットの速度変更
//=============================================================================
void SetEnemyBulletSpeedChange(int nBullet, int nBulletType)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);

	// 速度変更
	if (enemybullet->nBulletTime >= ENEMYBULLET_SPEEDCHANGE_TIME)
	{
		switch (enemy->nBulletSpeedChange[nBulletType])
		{
		case 1:
			enemybullet->fMoveChange += ENEMYBULLET_SPEED_CHANGE;
			if (enemybullet->fMoveChange >= ENEMYBULLET_SPEED_CHANGE_MAX)
			{
				enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHANGE_MAX;
			}
			break;
		case 2:
			enemybullet->fMoveChange -= ENEMYBULLET_SPEED_CHANGE;
			if (enemybullet->fMoveChange <= ENEMYBULLET_SPEED_CHANGE_MIN)
			{
				enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHANGE_MIN;
			}
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// エネミーバレットパターン00 ノーマル 1～7WAY
//=============================================================================
void SetEnemyBulletType00(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE00);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		// 射角変更
		switch(enemybullet->nPatternHoming)
		{
		case 0:
			enemybullet->fAngle += 0.0f;
			break;
		case 1:
			enemybullet->fAngle += 0.2f;
			break;
		case 2:
			enemybullet->fAngle -= 0.2f;
			break;
		case 3:
			enemybullet->fAngle += 0.4f;
			break;
		case 4:
			enemybullet->fAngle -= 0.4f;
			break;
		case 5:
			enemybullet->fAngle += 0.6f;
			break;
		case 6:
			enemybullet->fAngle -= 0.6f;
			break;
		}


		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE00];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE00];
	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン01 360度 時計回り
//=============================================================================
void SetEnemyBulletType01(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE01);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE01])
			* (enemy->nBulletCount[BTYPE01] % enemy->nBulletSplit[BTYPE01]);

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE01];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE01];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン02 360度 反時計回り
//=============================================================================
void SetEnemyBulletType02(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE02);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle -= ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE02])
			* (enemy->nBulletCount[BTYPE02] % enemy->nBulletSplit[BTYPE02]);

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE02];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE02];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン03 360度 時計回り 角度変化あり
//=============================================================================
void SetEnemyBulletType03(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE03);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;
		player = GetPlayer(enemybullet->nTarget);

		enemybullet->vecTa.x = enemybullet->pos.x - 1;
		enemybullet->vecTa.y = enemybullet->pos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE03])
			*(enemy->nBulletCount[BTYPE03] % enemy->nBulletSplit[BTYPE03]))
			+ (enemy->nBulletShiftAngle*ENEMYBULLET_SHIFT03);

		if (enemy->nBulletCount[BTYPE03] % enemy->nBulletSplit[BTYPE03] == 0)
		{
			enemy->nBulletShiftAngle++;
		}

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE03];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE03];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン04 360度 反時計回り 角度変化あり
//=============================================================================
void SetEnemyBulletType04(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE04);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - 1;
		enemybullet->vecTa.y = enemybullet->pos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle -= (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE04])
			*(enemy->nBulletCount[BTYPE04] % enemy->nBulletSplit[BTYPE04]))
			+ (enemy->nBulletShiftAngle*ENEMYBULLET_SHIFT04);

		if (enemy->nBulletCount[BTYPE04] % enemy->nBulletSplit[BTYPE04] == 0)
		{
			enemy->nBulletShiftAngle++;
		}

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE04];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE04];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン05 360度 同時展開
//=============================================================================
void SetEnemyBulletType05(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE05);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE05]) * enemybullet->nPatternHoming;

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE05];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE05];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン06 360度 同時展開 角度変化あり
//=============================================================================
void SetEnemyBulletType06(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE06);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		enemybullet->fAngle += (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE06]) * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE06]);

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE06];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE06];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン07 360度 逆同時展開 角度変化あり
//=============================================================================
void SetEnemyBulletType07(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE07);

	// プレイヤー検索
	SetSearchPlayer(nBullet);

	// ホーミング処理
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2のエラー防止
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// 角度計算
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		enemybullet->fAngle -= (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE07]) * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE07]);

		// 360度を超えたら360度を引く
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// 移動量計算
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE07];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE07];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// 移動量適用
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// エネミーバレットパターン08 360度 回転バレット
//=============================================================================
void SetEnemyBulletType08(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);

	// 速度変更
	SetEnemyBulletSpeedChange(nBullet, BTYPE08);

	if (enemybullet->nHomingFlag == 0)
	{
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE08] * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE08]);
		enemybullet->nHomingFlag = 1;
	}

	enemybullet->fAngle -= enemy->nBulletOption[BTYPE08];

	// 360度を超えたら360度を引く
	if (enemybullet->fAngle >= D3DX_PI * 2.0f)
	{
		enemybullet->fAngle -= D3DX_PI * 2.0f;
	}

	enemybullet->fDistance += enemy->nBulletSpeed[BTYPE08] * enemybullet->fMoveChange;

	// 移動量適用
	enemybullet->pos.x = enemybullet->vecOldEnemyPos.x + (cos(enemybullet->fAngle) * enemybullet->fDistance);
	enemybullet->pos.y = enemybullet->vecOldEnemyPos.y + (sin(enemybullet->fAngle) * enemybullet->fDistance);
}

//=============================================================================
// バレットのプレイヤー検索
//=============================================================================
void SetSearchPlayer(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy;
	PLAYER *player;

	// プレイヤー検索
	enemy = GetEnemy(0);
	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	{
		if (enemy->bUse)
		{
			if (enemybullet->nHomingFlag == 0)
			{
				player = GetPlayer(0);
				float fDistanceMin = 0.0f;
				for (int k = 0; k < PLAYER_MAX; k++, player++)
				{
					// 距離計算
					D3DXVECTOR3 temp = player->pos - enemy->pos;
					float fTempLengthSq = D3DXVec3LengthSq(&temp);

					// 最小距離算出
					if (fTempLengthSq < fDistanceMin || fDistanceMin == 0.0f)
					{
						fDistanceMin = fTempLengthSq;
						enemybullet->nTarget = k;
					}
					enemybullet->nHomingFlag = 1;
				}
			}
		}
	}
	return;
}

//=============================================================================
// バレットの再利用処理
//=============================================================================
void InitStatusEnemyBullet(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];

	// エネミーバレットステータスの初期化
	enemybullet->bUse = false;
	enemybullet->bTextureUse = false;
	enemybullet->bPatternHomingFlag = false;

	enemybullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
	enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecOldEnemyPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	enemybullet->nCountAnim = 0;
	enemybullet->nPatternAnim = 0;
	enemybullet->nPatternHoming = 0;
	enemybullet->nHomingFlag = 0;
	enemybullet->nTarget = 0;
	enemybullet->nBulletType = 0;
	enemybullet->nBulletTexture = 0;
	enemybullet->nBulletWay = 0;
	enemybullet->nBulletTime = 0;
	enemybullet->nSetEnemy = 0;
	enemybullet->nDirection = 0;

	enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHENGE_DEFAULT;
	enemybullet->fDistance = 0.0f;
	enemybullet->fAngle = 0.0f;
	return;
}

//=============================================================================
// エネミーバレット取得関数
//=============================================================================
ENEMYBULLET *GetEnemybullet(int no)
{
	return(&enemybulletWk[no]);
}
