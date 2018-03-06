//=============================================================================
//
// HOWTOPLAY処理 [howtoplay.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _HOWTOPLAY_H_
#define _HOWTOPLAY_H_

#include "main.h"

// マクロ定義
#define NUM_HOWTOPLAY		(2)	// ポリゴン数

#define TEXTURE_GAME_HOWTOPLAY	_T("data/TEXTURE/howtoplay.png")	// HOWTOPLAY用画像
#define TEXTURE_HOWTOPLAY_SIZE_X	(700 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_HOWTOPLAY_SIZE_Y	(700 * SCREEN_SCALING/2) // 同上

#define HOWTOPLAY_POS_X				(920 * SCREEN_SCALING)				// 初期座標X
#define HOWTOPLAY_POS_Y				(SCREEN_CENTER_Y)	// 初期座標Y

#define TEXTURE_HOWTOPLAY_R			(255) // テクスチャカラー赤
#define TEXTURE_HOWTOPLAY_G			(255) // テクスチャカラー緑
#define TEXTURE_HOWTOPLAY_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_HOWTOPLAY			(TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY*TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY)	// アニメーションパターン数
#define TIME_ANIMATION_HOWTOPLAY				(4)	// アニメーションの切り替わるカウント

#define HOWTOPLAY_MAX					(1)	// HOWTOPLAYの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// HOWTOPLAYの移動量
	D3DXVECTOR3				rot;					// HOWTOPLAYの回転量
	D3DXVECTOR2				size;					// HOWTOPLAYのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}HOWTOPLAY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHowtoplay(int type);
void UninitHowtoplay(void);
void UpdateHowtoplay(void);
void DrawHowtoplay(void);
HOWTOPLAY *GetHowtoplay(int no);


#endif
