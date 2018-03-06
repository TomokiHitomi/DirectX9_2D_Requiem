//=============================================================================
//
// タイトル処理 [thank.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _THANK_H_
#define _THANK_H_

#include "main.h"

// マクロ定義
#define NUM_THANK		(2)	// ポリゴン数

#define TEXTURE_GAME_THANK00	_T("data/TEXTURE/thank.png")	// タイトル00用画像
#define TEXTURE_THANK00_SIZE_X	(1200 * SCREEN_SCALING/2)		// テクスチャサイズ
#define TEXTURE_THANK00_SIZE_Y	(200 * SCREEN_SCALING/2)		// 同上
#define THANK_POS_X				(SCREEN_CENTER_X)		// 初期座標X
#define THANK_POS_Y				(SCREEN_CENTER_Y)		// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_THANK	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_THANK	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_THANK			(TEXTURE_PATTERN_DIVIDE_X_THANK*TEXTURE_PATTERN_DIVIDE_Y_THANK)	// アニメーションパターン数
#define TIME_ANIMATION_THANK				(4)	// アニメーションの切り替わるカウント

#define THANK_MAX					(1)		// タイトルの最大数
#define THANK_ALPHA_MAX				(255)	// フェード最大アルファ値
#define THANK_ALPHA_SPEED			(5)		// フェードスピード
#define THANK_SCENE_COUNT			(200)	// シーン遷移までのカウント

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
	int						nAlphaCount;			// フェードカウント
	int						nSceneCount;			// シーン遷移カウント

	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径

	bool					bUse;					// true:使用  false:未使用
}THANK;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitThank(int type);
void UninitThank(void);
void UpdateThank(void);
void DrawThank(void);
THANK *GetThank(int no);


#endif
