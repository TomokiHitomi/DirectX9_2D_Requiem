//=============================================================================
//
// エネミーバレット00処理 [enemybullet.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"
#include <time.h>

// マクロ定義
#define NUM_ENEMYBULLET						(2)					// ポリゴン数

#define TEXTURE_GAME_ENEMYBULLET	_T("data/TEXTURE/enemybullet.png")	// エネミーバレット0000用画像
#define TEXTURE_ENEMYBULLET_SIZE_X			(27 * SCREEN_SCALING/2)				// 横テクスチャサイズ
#define TEXTURE_ENEMYBULLET_SIZE_Y			(27 * SCREEN_SCALING/2)				// 縦テクスチャサイズ

// 当たり判定用サイズ ノーマル
#define ENEMYBULLET_CUSTOM_SIZE_NORMAL_X	(22 * SCREEN_SCALING/2)
#define ENEMYBULLET_CUSTOM_SIZE_NORMAL_Y	(22 * SCREEN_SCALING/2)

// 当たり判定用サイズ スモール
#define ENEMYBULLET_CUSTOM_SIZE_SMALL_X		(16 * SCREEN_SCALING/2)
#define ENEMYBULLET_CUSTOM_SIZE_SMALL_Y		(16 * SCREEN_SCALING/2)

// 設定値以降のテクスチャはスモール
#define ENEMYBULLET_SIZE_SMALL_NUM		(18)


#define TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET	(9)			// テクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET	(3)			// テクスチャ内分割数（Y)

// アニメーションパターン数
#define ANIM_PATTERN_NU_ENEMYBULLET				(TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET*TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET)

#define ENEMYBULLET_MAX				(1000)		// エネミーバレットの最大数
#define ENEMYBULLET_ROTATION		(0.0f)		// エネミーバレットの回転量

#define ENEMYBULLET_TYPE_MAX		(9)


// エネミーバレット360度分割
#define ENEMYBULLET_SPLIT01			(20)
#define ENEMYBULLET_SPLIT02			(20)
#define ENEMYBULLET_SPLIT03			(20)
#define ENEMYBULLET_SPLIT04			(20)
#define ENEMYBULLET_SPLIT05			(20)
#define ENEMYBULLET_SPLIT06			(11)

// エネミーバレット360度ずらし
#define ENEMYBULLET_SHIFT03			(0.05f)
#define ENEMYBULLET_SHIFT04			(0.05f)
#define ENEMYBULLET_SHIFT06			(0.01f)

// エネミーバレット速度
#define ENEMYBULLET_SPEED_MAX00		(7)
#define ENEMYBULLET_SPEED_MAX01		(5)
#define ENEMYBULLET_SPEED_MAX02		(5)
#define ENEMYBULLET_SPEED_MAX03		(5)
#define ENEMYBULLET_SPEED_MAX04		(5)
#define ENEMYBULLET_SPEED_MAX05		(5)
#define ENEMYBULLET_SPEED_MAX06		(2)

// エネミーバレットの速度変更
#define ENEMYBULLET_SPEEDCHANGE_TIME	(20)
#define ENEMYBULLET_SPEED_CHENGE_DEFAULT		(1.0f)
#define ENEMYBULLET_SPEED_CHANGE				(0.02f * SCREEN_SCALING)
#define ENEMYBULLET_SPEED_CHANGE_MAX			(1.5f)
#define ENEMYBULLET_SPEED_CHANGE_MIN			(-1.5f)

#define ENEMYBULLET_WAY00			(0)			// エネミーバレットWAYなし
#define ENEMYBULLET_WAY01			(1)			// エネミーバレットWAY01
#define ENEMYBULLET_WAY03			(3)			// エネミーバレットWAY03
#define ENEMYBULLET_WAY05			(5)			// エネミーバレットWAY05
#define ENEMYBULLET_WAY07			(7)			// エネミーバレットWAY07

// エネミーバレットタイプ
#define ENEMYBULLET_TYPE00			(0)			// エネミーバレットタイプ00
#define ENEMYBULLET_TYPE01			(1)			// エネミーバレットタイプ01
#define ENEMYBULLET_TYPE02			(2)			// エネミーバレットタイプ02
#define ENEMYBULLET_TYPE03			(3)			// エネミーバレットタイプ03
#define ENEMYBULLET_TYPE04			(4)			// エネミーバレットタイプ04
#define ENEMYBULLET_TYPE05			(5)			// エネミーバレットタイプ05
#define ENEMYBULLET_TYPE06			(6)			// エネミーバレットタイプ06

// エネミーバレットテクスチャー
#define ENEMYBULLET_TEXTURE00		(0)			// エネミーバレットテクスチャー00
#define ENEMYBULLET_TEXTURE01		(1)			// エネミーバレットテクスチャー01
#define ENEMYBULLET_TEXTURE02		(2)			// エネミーバレットテクスチャー02
#define ENEMYBULLET_TEXTURE03		(3)			// エネミーバレットテクスチャー03
#define ENEMYBULLET_TEXTURE04		(4)			// エネミーバレットテクスチャー04
#define ENEMYBULLET_TEXTURE05		(5)			// エネミーバレットテクスチャー05
#define ENEMYBULLET_TEXTURE06		(6)			// エネミーバレットテクスチャー06
#define ENEMYBULLET_TEXTURE07		(7)			// エネミーバレットテクスチャー07
#define ENEMYBULLET_TEXTURE08		(8)			// エネミーバレットテクスチャー08

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// エネミーバレット00の座標
	D3DXVECTOR3				rot;					// エネミーバレット00の回転量
	D3DXVECTOR2				size;					// エネミーバレット00のテクスチャサイズ(x,y)
	D3DXVECTOR3				vecTa;					// 距離
	D3DXVECTOR3				move;					// 移動量
	D3DXVECTOR3				vecTargetPos;			// エネミーバレットのターゲット座標
	D3DXVECTOR3				vecOldEnemyPos;			// エネミーの旧座標

	D3DXVECTOR3				vecMoveChange;			// 移動加速倍率

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nPatternHoming;			// ホーミングパターンナンバー
	int						nHomingFlag;			// エネミーバレット00のホーミングフラグ
	int						nDirection;				// エネミーバレット00の向き
	int						nTarget;				// エネミーバレット00のターゲット
	int						nBulletType;			// エネミーのバレットタイプ
	int						nBulletTexture;			// エネミーのバレットテクスチャー
	int						nBulletWay;				// エネミーのバレットWAY数
	int						nBulletTime;			// エネミーのバレット経過時間
	int						nSetEnemy;				// セットするエネミー

	float					fAngle;					// エネミーバレット00の角度
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	float					fMoveChange;			// 移動加減速倍率
	float					fDistance;				// 距離

	bool					bUse;					// エネミーバレット00の使用フラグ
	bool					bTextureUse;			// エネミーバレット00のテクスチャフラグ
	bool					bPatternHomingFlag;		// ホーミングパターンフラグ
}ENEMYBULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemybullet(int type);
void UninitEnemybullet(void);
void UpdateEnemybullet(void);
void DrawEnemybullet(void);
ENEMYBULLET *GetEnemybullet(int no);
void SetEnemybullet(int nEnemy, int nBulletSplit);
void InitStatusEnemyBullet(int nBullet);
#endif
