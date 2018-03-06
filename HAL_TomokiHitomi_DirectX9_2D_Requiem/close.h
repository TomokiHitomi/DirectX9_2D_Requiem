//=============================================================================
//
// クローズ処理 [close.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _CLOSE_H_
#define _CLOSE_H_

#include "main.h"

// マクロ定義
#define NUM_CLOSE		(2)	// ポリゴン数

#define TEXTURE_GAME_CLOSE00	_T("data/TEXTURE/close.png")	// クローズ00用画像
#define TEXTURE_CLOSE00_SIZE_X	(1000 * SCREEN_SCALING / 2) // テクスチャサイズ
#define TEXTURE_CLOSE00_SIZE_Y	(250  * SCREEN_SCALING / 2) // 同上

#define CLOSE00_POS_X			(SCREEN_CENTER_X)	// 初期座標X
#define CLOSE00_POS_Y			(SCREEN_CENTER_Y)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_CLOSE	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOSE	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_CLOSE			(TEXTURE_PATTERN_DIVIDE_X_CLOSE*TEXTURE_PATTERN_DIVIDE_Y_CLOSE)	// アニメーションパターン数
#define TIME_ANIMATION_CLOSE				(0)	// アニメーションの切り替わるカウント

#define CLOSE_MAX					(1)	// クローズの最大数
#define CLOSE_SE_COUNTMAX			(70)	// SE再生カウント
#define CLOSE_COUNTMAX				(630)	// 画面遷移カウント


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// クローズの移動量
	D3DXVECTOR3				rot;					// クローズの回転量
	D3DXVECTOR2				size;					// クローズのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bClearFlag;				// クリアフラグ
	bool					bUse;					// true:使用  false:未使用
}CLOSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitClose(int type);
void UninitClose(void);
void UpdateClose(void);
void DrawClose(void);
CLOSE *GetClose(int no);


#endif
