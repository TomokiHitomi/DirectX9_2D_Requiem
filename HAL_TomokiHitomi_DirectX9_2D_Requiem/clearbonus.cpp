//=============================================================================
//
// �^�C�g������ [clearbonus.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "clearbonus.h"
#include "input.h"
#include "sound.h"
#include "result.h"
#include "close.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexClearbonus(int no);
void SetTextureClearbonus( int no, int cntPattern );	//
void SetVertexClearbonus(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CLEARBONUS					clearbonusWk[CLEARBONUS_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureClearbonus = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitClearbonus(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_CLEARBONUS00,				// �t�@�C���̖��O
			&pD3DTextureClearbonus);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		clearbonus->bUse = true;

		clearbonus->pos = D3DXVECTOR3((float)CLEARBONUS_POS_X, (float)CLEARBONUS_POS_Y, 0.0f);
		clearbonus->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		clearbonus->nCountAnim = 0;
		clearbonus->nPatternAnim = 0;

		clearbonus->Texture = pD3DTextureClearbonus;			// �e�N�X�`���ւ̃G�l�~�[
		clearbonus->size = D3DXVECTOR2(TEXTURE_CLEARBONUS00_SIZE_X, TEXTURE_CLEARBONUS00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexClearbonus(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitClearbonus(void)
{
	CLEARBONUS *clearbonus = &clearbonusWk[0];

	// ���������
	if (pD3DTextureClearbonus != NULL)
	{
		pD3DTextureClearbonus->Release();
		pD3DTextureClearbonus = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateClearbonus(void)
{
	CLEARBONUS *clearbonus = &clearbonusWk[0];
	CLOSE *close = GetClose(0);

	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		if (clearbonus->bUse )
		{
			// �Q�[���N���A���̂݃g�[�^���X�R�A�{�[�i�X
			if (close->bClearFlag)
			{
				clearbonus->nPatternAnim = 0;
			}
			else
			{
				clearbonus->nPatternAnim = 1;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureClearbonus(i, clearbonus->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexClearbonus(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawClearbonus(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CLEARBONUS_MAX; i++, clearbonus++)
	{
		if (clearbonus->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, clearbonus->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLEARBONUS, clearbonus->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexClearbonus(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	// ���_���W�̐ݒ�
	clearbonus->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	clearbonus->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLEARBONUS00_SIZE_X, 100.0f, 0.0f);
	clearbonus->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CLEARBONUS00_SIZE_Y, 0.0f);
	clearbonus->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLEARBONUS00_SIZE_X, 100.0f+TEXTURE_CLEARBONUS00_SIZE_Y, 0.0f);
	//SetVertexClearbonus();

	// rhw�̐ݒ�
	clearbonus->vertexWk[0].rhw =
	clearbonus->vertexWk[1].rhw =
	clearbonus->vertexWk[2].rhw =
	clearbonus->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	clearbonus->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clearbonus->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	clearbonus->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	clearbonus->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS, 0.0f );
	clearbonus->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS );
	clearbonus->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureClearbonus( int no, int cntPattern )
{
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS;
	clearbonus->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	clearbonus->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	clearbonus->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	clearbonus->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexClearbonus(int no)
{
	CLEARBONUS *clearbonus = &clearbonusWk[no];

	clearbonus->vertexWk[0].vtx.x = clearbonus->pos.x - TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[0].vtx.y = clearbonus->pos.y - TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[0].vtx.z = 0.0f;

	clearbonus->vertexWk[1].vtx.x = clearbonus->pos.x + TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[1].vtx.y = clearbonus->pos.y - TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[1].vtx.z = 0.0f;

	clearbonus->vertexWk[2].vtx.x = clearbonus->pos.x - TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[2].vtx.y = clearbonus->pos.y + TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[2].vtx.z = 0.0f;

	clearbonus->vertexWk[3].vtx.x = clearbonus->pos.x + TEXTURE_CLEARBONUS00_SIZE_X;
	clearbonus->vertexWk[3].vtx.y = clearbonus->pos.y + TEXTURE_CLEARBONUS00_SIZE_Y;
	clearbonus->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
CLEARBONUS *GetClearbonus(int no)
{
	return(&clearbonusWk[no]);
}

