//=============================================================================
//
// タイトル処理 [rank.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _RANK_H_
#define _RANK_H_

#include "main.h"

// マクロ定義
#define NUM_RANK		(2)	// ポリゴン数

#define TEXTURE_GAME_RANK00	_T("data/TEXTURE/rank.png")	// タイトル00用画像
#define TEXTURE_RANK00_SIZE_X	(135 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_RANK00_SIZE_Y	(180 * SCREEN_SCALING/2)	// 同上
#define RANK_POS_X			(1050 * SCREEN_SCALING)	// 初期座標X
#define RANK_POS_Y			(577 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_RANK	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_RANK	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_RANK			(TEXTURE_PATTERN_DIVIDE_X_RANK*TEXTURE_PATTERN_DIVIDE_Y_RANK)	// アニメーションパターン数
#define TIME_ANIMATION_RANK				(4)	// アニメーションの切り替わるカウント

#define RANK_MAX					(1)			// トータルスコアボードの最大数

#define RANK_S						(800000000)		// Sランク表示値
#define RANK_A						(600000000)		// Aランク表示値
#define RANK_B						(450000000)		// Bランク表示値
#define RANK_C						(250000000)		// Cランク表示値


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
}RANK;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRank(int type);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);
RANK *GetRank(int no);


#endif
