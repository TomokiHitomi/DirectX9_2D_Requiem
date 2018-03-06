//=============================================================================
//
// HOWTOPLAY_CONTROLLER処理 [howtoplay_controller.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _HOWTOPLAY_CONTROLLER_H_
#define _HOWTOPLAY_CONTROLLER_H_

#include "main.h"

// マクロ定義
#define NUM_HOWTOPLAY_CONTROLLER		(2)	// ポリゴン数

#define TEXTURE_GAME_HOWTOPLAY_CONTROLLER	_T("data/TEXTURE/howtoplay_controller.png")	// HOWTOPLAY_CONTROLLER用画像
#define TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X	(1280 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y	(720 * SCREEN_SCALING/2) // 同上

#define HOWTOPLAY_CONTROLLER_POS_X				(SCREEN_CENTER_X)				// 初期座標X
#define HOWTOPLAY_CONTROLLER_POS_Y				(SCREEN_CENTER_Y)	// 初期座標Y

#define TEXTURE_HOWTOPLAY_CONTROLLER_R			(255) // テクスチャカラー赤
#define TEXTURE_HOWTOPLAY_CONTROLLER_G			(255) // テクスチャカラー緑
#define TEXTURE_HOWTOPLAY_CONTROLLER_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_HOWTOPLAY_CONTROLLER			(TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER*TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER)	// アニメーションパターン数
#define TIME_ANIMATION_HOWTOPLAY_CONTROLLER				(4)	// アニメーションの切り替わるカウント

#define HOWTOPLAY_CONTROLLER_MAX					(1)	// HOWTOPLAY_CONTROLLERの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// HOWTOPLAY_CONTROLLERの移動量
	D3DXVECTOR3				rot;					// HOWTOPLAY_CONTROLLERの回転量
	D3DXVECTOR2				size;					// HOWTOPLAY_CONTROLLERのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}HOWTOPLAY_CONTROLLER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHowtoplay_controller(int type);
void UninitHowtoplay_controller(void);
void UpdateHowtoplay_controller(void);
void DrawHowtoplay_controller(void);
HOWTOPLAY_CONTROLLER *GetHowtoplay_controller(int no);


#endif
