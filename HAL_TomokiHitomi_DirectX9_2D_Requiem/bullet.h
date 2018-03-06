//=============================================================================
//
// バレット01処理 [bullet.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include <time.h>

// マクロ定義
#define NUM_BULLET						(2)					// ポリゴン数

#define TEXTURE_GAME_BULLET	_T("data/TEXTURE/notes.png")	// バレット用画像

#define TEXTURE_BULLET_SIZE_X			(27 * SCREEN_SCALING / 2)				// 横テクスチャサイズ
#define TEXTURE_BULLET_SIZE_Y			(27 * SCREEN_SCALING / 2)				// 縦テクスチャサイズ

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(4)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(5)			// アニメパターンのテクスチャ内分割数（Y)

// アニメーションパターン数
#define ANIM_PATTERN_NU_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET * TEXTURE_PATTERN_DIVIDE_Y_BULLET)
#define TIME_ANIMATION_BULLET			(4)					// アニメーションの切り替わるカウント

#define BULLET_MAX						(255)				// バレット01の最大数

#define BULLET01_ROTATION				(0.05f)				// バレット01の回転量
#define BULLET01_COOLDOWN				(5)					// バレット01連射速度（数値が大きいと遅い）

#define BULLET_ALPHA					(200)				// バレットの透明度

// バレットの移動速度
#define BULLET00_SPEED_MAX				(20 * SCREEN_SCALING)	// バレット00の最大速度
#define BULLET01_SPEED_MAX				(20 * SCREEN_SCALING)	// バレット01の最大速度
#define BULLET02_SPEED_MAX				(50 * SCREEN_SCALING)	// バレット02の最大速度
#define BULLET03_SPEED_MAX				(20 * SCREEN_SCALING)	// バレット03の最大速度

#define BULLET02_SPEED_ACCELERATOR		(0.2 * SCREEN_SCALING)	// バレット02の加速度

// バレットの連射速度
#define BULLET00_RELOAD_SPEED			(8)		// バレット00
#define BULLET01_RELOAD_SPEED			(4)		// バレット01
#define BULLET02_RELOAD_SPEED			(4)		// バレット02
#define BULLET03_RELOAD_SPEED			(4)		// バレット03

// バレットのセット座標調整
#define BULLET_ADJUSTMENT_X				(20 * SCREEN_SCALING)
#define BULLET_ADJUSTMENT_Y				(-45 * SCREEN_SCALING)

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// バレット01の座標
	D3DXVECTOR3				rot;					// バレット01の回転量
	D3DXVECTOR2				size;					// バレット01のテクスチャサイズ(x,y)
	D3DXVECTOR3				vecTa;					// 距離
	D3DXVECTOR2				move;					// 移動量
	D3DXVECTOR3				vecDestination;			// バレットの移動先

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nBulletType;			// バレットのタイプ
	int						nBulletCount;			// バレットカウント
	int						nAngleType;				// バレットの角度タイプ
	int						nPatternHoming;			// ホーミングパターンナンバー
	int						nHomingFlag;			// バレットのホーミングフラグ
	int						nDirection;				// バレットの向き
	int						nTarget;				// バレットのターゲット

	float					fBulletSpeed;			// バレットの移動速度
	float					fAngle;					// バレットの角度
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径

	bool					bUse;					// バレットの使用フラグ
	bool					bTextureUse;			// バレットのテクスチャフラグ

}BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBullet(int no);
void SetBullet(D3DXVECTOR3 pos, int nBulletType);
void InitStatusBullet(int nBullet);

#endif
