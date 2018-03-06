//=============================================================================
//
// BG000���� [bg000.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "bg000.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBg000(int no);
void SetTextureBg000( int no, int cntPattern );	//
void SetVertexBg000(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BG000					bg000Wk[BG000_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureBg000 = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBg000(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BG000,				// �t�@�C���̖��O
			&pD3DTextureBg000);			// �ǂݍ��ރ������̃|�C���^
	}

	// BG000�̏�����
	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		bg000->bUse = true;
		bg000->pos = D3DXVECTOR3(TEXTURE_BG000_SIZE_X, TEXTURE_BG000_SIZE_Y, 0.0f);
		bg000->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg000->nCountAnim = 0;
		bg000->nPatternAnim = 0;

		bg000->Texture = pD3DTextureBg000;			// �e�N�X�`���ւ�BG000
		bg000->size = D3DXVECTOR2(TEXTURE_BG000_SIZE_X, TEXTURE_BG000_SIZE_Y);

		// ���_���̍쐬
		MakeVertexBg000(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg000(void)
{
	BG000 *bg000 = &bg000Wk[0];

	// ���������
	if (pD3DTextureBg000 != NULL)
	{
		pD3DTextureBg000->Release();
		pD3DTextureBg000 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg000(void)
{
	BG000 *bg000 = &bg000Wk[0];
	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		if (bg000->bUse == true)
		{
			// �A�j���[�V����
			bg000->nCountAnim++;
			if ((bg000->nCountAnim % TIME_ANIMATION_BG000) == 0)
			{
				// �p�^�[���̐؂�ւ�
				bg000->nPatternAnim = (bg000->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG000;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureBg000(i, bg000->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBg000(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg000(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG000_MAX; i++, bg000++)
	{
		if (bg000->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bg000->Texture);

			// BG000�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG000, bg000->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBg000(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG000 *bg000 = &bg000Wk[no];

	// ���_���W�̐ݒ�
	bg000->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg000->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG000_SIZE_X, 100.0f, 0.0f);
	bg000->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG000_SIZE_Y, 0.0f);
	bg000->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG000_SIZE_X, 100.0f+TEXTURE_BG000_SIZE_Y, 0.0f);
	//SetVertexBg000();

	// rhw�̐ݒ�
	bg000->vertexWk[0].rhw =
	bg000->vertexWk[1].rhw =
	bg000->vertexWk[2].rhw =
	bg000->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bg000->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);
	bg000->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG000_R, TEXTURE_BG000_G, TEXTURE_BG000_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	bg000->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg000->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG000, 0.0f );
	bg000->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG000 );
	bg000->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG000, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG000 );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBg000( int no, int cntPattern )
{
	BG000 *bg000 = &bg000Wk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG000;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG000;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG000;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG000;
	bg000->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg000->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg000->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg000->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexBg000(int no)
{
	BG000 *bg000 = &bg000Wk[no];

	bg000->vertexWk[0].vtx.x = bg000->pos.x - TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[0].vtx.y = bg000->pos.y - TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[0].vtx.z = 0.0f;

	bg000->vertexWk[1].vtx.x = bg000->pos.x + TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[1].vtx.y = bg000->pos.y - TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[1].vtx.z = 0.0f;

	bg000->vertexWk[2].vtx.x = bg000->pos.x - TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[2].vtx.y = bg000->pos.y + TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[2].vtx.z = 0.0f;

	bg000->vertexWk[3].vtx.x = bg000->pos.x + TEXTURE_BG000_SIZE_X;
	bg000->vertexWk[3].vtx.y = bg000->pos.y + TEXTURE_BG000_SIZE_Y;
	bg000->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// BG000�擾�֐�
//=============================================================================
BG000 *GetBg000(int no)
{
	return(&bg000Wk[no]);
}

