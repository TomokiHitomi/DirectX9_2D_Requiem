//=============================================================================
//
// FADE処理 [fade.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

// マクロ定義
#define NUM_FADE		(2)	// ポリゴン数

#define TEXTURE_GAME_FADE	_T("data/TEXTURE/fade.jpg")	// FADE用画像
#define TEXTURE_FADE_SIZE_X	(1280 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_FADE_SIZE_Y	(960 * SCREEN_SCALING/2) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_FADE	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_FADE	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_FADE			(TEXTURE_PATTERN_DIVIDE_X_FADE*TEXTURE_PATTERN_DIVIDE_Y_FADE)	// アニメーションパターン数
#define TIME_ANIMATION_FADE				(4)	// アニメーションの切り替わるカウント

#define FADE_MAX					(1)		// FADEの最大数
#define FADE_ALPHA_MAX				(255)	// フェード最大アルファ値
#define FADE_ALPHA_MID				(150)	// フェードアルファ値
#define FADE_SPEED					(7)		// フェードスピード
#define FADE_COMPLETE				(FADE_ALPHA_MAX/FADE_SPEED)

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// FADEの移動量
	D3DXVECTOR3				rot;					// FADEの回転量
	D3DXVECTOR2				size;					// FADEのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nAlphaCount;			// アルファ値のカウント
	int						nFadeFlag;				// フェードフラグ
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径

	bool					bUse;					// true:使用  false:未使用
}FADE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(int type);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(int nFade, int nFadeFlag);
FADE *GetFade(int no);


#endif
