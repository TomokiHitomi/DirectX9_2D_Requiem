//=============================================================================
//
// ファンネル処理 [funnel.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
//#include "main.h"
#include "funnel.h"
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
HRESULT MakeVertexFunnel(int no);
void SetTextureFunnel( int no, int cntPattern );
void SetVertexFunnel(int no);

void SetFunnelBullet(void);

void SetFunnelType(int nFunnel);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
FUNNEL					funnelWk[FUNNEL_MAX];
int						g_nTotalFunnel;					// ファンネル01の総発射数
int						g_nTotalFunnel02;					// ファンネル01の総発射数

int						g_nReloadFunnel00;
int						g_nReloadFunnel;
int						g_nReloadFunnel02;

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureFunnel = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFunnel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[0];

	g_nTotalFunnel = 0;
	g_nTotalFunnel02 = 0;

	g_nReloadFunnel00 = 0;
	g_nReloadFunnel = 0;
	g_nReloadFunnel02 = 0;

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_FUNNEL,				// ファイルの名前
			&pD3DTextureFunnel);			// 読み込むメモリのポインタ
	}

	// ファンネルの初期化
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		funnel->size = D3DXVECTOR2(TEXTURE_FUNNEL_SIZE_X, TEXTURE_FUNNEL_SIZE_Y);
		funnel->Texture = pD3DTextureFunnel;	// テクスチャへのファンネル

		funnel->fBaseAngle = 0.0f;
		funnel->fRadius = 0.0f;

		// ファンネルステータスの初期化
		InitStatusFunnel(i);

		// 頂点情報の作成
		MakeVertexFunnel(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];
	// メモリ解放
	if (pD3DTextureFunnel != NULL)
	{
		pD3DTextureFunnel->Release();
		pD3DTextureFunnel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];
	ENEMY *enemy;
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse == true)
		{
			// テクスチャー設定
			funnel->nCountAnim++;
			if (funnel->nCountAnim % TIME_ANIMATION_FUNNEL == 0)
			{
				// パターンの切り替え
				funnel->nPatternAnim = (funnel->nPatternAnim + 1) % ANIM_PATTERN_NU_FUNNEL;
			}

			// 無重力モードはファンネルを展開・バレット発射
			if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R))
			{
				funnel->fDistance += FUNNEL_INJECTION_SPEED;
				if (funnel->fDistance > FUNNEL_DISTANCE_MAX)
				{
					funnel->fDistance = FUNNEL_DISTANCE_MAX;
				}
			}
			else
			{
				funnel->fDistance -= FUNNEL_INJECTION_SPEED;
				if (funnel->fDistance < 0.0f)
				{
					funnel->bUse = false;
				}
			}

			// バレット発射
			if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_B) || IsButtonPressed(0, BUTTON_A))
			{
				if (funnel->fDistance == FUNNEL_DISTANCE_MAX)
				{
					SetFunnelBullet();
				}
			}

			SetFunnelType(i);

			// ファンネルの透明度をMP倍率で変更
			funnel->nAlpha = FUNNEL_ALPHA_MIN + (FUNNEL_ALPHA / (float)PLAYER_MANAMAX * player->fManaPoint);

			// 無敵点滅の適用
			funnel->nAlpha = funnel->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if (funnel->nAlpha < 0)
			{
				funnel->nAlpha = 0;
			}
			
			// テクスチャ座標を設定
			SetTextureFunnel(i, funnel->nPatternAnim);

			// 回転処理
			if (funnel->nPatternHoming)
			{
				funnel->rot.z -= FUNNEL01_ROTATION;
			}
			else
			{
				funnel->rot.z += FUNNEL01_ROTATION;
			}

			// 移動後の座標で頂点を設定
			SetVertexFunnel(i);

			// 連射速度調整
			funnel->nReloadBullet--;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFunnel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, funnel->Texture);

			// ファンネルの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FUNNEL, funnel->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexFunnel(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[no];

	// 角度と半径を求める
	funnel->fBaseAngle = atan2f(TEXTURE_FUNNEL_SIZE_Y, TEXTURE_FUNNEL_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_FUNNEL_SIZE_X, TEXTURE_FUNNEL_SIZE_Y);
	funnel->fRadius = D3DXVec2Length(&temp);

	// 頂点座標の設定
	funnel->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	funnel->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FUNNEL_SIZE_X, 100.0f, 0.0f);
	funnel->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FUNNEL_SIZE_Y, 0.0f);
	funnel->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FUNNEL_SIZE_X, 100.0f+TEXTURE_FUNNEL_SIZE_Y, 0.0f);
	//SetVertexFunnel();

	// rhwの設定
	funnel->vertexWk[0].rhw =
	funnel->vertexWk[1].rhw =
	funnel->vertexWk[2].rhw =
	funnel->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	funnel->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);

	// テクスチャ座標の設定
	funnel->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	funnel->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FUNNEL, 0.0f );
	funnel->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FUNNEL );
	funnel->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FUNNEL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FUNNEL );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureFunnel( int no, int cntPattern )
{
	FUNNEL *funnel = &funnelWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FUNNEL;
	funnel->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	funnel->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	funnel->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	funnel->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexFunnel(int no)
{
	FUNNEL *funnel = &funnelWk[no];
	// 頂点0:回転あり
	funnel->vertexWk[0].vtx.x = funnel->pos.x - cosf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[0].vtx.y = funnel->pos.y - sinf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[0].vtx.z = 0.0f;

	// 頂点1:回転あり
	funnel->vertexWk[1].vtx.x = funnel->pos.x + cosf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[1].vtx.y = funnel->pos.y - sinf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[1].vtx.z = 0.0f;

	// 頂点2:回転あり
	funnel->vertexWk[2].vtx.x = funnel->pos.x - cosf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[2].vtx.y = funnel->pos.y + sinf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[2].vtx.z = 0.0f;

	// 頂点3:回転あり
	funnel->vertexWk[3].vtx.x = funnel->pos.x + cosf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[3].vtx.y = funnel->pos.y + sinf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[3].vtx.z = 0.0f;

	// 反射光の設定
	funnel->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
}

//=============================================================================
// ファンネルをプレイヤーに設置
//=============================================================================
void SetFunnel(D3DXVECTOR3 pos)
{
	FUNNEL *funnel = &funnelWk[0];

	// 全ファンネルを等間隔にセット
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (!funnel->bUse)
		{
			// ファンネル座標を対象にセット
			funnel->pos.x = pos.x;
			funnel->pos.y = pos.y;
			// ファンネルのタイプをセット
			funnel->nFunnelType = i % FUNNEL_TYPE_MAX;
			// ファンネル射出角度をセット
			funnel->fAngle = ((D3DX_PI * 2.0f) / FUNNEL_MAX) * i;
			// ファンネルをアクティブにする
			funnel->bUse = true;
		}
	}
}

