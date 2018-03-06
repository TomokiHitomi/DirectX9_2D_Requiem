//=============================================================================
//
// COPYRIGHT処理 [copyright.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _COPYRIGHT_H_
#define _COPYRIGHT_H_

#include "main.h"

// マクロ定義
#define NUM_COPYRIGHT		(2)	// ポリゴン数

#define TEXTURE_GAME_COPYRIGHT	_T("data/TEXTURE/copyright.png")	// COPYRIGHT用画像
#define TEXTURE_COPYRIGHT_SIZE_X	(300 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_COPYRIGHT_SIZE_Y	(30 * SCREEN_SCALING/2) // 同上

#define COPYRIGHT_POS_X				(SCREEN_CENTER_X)	// 初期座標X
#define COPYRIGHT_POS_Y				(693 * SCREEN_SCALING)				// 初期座標Y

#define TEXTURE_COPYRIGHT_R			(255) // テクスチャカラー赤
#define TEXTURE_COPYRIGHT_G			(255) // テクスチャカラー緑
#define TEXTURE_COPYRIGHT_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_COPYRIGHT	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_COPYRIGHT	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_COPYRIGHT			(TEXTURE_PATTERN_DIVIDE_X_COPYRIGHT*TEXTURE_PATTERN_DIVIDE_Y_COPYRIGHT)	// アニメーションパターン数
#define TIME_ANIMATION_COPYRIGHT				(4)	// アニメーションの切り替わるカウント

#define COPYRIGHT_MAX					(1)	// COPYRIGHTの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// COPYRIGHTの移動量
	D3DXVECTOR3				rot;					// COPYRIGHTの回転量
	D3DXVECTOR2				size;					// COPYRIGHTのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}COPYRIGHT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCopyright(int type);
void UninitCopyright(void);
void UpdateCopyright(void);
void DrawCopyright(void);
COPYRIGHT *GetCopyright(int no);


#endif
