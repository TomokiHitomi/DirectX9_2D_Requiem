//=======================================================================Hitcircle======
//
// プレイヤー処理 [nogravity.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "nogravity.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexNogravity(int no);
void SetTextureNogravity( int no, int cntPattern );	//
void SetVertexNogravity(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
NOGRAVITY					nogravityWk[NOGRAVITY_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureNogravity = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitNogravity(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_NOGRAVITY00,				// ファイルの名前
			&pD3DTextureNogravity);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化
	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		nogravity->bUse = true;
		nogravity->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		nogravity->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		nogravity->nCountAnim = 0;
		nogravity->nPatternAnim = 0;
		nogravity->nScaling = TEXTURE_NOGRAVITY00_SIZE_X;
		nogravity->Texture = pD3DTextureNogravity;			// テクスチャへのエネミー
		nogravity->size = D3DXVECTOR2(TEXTURE_NOGRAVITY00_SIZE_X, TEXTURE_NOGRAVITY00_SIZE_Y);

		// 頂点情報の作成
		MakeVertexNogravity(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitNogravity(void)
{
	NOGRAVITY *nogravity = &nogravityWk[0];

	// メモリ解放
	if (pD3DTextureNogravity != NULL)
	{
		pD3DTextureNogravity->Release();
		pD3DTextureNogravity = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateNogravity(void)
{
	NOGRAVITY *nogravity = &nogravityWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		if (player->bUse)
		{
			nogravity->bUse = true;
			// アニメーション
			nogravity->nCountAnim++;
			if ((nogravity->nCountAnim % TIME_ANIMATION_NOGRAVITY) == 0)
			{
				// パターンの切り替え
				nogravity->nPatternAnim = (nogravity->nPatternAnim + 1) % ANIM_PATTERN_NUM_NOGRAVITY;
			}
			nogravity->pos.x = player->pos.x + NOGRAVITY_ADJUSTMENT_X;
			nogravity->pos.y = player->pos.y + NOGRAVITY_ADJUSTMENT_Y;
		}
		else
		{
			nogravity->bUse = false;
		}

		// 無重力モード
		if ((GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R) || GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L)) && player->fManaPoint >= 50.0f)
		{
			nogravity->nScaling += TEXTURE_NOGRAVITY00_SCALING_SPEED;
			if (nogravity->nScaling >= TEXTURE_NOGRAVITY00_SCALING_MAX)
			{
				nogravity->nScaling = TEXTURE_NOGRAVITY00_SCALING_MAX;
			}
		}
		else
		{
			nogravity->nScaling -= TEXTURE_NOGRAVITY00_SCALING_SPEED;
			if (nogravity->nScaling <= TEXTURE_NOGRAVITY00_SIZE_X)
			{
				nogravity->nScaling = TEXTURE_NOGRAVITY00_SIZE_X;
			}
		}

		// テクスチャ座標を設定
		SetTextureNogravity(i, nogravity->nPatternAnim);
		// 移動後の座標で頂点を設定
		SetVertexNogravity(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawNogravity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		if (nogravity->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, nogravity->Texture);

			// プレイヤーの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_NOGRAVITY, nogravity->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexNogravity(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[no];

	// 頂点座標の設定
	nogravity->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	nogravity->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_NOGRAVITY00_SIZE_X, 100.0f, 0.0f);
	nogravity->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_NOGRAVITY00_SIZE_Y, 0.0f);
	nogravity->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_NOGRAVITY00_SIZE_X, 100.0f+TEXTURE_NOGRAVITY00_SIZE_Y, 0.0f);
	//SetVertexNogravity();

	// rhwの設定
	nogravity->vertexWk[0].rhw =
	nogravity->vertexWk[1].rhw =
	nogravity->vertexWk[2].rhw =
	nogravity->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	nogravity->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);

	// テクスチャ座標の設定
	nogravity->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	nogravity->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY, 0.0f );
	nogravity->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY );
	nogravity->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureNogravity( int no, int cntPattern )
{
	NOGRAVITY *nogravity = &nogravityWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY;
	nogravity->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	nogravity->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	nogravity->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	nogravity->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexNogravity(int no)
{
	NOGRAVITY *nogravity = &nogravityWk[no];

	nogravity->vertexWk[0].vtx.x = nogravity->pos.x - nogravity->nScaling;
	nogravity->vertexWk[0].vtx.y = nogravity->pos.y - nogravity->nScaling;
	nogravity->vertexWk[0].vtx.z = 0.0f;

	nogravity->vertexWk[1].vtx.x = nogravity->pos.x + nogravity->nScaling;
	nogravity->vertexWk[1].vtx.y = nogravity->pos.y - nogravity->nScaling;
	nogravity->vertexWk[1].vtx.z = 0.0f;

	nogravity->vertexWk[2].vtx.x = nogravity->pos.x - nogravity->nScaling;
	nogravity->vertexWk[2].vtx.y = nogravity->pos.y + nogravity->nScaling;
	nogravity->vertexWk[2].vtx.z = 0.0f;

	nogravity->vertexWk[3].vtx.x = nogravity->pos.x + nogravity->nScaling;
	nogravity->vertexWk[3].vtx.y = nogravity->pos.y + nogravity->nScaling;
	nogravity->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
NOGRAVITY *GetNogravity(int no)
{
	return(&nogravityWk[no]);
}

