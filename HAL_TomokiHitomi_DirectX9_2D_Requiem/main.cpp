//=============================================================================
//
// プレイヤー表示Main処理 [main.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "menu.h"
#include "level.h"
#include "level_boss.h"
#include "motion_title.h"
#include "motion_result.h"
#include "fade.h"
#include "player.h"
#include "parameter.h"
#include "parameterbar.h"
#include "hitcircle.h"
#include "input.h"
#include "enemy.h"
#include "enemybullet.h"
#include "clearbonus.h"
#include "thank.h"
#include "nogravity.h"

// プレイヤーアタック
#include "bullet.h"
#include "funnel.h"
#include "barrier.h"

#include "effect_player_jump.h"
#include "effect_player_wing.h"
#include "effect_knockdown.h"
#include "effect_close.h"

#include "pause.h"
#include "ground.h"
#include "pausemenu.h"
#include "sound.h"
#include "title.h"
#include "close.h"
#include "result.h"
#include "bg000.h"
#include "bg001.h"
#include "bg002.h"
#include "bg003.h"
#include "time.h"
#include "timeboard.h"
#include "score.h"
#include "scoreboard.h"
#include "totalboard.h"
#include "total.h"
#include "rankboard.h"
#include "rank.h"
#include "pressenter.h"

#include "howtoplay.h"
#include "howtoplay_controller.h"
#include "copyright.h"
#include "version.h"
#include "credit.h"
#include "frame.h"

#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")				// ウインドウのクラス名
#define WINDOW_NAME			_T("DirectX 2D作品「Requiem」")		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void ChackHit(void);
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
void SetSound(void);

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				pD3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		ｇ_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

LPDIRECTSOUNDBUFFER8 g_pBGM[5];
LPDIRECTSOUNDBUFFER8 g_pSE[20];

// 画面遷移
eStage g_nStage = STAGE_TITLE;
int g_nLoop = 0;
int g_nCount = 0;
bool g_bEndFlag = true;
bool g_bSe11Flag = true;

long g_nVol[5] = { VOLUME_MAX, VOLUME_MIN, VOLUME_MIN, VOLUME_MIN, VOLUME_MIN };

#ifdef _DEBUG	// (*35) 追加分
LPD3DXFONT	pD3DXFont = NULL;	// フォントへのポインタ
int			nCountFPS;		// FPSカウンタ
#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）
	

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	bool flag = false; // フルスクリーンモードで初期化
	if(MessageBox(hWnd, "ウィンドウモードで起動しますか？", "起動確認", MB_YESNO)==IDYES)
	{
		flag = true;
	}

	if(FAILED(Init(hWnd, flag)))
	{
		return -1;
	}

	// インプット初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);									// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();		// ミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(g_bEndFlag)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// システム時刻を取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)									//0.5秒ごとに実行
			{
#ifdef _DEBUG
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	//FPSを計測
#endif
				dwFPSLastTime = dwCurrentTime;											//FPS計測時刻を保存
				dwFrameCount = 0;														//カウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))						// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;											// 処理した時刻を保存
				Update();																// 更新処理
				Draw();																	// 描画処理
				dwFrameCount++;															//処理回数のカウントを加算
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//case WM_KEYDOWN:
	//	switch(wParam)
	//	{
	//	case VK_ESCAPE:					// [ESC]キーが押された
	//		MessageBox(hWnd, "アプリケーションを終了します", "ESCの処理", MB_OK);
	//		DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
	//		break;
	//	}
	//	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	g_nCount = 0;

	// Direct3Dオブジェクトの作成
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定

	if(bWindow)
	{// ウィンドウモード
		//d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;	// D3DFMT_R5G6B5				// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
									D3DDEVTYPE_HAL,								// ディスプレイタイプ
									hWnd,										// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
									&d3dpp,										// デバイスのプレゼンテーションパラメータ
									&ｇ_pD3DDevice)))								// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&ｇ_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&ｇ_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	ｇ_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	ｇ_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	ｇ_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	ｇ_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	ｇ_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	ｇ_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャＵ値の繰り返し設定
	ｇ_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャＶ値の繰り返し設定
	ｇ_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補間設定
	ｇ_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小時の補間設定

		// テクスチャステージ加算合成処理
	ｇ_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	ｇ_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	ｇ_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	//Fontの初期化
