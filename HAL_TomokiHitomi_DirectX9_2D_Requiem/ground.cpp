//=============================================================================
//
// �^�C�g������ [ground.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "ground.h"
#include "input.h"
#include "sound.h"
#include "close.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGround(int no);
void SetTextureGround( int no, int cntPattern );	//
void SetVertexGround(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GROUND					groundWk[GROUND_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureGround = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGround(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_GROUND00,				// �t�@�C���̖��O
			&pD3DTextureGround);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		ground->bUse = true;
		ground->pos = D3DXVECTOR3(i*((float)TEXTURE_GROUND_SIZE_X * 2) + (float)GROUND_POS_X, (float)GROUND_POS_Y, 0.0f);
		ground->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ground->nCountAnim = 0;
		ground->nPatternAnim = 0;

		ground->Texture = pD3DTextureGround;			// �e�N�X�`���ւ̃G�l�~�[
		ground->size = D3DXVECTOR2(TEXTURE_GROUND_SIZE_X, TEXTURE_GROUND_SIZE_Y);

		// ���_���̍쐬
		MakeVertexGround(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGround(void)
{
	GROUND *ground = &groundWk[0];

	// ���������
	if (pD3DTextureGround != NULL)
	{
		pD3DTextureGround->Release();
		pD3DTextureGround = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGround(void)
{
	GROUND *ground = &groundWk[0];

	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		if (ground->bUse)
		{
			// �A�j���[�V����
			ground->nCountAnim++;
			if ((ground->nCountAnim % TIME_ANIMATION_GROUND) == 0)
			{
				// �p�^�[���̐؂�ւ�
				ground->nPatternAnim = (ground->nPatternAnim + 1) % ANIM_PATTERN_NUM_GROUND;
			}

			ground->pos.x -= GROUND_SPEED;

			if (ground->pos.x <= -150)
			{
				ground->pos.x =((GROUND_POS_X*2)*GROUND_MAX) - GROUND_POS_X;
			}


			// �e�N�X�`�����W��ݒ�
			SetTextureGround(i, ground->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexGround(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GROUND_MAX; i++, ground++)
	{
		if (ground->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, ground->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GROUND, ground->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGround(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GROUND *ground = &groundWk[no];

	// ���_���W�̐ݒ�
	ground->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	ground->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_GROUND_SIZE_X, 100.0f, 0.0f);
	ground->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_GROUND_SIZE_Y, 0.0f);
	ground->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_GROUND_SIZE_X, 100.0f+TEXTURE_GROUND_SIZE_Y, 0.0f);
	//SetVertexGround();

	// rhw�̐ݒ�
	ground->vertexWk[0].rhw =
	ground->vertexWk[1].rhw =
	ground->vertexWk[2].rhw =
	ground->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	ground->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);
	ground->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GROUND_R, TEXTURE_GROUND_G, TEXTURE_GROUND_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	ground->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	ground->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_GROUND, 0.0f );
	ground->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_GROUND );
	ground->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_GROUND, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_GROUND );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureGround( int no, int cntPattern )
{
	GROUND *ground = &groundWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_GROUND;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_GROUND;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_GROUND;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GROUND;
	ground->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ground->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ground->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ground->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexGround(int no)
{
	GROUND *ground = &groundWk[no];

	ground->vertexWk[0].vtx.x = ground->pos.x - TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[0].vtx.y = ground->pos.y - TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[0].vtx.z = 0.0f;

	ground->vertexWk[1].vtx.x = ground->pos.x + TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[1].vtx.y = ground->pos.y - TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[1].vtx.z = 0.0f;

	ground->vertexWk[2].vtx.x = ground->pos.x - TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[2].vtx.y = ground->pos.y + TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[2].vtx.z = 0.0f;

	ground->vertexWk[3].vtx.x = ground->pos.x + TEXTURE_GROUND_SIZE_X;
	ground->vertexWk[3].vtx.y = ground->pos.y + TEXTURE_GROUND_SIZE_Y;
	ground->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
GROUND *GetGround(int no)
{
	return(&groundWk[no]);
}

