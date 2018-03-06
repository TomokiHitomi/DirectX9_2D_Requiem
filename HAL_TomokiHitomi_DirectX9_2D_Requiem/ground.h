//=============================================================================
//
// タイトル処理 [ground.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _GROUND_H_
#define _GROUND_H_

#include "main.h"

// マクロ定義
#define NUM_GROUND		(2)	// ポリゴン数

#define TEXTURE_GAME_GROUND00	_T("data/TEXTURE/ground.png")	// タイトル00用画像
#define TEXTURE_GROUND_SIZE_X	(300 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_GROUND_SIZE_Y	(100 * SCREEN_SCALING/2) // 同上
#define GROUND_POS_X			(TEXTURE_GROUND_SIZE_X)	// 初期座標X
#define GROUND_POS_Y			(SCREEN_HEIGHT-10)		// 初期座標Y

#define TEXTURE_GROUND_R			(220) // テクスチャカラー赤
#define TEXTURE_GROUND_G			(220) // テクスチャカラー緑
#define TEXTURE_GROUND_B			(220) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_GROUND	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_GROUND	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_GROUND			(TEXTURE_PATTERN_DIVIDE_X_GROUND*TEXTURE_PATTERN_DIVIDE_Y_GROUND)	// アニメーションパターン数
#define TIME_ANIMATION_GROUND				(4)	// アニメーションの切り替わるカウント

#define GROUND_MAX					(6)		// タイトルの最大数
#define GROUND_SPEED				(1.5f * SCREEN_SCALING)	// スクロール速度

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
}GROUND;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGround(int type);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);
GROUND *GetGround(int no);


#endif
