//=============================================================================
//
// BG000処理 [bg000.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BG000_H_
#define _BG000_H_

#include "main.h"

// マクロ定義
#define NUM_BG000		(2)	// ポリゴン数

#define TEXTURE_GAME_BG000	_T("data/TEXTURE/bg000.png")	// BG000用画像
#define TEXTURE_BG000_SIZE_X	(SCREEN_WIDTH / 2) // テクスチャサイズ
#define TEXTURE_BG000_SIZE_Y	(SCREEN_HEIGHT / 2) // 同上

#define TEXTURE_BG000_R			(255) // テクスチャカラー赤
#define TEXTURE_BG000_G			(255) // テクスチャカラー緑
#define TEXTURE_BG000_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_BG000	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BG000	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BG000			(TEXTURE_PATTERN_DIVIDE_X_BG000*TEXTURE_PATTERN_DIVIDE_Y_BG000)	// アニメーションパターン数
#define TIME_ANIMATION_BG000				(4)	// アニメーションの切り替わるカウント

#define BG000_MAX					(1)	// BG000の最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// BG000の移動量
	D3DXVECTOR3				rot;					// BG000の回転量
	D3DXVECTOR2				size;					// BG000のテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}BG000;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBg000(int type);
void UninitBg000(void);
void UpdateBg000(void);
void DrawBg000(void);
BG000 *GetBg000(int no);


#endif
