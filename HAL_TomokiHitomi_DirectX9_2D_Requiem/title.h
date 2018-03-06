//=============================================================================
//
// タイトル処理 [title.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// マクロ定義
#define NUM_TITLE		(2)	// ポリゴン数

#define TEXTURE_GAME_TITLE00	_T("data/TEXTURE/title_logo.png")	// タイトル00用画像
#define TEXTURE_TITLE00_SIZE_X	(800 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_TITLE00_SIZE_Y	(1000/3 * SCREEN_SCALING/2) // 同上

#define TITLE_POS_X				(SCREEN_CENTER_X)				// 初期座標X
#define TITLE_POS_Y				(220 * SCREEN_SCALING)			// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_TITLE	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_TITLE	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_TITLE			(TEXTURE_PATTERN_DIVIDE_X_TITLE*TEXTURE_PATTERN_DIVIDE_Y_TITLE)	// アニメーションパターン数
#define TIME_ANIMATION_TITLE				(4)	// アニメーションの切り替わるカウント

#define TITLE_MAX					(1)	// タイトルの最大数

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
}TITLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLE *GetTitle(int no);


#endif
