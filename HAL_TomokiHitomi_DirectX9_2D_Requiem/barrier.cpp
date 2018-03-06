//=============================================================================
//
// ファンネル処理 [barrier.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
//#include "main.h"
#include "barrier.h"
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
HRESULT MakeVertexBarrier(int no);
void SetTextureBarrier( int no, int cntPattern );
void SetVertexBarrier(int no);

void SetBarrierType(int nBarrier);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BARRIER					barrierWk[BARRIER_MAX];
int						g_nTotalBarrier;					// ファンネル01の総発射数
int						g_nTotalBarrier02;					// ファンネル01の総発射数

int						g_nReloadBarrier00;
int						g_nReloadBarrier;
int						g_nReloadBarrier02;

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureBarrier = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBarrier(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[0];

	g_nTotalBarrier = 0;
	g_nTotalBarrier02 = 0;

	g_nReloadBarrier00 = 0;
	g_nReloadBarrier = 0;
	g_nReloadBarrier02 = 0;

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BARRIER,				// ファイルの名前
			&pD3DTextureBarrier);			// 読み込むメモリのポインタ
	}

	// ファンネルの初期化
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		barrier->size = D3DXVECTOR2(BARRIER_CUSTOM_SIZE_X, BARRIER_CUSTOM_SIZE_Y);
		barrier->Texture = pD3DTextureBarrier;	// テクスチャへのファンネル

		barrier->fBaseAngle = 0.0f;
		barrier->fRadius = 0.0f;

		// ファンネルステータスの初期化
		InitStatusBarrier(i);

		// 頂点情報の作成
		MakeVertexBarrier(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];
	// メモリ解放
	if (pD3DTextureBarrier != NULL)
	{
		pD3DTextureBarrier->Release();
		pD3DTextureBarrier = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];
	ENEMY *enemy;
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse == true)
		{
			// テクスチャー設定
			barrier->nCountAnim++;
			if (barrier->nCountAnim % TIME_ANIMATION_BARRIER == 0)
			{
				// パターンの切り替え
				barrier->nPatternAnim = (barrier->nPatternAnim + 1) % ANIM_PATTERN_NU_BARRIER;
			}

			// 無重力モードはファンネルを展開・バレット発射
			if (GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L))
			{
				barrier->fDistance += BARRIER_INJECTION_SPEED;
				if (barrier->fDistance > BARRIER_DISTANCE_MAX)
				{
					barrier->fDistance = BARRIER_DISTANCE_MAX;
				}
			}
			else
			{
				barrier->fDistance -= BARRIER_INJECTION_SPEED;
				if (barrier->fDistance < 0.0f)
				{
					barrier->bUse = false;
				}
			}

			SetBarrierType(i);

			// ファンネルの透明度をMP倍率で変更
			barrier->nAlpha = BARRIER_ALPHA_MIN + (BARRIER_ALPHA / (float)PLAYER_MANAMAX * player->fManaPoint);

			// 無敵点滅の適用
			barrier->nAlpha = barrier->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if (barrier->nAlpha < 0)
			{
				barrier->nAlpha = 0;
			}
			
			// テクスチャ座標を設定
			SetTextureBarrier(i, barrier->nPatternAnim);

			// 回転処理
			if (barrier->nPatternHoming)
			{
				barrier->rot.z -= BARRIER01_ROTATION;
			}
			else
			{
				barrier->rot.z += BARRIER01_ROTATION;
			}

			// 移動後の座標で頂点を設定
			SetVertexBarrier(i);

			// 連射速度調整
			barrier->nReloadBullet--;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, barrier->Texture);

			// ファンネルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BARRIER, barrier->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBarrier(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[no];

	// 角度と半径を求める
	barrier->fBaseAngle = atan2f(TEXTURE_BARRIER_SIZE_Y, TEXTURE_BARRIER_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BARRIER_SIZE_X, TEXTURE_BARRIER_SIZE_Y);
	barrier->fRadius = D3DXVec2Length(&temp);

	// 頂点座標の設定
	barrier->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	barrier->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BARRIER_SIZE_X, 100.0f, 0.0f);
	barrier->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BARRIER_SIZE_Y, 0.0f);
	barrier->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BARRIER_SIZE_X, 100.0f+TEXTURE_BARRIER_SIZE_Y, 0.0f);
	//SetVertexBarrier();

	// rhwの設定
	barrier->vertexWk[0].rhw =
	barrier->vertexWk[1].rhw =
	barrier->vertexWk[2].rhw =
	barrier->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	barrier->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);

	// テクスチャ座標の設定
	barrier->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	barrier->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BARRIER, 0.0f );
	barrier->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BARRIER );
	barrier->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BARRIER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BARRIER );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBarrier( int no, int cntPattern )
{
	BARRIER *barrier = &barrierWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BARRIER;
	barrier->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	barrier->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	barrier->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	barrier->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexBarrier(int no)
{
	BARRIER *barrier = &barrierWk[no];
	// 頂点0:回転あり
	barrier->vertexWk[0].vtx.x = barrier->pos.x - cosf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[0].vtx.y = barrier->pos.y - sinf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[0].vtx.z = 0.0f;

	// 頂点1:回転あり
	barrier->vertexWk[1].vtx.x = barrier->pos.x + cosf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[1].vtx.y = barrier->pos.y - sinf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[1].vtx.z = 0.0f;

	// 頂点2:回転あり
	barrier->vertexWk[2].vtx.x = barrier->pos.x - cosf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[2].vtx.y = barrier->pos.y + sinf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[2].vtx.z = 0.0f;

	// 頂点3:回転あり
	barrier->vertexWk[3].vtx.x = barrier->pos.x + cosf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[3].vtx.y = barrier->pos.y + sinf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[3].vtx.z = 0.0f;

	// 反射光の設定
	barrier->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
}

//=============================================================================
// ファンネルをプレイヤーに設置
//=============================================================================
void SetBarrier(D3DXVECTOR3 pos)
{
	BARRIER *barrier = &barrierWk[0];

	// 全ファンネルを等間隔にセット
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (!barrier->bUse)
		{
			// ファンネル座標を対象にセット
			barrier->pos.x = pos.x;
			barrier->pos.y = pos.y;
			// ファンネルのタイプをセット
			barrier->nBarrierType = i % BARRIER_TYPE_MAX;
			// ファンネル射出角度をセット
			barrier->fAngle = ((D3DX_PI * 2.0f) / BARRIER_MAX) * i;
			// ファンネルをアクティブにする
			barrier->bUse = true;
		}
	}
}