#ifdef  _DEBUG
	D3DXCreateFont(ｇ_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		_T("Terminal"), &pD3DXFont);
#endif


	// サウンドの初期化処理
	InitSound(hWnd);

	SetSound();

	InitGame(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if(ｇ_pD3DDevice != NULL)
	{// デバイスの開放
		ｇ_pD3DDevice->Release();
	}

	if(pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		pD3D->Release();
	}

	// 入力処理の終了処理
	UninitInput();

	// BGMのメモリ開放
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(g_pBGM[i]);
	}

	// SEのメモリ開放
	//SAFE_RELEASE(g_pSE);

	UninitSound();					// サウンド

	UninitBg000();					// BG000
	UninitMotion_title();			// タイトルモーション
	UninitTitle();					// タイトル
	UninitMenu();					// メニュー
	UninitLevel();					// 難易度選択
	UninitLevel_boss();				// 難易度選択（ボスのみ）
	UninitCopyright();				// コピーライト
	UninitVersion();				// バージョン
	UninitCredit();					// クレジット

	UninitBg001();					// BG001
	UninitGround();					// グラウンド
	UninitPlayer();					// プレイヤー
	UninitParameter();				// パラメータ
	UninitParameterbar();			// パラメータフレーム
	UninitEffect_player_jump();		// プレイヤーのジャンプエフェクト
	UninitEffect_player_wing();		// プレイヤーのウイングエフェクト
	UninitEffect_knockdown();		// エネミー撃破エフェクト
	UninitNogravity();				// ノーグラビティエフェクト
	UninitHitcircle();				// ヒットサークル
	UninitEnemy();					// エネミー
	UninitBullet();					// バレット
	UninitFunnel();					// ファンネル
	UninitBarrier();				// バリア
	UninitEnemybullet();			// エネミーバレット
	UninitPause();					// ポーズ
	UninitPausemenu();				// ポーズメニュー
	//UninitHowtoplay();				// ハウトゥープレイ
	UninitHowtoplay_controller();	// ハウトゥープレイ コントローラー
	UninitBg002();					// BG002
	UninitBg003();					// BG003
	UninitClose();					// クローズ（ゲーム終了時メッセージ）
	UninitEffect_close();			// クローズエフェクト
	UninitMotion_result();			// リザルトモーション
	UninitTimeboard();				// タイムボード
	UninitTime();					// タイム
	UninitScoreboard();				// スコアボード
	UninitScore();					// スコア
	UninitTotalboard();				// トータルスコアボード
	UninitTotal();					// トータルスコア
	UninitRankboard();				// ランクボード
	UninitRank();					// ランク
	UninitResult();					// リザルト
	UninitClearbonus();				// クリアボーナス
	UninitPressenter();				// プレスエンター
	UninitThank();					// サンキューフォープレイング
	UninitFrame();					// フレーム

	UninitFade();					// フェード

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	CLOSE *close = GetClose(0);
	PAUSE *pause = GetPause(0);
	CREDIT *credit = GetCredit(0);

	// Update関数の一番上の行に追加
	UpdateInput();

	switch (g_nStage)
	{
	case STAGE_TITLE:					// タイトル
		UpdateBg000();						// BG000
		UpdateMotion_title();				// タイトルモーション
		UpdateTitle();						// タイトル
		UpdateLevel_boss();					// 難易度選択（ボスのみ）
		UpdateLevel();						// 難易度選択
		UpdateMenu();						// メニュー
		UpdateCopyright();					// コピーライト
		UpdateVersion();					// バージョン
		break;
	case STAGE_TUTORIAL:			// チュートリアル
		UpdateBg001();					// BG001
		UpdateGround();					// グラウンド
		UpdatePlayer();					// プレイヤー
		UpdateNogravity();				// ノーグラビティエフェクト
		UpdateEffect_player_jump();		// プレイヤーのジャンプエフェクト
		UpdateEffect_player_wing();		// プレイヤーのウイングエフェクト
		UpdateParameter();				// パラメータ
		UpdateParameterbar();			// パラメータバー
		UpdateHitcircle();				// ヒットサークル
		UpdateBullet();					// バレット
		UpdateFunnel();					// ファンネル
		UpdateBarrier();				// バリア
		//UpdateHowtoplay();				// ハウトゥープレイ
		UpdateHowtoplay_controller();	// ハウトゥープレイ
		break;
	case STAGE_CREDIT:					// クレジット
		UpdateBg000();						// BG000
		UpdateCopyright();					// コピーライト
		UpdateVersion();					// バージョン
		UpdateCredit();						// クレジット
		break;
	case STAGE_GAME:					// ゲーム
		if (!pause->bStop)
		{
			UpdateGame();					// ゲーム
			UpdateBg001();					// BG001
			UpdateGround();					// グラウンド
			UpdatePlayer();					// プレイヤー
			UpdateNogravity();				// ノーグラビティエフェクト
			UpdateEffect_player_jump();		// プレイヤーのジャンプエフェクト
			UpdateEffect_player_wing();		// プレイヤーのウイングエフェクト
			UpdateParameter();				// パラメータ
			UpdateParameterbar();			// パラメータバー
			UpdateHitcircle();				// ヒットサークル
			UpdateBullet();					// バレット
			UpdateFunnel();					// ファンネル
			UpdateBarrier();				// バリア
			UpdateEffect_knockdown();		// エネミー撃破エフェクト
			UpdateEnemy();					// エネミー
			UpdateEnemybullet();			// エネミーバレット
			UpdateEffect_close();			// クローズエフェクト
			UpdateClose();					// クローズ（ゲーム終了時メッセージ）
			UpdateTimeboard();				// タイムボード
			UpdateTime();					// タイム
			UpdateScoreboard();				// スコアボード
			UpdateScore();					// スコア
			if (!close->bUse)
			{
				ChackHit();					// 当たり判定処理
			}
			g_nCount++;						// ゲームカウント
		}
		UpdatePause();						// ポーズ
		UpdatePausemenu();					// ポーズメニュー
		break;
	case STAGE_RESULT:					// リザルト
		UpdateBg002();						// BG002
		UpdateBg003();						// BG003
		UpdateMotion_result();				// リザルトモーション
		UpdateResult();						// リザルト
		UpdateTimeboard();					// タイムボード
		UpdateTime();						// タイム
		UpdateScoreboard();					// スコアボード
		UpdateScore();						// スコア
		UpdateTotalboard();					// トータルスコアボード
		UpdateTotal();						// トータルスコア
		UpdateRankboard();					// ランクボード
		UpdateRank();						// ランク
		UpdateClearbonus();					// クリアボーナス
		UpdatePressenter();					// プレスエンター
		UpdateThank();						// サンキューフォープレイング
		break;
	}

	UpdateFrame();			// フレーム
	UpdateFade();			// フェード

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	ｇ_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(ｇ_pD3DDevice->BeginScene()))
	{
		switch (g_nStage)
		{
		case STAGE_TITLE:			// タイトル
			DrawBg000();				// BG000
			DrawMotion_title();			// タイトルモーション
			DrawTitle();				// タイトル
			DrawMenu();					// メニュー
			DrawLevel();				// 難易度選択
			DrawLevel_boss();			// 難易度選択(ボスのみ）
			DrawCopyright();			// コピーライト
			DrawVersion();				// バージョン
			DrawFrame();				// フレーム
			DrawFade();					// フェード
			break;
		case STAGE_TUTORIAL:
			DrawBg001();				// BG001
			DrawGround();				// グラウンド
			DrawNogravity();			// ノーグラビティエフェクト
			DrawBullet();				// バレット
			DrawFunnel();				// ファンネル
			DrawBarrier();				// バリア
			DrawEffect_player_jump();	// プレイヤーのジャンプエフェクト
			DrawEffect_player_wing();	// プレイヤーのウイングエフェクト
			DrawPlayer();				// プレイヤー
			DrawParameter();			// パラメーター
			DrawParameterbar();			// パラメーターフレーム
			DrawHitcircle();			// ヒットサークル
			DrawFrame();				// フレーム
			//DrawHowtoplay();			// ハウトゥープレイ
			DrawHowtoplay_controller();	// ハウトゥープレイ
			DrawFade();					// フェード
			break;
		case STAGE_CREDIT:			// タイトル
			DrawBg000();				// BG000
			DrawCopyright();			// コピーライト
			DrawVersion();				// バージョン
			DrawFrame();				// フレーム
			DrawCredit();				// クレジット
			DrawFade();					// フェード
			break;
		case STAGE_GAME:			// 本編
			DrawBg001();				// BG001
			DrawGround();				// グラウンド
			DrawNogravity();			// ノーグラビティエフェクト
			DrawBullet();				// バレット
			DrawFunnel();				// ファンネル
			DrawBarrier();				// バリア
			DrawEffect_player_jump();	// プレイヤーのジャンプエフェクト
			DrawEffect_player_wing();	// プレイヤーのウイングエフェクト
			DrawPlayer();				// プレイヤー
			DrawEffect_knockdown();		// エネミー撃破エフェクト
			DrawEnemybullet();			// エネミーバレット
			DrawEnemy();				// エネミー
			DrawParameter();			// パラメーター
			DrawParameterbar();			// パラメーターフレーム
			DrawHitcircle();			// ヒットサークル
			DrawTimeboard();			// タイムボード
			DrawTime();					// タイム
			DrawScoreboard();			// スコアボード
			DrawScore();				// スコア
			DrawEffect_close();			// クローズエフェクト
			DrawClose();				// クローズ（ゲーム終了時メッセージ）
			DrawFrame();				// フレーム
			DrawFade();					// フェード
			DrawPause();				// ポーズ
			DrawPausemenu();			// ポーズメニュー
			break;
		case STAGE_RESULT:			// リザルト
			DrawBg002();				// BG002
			DrawBg003();				// BG003
			DrawMotion_result();		// リザルトモーション
			DrawResult();				// リザルト
			DrawTimeboard();			// タイムボード
			DrawTime();					// タイム
			DrawScoreboard();			// スコアボード
			DrawScore();				// スコア
			DrawTotalboard();			// トータルスコアボード
			DrawTotal();				// トータルスコア
			DrawRankboard();			// ランクボード
			DrawRank();					// ランク
			DrawClearbonus();			// クリアボーナス
			DrawPressenter();			// プレスエンター
			DrawFrame();				// フレーム
			DrawFade();					// フェード
			DrawThank();				// サンキューフォープレイング
			break;
		}

#ifdef _DEBUG
		//FPS表示 描画の一番下に入れておく
		DrawDebugFont();
#endif

		// Direct3Dによる描画の終了
		ｇ_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	ｇ_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(ｇ_pD3DDevice);
}

