//=============================================================================
//
// タイトル処理 [scoreboard.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "main.h"

// マクロ定義
#define NUM_SCOREBOARD		(2)	// ポリゴン数

#define TEXTURE_GAME_SCOREBOARD00	_T("data/TEXTURE/scoreboard.png")	// タイトル00用画像
#define TEXTURE_SCOREBOARD00_SIZE_X	(612 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_SCOREBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2) // 同上
#define SCOREBOARD_POS_X			(865 * SCREEN_SCALING)	// 初期座標X
#define SCOREBOARD_POS_Y			(53 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_SCOREBOARD			(TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD*TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD)	// アニメーションパターン数
#define TIME_ANIMATION_SCOREBOARD				(4)	// アニメーションの切り替わるカウント

#define SCOREBOARD_MAX					(1)	// スコアボードの最大数


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
}SCOREBOARD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScoreboard(int type);
void UninitScoreboard(void);
void UpdateScoreboard(void);
void DrawScoreboard(void);
SCOREBOARD *GetScoreboard(int no);


#endif
