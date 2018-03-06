//=============================================================================
//
// タイトル処理 [level.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "main.h"

// マクロ定義
#define NUM_LEVEL		(2)	// ポリゴン数

#define TEXTURE_GAME_LEVEL00	_T("data/TEXTURE/level.png")	// タイトル00用画像
#define TEXTURE_LEVEL00_SIZE_X	(400 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_LEVEL00_SIZE_Y	(80 * SCREEN_SCALING/2) // 同上

#define LEVEL_POS_X			(SCREEN_CENTER_X)	// 初期座標X
#define LEVEL_POS_Y			(380 * SCREEN_SCALING)				// 初期座標Y
#define LEVEL_SPACING		(75 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_LEVEL	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_LEVEL	(4)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_LEVEL			(TEXTURE_PATTERN_DIVIDE_X_LEVEL*TEXTURE_PATTERN_DIVIDE_Y_LEVEL)	// アニメーションパターン数
#define TIME_ANIMATION_LEVEL				(1)	// アニメーションの切り替わるカウント

#define LEVEL_MAX					(4)	// タイトルの最大数
#define LEVEL_SELECT_PRESS			(40)	// メニュー自動送り開始タイム
#define LEVEL_SELECT_SPEED			(7)		// メニュ－自動送り速度

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
	float					fRadius;					// 半径
	bool					bUse;					// true:使用  false:未使用
}LEVEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLevel(int type);
void UninitLevel(void);
void UpdateLevel(void);
void DrawLevel(void);
void SetLevel(void);
void ReleaseLevel(void);
LEVEL *GetLevel(int no);


#endif