//=============================================================================
// 当たり判定関数
//=============================================================================
void ChackHit(void)
{
	PLAYER *player;
	BULLET *bullet;
	ENEMY *enemy;
	ENEMYBULLET *enemybullet;
	BARRIER *barrier;
	HITCIRCLE *hitcircle = GetHitcircle(0);
	CLOSE *close = GetClose(0);

	// プレイヤーとエネミーの当たり判定(BB)
	player = GetPlayer(0);
	if (player->bUse == true)
	{
		enemy = GetEnemy(0);
		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			// 使用しているエネミーがいるかを確認
			if (enemy->bUse == true)
			{
				// BBの確認
				if (CheckHitBB(player->pos, enemy->pos, player->size, enemy->size) == true)
				{
					// プレイヤーHPの減算処理
					if (!player->bInvisibleFlag)
					{
						player->fHitPoint -= 1;
						player->bInvisibleFlag = true;
						SetPlayerVoice(rand() % 2);
					}
				}
			}
		}
	}

	// エネミーバレットとプレイヤーの当たり判定(BC)
	player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// 使用しているプレイヤーがいるかを確認
		if (player->bUse)
		{
			enemybullet = GetEnemybullet(0);
			for (int j = 0; j < ENEMYBULLET_MAX; j++, enemybullet++)
			{
				// 使用している弾があるかを確認
				if (enemybullet->bUse)
				{
					// BCの確認
					if (CheckHitBC(enemybullet->pos, hitcircle->pos, enemybullet->size.y, hitcircle->size.x))
					{
						// プレイヤーHPの減算処理
						if (!player->bInvisibleFlag)
						{
							player->fHitPoint -= 1;
							player->bInvisibleFlag = true;
							SetPlayerVoice(rand()%2);
						}
					}
				}
			}
		}
	}

	// エネミーバレットとバリアの当たり判定(BC)
	barrier = GetBarrier(0);
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		// 使用しているバリアがあるかを確認
		if (barrier->bUse)
		{
			enemybullet = GetEnemybullet(0);
			for (int j = 0; j < ENEMYBULLET_MAX; j++, enemybullet++)
			{
				// 使用している弾があるかを確認
				if (enemybullet->bUse)
				{
					// BCの確認
					if (CheckHitBC(enemybullet->pos, barrier->pos, enemybullet->size.y, barrier->size.x))
					{
						// エネミーバレットの初期化
						InitStatusEnemyBullet(j);
					}
				}
			}
		}
	}

	// バレットとエネミーのヒットSE再生間隔
	if (g_nCount % SE_11_CONTINUITY == 0)
	{
		g_bSe11Flag = true;
	}
	// バレットとエネミーの当たり判定(BC)
	enemy = GetEnemy(0);
 	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// 使用しているエネミーがいるかを確認
		if (enemy->bUse == true)
		{
			bullet = GetBullet(0);
			for (int j = 0; j < BULLET_MAX; j++, bullet++)
			{
				// 使用している弾があるかを確認
				if (bullet->bUse == true)
				{
					// BCの確認
					if (CheckHitBC(bullet->pos, enemy->pos, bullet->size.x, enemy->size.x) == true)
					{
						// エネミーのHPを減算する
						switch (bullet->nBulletType)
						{
						case 2:
							enemy->fHitPoint -= 2;
							break;
						default:
							enemy->fHitPoint -= 1;
								break;
						}
						// バレットステータスの初期化
						InitStatusBullet(j);
						if (g_bSe11Flag)
						{
							SetSe(11, E_DS8_FLAG_NONE, CONTINUITY_ON);
							g_bSe11Flag = false;
						}
						AddScore(ADD_SCORE_BULLETHIT);
					}
				}
			}
		}
	}

	// プレイヤーのHP確認
	player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->fHitPoint <= 0)
		{
			player->fHitPoint = 0;
			player->bUse = false;
		}
		else
		{
			AddScore(1);
		}
	}
	// エネミーのHP確認
	enemy = GetEnemy(0);
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->bUse)
		{
			if (enemy->fHitPoint <= 0)
			{
				if (enemy->nSpec == ENEMY_BOSS)
				{
					SetTotal(2, player->fHitPoint);
					close->bUse = true;
					close->bClearFlag = true;
					SetEffect_close();
				}
				SetEffect_knockdown(enemy->pos, enemy->nType);
				InitStatusEnemy(i);
				AddScore(ADD_SCORE_ENEMYKNOCKDOWN);
				SetSe(12, E_DS8_FLAG_NONE, CONTINUITY_ON);
			}
		}
	}
}

