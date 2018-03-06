//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
//#include "main.h"
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetTextureBullet( int no, int cntPattern );
void SetVertexBullet(int no);

void SetSearchEnemy(int nBullet);

void SetBulletType(int nBullet);
void SetBulletType00(int nBullet);
void SetBulletType01(int nBullet);
void SetBulletType02(int nBullet);
void SetBulletType03(int nBullet);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
BULLET					bulletWk[BULLET_MAX];
int						g_nTotalBullet;					// バレット01の総発射数
int						g_nTotalBullet02;					// バレット01の総発射数

int						g_nReloadBullet00;
int						g_nReloadBullet;
int						g_nReloadBullet02;

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBullet = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];

	g_nTotalBullet = 0;
	g_nTotalBullet02 = 0;

	g_nReloadBullet00 = 0;
	g_nReloadBullet = 0;
	g_nReloadBullet02 = 0;

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BULLET,				// ファイルの名前
			&pD3DTextureBullet);			// 読み込むメモリのポインタ
	}

	// バレットの初期化
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->size = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
		bullet->Texture = pD3DTextureBullet;	// テクスチャへのバレット

		bullet->fBaseAngle = 0.0f;
		bullet->fRadius = 0.0f;

		// バレットステータスの初期化
		InitStatusBullet(i);

		// 頂点情報の作成
		MakeVertexBullet(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	BULLET *bullet = &bulletWk[0];
	// メモリ解放
	if (pD3DTextureBullet != NULL)
	{
		pD3DTextureBullet->Release();
		pD3DTextureBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	BULLET *bullet = &bulletWk[0];
	ENEMY *enemy;
	PLAYER *player;

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->bUse)
		{
			// テクスチャーをランダム設定
			if (bullet->bTextureUse == false)
			{
				bullet->nPatternAnim = (bullet->nBulletType * TEXTURE_PATTERN_DIVIDE_X_BULLET ) + (rand() % TEXTURE_PATTERN_DIVIDE_X_BULLET);
				bullet->bTextureUse = true;
			}

			SetBulletType(i);

			// フィールド外で未使用化（画面外弾道調整）
			if (bullet->pos.y < 0 - (TEXTURE_BULLET_SIZE_Y + SCREEN_MARGIN)
				|| bullet->pos.y > SCREEN_HEIGHT + (TEXTURE_BULLET_SIZE_Y + SCREEN_MARGIN)
				|| bullet->pos.x < 0 - (TEXTURE_BULLET_SIZE_X + SCREEN_MARGIN)
				|| bullet->pos.x > SCREEN_WIDTH + (TEXTURE_BULLET_SIZE_X + SCREEN_MARGIN) )
			{
				// バレットステータスの初期化
				InitStatusBullet(i);
			}
			

			// 回転処理
			if (bullet->nPatternHoming)
			{
				bullet->rot.z -= BULLET01_ROTATION;
			}
			else
			{
				bullet->rot.z += BULLET01_ROTATION;
			}

			// テクスチャ座標を設定
			SetTextureBullet(i, bullet->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexBullet(i);
		}
	}
	// 連射速度調整
	g_nReloadBullet00--;
	g_nReloadBullet--;
	g_nReloadBullet02--;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bullet->Texture);

			// バレットの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[no];

	// 角度と半径を求める
	bullet->fBaseAngle = atan2f(TEXTURE_BULLET_SIZE_Y, TEXTURE_BULLET_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
	bullet->fRadius = D3DXVec2Length(&temp);

	// 頂点座標の設定
	bullet->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bullet->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BULLET_SIZE_X, 100.0f, 0.0f);
	bullet->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BULLET_SIZE_Y, 0.0f);
	bullet->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BULLET_SIZE_X, 100.0f+TEXTURE_BULLET_SIZE_Y, 0.0f);
	//SetVertexBullet();

	// rhwの設定
	bullet->vertexWk[0].rhw =
	bullet->vertexWk[1].rhw =
	bullet->vertexWk[2].rhw =
	bullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);

	// テクスチャ座標の設定
	bullet->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bullet->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BULLET, 0.0f );
	bullet->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET );
	bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet( int no, int cntPattern )
{
	BULLET *bullet = &bulletWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET;
	bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBullet(int no)
{
	BULLET *bullet = &bulletWk[no];
	// 頂点0:回転あり
	bullet->vertexWk[0].vtx.x = bullet->pos.x - cosf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[0].vtx.y = bullet->pos.y - sinf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[0].vtx.z = 0.0f;

	// 頂点1:回転あり
	bullet->vertexWk[1].vtx.x = bullet->pos.x + cosf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[1].vtx.y = bullet->pos.y - sinf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[1].vtx.z = 0.0f;

	// 頂点2:回転あり
	bullet->vertexWk[2].vtx.x = bullet->pos.x - cosf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[2].vtx.y = bullet->pos.y + sinf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[2].vtx.z = 0.0f;

	// 頂点3:回転あり
	bullet->vertexWk[3].vtx.x = bullet->pos.x + cosf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[3].vtx.y = bullet->pos.y + sinf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットをプレイヤーに設置
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,int nBulletType)
{
	BULLET *bullet = &bulletWk[0];
	bool bReload00 = false;
	bool bReload01 = false;
	bool bReload02 = false;
	bool bReload03 = false;
	int nLoop = 0;
	int nAngleType = 0;

	switch (nBulletType)
	{
	case 0:
		if (g_nReloadBullet00 <= 0)
		{
			g_nReloadBullet00 = BULLET00_RELOAD_SPEED;
			bReload00 = true;
			nLoop = 2;
		}
		break;
	case 1:
		if (g_nReloadBullet <= 0)
		{
			g_nReloadBullet = BULLET01_RELOAD_SPEED;
			bReload01 = true;
		}
		break;
	case 2:
		if (g_nReloadBullet02 <= 0)
		{
			g_nReloadBullet02 = BULLET02_RELOAD_SPEED;
			bReload02 = true;
		}
		break;
	case 3:
		// バレット03はファンネル側でリロード管理
		bReload03 = true;
		break;
	}

	if (bReload00 || bReload01 || bReload02 || bReload03)
	{
		// 未使用の弾を探す
		for (int i = 0; i < BULLET_MAX; i++, bullet++)
		{
			if (!bullet->bUse)
			{
				// posを自分にセット
				if (nBulletType != 3)
				{
					bullet->pos.x = pos.x + BULLET_ADJUSTMENT_X;
					bullet->pos.y = pos.y + BULLET_ADJUSTMENT_Y;
				}
				// バレットの向きをセット
				bullet->nBulletType = nBulletType;
				// 未使用の弾があったら使用に変更
				bullet->bUse = true;
				// テクスチャ座標を設定
				SetTextureBullet(i, bullet->nPatternAnim);
				// 移動後の座標で頂点を設定
				SetVertexBullet(i);

				switch (nBulletType)
				{
				case 0:
					bullet->nAngleType = nAngleType;
					break;
				case 1:
					// ホーミングパターン設置
					bullet->nPatternHoming = g_nTotalBullet % 2;
					// 総発射数をカウント
					g_nTotalBullet++;
					break;
				case 2:
					// ホーミングパターン設置
					bullet->nPatternHoming = g_nTotalBullet02 % 2;
					// 総発射数をカウント
					g_nTotalBullet02++;
					break;
				case 3:
					// ファンネルバレットは座標調整なし
					bullet->pos.x = pos.x;
					bullet->pos.y = pos.y;
					break;
				}
				if (nLoop <= 0)
				{
					return;
				}
				else
				{
					nLoop--;
					nAngleType++;
				}
			}
		}
	}
}

//=============================================================================
// バレットパターン
//=============================================================================
void SetBulletType(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	switch(bullet->nBulletType)
	{
	case 0:
		SetBulletType00(nBullet);
		break;
	case 1:
		SetBulletType01(nBullet);
		break;
	case 2:
		SetBulletType02(nBullet);
		break;
	case 3:
		SetBulletType03(nBullet);
		break;
	}
}

//=============================================================================
// バレットパターン00 ノーマルバレット
//=============================================================================
void SetBulletType00(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	// 通常弾（角度固定）
	switch (bullet->nAngleType)
	{
	case 0:
		bullet->fAngle = 0.1f;
		break;
	case 1:
		bullet->fAngle = 0.0f;
		break;
	case 2:
		bullet->fAngle = -0.1f;
		break;
	}

	// 移動量計算
	bullet->move.x = cos(bullet->fAngle) * BULLET00_SPEED_MAX;
	bullet->move.y = sin(bullet->fAngle) * BULLET00_SPEED_MAX;
	// 移動量適用
	bullet->pos.x += bullet->move.x;
	bullet->pos.y += bullet->move.y;
}


//=============================================================================
// バレットパターン01 ホーミングバレット（湾曲）
//=============================================================================
void SetBulletType01(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// エネミー検索
	SetSearchEnemy(nBullet);

	// ホーミング処理
	if (bullet->nHomingFlag == 1)
	{
		bullet->nHomingFlag = 2;
		enemy = GetEnemy(bullet->nTarget);
		if (enemy->bUse)
		{
			bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
			bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

			// atan2のエラー防止
			if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
			{
				bullet->vecTa.x += 0.00001;
			}

			// 角度計算
			bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);

			// 射角変更
			if (bullet->nPatternHoming == 0)
			{
				bullet->fAngle += 0.3;
			}
			else if (bullet->nPatternHoming == 1)
			{
				bullet->fAngle -= 0.3;
			}
		}
	}
	if (bullet->nHomingFlag == 2)
	{
		// 移動量計算
		bullet->move.x = cos(bullet->fAngle) * BULLET01_SPEED_MAX;
		bullet->move.y = sin(bullet->fAngle) * BULLET01_SPEED_MAX;
		// 移動量適用
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		bullet->nHomingFlag = 3;
		if (bullet->nPatternHoming)
		{
			bullet->pos.x += BULLET01_SPEED_MAX;
			bullet->pos.y += BULLET01_SPEED_MAX / 4;
		}
		else
		{
			bullet->pos.x += BULLET01_SPEED_MAX;
			bullet->pos.y -= BULLET01_SPEED_MAX / 4;
		}
	}
}

