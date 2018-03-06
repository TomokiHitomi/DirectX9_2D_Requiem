//=============================================================================
//
// �v���C���[�\��Main���� [main.cpp]
// Author : GP11B243 24 �l���F��
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

// �v���C���[�A�^�b�N
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("DirectX 2D��i�uRequiem�v")		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		��_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

LPDIRECTSOUNDBUFFER8 g_pBGM[5];
LPDIRECTSOUNDBUFFER8 g_pSE[20];

// ��ʑJ��
eStage g_nStage = STAGE_TITLE;
int g_nLoop = 0;
int g_nCount = 0;
bool g_bEndFlag = true;
bool g_bSe11Flag = true;

long g_nVol[5] = { VOLUME_MAX, VOLUME_MIN, VOLUME_MIN, VOLUME_MIN, VOLUME_MIN };

#ifdef _DEBUG	// (*35) �ǉ���
LPD3DXFONT	pD3DXFont = NULL;	// �t�H���g�ւ̃|�C���^
int			nCountFPS;		// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	

	// ���Ԍv���p
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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	bool flag = false; // �t���X�N���[�����[�h�ŏ�����
	if(MessageBox(hWnd, "�E�B���h�E���[�h�ŋN�����܂����H", "�N���m�F", MB_YESNO)==IDYES)
	{
		flag = true;
	}

	if(FAILED(Init(hWnd, flag)))
	{
		return -1;
	}

	// �C���v�b�g������
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);									// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();		// �~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(g_bEndFlag)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// �V�X�e���������擾
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)									//0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	//FPS���v��
#endif
				dwFPSLastTime = dwCurrentTime;											//FPS�v��������ۑ�
				dwFrameCount = 0;														//�J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))						// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;											// ��������������ۑ�
				Update();																// �X�V����
				Draw();																	// �`�揈��
				dwFrameCount++;															//�����񐔂̃J�E���g�����Z
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
	//	case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
	//		MessageBox(hWnd, "�A�v���P�[�V�������I�����܂�", "ESC�̏���", MB_OK);
	//		DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
	//		break;
	//	}
	//	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	g_nCount = 0;

	// Direct3D�I�u�W�F�N�g�̍쐬
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��

	if(bWindow)
	{// �E�B���h�E���[�h
		//d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;	// D3DFMT_R5G6B5				// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
									hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&��_pD3DDevice)))								// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&��_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&��_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	��_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	��_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	��_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	��_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	��_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	��_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	��_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	��_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�厞�̕�Ԑݒ�
	��_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���k�����̕�Ԑݒ�

		// �e�N�X�`���X�e�[�W���Z��������
	��_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	��_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	��_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	//Font�̏�����
#ifdef  _DEBUG
	D3DXCreateFont(��_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		_T("Terminal"), &pD3DXFont);
