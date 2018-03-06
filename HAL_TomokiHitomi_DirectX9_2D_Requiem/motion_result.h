//=============================================================================
//
// ヒットサークル処理 [motion_result.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _MOTION_RESULT_H_
#define _MOTION_RESULT_H_

#include "main.h"

// マクロ定義
#define NUM_MOTION_RESULT						(2)		// ポリゴン数
#define TEXTURE_GAME_MOTION_RESULT		_T("data/TEXTURE/motion_result.png")	// ヒットサークル00用画像
#define TEXTURE_MOTION_RESULT00_SIZE_X			(350 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_MOTION_RESULT00_SIZE_Y			(350 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT	(10)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT	(9)		// アニメパターンのテクスチャ内分割数（Y)

#define MOTION_RESULT_POS_X			(810 * SCREEN_SCALING)		// ポリゴンの初期位置X
#define MOTION_RESULT_POS_Y			(450 * SCREEN_SCALING)		// 同上

#define ANIM_PATTERN_NUM_MOTION_RESULT		(84)	// アニメーションパターン数
#define TIME_ANIMATION_MOTION_RESULT			(6)	// アニメーションの切り替わるカウント
#define MOTION_RESULT_MAX						(1)		// 最大数出現数

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 移動量
	D3DXVECTOR3				rot;					// 回転量
	D3DXVECTOR2				size;					// テクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// 使用フラグ
}MOTION_RESULT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMotion_result(int type);
void UninitMotion_result(void);
void UpdateMotion_result(void);
void DrawMotion_result(void);
void SetMotion_result(void);
MOTION_RESULT *GetMotion_result(int no);


#endif
