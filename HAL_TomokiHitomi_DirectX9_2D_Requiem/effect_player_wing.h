//=============================================================================
//
// ヒットサークル処理 [effect_player_wing.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _EFFECT_PLAYER_WING_H_
#define _EFFECT_PLAYER_WING_H_

#include "main.h"

// マクロ定義
#define NUM_EFFECT_PLAYER_WING						(2)		// ポリゴン数
#define TEXTURE_GAME_EFFECT_PLAYER_WING		_T("data/TEXTURE/effect_player_wing.png")	// ヒットサークル00用画像
#define TEXTURE_EFFECT_PLAYER_WING00_SIZE_X			(120 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y			(120 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING	(5)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING	(6)		// アニメパターンのテクスチャ内分割数（Y)

#define EFFECT_PLAYER_WING_LOOP_MIN					(5)
#define EFFECT_PLAYER_WING_LOOP_MAX					(25)

#define EFFECT_PLAYER_WING_ALPHA_MAX				(255)

#define ANIM_PATTERN_NUM_EFFECT_PLAYER_WING			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT_PLAYER_WING			(3)		// アニメーションの切り替わるカウント
#define EFFECT_PLAYER_WING_MAX						(1)		// 最大数出現数

// セット座標調整
#define EFFECT_PLAYER_WING_ADJUSTMENT_X				(0)
#define EFFECT_PLAYER_WING_ADJUSTMENT_Y				(-30 * SCREEN_SCALING)

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
	int						nAlpha;					// α値
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bLoop;					// ループフラグ
	bool					bUse;					// アクティブフラグ
}EFFECT_PLAYER_WING;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect_player_wing(int type);
void UninitEffect_player_wing(void);
void UpdateEffect_player_wing(void);
void DrawEffect_player_wing(void);
void SetEffect_player_wing();
void ReleaseEffect_player_wing();
EFFECT_PLAYER_WING *GetEffect_player_wing(int no);


#endif