//=============================================================================
// ファンネルをプレイヤーに格納
//=============================================================================
void ReleaseFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];

	// 全ファンネルをノンアクティブ
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse)
		{
			InitStatusFunnel(i);
			funnel->bUse = false;
		}
	}
}

//=============================================================================
// ファンネルにバレットを設置
//=============================================================================
void SetFunnelBullet(void)
{
	FUNNEL *funnel = &funnelWk[0];

	// 全ファンネルをノンアクティブ
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		// リロードを確認
		if (funnel->nReloadBullet <= 0)
		{
			funnel->nReloadBullet = FUNNEL_BULLET_RELOAD_SPEED;
			funnel->bReload = true;
		}
		// リロードが完了している場合はバレットをセット
		if (funnel->bReload)
		{
			SetBullet(funnel->pos, 3);
		}
		funnel->bReload = false;
	}
}

//=============================================================================
// ファンネルパターン00 ファンネル
//=============================================================================
void SetFunnelType(int nFunnel)
{
	FUNNEL *funnel = &funnelWk[nFunnel];
	PLAYER *player = GetPlayer(0);

	// 角度変更
	funnel->fAngle += D3DX_PI / FUNNEL_ROTATIONAL_SPEED;

	// 360度を超えたら360度を引く
	if (funnel->fAngle >= D3DX_PI * 2.0f)
	{
		funnel->fAngle -= D3DX_PI * 2.0f;
	}

	// 移動量適用
	funnel->pos.x = player->pos.x + (cos(funnel->fAngle) * funnel->fDistance);
	funnel->pos.y = player->pos.y + (sin(funnel->fAngle) * funnel->fDistance);
}

//=============================================================================
// ファンネルの再利用処理
//=============================================================================
void InitStatusFunnel(int nFunnel)
{
	FUNNEL *funnel = &funnelWk[nFunnel];

	// ファンネルステータスの初期化
	funnel->bUse = false;
	funnel->bTextureUse = false;
	funnel->bReload = false;

	funnel->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
	funnel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	funnel->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	funnel->nCountAnim = 0;
	funnel->nPatternAnim = 0;
	funnel->nFunnelType = 0;
	funnel->nFunnelCount = 0;
	funnel->nAngleType = 0;
	funnel->nPatternHoming = 0;
	funnel->nHomingFlag = 0;
	funnel->nTarget = 0;
	funnel->nReloadBullet = 0;
	funnel->nAlpha = FUNNEL_ALPHA_MAX;

	funnel->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	funnel->nDirection = 0;

	funnel->fFunnelSpeed = 0.0f;
	funnel->fAngle = 0.0f;
	funnel->fDistance = 0.0f;
		

	return;
}

//=============================================================================
// ファンネル取得関数
//=============================================================================
FUNNEL *GetFunnel(int no)
{
	return(&funnelWk[no]);
}