#endif


	// �T�E���h�̏���������
	InitSound(hWnd);

	SetSound();

	InitGame(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if(��_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		��_pD3DDevice->Release();
	}

	if(pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		pD3D->Release();
	}

	// ���͏����̏I������
	UninitInput();

	// BGM�̃������J��
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(g_pBGM[i]);
	}

	// SE�̃������J��
	//SAFE_RELEASE(g_pSE);

	UninitSound();					// �T�E���h

	UninitBg000();					// BG000
	UninitMotion_title();			// �^�C�g�����[�V����
	UninitTitle();					// �^�C�g��
	UninitMenu();					// ���j���[
	UninitLevel();					// ��Փx�I��
	UninitLevel_boss();				// ��Փx�I���i�{�X�̂݁j
	UninitCopyright();				// �R�s�[���C�g
	UninitVersion();				// �o�[�W����
	UninitCredit();					// �N���W�b�g

	UninitBg001();					// BG001
	UninitGround();					// �O���E���h
	UninitPlayer();					// �v���C���[
	UninitParameter();				// �p�����[�^
	UninitParameterbar();			// �p�����[�^�t���[��
	UninitEffect_player_jump();		// �v���C���[�̃W�����v�G�t�F�N�g
	UninitEffect_player_wing();		// �v���C���[�̃E�C���O�G�t�F�N�g
	UninitEffect_knockdown();		// �G�l�~�[���j�G�t�F�N�g
	UninitNogravity();				// �m�[�O���r�e�B�G�t�F�N�g
	UninitHitcircle();				// �q�b�g�T�[�N��
	UninitEnemy();					// �G�l�~�[
	UninitBullet();					// �o���b�g
	UninitFunnel();					// �t�@���l��
	UninitBarrier();				// �o���A
	UninitEnemybullet();			// �G�l�~�[�o���b�g
	UninitPause();					// �|�[�Y
	UninitPausemenu();				// �|�[�Y���j���[
	//UninitHowtoplay();				// �n�E�g�D�[�v���C
	UninitHowtoplay_controller();	// �n�E�g�D�[�v���C �R���g���[���[
	UninitBg002();					// BG002
	UninitBg003();					// BG003
	UninitClose();					// �N���[�Y�i�Q�[���I�������b�Z�[�W�j
	UninitEffect_close();			// �N���[�Y�G�t�F�N�g
	UninitMotion_result();			// ���U���g���[�V����
	UninitTimeboard();				// �^�C���{�[�h
	UninitTime();					// �^�C��
	UninitScoreboard();				// �X�R�A�{�[�h
	UninitScore();					// �X�R�A
	UninitTotalboard();				// �g�[�^���X�R�A�{�[�h
	UninitTotal();					// �g�[�^���X�R�A
	UninitRankboard();				// �����N�{�[�h
	UninitRank();					// �����N
	UninitResult();					// ���U���g
	UninitClearbonus();				// �N���A�{�[�i�X
	UninitPressenter();				// �v���X�G���^�[
	UninitThank();					// �T���L���[�t�H�[�v���C���O
	UninitFrame();					// �t���[��

	UninitFade();					// �t�F�[�h

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	CLOSE *close = GetClose(0);
	PAUSE *pause = GetPause(0);
	CREDIT *credit = GetCredit(0);

	// Update�֐��̈�ԏ�̍s�ɒǉ�
	UpdateInput();

	switch (g_nStage)
	{
	case STAGE_TITLE:					// �^�C�g��
		UpdateBg000();						// BG000
		UpdateMotion_title();				// �^�C�g�����[�V����
		UpdateTitle();						// �^�C�g��
		UpdateLevel_boss();					// ��Փx�I���i�{�X�̂݁j
		UpdateLevel();						// ��Փx�I��
		UpdateMenu();						// ���j���[
		UpdateCopyright();					// �R�s�[���C�g
		UpdateVersion();					// �o�[�W����
		break;
	case STAGE_TUTORIAL:			// �`���[�g���A��
		UpdateBg001();					// BG001
		UpdateGround();					// �O���E���h
		UpdatePlayer();					// �v���C���[
		UpdateNogravity();				// �m�[�O���r�e�B�G�t�F�N�g
		UpdateEffect_player_jump();		// �v���C���[�̃W�����v�G�t�F�N�g
		UpdateEffect_player_wing();		// �v���C���[�̃E�C���O�G�t�F�N�g
		UpdateParameter();				// �p�����[�^
		UpdateParameterbar();			// �p�����[�^�o�[
		UpdateHitcircle();				// �q�b�g�T�[�N��
		UpdateBullet();					// �o���b�g
		UpdateFunnel();					// �t�@���l��
		UpdateBarrier();				// �o���A
		//UpdateHowtoplay();				// �n�E�g�D�[�v���C
		UpdateHowtoplay_controller();	// �n�E�g�D�[�v���C
		break;
	case STAGE_CREDIT:					// �N���W�b�g
		UpdateBg000();						// BG000
		UpdateCopyright();					// �R�s�[���C�g
		UpdateVersion();					// �o�[�W����
		UpdateCredit();						// �N���W�b�g
		break;
	case STAGE_GAME:					// �Q�[��
		if (!pause->bStop)
		{
			UpdateGame();					// �Q�[��
			UpdateBg001();					// BG001
			UpdateGround();					// �O���E���h
			UpdatePlayer();					// �v���C���[
			UpdateNogravity();				// �m�[�O���r�e�B�G�t�F�N�g
			UpdateEffect_player_jump();		// �v���C���[�̃W�����v�G�t�F�N�g
			UpdateEffect_player_wing();		// �v���C���[�̃E�C���O�G�t�F�N�g
			UpdateParameter();				// �p�����[�^
			UpdateParameterbar();			// �p�����[�^�o�[
			UpdateHitcircle();				// �q�b�g�T�[�N��
			UpdateBullet();					// �o���b�g
			UpdateFunnel();					// �t�@���l��
			UpdateBarrier();				// �o���A
			UpdateEffect_knockdown();		// �G�l�~�[���j�G�t�F�N�g
			UpdateEnemy();					// �G�l�~�[
			UpdateEnemybullet();			// �G�l�~�[�o���b�g
			UpdateEffect_close();			// �N���[�Y�G�t�F�N�g
			UpdateClose();					// �N���[�Y�i�Q�[���I�������b�Z�[�W�j
			UpdateTimeboard();				// �^�C���{�[�h
			UpdateTime();					// �^�C��
			UpdateScoreboard();				// �X�R�A�{�[�h
			UpdateScore();					// �X�R�A
			if (!close->bUse)
			{
				ChackHit();					// �����蔻�菈��
			}
			g_nCount++;						// �Q�[���J�E���g
		}
		UpdatePause();						// �|�[�Y
		UpdatePausemenu();					// �|�[�Y���j���[
		break;
	case STAGE_RESULT:					// ���U���g
		UpdateBg002();						// BG002
		UpdateBg003();						// BG003
		UpdateMotion_result();				// ���U���g���[�V����
		UpdateResult();						// ���U���g
		UpdateTimeboard();					// �^�C���{�[�h
		UpdateTime();						// �^�C��
		UpdateScoreboard();					// �X�R�A�{�[�h
		UpdateScore();						// �X�R�A
		UpdateTotalboard();					// �g�[�^���X�R�A�{�[�h
		UpdateTotal();						// �g�[�^���X�R�A
		UpdateRankboard();					// �����N�{�[�h
		UpdateRank();						// �����N
		UpdateClearbonus();					// �N���A�{�[�i�X
		UpdatePressenter();					// �v���X�G���^�[
		UpdateThank();						// �T���L���[�t�H�[�v���C���O
		break;
	}

	UpdateFrame();			// �t���[��
	UpdateFade();			// �t�F�[�h

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	��_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(��_pD3DDevice->BeginScene()))
	{
		switch (g_nStage)
		{
		case STAGE_TITLE:			// �^�C�g��
			DrawBg000();				// BG000
			DrawMotion_title();			// �^�C�g�����[�V����
			DrawTitle();				// �^�C�g��
			DrawMenu();					// ���j���[
			DrawLevel();				// ��Փx�I��
			DrawLevel_boss();			// ��Փx�I��(�{�X�̂݁j
			DrawCopyright();			// �R�s�[���C�g
			DrawVersion();				// �o�[�W����
			DrawFrame();				// �t���[��
			DrawFade();					// �t�F�[�h
			break;
		case STAGE_TUTORIAL:
			DrawBg001();				// BG001
			DrawGround();				// �O���E���h
			DrawNogravity();			// �m�[�O���r�e�B�G�t�F�N�g
			DrawBullet();				// �o���b�g
			DrawFunnel();				// �t�@���l��
			DrawBarrier();				// �o���A
			DrawEffect_player_jump();	// �v���C���[�̃W�����v�G�t�F�N�g
			DrawEffect_player_wing();	// �v���C���[�̃E�C���O�G�t�F�N�g
			DrawPlayer();				// �v���C���[
			DrawParameter();			// �p�����[�^�[
			DrawParameterbar();			// �p�����[�^�[�t���[��
			DrawHitcircle();			// �q�b�g�T�[�N��
			DrawFrame();				// �t���[��
			//DrawHowtoplay();			// �n�E�g�D�[�v���C
			DrawHowtoplay_controller();	// �n�E�g�D�[�v���C
			DrawFade();					// �t�F�[�h
			break;
		case STAGE_CREDIT:			// �^�C�g��
			DrawBg000();				// BG000
			DrawCopyright();			// �R�s�[���C�g
			DrawVersion();				// �o�[�W����
			DrawFrame();				// �t���[��
			DrawCredit();				// �N���W�b�g
			DrawFade();					// �t�F�[�h
			break;
		case STAGE_GAME:			// �{��
			DrawBg001();				// BG001
			DrawGround();				// �O���E���h
			DrawNogravity();			// �m�[�O���r�e�B�G�t�F�N�g
			DrawBullet();				// �o���b�g
			DrawFunnel();				// �t�@���l��
			DrawBarrier();				// �o���A
			DrawEffect_player_jump();	// �v���C���[�̃W�����v�G�t�F�N�g
			DrawEffect_player_wing();	// �v���C���[�̃E�C���O�G�t�F�N�g
			DrawPlayer();				// �v���C���[
			DrawEffect_knockdown();		// �G�l�~�[���j�G�t�F�N�g
			DrawEnemybullet();			// �G�l�~�[�o���b�g
			DrawEnemy();				// �G�l�~�[
			DrawParameter();			// �p�����[�^�[
			DrawParameterbar();			// �p�����[�^�[�t���[��
			DrawHitcircle();			// �q�b�g�T�[�N��
			DrawTimeboard();			// �^�C���{�[�h
			DrawTime();					// �^�C��
			DrawScoreboard();			// �X�R�A�{�[�h
			DrawScore();				// �X�R�A
			DrawEffect_close();			// �N���[�Y�G�t�F�N�g
			DrawClose();				// �N���[�Y�i�Q�[���I�������b�Z�[�W�j
			DrawFrame();				// �t���[��
			DrawFade();					// �t�F�[�h
			DrawPause();				// �|�[�Y
			DrawPausemenu();			// �|�[�Y���j���[
			break;
		case STAGE_RESULT:			// ���U���g
			DrawBg002();				// BG002
			DrawBg003();				// BG003
			DrawMotion_result();		// ���U���g���[�V����
			DrawResult();				// ���U���g
			DrawTimeboard();			// �^�C���{�[�h
			DrawTime();					// �^�C��
			DrawScoreboard();			// �X�R�A�{�[�h
			DrawScore();				// �X�R�A
			DrawTotalboard();			// �g�[�^���X�R�A�{�[�h
			DrawTotal();				// �g�[�^���X�R�A
			DrawRankboard();			// �����N�{�[�h
			DrawRank();					// �����N
			DrawClearbonus();			// �N���A�{�[�i�X
			DrawPressenter();			// �v���X�G���^�[
			DrawFrame();				// �t���[��
			DrawFade();					// �t�F�[�h
			DrawThank();				// �T���L���[�t�H�[�v���C���O
			break;
		}

#ifdef _DEBUG
		//FPS�\�� �`��̈�ԉ��ɓ���Ă���
		DrawDebugFont();
#endif

		// Direct3D�ɂ��`��̏I��
		��_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	��_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(��_pD3DDevice);
}

