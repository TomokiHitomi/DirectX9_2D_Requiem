//=============================================================================
//
// ヒットサークル処理 [effect_close.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _EFFECT_CLOSE_H_
#define _EFFECT_CLOSE_H_

#include "main.h"

// マクロ定義
#define NUM_EFFECT_CLOSE						(2)		// ポリゴン数
#define TEXTURE_GAME_EFFECT_CLOSE		_T("data/TEXTURE/effect_close.png")	// ヒットサークル00用画像
#define TEXTURE_EFFECT_CLOSE00_SIZE_X			(1280 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_EFFECT_CLOSE00_SIZE_Y			(480 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE	(1)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE	(15)		// アニメパターンのテクスチャ内分割数（Y)

#define EFFECT_CLOSE_SKIPANIME00	(0)
#define EFFECT_CLOSE_SKIPANIME14	(14)

#define EFFECT_CLOSE_POS_X			(SCREEN_CENTER_X)		// ポリゴンの初期位置X
#define EFFECT_CLOSE_POS_Y			(SCREEN_CENTER_Y)		// 同上

#define ANIM_PATTERN_NUM_EFFECT_CLOSE			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT_CLOSE			(10)		// アニメーションの切り替わるカウント
#define EFFECT_CLOSE_MAX						(1)		// 最大数出現数

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
}EFFECT_CLOSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect_close(int type);
void UninitEffect_close(void);
void UpdateEffect_close(void);
void DrawEffect_close(void);
void SetEffect_close(void);
EFFECT_CLOSE *GetEffect_close(int no);


#endif
