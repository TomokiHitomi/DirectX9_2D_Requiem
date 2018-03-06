//=============================================================================
//
// ヒットサークル処理 [hitcircle.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _HITCIRCLE_H_
#define _HITCIRCLE_H_

#include "main.h"

// マクロ定義
#define NUM_HITCIRCLE						(2)		// ポリゴン数
#define TEXTURE_GAME_HITCIRCLE00		_T("data/TEXTURE/hit.png")	// ヒットサークル00用画像
#define TEXTURE_HITCIRCLE00_SIZE_X			(20 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_HITCIRCLE00_SIZE_Y			(20 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE	(1)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE	(1)		// アニメパターンのテクスチャ内分割数（Y)

// 当たり判定用サイズ
#define HITCIRCLE_CUSTOM_SIZE_X				(1)
#define HITCIRCLE_CUSTOM_SIZE_Y				(1)

#define ANIM_PATTERN_NUM_HITCIRCLE			(TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE*TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE)	// アニメーションパターン数
#define TIME_ANIMATION_HITCIRCLE			(4)		// アニメーションの切り替わるカウント
#define HITCIRCLE_MAX						(1)		// ヒットサークルの最大数

// ヒットサークルのセット座標調整
#define HITCIRCLE_ADJUSTMENT_X				(0)
#define HITCIRCLE_ADJUSTMENT_Y				(-5)

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 移動量
	D3DXVECTOR3				rot;					// 回転量
	D3DXVECTOR2				size;					// テクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// ヒットサークルフラグ
}HITCIRCLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHitcircle(int type);
void UninitHitcircle(void);
void UpdateHitcircle(void);
void DrawHitcircle(void);
HITCIRCLE *GetHitcircle(int no);


#endif
