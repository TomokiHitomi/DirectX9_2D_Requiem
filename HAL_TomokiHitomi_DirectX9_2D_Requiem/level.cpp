//=============================================================================
//
// �^�C�g������ [level.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "level.h"
#include "level_boss.h"
#include "input.h"
#include "sound.h"
#include "credit.h"
#include "menu.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLevel(int no);
void SetTextureLevel( int no, int cntPattern );
void SetVertexLevel(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LEVEL					levelWk[LEVEL_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureLevel = NULL;

int g_nSelectLevel;
int g_nSelectLevelCount;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLevel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL *level = &levelWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_LEVEL00,				// �t�@�C���̖��O
			&pD3DTextureLevel);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < LEVEL_MAX; i++, level++)
	{
		level->bUse = false;
		level->pos = D3DXVECTOR3((float)LEVEL_POS_X, i*(float)LEVEL_SPACING + (float)LEVEL_POS_Y, 0.0f);
		level->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		level->nCountAnim = 0;
		level->nPatternAnim = 0;

		level->Texture = pD3DTextureLevel;			// �e�N�X�`���ւ̃G�l�~�[
		level->size = D3DXVECTOR2(TEXTURE_LEVEL00_SIZE_X, TEXTURE_LEVEL00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexLevel(i);
	}

	g_nSelectLevel = 0;
	g_nSelectLevelCount = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLevel(void)
{
	LEVEL *level = &levelWk[0];

	// ���������
	if (pD3DTextureLevel != NULL)
	{
		pD3DTextureLevel->Release();
		pD3DTextureLevel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLevel(void)
{
	LEVEL *level = &levelWk[0];
	if (level->bUse)
	{
		// ��ړ�
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W)
			|| IsButtonTriggered(0, BUTTON_UP) || IsButtonTriggered(0, LSTICK_UP))
		{
			g_nSelectLevel--;
			if (g_nSelectLevel < 0)
			{
				g_nSelectLevel += LEVEL_MAX;
			}
			SetSe(1, E_DS8_FLAG_NONE, true);
		}
		// ���ړ�
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_DOWN) || IsButtonTriggered(0, LSTICK_DOWN))
		{
			g_nSelectLevel++;
			SetSe(1, E_DS8_FLAG_NONE, true);
		}

		// ��ړ�������
		if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)
			|| IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, LSTICK_UP))
		{
			g_nSelectLevelCount++;
			if (g_nSelectLevelCount > LEVEL_SELECT_PRESS && g_nSelectLevelCount % LEVEL_SELECT_SPEED == 0)
			{
				g_nSelectLevel--;
				if (g_nSelectLevel < 0)
				{
					g_nSelectLevel += LEVEL_MAX;
				}
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		// ���ړ�������
		else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, LSTICK_DOWN))
		{
			g_nSelectLevelCount++;
			if (g_nSelectLevelCount > LEVEL_SELECT_PRESS && g_nSelectLevelCount  % LEVEL_SELECT_SPEED == 0)
			{
				g_nSelectLevel++;
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		else
		{
			g_nSelectLevelCount = 0;
		}

		for (int i = 0; i < LEVEL_MAX; i++, level++)
		{
			if (i == g_nSelectLevel % LEVEL_MAX)
			{
				level->nPatternAnim = i + LEVEL_MAX;
			}
			else
			{
				level->nPatternAnim = i;
			}
			// �e�N�X�`�����W��ݒ�
			SetTextureLevel(i, level->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexLevel(i);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_C))
		{
			// �X�e�[�W�ݒ�
			switch (g_nSelectLevel % LEVEL_MAX)
			{
			case EASY:
				SetGameLevel(EASY);
				break;
			case NORMAL:
				SetGameLevel(NORMAL);
				break;
			case HARD:
				SetGameLevel(HARD);
				break;
			case ONLY_BOSS:
				ReleaseLevel();
				SetLevel_boss();
				break;
			}

			// ����SE�Đ�
			SetSe(2, E_DS8_FLAG_NONE, true);
			if (g_nSelectLevel % LEVEL_MAX != ONLY_BOSS)
			{
				// �X�e�[�W�J��:�Q�[��
				SetStage(STAGE_GAME);
			}
		}

		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_START))
		{
			ReleaseLevel();
			SetMenu();
			SetSe(3, E_DS8_FLAG_NONE, true);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLevel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL *level = &levelWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < LEVEL_MAX; i++, level++)
	{
		if (level->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, level->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_LEVEL, level->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLevel(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LEVEL *level = &levelWk[no];

	// ���_���W�̐ݒ�
	level->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	level->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL00_SIZE_X, 100.0f, 0.0f);
	level->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_LEVEL00_SIZE_Y, 0.0f);
	level->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_LEVEL00_SIZE_X, 100.0f+TEXTURE_LEVEL00_SIZE_Y, 0.0f);
	//SetVertexLevel();

	// rhw�̐ݒ�
	level->vertexWk[0].rhw =
	level->vertexWk[1].rhw =
	level->vertexWk[2].rhw =
	level->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	level->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	level->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	level->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	level->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL, 0.0f );
	level->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL );
	level->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_LEVEL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LEVEL );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureLevel( int no, int cntPattern )
{
	LEVEL *level = &levelWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_LEVEL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_LEVEL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_LEVEL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LEVEL;
	level->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	level->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	level->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	level->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexLevel(int no)
{
	LEVEL *level = &levelWk[no];

	level->vertexWk[0].vtx.x = level->pos.x - TEXTURE_LEVEL00_SIZE_X;
	level->vertexWk[0].vtx.y = level->pos.y - TEXTURE_LEVEL00_SIZE_Y;
	level->vertexWk[0].vtx.z = 0.0f;

	level->vertexWk[1].vtx.x = level->pos.x + TEXTURE_LEVEL00_SIZE_X;
	level->vertexWk[1].vtx.y = level->pos.y - TEXTURE_LEVEL00_SIZE_Y;
	level->vertexWk[1].vtx.z = 0.0f;

	level->vertexWk[2].vtx.x = level->pos.x - TEXTURE_LEVEL00_SIZE_X;
	level->vertexWk[2].vtx.y = level->pos.y + TEXTURE_LEVEL00_SIZE_Y;
	level->vertexWk[2].vtx.z = 0.0f;

	level->vertexWk[3].vtx.x = level->pos.x + TEXTURE_LEVEL00_SIZE_X;
	level->vertexWk[3].vtx.y = level->pos.y + TEXTURE_LEVEL00_SIZE_Y;
	level->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetLevel(void)
{
	LEVEL *level = &levelWk[0];

	// ���g�p����
	for (int i = 0; i < LEVEL_MAX; i++, level++)
	{
		if (!level->bUse)
		{
			// �L���ɂ���
			level->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			level->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			level->nPatternAnim = 0;
			// �e�N�X�`�����W��ݒ�
			SetTextureLevel(i, level->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexLevel(i);
		}
	}
}

//=============================================================================
// �m���A�N�e�B�u����
//=============================================================================
void ReleaseLevel(void)
{
	LEVEL *level = &levelWk[0];

	// �g�p����
	for (int i = 0; i < LEVEL_MAX; i++, level++)
	{
		if (level->bUse)
		{
			// �����ɂ���
			level->bUse = false;
		}
	}
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
LEVEL *GetLevel(int no)
{
	return(&levelWk[no]);
}

