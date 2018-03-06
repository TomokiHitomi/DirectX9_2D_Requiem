//=======================================================================Hitcircle======
//
// �v���C���[���� [nogravity.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "nogravity.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexNogravity(int no);
void SetTextureNogravity( int no, int cntPattern );	//
void SetVertexNogravity(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
NOGRAVITY					nogravityWk[NOGRAVITY_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureNogravity = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitNogravity(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_NOGRAVITY00,				// �t�@�C���̖��O
			&pD3DTextureNogravity);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		nogravity->bUse = true;
		nogravity->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		nogravity->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		nogravity->nCountAnim = 0;
		nogravity->nPatternAnim = 0;
		nogravity->nScaling = TEXTURE_NOGRAVITY00_SIZE_X;
		nogravity->Texture = pD3DTextureNogravity;			// �e�N�X�`���ւ̃G�l�~�[
		nogravity->size = D3DXVECTOR2(TEXTURE_NOGRAVITY00_SIZE_X, TEXTURE_NOGRAVITY00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexNogravity(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitNogravity(void)
{
	NOGRAVITY *nogravity = &nogravityWk[0];

	// ���������
	if (pD3DTextureNogravity != NULL)
	{
		pD3DTextureNogravity->Release();
		pD3DTextureNogravity = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateNogravity(void)
{
	NOGRAVITY *nogravity = &nogravityWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		if (player->bUse)
		{
			nogravity->bUse = true;
			// �A�j���[�V����
			nogravity->nCountAnim++;
			if ((nogravity->nCountAnim % TIME_ANIMATION_NOGRAVITY) == 0)
			{
				// �p�^�[���̐؂�ւ�
				nogravity->nPatternAnim = (nogravity->nPatternAnim + 1) % ANIM_PATTERN_NUM_NOGRAVITY;
			}
			nogravity->pos.x = player->pos.x + NOGRAVITY_ADJUSTMENT_X;
			nogravity->pos.y = player->pos.y + NOGRAVITY_ADJUSTMENT_Y;
		}
		else
		{
			nogravity->bUse = false;
		}

		// ���d�̓��[�h
		if ((GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R) || GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L)) && player->fManaPoint >= 50.0f)
		{
			nogravity->nScaling += TEXTURE_NOGRAVITY00_SCALING_SPEED;
			if (nogravity->nScaling >= TEXTURE_NOGRAVITY00_SCALING_MAX)
			{
				nogravity->nScaling = TEXTURE_NOGRAVITY00_SCALING_MAX;
			}
		}
		else
		{
			nogravity->nScaling -= TEXTURE_NOGRAVITY00_SCALING_SPEED;
			if (nogravity->nScaling <= TEXTURE_NOGRAVITY00_SIZE_X)
			{
				nogravity->nScaling = TEXTURE_NOGRAVITY00_SIZE_X;
			}
		}

		// �e�N�X�`�����W��ݒ�
		SetTextureNogravity(i, nogravity->nPatternAnim);
		// �ړ���̍��W�Œ��_��ݒ�
		SetVertexNogravity(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawNogravity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NOGRAVITY_MAX; i++, nogravity++)
	{
		if (nogravity->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nogravity->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_NOGRAVITY, nogravity->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexNogravity(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOGRAVITY *nogravity = &nogravityWk[no];

	// ���_���W�̐ݒ�
	nogravity->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	nogravity->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_NOGRAVITY00_SIZE_X, 100.0f, 0.0f);
	nogravity->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_NOGRAVITY00_SIZE_Y, 0.0f);
	nogravity->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_NOGRAVITY00_SIZE_X, 100.0f+TEXTURE_NOGRAVITY00_SIZE_Y, 0.0f);
	//SetVertexNogravity();

	// rhw�̐ݒ�
	nogravity->vertexWk[0].rhw =
	nogravity->vertexWk[1].rhw =
	nogravity->vertexWk[2].rhw =
	nogravity->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	nogravity->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);
	nogravity->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, NOGRAVITY_ALPHA);

	// �e�N�X�`�����W�̐ݒ�
	nogravity->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	nogravity->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY, 0.0f );
	nogravity->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY );
	nogravity->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureNogravity( int no, int cntPattern )
{
	NOGRAVITY *nogravity = &nogravityWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY;
	nogravity->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	nogravity->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	nogravity->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	nogravity->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexNogravity(int no)
{
	NOGRAVITY *nogravity = &nogravityWk[no];

	nogravity->vertexWk[0].vtx.x = nogravity->pos.x - nogravity->nScaling;
	nogravity->vertexWk[0].vtx.y = nogravity->pos.y - nogravity->nScaling;
	nogravity->vertexWk[0].vtx.z = 0.0f;

	nogravity->vertexWk[1].vtx.x = nogravity->pos.x + nogravity->nScaling;
	nogravity->vertexWk[1].vtx.y = nogravity->pos.y - nogravity->nScaling;
	nogravity->vertexWk[1].vtx.z = 0.0f;

	nogravity->vertexWk[2].vtx.x = nogravity->pos.x - nogravity->nScaling;
	nogravity->vertexWk[2].vtx.y = nogravity->pos.y + nogravity->nScaling;
	nogravity->vertexWk[2].vtx.z = 0.0f;

	nogravity->vertexWk[3].vtx.x = nogravity->pos.x + nogravity->nScaling;
	nogravity->vertexWk[3].vtx.y = nogravity->pos.y + nogravity->nScaling;
	nogravity->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
NOGRAVITY *GetNogravity(int no)
{
	return(&nogravityWk[no]);
}

