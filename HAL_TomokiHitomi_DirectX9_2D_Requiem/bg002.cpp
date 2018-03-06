//=============================================================================
//
// BG002���� [bg002.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "bg002.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBg002(int no);
void SetTextureBg002( int no, int cntPattern );	//
void SetVertexBg002(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BG002					bg002Wk[BG002_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureBg002 = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBg002(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BG002,				// �t�@�C���̖��O
			&pD3DTextureBg002);			// �ǂݍ��ރ������̃|�C���^
	}

	// BG002�̏�����
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		bg002->bUse = true;
		bg002->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		bg002->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg002->nCountAnim = 0;
		bg002->nPatternAnim = 0;

		bg002->Texture = pD3DTextureBg002;			// �e�N�X�`���ւ�BG002
		bg002->size = D3DXVECTOR2(TEXTURE_BG002_SIZE_X, TEXTURE_BG002_SIZE_Y);

		// ���_���̍쐬
		MakeVertexBg002(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];

	// ���������
	if (pD3DTextureBg002 != NULL)
	{
		pD3DTextureBg002->Release();
		pD3DTextureBg002 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (bg002->bUse == true)
		{
			// �A�j���[�V����
			bg002->nCountAnim++;
			if ((bg002->nCountAnim % TIME_ANIMATION_BG002) == 0)
			{
				// �p�^�[���̐؂�ւ�
				bg002->nPatternAnim = (bg002->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG002;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureBg002(i, bg002->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBg002(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg002(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (bg002->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bg002->Texture);

			// BG002�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG002, bg002->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBg002(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG002 *bg002 = &bg002Wk[no];

	// ���_���W�̐ݒ�
	bg002->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg002->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG002_SIZE_X, 100.0f, 0.0f);
	bg002->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG002_SIZE_Y, 0.0f);
	bg002->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG002_SIZE_X, 100.0f+TEXTURE_BG002_SIZE_Y, 0.0f);
	//SetVertexBg002();

	// rhw�̐ݒ�
	bg002->vertexWk[0].rhw =
	bg002->vertexWk[1].rhw =
	bg002->vertexWk[2].rhw =
	bg002->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bg002->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);
	bg002->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG002_R, TEXTURE_BG002_G, TEXTURE_BG002_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	bg002->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg002->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG002, 0.0f );
	bg002->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG002 );
	bg002->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG002, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG002 );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBg002( int no, int cntPattern )
{
	BG002 *bg002 = &bg002Wk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG002;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG002;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG002;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG002;
	bg002->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg002->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg002->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg002->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexBg002(int no)
{
	BG002 *bg002 = &bg002Wk[no];

	bg002->vertexWk[0].vtx.x = bg002->pos.x - TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[0].vtx.y = bg002->pos.y - TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[0].vtx.z = 0.0f;

	bg002->vertexWk[1].vtx.x = bg002->pos.x + TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[1].vtx.y = bg002->pos.y - TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[1].vtx.z = 0.0f;

	bg002->vertexWk[2].vtx.x = bg002->pos.x - TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[2].vtx.y = bg002->pos.y + TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[2].vtx.z = 0.0f;

	bg002->vertexWk[3].vtx.x = bg002->pos.x + TEXTURE_BG002_SIZE_X;
	bg002->vertexWk[3].vtx.y = bg002->pos.y + TEXTURE_BG002_SIZE_Y;
	bg002->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetBg002(void)
{
	BG002 *bg002 = &bg002Wk[0];

	// ���g�p����
	for (int i = 0; i < BG002_MAX; i++, bg002++)
	{
		if (!bg002->bUse)
		{
			// �L���ɂ���
			bg002->bUse = true;
			return;
		}
	}
}

//=============================================================================
// BG002�擾�֐�
//=============================================================================
BG002 *GetBg002(int no)
{
	return(&bg002Wk[no]);
}

