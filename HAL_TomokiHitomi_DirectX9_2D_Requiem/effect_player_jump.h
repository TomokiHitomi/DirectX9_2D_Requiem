//=============================================================================
//
// ヒットサークル処理 [effect_player_jump.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _EFFECT_PLAYER_JUMP_H_
#define _EFFECT_PLAYER_JUMP_H_

#include "main.h"

// マクロ定義
#define NUM_EFFECT_PLAYER_JUMP						(2)		// ポリゴン数
#define TEXTURE_GAME_EFFECT_PLAYER_JUMP		_T("data/TEXTURE/effect_player_jump.png")	// ヒットサークル00用画像
#define TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X			(160 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y			(60 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP	(1)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP	(7)		// アニメパターンのテクスチャ内分割数（Y)

#define ANIM_PATTERN_NUM_EFFECT_PLAYER_JUMP			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT_PLAYER_JUMP			(3)		// アニメーションの切り替わるカウント
#define EFFECT_PLAYER_JUMP_MAX						(2)		// 最大数出現数

// セット座標調整
#define EFFECT_PLAYER_JUMP_ADJUSTMENT_X				(0)
#define EFFECT_PLAYER_JUMP_ADJUSTMENT_Y				(50 * SCREEN_SCALING)

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
}EFFECT_PLAYER_JUMP;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect_player_jump(int type);
void UninitEffect_player_jump(void);
void UpdateEffect_player_jump(void);
void DrawEffect_player_jump(void);
void SetEffect_player_jump(D3DXVECTOR3 vecPos);
EFFECT_PLAYER_JUMP *GetEffect_player_jump(int no);


#endif