//=============================================================================
// バレットパターン02 ホーミングバレット
//=============================================================================
void SetBulletType02(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// バレット02の加速
	bullet->fBulletSpeed += BULLET02_SPEED_ACCELERATOR;
	if (bullet->fBulletSpeed >= BULLET02_SPEED_MAX)
	{
		bullet->fBulletSpeed = BULLET02_SPEED_MAX;
	}

	if (bullet->nBulletCount == 0)
	{
		// 射角変更
		if (bullet->nPatternHoming == 0)
		{
			bullet->vecTa.x = -50 - (rand() % 100);
			bullet->vecTa.y = +50 + (rand() % 200);
		}
		else if (bullet->nPatternHoming == 1)
		{
			bullet->vecTa.x = -50 - (rand() % 100);
			bullet->vecTa.y = -50 - (rand() % 200);
		}

		// atan2のエラー防止
		if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
		{
			bullet->vecTa.x += 0.00001;
		}

		// 角度計算
		bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);

		// 射角変更
		if (bullet->nPatternHoming == 0)
		{
			bullet->fAngle += 0.5;
		}
		else if (bullet->nPatternHoming == 1)
		{
			bullet->fAngle -= 0.5;
		}
	}
	else if (bullet->nBulletCount <= 30)
	{
		// 移動量計算
		bullet->move.x = cos(bullet->fAngle) * bullet->fBulletSpeed;
		bullet->move.y = sin(bullet->fAngle) * bullet->fBulletSpeed;
		// 移動量適用
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		// エネミー検索
		SetSearchEnemy(nBullet);

		// ホーミング処理
		if (bullet->nHomingFlag == 1)
		{
			bullet->nHomingFlag = 2;
			enemy = GetEnemy(bullet->nTarget);
			if (enemy->bUse)
			{
				bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
				bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

				// atan2のエラー防止
				if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
				{
					bullet->vecTa.x += 0.00001;
				}

				// 角度計算
				bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);
			}
		}
		if (bullet->nHomingFlag == 2)
		{
			// 移動量計算
			bullet->move.x = cos(bullet->fAngle) * bullet->fBulletSpeed;
			bullet->move.y = sin(bullet->fAngle) * bullet->fBulletSpeed;
			// 移動量適用
			bullet->pos.x += bullet->move.x;
			bullet->pos.y += bullet->move.y;
		}
		else
		{
			bullet->pos.x += bullet->fBulletSpeed;
		}
	}


	bullet->nBulletCount++;

}

