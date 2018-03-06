//=============================================================================
//
// FRAME処理 [frame.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"

// マクロ定義
#define NUM_FRAME		(2)	// ポリゴン数

#define TEXTURE_GAME_FRAME	_T("data/TEXTURE/frame.png")	// FRAME用画像
#define TEXTURE_FRAME_SIZE_X	(1280 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_FRAME_SIZE_Y	(720 * SCREEN_SCALING/2) // 同上

#define TEXTURE_FRAME_R			(255) // テクスチャカラー赤
#define TEXTURE_FRAME_G			(255) // テクスチャカラー緑
#define TEXTURE_FRAME_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_FRAME	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_FRAME	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_FRAME			(TEXTURE_PATTERN_DIVIDE_X_FRAME*TEXTURE_PATTERN_DIVIDE_Y_FRAME)	// アニメーションパターン数
#define TIME_ANIMATION_FRAME			(4)	// アニメーションの切り替わるカウント

#define FRAME_MAX					(1)	// FRAMEの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// FRAMEの移動量
	D3DXVECTOR3				rot;					// FRAMEの回転量
	D3DXVECTOR2				size;					// FRAMEのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}FRAME;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFrame(int type);
void UninitFrame(void);
void UpdateFrame(void);
void DrawFrame(void);
FRAME *GetFrame(int no);


#endif
