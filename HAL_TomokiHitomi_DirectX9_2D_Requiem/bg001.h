//=============================================================================
//
// BG001処理 [bg001.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BG001_H_
#define _BG001_H_

#include "main.h"

// マクロ定義
#define NUM_BG001		(2)	// ポリゴン数

#define TEXTURE_GAME_BG001	_T("data/TEXTURE/bg001.png")	// BG001用画像
#define TEXTURE_BG001_SIZE_X	((5000 * SCREEN_SCALING) / 2) // テクスチャサイズ
#define TEXTURE_BG001_SIZE_Y	((915 * SCREEN_SCALING) / 2) // 同上

#define BG001_POS_X				(TEXTURE_BG001_SIZE_X)	// 初期座標X
#define BG001_POS_Y				(300 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_BG001_R			(100) // テクスチャカラー赤
#define TEXTURE_BG001_G			(100) // テクスチャカラー緑
#define TEXTURE_BG001_B			(100) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_BG001	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BG001	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BG001			(TEXTURE_PATTERN_DIVIDE_X_BG001*TEXTURE_PATTERN_DIVIDE_Y_BG001)	// アニメーションパターン数
#define TIME_ANIMATION_BG001				(4)	// アニメーションの切り替わるカウント

#define BG001_MAX					(2)	// 最大数
#define BG001_SPEED					(1.5f * SCREEN_SCALING)	// スクロール速度


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// BG001の移動量
	D3DXVECTOR3				rot;					// BG001の回転量
	D3DXVECTOR2				size;					// BG001のテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;					// 半径
	bool					bUse;					// true:使用  false:未使用
}BG001;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBg001(int type);
void UninitBg001(void);
void UpdateBg001(void);
void DrawBg001(void);
BG001 *GetBg001(int no);


#endif