//=============================================================================
// バレットパターン03 ホーミングバレット（直進・ファンネル用）
//=============================================================================
void SetBulletType03(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// エネミー検索
	SetSearchEnemy(nBullet);

	// ホーミング処理
	if (bullet->nHomingFlag == 1)
	{
		bullet->nHomingFlag = 2;
		enemy = GetEnemy(bullet->nTarget);
		if (enemy->bUse)
		{
			bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
			bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

			// atan2のエラー防止
			if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
			{
				bullet->vecTa.x += 0.00001;
			}

			// 角度計算
			bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);
		}
	}
	if (bullet->nHomingFlag == 2)
	{
		// 移動量計算
		bullet->move.x = cos(bullet->fAngle) * BULLET03_SPEED_MAX;
		bullet->move.y = sin(bullet->fAngle) * BULLET03_SPEED_MAX;
		// 移動量適用
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		bullet->pos.x += BULLET03_SPEED_MAX;
	}
}

//=============================================================================
// バレットのエネミー検索
//=============================================================================
void SetSearchEnemy(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;
	PLAYER *player;

	// エネミー検索
	player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->bUse)
		{
			if (bullet->nHomingFlag == 0)
			{
				enemy = GetEnemy(0);
				float fDistanceMin = 0.0f;
				int nEnemyCount = 0;
				for (int j = 0; j < ENEMY_MAX; j++, enemy++)
				{
					// 使用しているエネミーがいるかを確認
					if (enemy->bUse)
					{
						// 距離計算
						D3DXVECTOR3 temp = player->pos - enemy->pos;
						float fTempLengthSq = D3DXVec3LengthSq(&temp);

						// 最小距離算出
						if (fTempLengthSq < fDistanceMin || fDistanceMin == 0.0f)
						{
							fDistanceMin = fTempLengthSq;
							bullet->nTarget = j;
						}
						bullet->nHomingFlag = 1;
						nEnemyCount++;
					}
					if (nEnemyCount == 0)
					{
						bullet->nHomingFlag = 3;
					}
				}
			}
			if (bullet->nHomingFlag == 2)
			{
				bullet->nHomingFlag = 1;
			}
		}
	}
	return;
}

//=============================================================================
// バレットの再利用処理
//=============================================================================
void InitStatusBullet(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	// バレットステータスの初期化
	bullet->bUse = false;
	bullet->bTextureUse = false;

	bullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
	bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bullet->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bullet->nCountAnim = 0;
	bullet->nPatternAnim = 0;
	bullet->nBulletType = 0;
	bullet->nBulletCount = 0;
	bullet->nAngleType = 0;
	bullet->nPatternHoming = 0;
	bullet->nHomingFlag = 0;
	bullet->nTarget = 0;

	bullet->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bullet->nDirection = 0;

	bullet->fBulletSpeed = 0.0f;
	bullet->fAngle = 0.0f;

	return;
}

//=============================================================================
// バレット01取得関数
//=============================================================================
BULLET *GetBullet(int no)
{
	return(&bulletWk[no]);
}