//=============================================================================
// BBの判定関数
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// 当たり判定の確認(BB)
	if ( ((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.y + size1.y) > (pos2.y - size2.y)) && ((pos2.y + size2.y) > (pos1.y - size1.y)) )
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// BCの判定関数
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// 当たり判定の確認(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2) )
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage(eStage no)
{
	g_nStage = no;
	InitFade(no);			// フェード
}

//=============================================================================
// 遷移確認
//=============================================================================
eStage CheckStage(void)
{
	return g_nStage;
}

//=============================================================================
// 終了フラグ
//=============================================================================
void SetEndFlag(void)
{
	g_bEndFlag = 0;
}

//=============================================================================
// BGMボリュームコントロール
//=============================================================================
void SetBgmVol(int no, bool type)
{
	// type 0=フェードアウト 1=フェードイン
	if (type == false)
	{
		if (g_nVol[no] > VOLUME_MIN)
		{
			g_nVol[no] -= VOLUME_CONTROL_DOWN;
			SetVol(g_pBGM[no], g_nVol[no]);
		}
	}
	if (type == true)
	{
		if (g_nVol[no] < VOLUME_MAX)
		{
			g_nVol[no] += VOLUME_CONTROL_UP;
			SetVol(g_pBGM[no], g_nVol[no]);
		}
	}
}


