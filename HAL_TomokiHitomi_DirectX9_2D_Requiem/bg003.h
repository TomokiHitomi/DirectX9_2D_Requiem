//=============================================================================
//
// BG003処理 [bg003.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BG003_H_
#define _BG003_H_

#include "main.h"

// マクロ定義
#define NUM_BG003		(2)	// ポリゴン数

#define TEXTURE_GAME_BG003	_T("data/TEXTURE/bg003.png")	// BG003用画像
#define TEXTURE_BG003_SIZE_X	(SCREEN_WIDTH / 2) // テクスチャサイズ
#define TEXTURE_BG003_SIZE_Y	(SCREEN_HEIGHT / 2) // 同上

#define TEXTURE_BG003_R			(180) // テクスチャカラー赤
#define TEXTURE_BG003_G			(180) // テクスチャカラー緑
#define TEXTURE_BG003_B			(180) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_BG003	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BG003	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BG003			(TEXTURE_PATTERN_DIVIDE_X_BG003*TEXTURE_PATTERN_DIVIDE_Y_BG003)	// アニメーションパターン数
#define TIME_ANIMATION_BG003				(4)	// アニメーションの切り替わるカウント

#define BG003_MAX					(1)	// BG003の最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// BG003の移動量
	D3DXVECTOR3				rot;					// BG003の回転量
	D3DXVECTOR2				size;					// BG003のテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}BG003;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBg003(int type);
void UninitBg003(void);
void UpdateBg003(void);
void DrawBg003(void);
void SetBg003(void);
BG003 *GetBg003(int no);


#endif
