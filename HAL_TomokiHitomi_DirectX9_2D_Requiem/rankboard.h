//=============================================================================
//
// タイトル処理 [rankboard.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _RANKBOARD_H_
#define _RANKBOARD_H_

#include "main.h"

// マクロ定義
#define NUM_RANKBOARD		(2)	// ポリゴン数

#define TEXTURE_GAME_RANKBOARD00	_T("data/TEXTURE/rankboard.png")	// タイトル00用画像
#define TEXTURE_RANKBOARD00_SIZE_X	(225 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_RANKBOARD00_SIZE_Y	(290 * SCREEN_SCALING/2)	// 同上
#define RANKBOARD_POS_X			(1050 * SCREEN_SCALING)	// 初期座標X
#define RANKBOARD_POS_Y			(530 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_RANKBOARD	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_RANKBOARD			(TEXTURE_PATTERN_DIVIDE_X_RANKBOARD*TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD)	// アニメーションパターン数
#define TIME_ANIMATION_RANKBOARD				(4)	// アニメーションの切り替わるカウント

#define RANKBOARD_MAX					(1)	// トータルスコアボードの最大数
#define RANKBOARD_MAX					(1)	// トータルスコアボードの最大数


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
	bool					bUse;					// true:使用  false:未使用
}RANKBOARD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRankboard(int type);
void UninitRankboard(void);
void UpdateRankboard(void);
void DrawRankboard(void);
RANKBOARD *GetRankboard(int no);


#endif
