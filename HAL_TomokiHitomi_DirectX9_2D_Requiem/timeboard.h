//=============================================================================
//
// タイトル処理 [timeboard.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _TIMEBOARD_H_
#define _TIMEBOARD_H_

#include "main.h"

// マクロ定義
#define NUM_TIMEBOARD		(2)	// ポリゴン数

#define TEXTURE_GAME_TIMEBOARD00	_T("data/TEXTURE/timeboard.png")	// タイトル00用画像
#define TEXTURE_TIMEBOARD00_SIZE_X	(396 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_TIMEBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2) // 同上
#define TIMEBOARD_POS_X			(310 * SCREEN_SCALING)	// 初期座標X
#define TIMEBOARD_POS_Y			(53 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_TIMEBOARD			(TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD*TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD)	// アニメーションパターン数
#define TIME_ANIMATION_TIMEBOARD				(4)	// アニメーションの切り替わるカウント

#define TIMEBOARD_MAX					(1)	// スコアボードの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// タイトルの移動量
	D3DXVECTOR3				rot;					// タイトルの回転量
	D3DXVECTOR2				size;					// タイトルのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bPosMoveFlag;			// UIの移動フラグ
	bool					bUse;					// true:使用  false:未使用
}TIMEBOARD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimeboard(int type);
void UninitTimeboard(void);
void UpdateTimeboard(void);
void DrawTimeboard(void);
TIMEBOARD *GetTimeboard(int no);


#endif
