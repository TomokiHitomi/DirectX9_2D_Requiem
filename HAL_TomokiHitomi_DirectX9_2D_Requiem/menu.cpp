//=============================================================================
//
// �^�C�g������ [menu.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "menu.h"
#include "input.h"
#include "sound.h"
#include "credit.h"
#include "level.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMenu(int no);
void SetTextureMenu( int no, int cntPattern );
void SetVertexMenu(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
MENU					menuWk[MENU_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureMenu = NULL;

int g_nSelectMenu;
int g_nSelectMenuCount;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMenu(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MENU00,				// �t�@�C���̖��O
			&pD3DTextureMenu);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		menu->bUse = true;
		menu->pos = D3DXVECTOR3((float)MENU_POS_X, i*(float)MENU_SPACING + (float)MENU_POS_Y, 0.0f);
		menu->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		menu->nCountAnim = 0;
		menu->nPatternAnim = 0;

		menu->Texture = pD3DTextureMenu;			// �e�N�X�`���ւ̃G�l�~�[
		menu->size = D3DXVECTOR2(TEXTURE_MENU00_SIZE_X, TEXTURE_MENU00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexMenu(i);
	}

	g_nSelectMenu = 0;
	g_nSelectMenuCount = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMenu(void)
{
	MENU *menu = &menuWk[0];

	// ���������
	if (pD3DTextureMenu != NULL)
	{
		pD3DTextureMenu->Release();
		pD3DTextureMenu = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMenu(void)
{
	MENU *menu = &menuWk[0];

	if (menu->bUse)
	{
		// ��ړ�
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W)
			|| IsButtonTriggered(0, BUTTON_UP) || IsButtonTriggered(0, LSTICK_UP))
		{
			g_nSelectMenu--;
			if (g_nSelectMenu < 0)
			{
				g_nSelectMenu += MENU_MAX;
			}
			SetSe(1, E_DS8_FLAG_NONE, true);
		}
		// ���ړ�
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_DOWN) || IsButtonTriggered(0, LSTICK_DOWN))
		{
			g_nSelectMenu++;
			SetSe(1, E_DS8_FLAG_NONE, true);
		}

		// ��ړ�������
		if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)
			|| IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, LSTICK_UP))
		{
			g_nSelectMenuCount++;
			if (g_nSelectMenuCount > MENU_SELECT_PRESS && g_nSelectMenuCount % MENU_SELECT_SPEED == 0)
			{
				g_nSelectMenu--;
				if (g_nSelectMenu < 0)
				{
					g_nSelectMenu += MENU_MAX;
				}
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		// ���ړ�������
		else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, LSTICK_DOWN))
		{
			g_nSelectMenuCount++;
			if (g_nSelectMenuCount > MENU_SELECT_PRESS && g_nSelectMenuCount  % MENU_SELECT_SPEED == 0)
			{
				g_nSelectMenu++;
				SetSe(1, E_DS8_FLAG_NONE, true);
			}
		}
		else
		{
			g_nSelectMenuCount = 0;
		}


		for (int i = 0; i < MENU_MAX; i++, menu++)
		{
			if (i == g_nSelectMenu % MENU_MAX)
			{
				menu->nPatternAnim = i + MENU_MAX;
			}
			else
			{
				menu->nPatternAnim = i;
			}
			// �e�N�X�`�����W��ݒ�
			SetTextureMenu(i, menu->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexMenu(i);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_C))
		{
			switch (g_nSelectMenu % MENU_MAX)
			{
			case 0:
				ReleaseMenu();
				SetLevel();
				break;
			case 1:
				InitGame(1);
				SetStage(STAGE_TUTORIAL);
				break;
			case 2:
				InitGame(1);
				SetStage(STAGE_CREDIT);
				break;
			case 3:
				SetEndFlag();
				break;
			}
			SetSe(2, E_DS8_FLAG_NONE, true);
		}
		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B))
		{
			SetSe(3, E_DS8_FLAG_NONE, true);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (menu->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, menu->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MENU, menu->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMenu(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[no];

	// ���_���W�̐ݒ�
	menu->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	menu->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MENU00_SIZE_X, 100.0f, 0.0f);
	menu->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MENU00_SIZE_Y, 0.0f);
	menu->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MENU00_SIZE_X, 100.0f+TEXTURE_MENU00_SIZE_Y, 0.0f);
	//SetVertexMenu();

	// rhw�̐ݒ�
	menu->vertexWk[0].rhw =
	menu->vertexWk[1].rhw =
	menu->vertexWk[2].rhw =
	menu->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	menu->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	menu->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	menu->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	menu->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MENU, 0.0f );
	menu->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MENU );
	menu->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MENU, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MENU );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMenu( int no, int cntPattern )
{
	MENU *menu = &menuWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MENU;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MENU;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MENU;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MENU;
	menu->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	menu->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	menu->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	menu->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexMenu(int no)
{
	MENU *menu = &menuWk[no];

	menu->vertexWk[0].vtx.x = menu->pos.x - TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[0].vtx.y = menu->pos.y - TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[0].vtx.z = 0.0f;

	menu->vertexWk[1].vtx.x = menu->pos.x + TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[1].vtx.y = menu->pos.y - TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[1].vtx.z = 0.0f;

	menu->vertexWk[2].vtx.x = menu->pos.x - TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[2].vtx.y = menu->pos.y + TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[2].vtx.z = 0.0f;

	menu->vertexWk[3].vtx.x = menu->pos.x + TEXTURE_MENU00_SIZE_X;
	menu->vertexWk[3].vtx.y = menu->pos.y + TEXTURE_MENU00_SIZE_Y;
	menu->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetMenu(void)
{
	MENU *menu = &menuWk[0];

	// ���g�p����
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (!menu->bUse)
		{
			// �L���ɂ���
			menu->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			menu->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			menu->nPatternAnim = 0;
		}
	}
}

//=============================================================================
// �m���A�N�e�B�u����
//=============================================================================
void ReleaseMenu(void)
{
	MENU *menu = &menuWk[0];

	// �g�p����
	for (int i = 0; i < MENU_MAX; i++, menu++)
	{
		if (menu->bUse)
		{
			// �����ɂ���
			menu->bUse = false;
		}
	}
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
MENU *GetMenu(int no)
{
	return(&menuWk[no]);
}

