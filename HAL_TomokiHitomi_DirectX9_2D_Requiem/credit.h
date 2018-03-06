//=============================================================================
//
// CREDIT処理 [credit.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _CREDIT_H_
#define _CREDIT_H_

#include "main.h"

// マクロ定義
#define NUM_CREDIT		(2)	// ポリゴン数

#define TEXTURE_GAME_CREDIT	_T("data/TEXTURE/credit.png")	// CREDIT用画像
#define TEXTURE_CREDIT_SIZE_X	(1280 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_CREDIT_SIZE_Y	(648 * SCREEN_SCALING/2) // 同上

#define CREDIT_POS_X				(SCREEN_CENTER_X)			// 初期座標X
#define CREDIT_POS_Y				(SCREEN_CENTER_Y)			// 初期座標Y

#define TEXTURE_CREDIT_R			(255) // テクスチャカラー赤
#define TEXTURE_CREDIT_G			(255) // テクスチャカラー緑
#define TEXTURE_CREDIT_B			(255) // テクスチャカラー青

#define TEXTURE_PATTERN_DIVIDE_X_CREDIT	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_CREDIT	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_CREDIT			(TEXTURE_PATTERN_DIVIDE_X_CREDIT*TEXTURE_PATTERN_DIVIDE_Y_CREDIT)	// アニメーションパターン数
#define TIME_ANIMATION_CREDIT				(4)	// アニメーションの切り替わるカウント

#define CREDIT_MAX					(1)	// CREDITの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// CREDITの移動量
	D3DXVECTOR3				rot;					// CREDITの回転量
	D3DXVECTOR2				size;					// CREDITのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}CREDIT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCredit(int type);
void UninitCredit(void);
void UpdateCredit(void);
void DrawCredit(void);
void SetCredit(void);
CREDIT *GetCredit(int no);


#endif