//=============================================================================
// ファンネルをプレイヤーに格納
//=============================================================================
void ReleaseBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];

	// 全ファンネルをノンアクティブ
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse)
		{
			InitStatusBarrier(i);
			barrier->bUse = false;
		}
	}
}

//=============================================================================
// ファンネルパターン00 ファンネル
//=============================================================================
void SetBarrierType(int nBarrier)
{
	BARRIER *barrier = &barrierWk[nBarrier];
	PLAYER *player = GetPlayer(0);

	// 角度変更
	barrier->fAngle -= D3DX_PI / BARRIER_ROTATIONAL_SPEED;

	// 360度を超えたら360度を引く
	if (barrier->fAngle <= D3DX_PI * 2.0f)
	{
		barrier->fAngle += D3DX_PI * 2.0f;
	}

	// 移動量適用
	barrier->pos.x = player->pos.x + (cos(barrier->fAngle) * barrier->fDistance);
	barrier->pos.y = player->pos.y + (sin(barrier->fAngle) * barrier->fDistance);
}

//=============================================================================
// ファンネルの再利用処理
//=============================================================================
void InitStatusBarrier(int nBarrier)
{
	BARRIER *barrier = &barrierWk[nBarrier];

	// ファンネルステータスの初期化
	barrier->bUse = false;
	barrier->bTextureUse = false;
	barrier->bReload = false;

	barrier->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
	barrier->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	barrier->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	barrier->nCountAnim = 0;
	barrier->nPatternAnim = 0;
	barrier->nBarrierType = 0;
	barrier->nBarrierCount = 0;
	barrier->nAngleType = 0;
	barrier->nPatternHoming = 0;
	barrier->nHomingFlag = 0;
	barrier->nTarget = 0;
	barrier->nReloadBullet = 0;
	barrier->nAlpha = BARRIER_ALPHA_MAX;

	barrier->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	barrier->nDirection = 0;

	barrier->fBarrierSpeed = 0.0f;
	barrier->fAngle = 0.0f;
	barrier->fDistance = 0.0f;
		

	return;
}

//=============================================================================
// ファンネル取得関数
//=============================================================================
BARRIER *GetBarrier(int no)
{
	return(&barrierWk[no]);
}
