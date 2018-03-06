//=============================================================================
//
// ファンネル処理 [funnel.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"
#include <time.h>

// マクロ定義
#define NUM_BARRIER						(2)					// ポリゴン数

#define TEXTURE_GAME_BARRIER	_T("data/TEXTURE/barrier.png")	// ファンネル用画像

#define TEXTURE_BARRIER_SIZE_X			(100 * SCREEN_SCALING/2)				// 横テクスチャサイズ
#define TEXTURE_BARRIER_SIZE_Y			(100 * SCREEN_SCALING/2)				// 縦テクスチャサイズ

// 当たり判定用サイズ
#define BARRIER_CUSTOM_SIZE_X	(70 * SCREEN_SCALING/2)
#define BARRIER_CUSTOM_SIZE_Y	(70 * SCREEN_SCALING/2)

#define TEXTURE_PATTERN_DIVIDE_X_BARRIER	(5)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BARRIER	(6)			// アニメパターンのテクスチャ内分割数（Y)

// アニメーションパターン数
#define ANIM_PATTERN_NU_BARRIER			(TEXTURE_PATTERN_DIVIDE_X_BARRIER*TEXTURE_PATTERN_DIVIDE_Y_BARRIER)
#define TIME_ANIMATION_BARRIER			(4)					// アニメーションの切り替わるカウント

#define BARRIER_MAX						(3)				// ファンネルの最大数
#define BARRIER_TYPE_MAX					(2)				// ファンネルのタイプ最大数

#define BARRIER_ALPHA_MAX				(255)			// ファンネルの最大α値
#define BARRIER_ALPHA					(100)			// ファンネルの最小α値
#define BARRIER_ALPHA_MIN				(BARRIER_ALPHA_MAX - BARRIER_ALPHA)			// ファンネルのα値

#define BARRIER01_ROTATION				(0.05f)				// ファンネルの回転量
#define BARRIER01_COOLDOWN				(5)					// ファンネル連射速度（数値が大きいと遅い）

// ファンネルの移動速度
#define BARRIER00_SPEED_MAX				(20)	// ファンネル00の最大速度
#define BARRIER01_SPEED_MAX				(5)	// ファンネル01の最大速度
#define BARRIER02_SPEED_MAX				(50)	// ファンネル02の最大速度

#define BARRIER02_SPEED_ACCELERATOR		(0.2)	// ファンネル02の加速度

// ファンネルの連射速度
#define BARRIER00_RELOAD_SPEED			(10)	// ファンネル00
#define BARRIER01_RELOAD_SPEED			(5)		// ファンネル01
#define BARRIER02_RELOAD_SPEED			(5)		// ファンネル02

// ファンネルバレットの連射速度
#define BARRIER_BULLET_RELOAD_SPEED		(4)

#define BARRIER_DISTANCE_MAX				(80 * SCREEN_SCALING)	// ファンネルと設置対象の距離
#define BARRIER_INJECTION_SPEED			(2.0f)	// ファンネルの射出速度
#define BARRIER_ROTATIONAL_SPEED			(40)	// ファンネルの回転速度

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// ファンネル01の座標
	D3DXVECTOR3				rot;					// ファンネル01の回転量
	D3DXVECTOR2				size;					// ファンネル01のテクスチャサイズ(x,y)
	D3DXVECTOR3				vecTa;					// 距離
	D3DXVECTOR2				move;					// 移動量
	D3DXVECTOR3				vecDestination;			// ファンネルの移動先

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nBarrierType;			// ファンネルのタイプ
	int						nBarrierCount;			// ファンネルカウント
	int						nAngleType;				// ファンネルの角度タイプ
	int						nPatternHoming;			// ホーミングパターンナンバー
	int						nHomingFlag;			// ファンネルのホーミングフラグ
	int						nDirection;				// ファンネルの向き
	int						nTarget;				// ファンネルのターゲット
	int						nReloadBullet;			// ファンネルバレットのリロードカウント
	int						nAlpha;					// ファンネルのα値

	float					fBarrierSpeed;			// ファンネルの移動速度
	float					fAngle;					// ファンネルの角度
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	float					fDistance;				// プレイヤーとファンネルの距離

	bool					bUse;					// ファンネルの使用フラグ
	bool					bTextureUse;			// ファンネルのテクスチャフラグ
	bool					bReload;				// ファンネルバレットのリロードフラグ

}BARRIER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBarrier(int type);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
BARRIER *GetBarrier(int no);
void SetBarrier(D3DXVECTOR3 pos);
void ReleaseBarrier(void);
void InitStatusBarrier(int nBarrier);

#endif
