//=============================================================================
//
// �v���C���[���� [motion_title.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "motion_title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMotion_title(int no);
void SetTextureMotion_title( int no, int cntPattern );
void SetVertexMotion_title(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
MOTION_TITLE					motion_titleWk[MOTION_TITLE_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureMotion_title = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMotion_title(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MOTION_TITLE,				// �t�@�C���̖��O
			&pD3DTextureMotion_title);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		motion_title->bUse = true;
		motion_title->bFlap = false;
		motion_title->pos = D3DXVECTOR3((float)MOTION_TITLE_POS_X, (float)MOTION_TITLE_POS_Y, 0.0f);
		motion_title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		motion_title->nCountAnim = 0;
		motion_title->nPatternAnim = 0;
		motion_title->Texture = pD3DTextureMotion_title;			// �e�N�X�`���ւ̃G�l�~�[
		motion_title->size = D3DXVECTOR2(TEXTURE_MOTION_TITLE00_SIZE_X, TEXTURE_MOTION_TITLE00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexMotion_title(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// ���������
	if (pD3DTextureMotion_title != NULL)
	{
		pD3DTextureMotion_title->Release();
		pD3DTextureMotion_title = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (motion_title->bUse)
		{
			// �A�j���[�V����
			motion_title->nCountAnim++;
			if (motion_title->nCountAnim % TIME_ANIMATION_MOTION_TITLE == 0)
			{	// �p�^�[���̐؂�ւ�
				if (!motion_title->bFlap)
				{
					motion_title->nPatternAnim = (motion_title->nPatternAnim + 1) % ANIM_PATTERN_NUM_MOTION_TITLE;
					if (motion_title->nPatternAnim >= ANIM_PATTERN_NUM_MOTION_TITLE-1)
					{
						motion_title->bFlap = true;
					}
				}
				else
				{
					motion_title->nPatternAnim = (motion_title->nPatternAnim - 1) % ANIM_PATTERN_NUM_MOTION_TITLE;
					if (motion_title->nPatternAnim <= 0)
					{
						motion_title->bFlap = false;
					}
				}
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureMotion_title(i, motion_title->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexMotion_title(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMotion_title(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (motion_title->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, motion_title->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MOTION_TITLE, motion_title->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMotion_title(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	// ���_���W�̐ݒ�
	motion_title->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	motion_title->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_TITLE00_SIZE_X, 100.0f, 0.0f);
	motion_title->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MOTION_TITLE00_SIZE_Y, 0.0f);
	motion_title->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_TITLE00_SIZE_X, 100.0f+TEXTURE_MOTION_TITLE00_SIZE_Y, 0.0f);
	//SetVertexMotion_title();

	// rhw�̐ݒ�
	motion_title->vertexWk[0].rhw =
	motion_title->vertexWk[1].rhw =
	motion_title->vertexWk[2].rhw =
	motion_title->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	motion_title->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_title->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	motion_title->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	motion_title->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE, 0.0f );
	motion_title->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE );
	motion_title->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMotion_title( int no, int cntPattern )
{
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE;
	motion_title->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	motion_title->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	motion_title->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	motion_title->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexMotion_title(int no)
{
	MOTION_TITLE *motion_title = &motion_titleWk[no];

	motion_title->vertexWk[0].vtx.x = motion_title->pos.x - TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[0].vtx.y = motion_title->pos.y - TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[0].vtx.z = 0.0f;

	motion_title->vertexWk[1].vtx.x = motion_title->pos.x + TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[1].vtx.y = motion_title->pos.y - TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[1].vtx.z = 0.0f;

	motion_title->vertexWk[2].vtx.x = motion_title->pos.x - TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[2].vtx.y = motion_title->pos.y + TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[2].vtx.z = 0.0f;

	motion_title->vertexWk[3].vtx.x = motion_title->pos.x + TEXTURE_MOTION_TITLE00_SIZE_X;
	motion_title->vertexWk[3].vtx.y = motion_title->pos.y + TEXTURE_MOTION_TITLE00_SIZE_Y;
	motion_title->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
void SetMotion_title(void)
{
	MOTION_TITLE *motion_title = &motion_titleWk[0];

	// ���g�p����
	for (int i = 0; i < MOTION_TITLE_MAX; i++, motion_title++)
	{
		if (!motion_title->bUse)
		{
			// �L���ɂ���
			motion_title->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			motion_title->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			motion_title->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
MOTION_TITLE *GetMotion_title(int no)
{
	return(&motion_titleWk[no]);
}

