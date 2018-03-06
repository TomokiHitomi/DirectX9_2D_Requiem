//=============================================================================
//
// FRAME処理 [frame.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "frame.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexFrame(int no);
void SetTextureFrame( int no, int cntPattern );	//
void SetVertexFrame(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
FRAME					frameWk[FRAME_MAX];

// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		pD3DTextureFrame = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFrame(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[0];

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_FRAME,				// ファイルの名前
			&pD3DTextureFrame);			// 読み込むメモリのポインタ
	}

	// FRAMEの初期化
	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		frame->bUse = true;
		frame->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		frame->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frame->nCountAnim = 0;
		frame->nPatternAnim = 0;

		frame->Texture = pD3DTextureFrame;			// テクスチャへのFRAME
		frame->size = D3DXVECTOR2(TEXTURE_FRAME_SIZE_X, TEXTURE_FRAME_SIZE_Y);

		// 頂点情報の作成
		MakeVertexFrame(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFrame(void)
{
	FRAME *frame = &frameWk[0];

	// メモリ解放
	if (pD3DTextureFrame != NULL)
	{
		pD3DTextureFrame->Release();
		pD3DTextureFrame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFrame(void)
{
	FRAME *frame = &frameWk[0];
	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		if (frame->bUse == true)
		{
			// アニメーション
			frame->nCountAnim++;
			if ((frame->nCountAnim % TIME_ANIMATION_FRAME) == 0)
			{
				// パターンの切り替え
				frame->nPatternAnim = (frame->nPatternAnim + 1) % ANIM_PATTERN_NUM_FRAME;
			}

			// テクスチャ座標を設定
			SetTextureFrame(i, frame->nPatternAnim);
			// 移動後の座標で頂点を設定
			SetVertexFrame(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		if (frame->bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, frame->Texture);

			// FRAMEの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FRAME, frame->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexFrame(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[no];

	// 頂点座標の設定
	frame->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	frame->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FRAME_SIZE_X, 100.0f, 0.0f);
	frame->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FRAME_SIZE_Y, 0.0f);
	frame->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FRAME_SIZE_X, 100.0f+TEXTURE_FRAME_SIZE_Y, 0.0f);
	//SetVertexFrame();

	// rhwの設定
	frame->vertexWk[0].rhw =
	frame->vertexWk[1].rhw =
	frame->vertexWk[2].rhw =
	frame->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	frame->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);

	// テクスチャ座標の設定
	frame->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	frame->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FRAME, 0.0f );
	frame->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FRAME );
	frame->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FRAME, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FRAME );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureFrame( int no, int cntPattern )
{
	FRAME *frame = &frameWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FRAME;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FRAME;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FRAME;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FRAME;
	frame->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	frame->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	frame->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	frame->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexFrame(int no)
{
	FRAME *frame = &frameWk[no];

	frame->vertexWk[0].vtx.x = frame->pos.x - TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[0].vtx.y = frame->pos.y - TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[0].vtx.z = 0.0f;

	frame->vertexWk[1].vtx.x = frame->pos.x + TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[1].vtx.y = frame->pos.y - TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[1].vtx.z = 0.0f;

	frame->vertexWk[2].vtx.x = frame->pos.x - TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[2].vtx.y = frame->pos.y + TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[2].vtx.z = 0.0f;

	frame->vertexWk[3].vtx.x = frame->pos.x + TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[3].vtx.y = frame->pos.y + TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// FRAME取得関数
//=============================================================================
FRAME *GetFrame(int no)
{
	return(&frameWk[no]);
}

