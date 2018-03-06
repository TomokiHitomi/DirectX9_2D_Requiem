//=============================================================================
//
// ヒットサークル処理 [effect_knockdown.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _EFFECT_KNOCKDOWN_H_
#define _EFFECT_KNOCKDOWN_H_

#include "main.h"

// マクロ定義
#define NUM_EFFECT_KNOCKDOWN						(2)		// ポリゴン数
#define TEXTURE_GAME_EFFECT_KNOCKDOWN		_T("data/TEXTURE/effect_knockdown.png")	// ヒットサークル00用画像
#define TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X			(160 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y			(160 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN	(10)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN	(10)		// アニメパターンのテクスチャ内分割数（Y)

#define ANIM_PATTERN_NUM_EFFECT_KNOCKDOWN			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT_KNOCKDOWN				(3)		// アニメーションの切り替わるカウント
#define EFFECT_KNOCKDOWN_MAX						(30)		// 最大数出現数

// セット座標調整
#define EFFECT_KNOCKDOWN_ADJUSTMENT_X				(0)
#define EFFECT_KNOCKDOWN_ADJUSTMENT_Y				(0)

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
	int						nTypeAnim;				// アニメーションタイプ
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// ヒットサークルフラグ
}EFFECT_KNOCKDOWN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect_knockdown(int type);
void UninitEffect_knockdown(void);
void UpdateEffect_knockdown(void);
void DrawEffect_knockdown(void);
void SetEffect_knockdown(D3DXVECTOR3 vecPos, int nType);
EFFECT_KNOCKDOWN *GetEffect_knockdown(int no);


#endif
