//=============================================================================
//
// タイトル処理 [totalboard.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _TOTALBOARD_H_
#define _TOTALBOARD_H_

#include "main.h"

// マクロ定義
#define NUM_TOTALBOARD		(2)	// ポリゴン数

#define TEXTURE_GAME_TOTALBOARD00	_T("data/TEXTURE/totalboard.png")	// タイトル00用画像
#define TEXTURE_TOTALBOARD00_SIZE_X	(768 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_TOTALBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2)	// 同上
#define TOTALBOARD_POS_X			(490 * SCREEN_SCALING)	// 初期座標X
#define TOTALBOARD_POS_Y			(530 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_TOTALBOARD			(TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD*TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD)	// アニメーションパターン数
#define TIME_ANIMATION_TOTALBOARD				(4)	// アニメーションの切り替わるカウント

#define TOTALBOARD_MAX					(1)	// トータルスコアボードの最大数


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
}TOTALBOARD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTotalboard(int type);
void UninitTotalboard(void);
void UpdateTotalboard(void);
void DrawTotalboard(void);
TOTALBOARD *GetTotalboard(int no);


#endif