//=============================================================================
// �����蔻��֐�
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

	// �v���C���[�ƃG�l�~�[�̓����蔻��(BB)
	player = GetPlayer(0);
	if (player->bUse == true)
	{
		enemy = GetEnemy(0);
		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			// �g�p���Ă���G�l�~�[�����邩���m�F
			if (enemy->bUse == true)
			{
				// BB�̊m�F
				if (CheckHitBB(player->pos, enemy->pos, player->size, enemy->size) == true)
				{
					// �v���C���[HP�̌��Z����
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

	// �G�l�~�[�o���b�g�ƃv���C���[�̓����蔻��(BC)
	player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// �g�p���Ă���v���C���[�����邩���m�F
		if (player->bUse)
		{
			enemybullet = GetEnemybullet(0);
			for (int j = 0; j < ENEMYBULLET_MAX; j++, enemybullet++)
			{
				// �g�p���Ă���e�����邩���m�F
				if (enemybullet->bUse)
				{
					// BC�̊m�F
					if (CheckHitBC(enemybullet->pos, hitcircle->pos, enemybullet->size.y, hitcircle->size.x))
					{
						// �v���C���[HP�̌��Z����
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

	// �G�l�~�[�o���b�g�ƃo���A�̓����蔻��(BC)
	barrier = GetBarrier(0);
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		// �g�p���Ă���o���A�����邩���m�F
		if (barrier->bUse)
		{
			enemybullet = GetEnemybullet(0);
			for (int j = 0; j < ENEMYBULLET_MAX; j++, enemybullet++)
			{
				// �g�p���Ă���e�����邩���m�F
				if (enemybullet->bUse)
				{
					// BC�̊m�F
					if (CheckHitBC(enemybullet->pos, barrier->pos, enemybullet->size.y, barrier->size.x))
					{
						// �G�l�~�[�o���b�g�̏�����
						InitStatusEnemyBullet(j);
					}
				}
			}
		}
	}

	// �o���b�g�ƃG�l�~�[�̃q�b�gSE�Đ��Ԋu
	if (g_nCount % SE_11_CONTINUITY == 0)
	{
		g_bSe11Flag = true;
	}
	// �o���b�g�ƃG�l�~�[�̓����蔻��(BC)
	enemy = GetEnemy(0);
 	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// �g�p���Ă���G�l�~�[�����邩���m�F
		if (enemy->bUse == true)
		{
			bullet = GetBullet(0);
			for (int j = 0; j < BULLET_MAX; j++, bullet++)
			{
				// �g�p���Ă���e�����邩���m�F
				if (bullet->bUse == true)
				{
					// BC�̊m�F
					if (CheckHitBC(bullet->pos, enemy->pos, bullet->size.x, enemy->size.x) == true)
					{
						// �G�l�~�[��HP�����Z����
						switch (bullet->nBulletType)
						{
						case 2:
							enemy->fHitPoint -= 2;
							break;
						default:
							enemy->fHitPoint -= 1;
								break;
						}
						// �o���b�g�X�e�[�^�X�̏�����
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

	// �v���C���[��HP�m�F
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
	// �G�l�~�[��HP�m�F
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
// BB�̔���֐�
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// �����蔻��̊m�F(BB)
	if ( ((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.y + size1.y) > (pos2.y - size2.y)) && ((pos2.y + size2.y) > (pos1.y - size1.y)) )
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// BC�̔���֐�
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// �����蔻��̊m�F(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2) )
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// ��ʑJ��
//=============================================================================
void SetStage(eStage no)
{
	g_nStage = no;
	InitFade(no);			// �t�F�[�h
}

//=============================================================================
// �J�ڊm�F
//=============================================================================
eStage CheckStage(void)
{
	return g_nStage;
}

//=============================================================================
// �I���t���O
//=============================================================================
void SetEndFlag(void)
{
	g_bEndFlag = 0;
}

//=============================================================================
// BGM�{�����[���R���g���[��
//=============================================================================
void SetBgmVol(int no, bool type)
{
	// type 0=�t�F�[�h�A�E�g 1=�t�F�[�h�C��
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
// ������
//=============================================================================
void InitGame(int no)
{
	// ����������
	g_nCount = 0;
	InitBg000(no);					// BG000
	InitTitle(no);					// �^�C�g��
	InitMotion_title(no);			// �^�C�g�����[�V����
	InitMenu(no);					// ���j���[
	InitLevel(no);					// ��Փx�I��
	InitLevel_boss(no);				// ��Փx�I���i�{�X�̂݁j
	InitCopyright(no);				// �R�s�[���C�g
	InitVersion(no);				// �o�[�W����
	InitFrame(no);					// �t���[��
	InitCredit(no);					// �N���W�b�g
	InitFade(no);					// �t�F�[�h
	InitBg001(no);					// BG001
	InitGround(no);					// �O���E���h
	InitPlayer(no);					// �v���C���[
	InitParameter(no);				// �p�����[�^
	InitParameterbar(no);			// �p�����[�^�t���[��
	InitEnemy(no);					// �G�l�~�[
	InitEffect_player_jump(no);		// �v���C���[�̃W�����v�G�t�F�N�g
	InitEffect_player_wing(no);		// �v���C���[�̃E�C���O�G�t�F�N�g
	InitEffect_knockdown(no);		// �G�l�~�[���j�G�t�F�N�g
	InitNogravity(no);				// �m�[�O���r�e�B�G�t�F�N�g
	InitHitcircle(no);				// �q�b�g�T�[�N��
	InitBullet(no);					// �o���b�g
	InitFunnel(no);					// �t�@���l��
	InitBarrier(no);				// �o���A
	InitEnemybullet(no);			// �G�l�~�[�o���b�g
	InitBg002(no);					// BG002
	InitBg003(no);					// BG003
	InitMotion_result(no);			// ���U���g���[�V����
	InitEffect_close(no);			// �N���[�Y�G�t�F�N�g
	InitClose(no);					// �N���[�Y�i�Q�[���I�������b�Z�[�W�j
	InitTime(no);					// �^�C��
	InitTimeboard(no);				// �^�C���{�[�h
	InitScore(no);					// �X�R�A
	InitScoreboard(no);				// �X�R�A�{�[�h
	InitTotalboard(no);				// �g�[�^���X�R�A�{�[�h
	InitTotal(no);					// �g�[�^���X�R�A
	InitRankboard(no);				// �����N�{�[�h
	InitRank(no);					// �����N
	InitPause(no);					// �|�[�Y
	InitPausemenu(no);				// �|�[�Y���j���[
	//InitHowtoplay(no);				// �n�E�g�D�[�v���C
	InitHowtoplay_controller(no);	// �n�E�g�D�[�v���C
	InitClearbonus(no);				// �N���A�{�[�i�X
	InitPressenter(no);				// �v���X�G���^�[
	InitThank(no);					// �T���L���[�t�H�[�v���C���O
	InitResult(no);					// ���U���g
}

//=============================================================================
// �J�E���g�擾�֐�
//=============================================================================
void SetSound(void)
{
	// �eBGM���[�h
	g_pBGM[0] = LoadSound(BGM_00);
	g_pBGM[1] = LoadSound(BGM_01);
	g_pBGM[2] = LoadSound(BGM_02);
	g_pBGM[3] = LoadSound(BGM_03);
	g_pBGM[4] = LoadSound(BGM_04);

	// �eBGM�{�����[���Z�b�g
	for (int i = 0; i < 5; i++)
	{
		PlaySound(g_pBGM[i], E_DS8_FLAG_LOOP);
		if (i != 0)
		{
			SetVol(g_pBGM[i], VOLUME_MIN);
		}
	}

	// �eSE���[�h
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

	// �eSE�{�����[���Z�b�g
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
// SE�Đ��֐�
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
// �J�E���g�擾�֐�
//=============================================================================
int *GetCount(void)
{
	return(&g_nCount);
}

//=============================================================================
// �f�o�b�N�p�֐�
//=============================================================================
#ifdef _DEBUG
//Font�̕\���֐�
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