//=============================================================================
// 初期化
//=============================================================================
void InitGame(int no)
{
	// 初期化処理
	g_nCount = 0;
	InitBg000(no);					// BG000
	InitTitle(no);					// タイトル
	InitMotion_title(no);			// タイトルモーション
	InitMenu(no);					// メニュー
	InitLevel(no);					// 難易度選択
	InitLevel_boss(no);				// 難易度選択（ボスのみ）
	InitCopyright(no);				// コピーライト
	InitVersion(no);				// バージョン
	InitFrame(no);					// フレーム
	InitCredit(no);					// クレジット
	InitFade(no);					// フェード
	InitBg001(no);					// BG001
	InitGround(no);					// グラウンド
	InitPlayer(no);					// プレイヤー
	InitParameter(no);				// パラメータ
	InitParameterbar(no);			// パラメータフレーム
	InitEnemy(no);					// エネミー
	InitEffect_player_jump(no);		// プレイヤーのジャンプエフェクト
	InitEffect_player_wing(no);		// プレイヤーのウイングエフェクト
	InitEffect_knockdown(no);		// エネミー撃破エフェクト
	InitNogravity(no);				// ノーグラビティエフェクト
	InitHitcircle(no);				// ヒットサークル
	InitBullet(no);					// バレット
	InitFunnel(no);					// ファンネル
	InitBarrier(no);				// バリア
	InitEnemybullet(no);			// エネミーバレット
	InitBg002(no);					// BG002
	InitBg003(no);					// BG003
	InitMotion_result(no);			// リザルトモーション
	InitEffect_close(no);			// クローズエフェクト
	InitClose(no);					// クローズ（ゲーム終了時メッセージ）
	InitTime(no);					// タイム
	InitTimeboard(no);				// タイムボード
	InitScore(no);					// スコア
	InitScoreboard(no);				// スコアボード
	InitTotalboard(no);				// トータルスコアボード
	InitTotal(no);					// トータルスコア
	InitRankboard(no);				// ランクボード
	InitRank(no);					// ランク
	InitPause(no);					// ポーズ
	InitPausemenu(no);				// ポーズメニュー
	//InitHowtoplay(no);				// ハウトゥープレイ
	InitHowtoplay_controller(no);	// ハウトゥープレイ
	InitClearbonus(no);				// クリアボーナス
	InitPressenter(no);				// プレスエンター
	InitThank(no);					// サンキューフォープレイング
	InitResult(no);					// リザルト
}

