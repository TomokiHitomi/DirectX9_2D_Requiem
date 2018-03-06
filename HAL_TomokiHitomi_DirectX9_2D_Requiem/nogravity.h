//=============================================================================
//
// ヒットサークル処理 [nogravity.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _NOGRAVITY_H_
#define _NOGRAVITY_H_

#include "main.h"

// マクロ定義
#define NUM_NOGRAVITY						(2)		// ポリゴン数
#define TEXTURE_GAME_NOGRAVITY00		_T("data/TEXTURE/nogravity.png")	// ヒットサークル00用画像
#define TEXTURE_NOGRAVITY00_SIZE_X			(20 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_NOGRAVITY00_SIZE_Y			(20 * SCREEN_SCALING/2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY	(1)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY	(1)		// アニメパターンのテクスチャ内分割数（Y)

#define TEXTURE_NOGRAVITY00_SCALING_SPEED	(25)		// 拡大縮小スピード
#define TEXTURE_NOGRAVITY00_SCALING_MAX		(1800 * SCREEN_SCALING)		// 最大拡大値


#define ANIM_PATTERN_NUM_NOGRAVITY			(TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY*TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY)	// アニメーションパターン数
#define TIME_ANIMATION_NOGRAVITY			(4)		// アニメーションの切り替わるカウント
#define NOGRAVITY_MAX						(1)		// ヒットサークルの最大数

#define NOGRAVITY_ALPHA						(100)	// 無重力サークルのα値

// ヒットサークルのセット座標調整
#define NOGRAVITY_ADJUSTMENT_X				(0)
#define NOGRAVITY_ADJUSTMENT_Y				(-5)

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
	int						nScaling;				// 拡大・縮小
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// ヒットサークルフラグ
}NOGRAVITY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitNogravity(int type);
void UninitNogravity(void);
void UpdateNogravity(void);
void DrawNogravity(void);
NOGRAVITY *GetNogravity(int no);


#endif
