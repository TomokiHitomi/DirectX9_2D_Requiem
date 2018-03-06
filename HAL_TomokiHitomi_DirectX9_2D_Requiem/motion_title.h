//=============================================================================
//
// ヒットサークル処理 [motion_title.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _MOTION_TITLE_H_
#define _MOTION_TITLE_H_

#include "main.h"

// マクロ定義
#define NUM_MOTION_TITLE						(2)		// ポリゴン数
#define TEXTURE_GAME_MOTION_TITLE		_T("data/TEXTURE/motion_title.png")	// ヒットサークル00用画像
#define TEXTURE_MOTION_TITLE00_SIZE_X			(300 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_MOTION_TITLE00_SIZE_Y			(540 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE	(13)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE	(6)		// アニメパターンのテクスチャ内分割数（Y)

#define MOTION_TITLE_POS_X			(350 * SCREEN_SCALING)		// ポリゴンの初期位置X
#define MOTION_TITLE_POS_Y			(550 * SCREEN_SCALING)		// 同上

#define ANIM_PATTERN_NUM_MOTION_TITLE		(TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE*TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE)	// アニメーションパターン数
#define TIME_ANIMATION_MOTION_TITLE			(10)	// アニメーションの切り替わるカウント
#define MOTION_TITLE_MAX						(1)		// 最大数出現数

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
	bool					bUse;					// 使用フラグ
	bool					bFlap;					// 折り返し
}MOTION_TITLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMotion_title(int type);
void UninitMotion_title(void);
void UpdateMotion_title(void);
void DrawMotion_title(void);
void SetMotion_title(void);
MOTION_TITLE *GetMotion_title(int no);


#endif