//=============================================================================
// カウント取得関数
//=============================================================================
void SetSound(void)
{
	// 各BGMロード
	g_pBGM[0] = LoadSound(BGM_00);
	g_pBGM[1] = LoadSound(BGM_01);
	g_pBGM[2] = LoadSound(BGM_02);
	g_pBGM[3] = LoadSound(BGM_03);
	g_pBGM[4] = LoadSound(BGM_04);

	// 各BGMボリュームセット
	for (int i = 0; i < 5; i++)
	{
		PlaySound(g_pBGM[i], E_DS8_FLAG_LOOP);
		if (i != 0)
		{
			SetVol(g_pBGM[i], VOLUME_MIN);
		}
	}

	// 各SEロード
	g_pSE[0] = LoadSound(SE_00);
	g_pSE[1] = LoadSound(SE_01);
	g_pSE[2] = LoadSound(SE_02);
	g_pSE[3] = LoadSound(SE_03);
	g_pSE[4] = LoadSound(SE_04);
	g_pSE[5] = LoadSound(SE_05);
	g_pSE[6] = LoadSound(SE_06);
	g_pSE[7] = LoadSound(SE_07);
	g_pSE[8] = LoadSound(SE_08);
	g_pSE[9] = LoadSound(SE_09);
	g_pSE[10] = LoadSound(SE_10);
	g_pSE[11] = LoadSound(SE_11);
	g_pSE[12] = LoadSound(SE_12);
	g_pSE[13] = LoadSound(SE_13);

	// 各SEボリュームセット
	for (int i = 0; i < 14; i++)
	{
		if (i != 0 || i != 11 || i != 13)
		{
			SetVol(g_pSE[i], VOLUME_SE);
		}
	}
	SetVol(g_pSE[11], SE_11_VOLUME_SE);
}

