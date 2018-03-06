//=============================================================================
//
// タイトル処理 [pressenter.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _PRESSENTER_H_
#define _PRESSENTER_H_

#include "main.h"

// マクロ定義
#define NUM_PRESSENTER		(2)	// ポリゴン数

#define TEXTURE_GAME_PRESSENTER00	_T("data/TEXTURE/pressenter.png")	// タイトル00用画像
#define TEXTURE_PRESSENTER00_SIZE_X	(700 * SCREEN_SCALING/2)		// テクスチャサイズ
#define TEXTURE_PRESSENTER00_SIZE_Y	(100 * SCREEN_SCALING/2)		// 同上
#define PRESSENTER_POS_X				(500 * SCREEN_SCALING)		// 初期座標X
#define PRESSENTER_POS_Y				(630 * SCREEN_SCALING)		// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_PRESSENTER	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PRESSENTER			(TEXTURE_PATTERN_DIVIDE_X_PRESSENTER*TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER)	// アニメーションパターン数
#define TIME_ANIMATION_PRESSENTER				(4)	// アニメーションの切り替わるカウント

#define PRESSENTER_MAX					(1)		// タイトルの最大数
#define PRESSENTER_ALPHA_MAX			(255)	// フェード最大アルファ値
#define PRESSENTER_ALPHA_MIN			(150)	// フェード最大アルファ値
#define PRESSENTER_ALPHA_UP_SPEED		(3)		// フェード最大アルファ値
#define PRESSENTER_ALPHA_DOWN_SPEED		(3)		// フェード最大アルファ値

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
	int						nAlphaCount;			// フェードカウント

	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径

	bool					bUse;					// true:使用  false:未使用
	bool					bAlphaFlag;				// アルファフラグ
}PRESSENTER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPressenter(int type);
void UninitPressenter(void);
void UpdatePressenter(void);
void DrawPressenter(void);
PRESSENTER *GetPressenter(int no);


#endif
