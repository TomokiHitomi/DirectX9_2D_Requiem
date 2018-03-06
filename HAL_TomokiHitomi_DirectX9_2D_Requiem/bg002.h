//=============================================================================
//
// BG002処理 [bg002.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BG002_H_
#define _BG002_H_

#include "main.h"

// マクロ定義
#define NUM_BG002		(2)	// ポリゴン数

#define TEXTURE_GAME_BG002	_T("data/TEXTURE/bg002.png")	// BG002用画像
#define TEXTURE_BG002_SIZE_X	(SCREEN_WIDTH / 2) // テクスチャサイズ
#define TEXTURE_BG002_SIZE_Y	(SCREEN_HEIGHT / 2) // 同上

#define TEXTURE_BG002_R			(180) // テクスチャカラー赤
#define TEXTURE_BG002_G			(180) // テクスチャカラー緑
#define TEXTURE_BG002_B			(180) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_BG002	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BG002	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BG002			(TEXTURE_PATTERN_DIVIDE_X_BG002*TEXTURE_PATTERN_DIVIDE_Y_BG002)	// アニメーションパターン数
#define TIME_ANIMATION_BG002				(4)	// アニメーションの切り替わるカウント

#define BG002_MAX					(1)	// BG002の最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// BG002の移動量
	D3DXVECTOR3				rot;					// BG002の回転量
	D3DXVECTOR2				size;					// BG002のテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}BG002;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBg002(int type);
void UninitBg002(void);
void UpdateBg002(void);
void DrawBg002(void);
void SetBg002(void);
BG002 *GetBg002(int no);


#endif