//=============================================================================
// SE再生関数
//=============================================================================
void SetSe(int nVoice,int nFlag, bool bContinuity)
{
	if(bContinuity)
	{
		PlayContinuitySound(g_pSE[nVoice], nFlag);
	}
	else
	{
		PlaySound(g_pSE[nVoice], nFlag);
	}
}

//=============================================================================
// カウント取得関数
//=============================================================================
int *GetCount(void)
{
	return(&g_nCount);
}

//=============================================================================
// デバック用関数
//=============================================================================
#ifdef _DEBUG
//Fontの表示関数
void DrawDebugFont(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char str[256];

	PLAYER *player = GetPlayer(0);
	HITCIRCLE *hitcircle = GetHitcircle(0);
	ENEMY *enemy = GetEnemy(0);
	ENEMYBULLET *enemybullet = GetEnemybullet(0);
	BULLET *bullet = GetBullet(0);
	BG001 *bg001 = GetBg001(0);
	FADE *fade = GetFade(0);
	FUNNEL *funnel = GetFunnel(0);

	//// FPS
	//sprintf(str, _T("FPS:%d\n"), nCountFPS);
	//pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT,
	//	D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//// PX PY
	//rect.top = 20*PLAYER_MAX;
	//sprintf(str, "PX1:%f PY1:%f C:%d HP:%2f MP:%2f A:%3d FA:%3d", player->pos.x, player->pos.y, g_nCount, player->fHitPoint, player->fManaPoint, player->nAlphaCount, funnel->nAlpha);
	//pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	//// EX EY
	//for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	//{
	//	rect.top = (20 * PLAYER_MAX) + (i+1) * 20;
	//	sprintf(str, "EX%d:%f EY%d:%f HP:%2d BOSS:%f", i + 1, enemy->pos.x, i + 1, enemy->pos.y, enemy->fHitPoint, enemy->nSpec);
	//	pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}
	//// BX BY
	//for (int i = 0; i < BULLET_MAX; i++, bullet++)
	//{
	//	rect.top = (20 * PLAYER_MAX) + (20*ENEMY_MAX) + (i + 1) * 20;
	//	sprintf(str, "BX%d:%f B Y%d:%f T:%d H:%d", i + 1, bullet->pos.x, i + 1, bullet->pos.y, bullet->nTarget, bullet->nHomingFlag);
	//	pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	//// BX BY
	//for (int i = 0; i < 30; i++, bullet++)
	//{
	//	rect.top = (i + 1) * 20;
	//	sprintf(str, "BX%d:%f B Y%d:%f MX:%f MY:%f MS:%f", i + 1, enemybullet->pos.x, i + 1, enemybullet->pos.y, enemybullet->move.x, enemybullet->move.y ,enemybullet->fMoveChange);
	//	pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}
}

#endif

