//=============================================================================
//
// �^�C�g������ [level_boss.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "level.h"
#include "level_boss.h"
#include "input.h"
#include "sound.h"
#include "menu.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLevel_boss(int no);
void SetTextureLevel_boss( int no, int cntPattern );
void SetVertexLevel_boss(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LEVEL_BOSS					level_bossWk[LEVEL_BOSS_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureLevel_boss = NULL;

int		g_nSelectLevel_boss;
int		g_nSelectLevel_bossCount;
bool	g_bSelectLevel_ReturnFlag;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLevel_boss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_LEVEL_BOSS00,				// �t�@�C���̖��O
			&pD3DTextureLevel_boss);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		level_boss->bUse = false;
		level_boss->pos = D3DXVECTOR3((float)LEVEL_BOSS_POS_X, i*(float)LEVEL_BOSS_SPACING + (float)LEVEL_BOSS_POS_Y, 0.0f);
		level_boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		level_boss->nCountAnim = 0;
		level_boss->nPatternAnim = 0;

		level_boss->Texture = pD3DTextureLevel_boss;			// �e�N�X�`���ւ̃G�l�~�[
		level_boss->size = D3DXVECTOR2(TEXTURE_LEVEL_BOSS00_SIZE_X, TEXTURE_LEVEL_BOSS00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexLevel_boss(i);
	}

	g_nSelectLevel_boss = 0;
	g_nSelectLevel_bossCount = 0;
	g_bSelectLevel_ReturnFlag = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// ���������
	if (pD3DTextureLevel_boss != NULL)
	{
		pD3DTextureLevel_boss->Release();
		pD3DTextureLevel_boss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	if(g_bSelectLevel_ReturnFlag)
	{
		ReleaseLevel_boss();
		SetLevel();
		g_bSelectLevel_ReturnFlag = false;
	}

	if (level_boss->bUse)
	{
		// ��ړ�
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W)
			|| IsButtonTriggered(0, BUTTON_UP) || IsButtonTriggered(0, LSTICK_UP))
		{
			g_nSelectLevel_boss--;
			if (g_nSelectLevel_boss < 0)
			{
				g_nSelectLevel_boss += LEVEL_BOSS_MAX;
			}
			SetSe(1, E_DS8_FLAG_NONE, true);
		}
		// ���ړ�
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_DOWN) || IsButtonTriggered(0, LSTICK_DOWN))
		{
			g_nSelectLevel_boss++;
			SetSe(1, E_DS8_FLAG_NONE, true);
		}

		// ��ړ�������
		if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)
			|| IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, LSTICK_UP))
		{
			g_nSelectLevel_bossCount++;
			if (g_nSelectLevel_bossCount > LEVEL_BOSS_SELECT_PRESS && g_nSelectLevel_bossCount % LEVEL_BOSS_SELECT_SPEED == 0)
			{
				g_nSelectLevel_boss--;
				if (g_nSelectLevel_boss < 0)
				{
					g_nSelectLevel_boss += LEVEL_BOSS_MAX;
				}
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		// ���ړ�������
		else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, LSTICK_DOWN))
		{
			g_nSelectLevel_bossCount++;
			if (g_nSelectLevel_bossCount > LEVEL_BOSS_SELECT_PRESS && g_nSelectLevel_bossCount  % LEVEL_BOSS_SELECT_SPEED == 0)
			{
				g_nSelectLevel_boss++;
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		else
		{
			g_nSelectLevel_bossCount = 0;
		}

		for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
		{
			if (i == g_nSelectLevel_boss % LEVEL_BOSS_MAX)
			{
				level_boss->nPatternAnim = i + LEVEL_BOSS_MAX;
			}
			else
			{
				level_boss->nPatternAnim = i;
			}
			// �e�N�X�`�����W��ݒ�
			SetTextureLevel_boss(i, level_boss->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexLevel_boss(i);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_C))
		{
			// �X�e�[�W�ݒ�
			switch ((g_nSelectLevel_boss % LEVEL_MAX) + ONLY_BOSS + 1)
			{
			case BOSS_EASY:
				SetGameLevel(BOSS_EASY);
				break;
			case BOSS_NORMAL:
				SetGameLevel(BOSS_NORMAL);
				break;
			case BOSS_HARD:
				SetGameLevel(BOSS_HARD);
				break;
			case BOSS_ULTIMATE:
				SetGameLevel(BOSS_ULTIMATE);
				break;
			}

			// ����SE�Đ�
			SetSe(2, E_DS8_FLAG_NONE, true);

			// �X�e�[�W�J��:�Q�[��
			SetStage(STAGE_GAME);
		}

		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_START))
		{
			g_bSelectLevel_ReturnFlag = true;
			SetSe(3, E_DS8_FLAG_NONE, true);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLevel_boss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (level_boss->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, level_boss->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_LEVEL_BOSS, level_boss->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLevel_boss(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	// ���_���W�̐ݒ�
	level_boss->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	level_boss->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL_BOSS00_SIZE_X, 100.0f, 0.0f);
	level_boss->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_LEVEL_BOSS00_SIZE_Y, 0.0f);
	level_boss->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL_BOSS00_SIZE_X, 100.0f+TEXTURE_LEVEL_BOSS00_SIZE_Y, 0.0f);
	//SetVertexLevel_boss();

	// rhw�̐ݒ�
	level_boss->vertexWk[0].rhw =
	level_boss->vertexWk[1].rhw =
	level_boss->vertexWk[2].rhw =
	level_boss->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	level_boss->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level_boss->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	level_boss->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	level_boss->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS, 0.0f );
	level_boss->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS );
	level_boss->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureLevel_boss( int no, int cntPattern )
{
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS;
	level_boss->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	level_boss->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	level_boss->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	level_boss->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexLevel_boss(int no)
{
	LEVEL_BOSS *level_boss = &level_bossWk[no];

	level_boss->vertexWk[0].vtx.x = level_boss->pos.x - TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[0].vtx.y = level_boss->pos.y - TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[0].vtx.z = 0.0f;

	level_boss->vertexWk[1].vtx.x = level_boss->pos.x + TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[1].vtx.y = level_boss->pos.y - TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[1].vtx.z = 0.0f;

	level_boss->vertexWk[2].vtx.x = level_boss->pos.x - TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[2].vtx.y = level_boss->pos.y + TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[2].vtx.z = 0.0f;

	level_boss->vertexWk[3].vtx.x = level_boss->pos.x + TEXTURE_LEVEL_BOSS00_SIZE_X;
	level_boss->vertexWk[3].vtx.y = level_boss->pos.y + TEXTURE_LEVEL_BOSS00_SIZE_Y;
	level_boss->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// ���g�p����
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (!level_boss->bUse)
		{
			// �L���ɂ���
			level_boss->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			level_boss->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			level_boss->nPatternAnim = 0;
			// �e�N�X�`�����W��ݒ�
			SetTextureLevel_boss(i, level_boss->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexLevel_boss(i);
		}
	}
}

//=============================================================================
// �m���A�N�e�B�u����
//=============================================================================
void ReleaseLevel_boss(void)
{
	LEVEL_BOSS *level_boss = &level_bossWk[0];

	// �g�p����
	for (int i = 0; i < LEVEL_BOSS_MAX; i++, level_boss++)
	{
		if (level_boss->bUse)
		{
			// �����ɂ���
			level_boss->bUse = false;
		}
	}
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
LEVEL_BOSS *GetLevel_boss(int no)
{
	return(&level_bossWk[no]);
}

