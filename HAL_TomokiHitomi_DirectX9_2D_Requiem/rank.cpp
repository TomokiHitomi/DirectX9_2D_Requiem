//=============================================================================
//
// �^�C�g������ [rank.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "rank.h"
#include "input.h"
#include "sound.h"
#include "result.h"
#include "close.h"
#include "total.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRank(int no);
void SetTextureRank( int no, int cntPattern );	//
void SetVertexRank(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
RANK					rankWk[RANK_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureRank = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRank(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK00,				// �t�@�C���̖��O
			&pD3DTextureRank);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		rank->bUse = true;

		rank->pos = D3DXVECTOR3((float)RANK_POS_X, (float)RANK_POS_Y, 0.0f);
		rank->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rank->nCountAnim = 0;
		rank->nPatternAnim = 0;

		rank->Texture = pD3DTextureRank;			// �e�N�X�`���ւ̃G�l�~�[
		rank->size = D3DXVECTOR2(TEXTURE_RANK00_SIZE_X, TEXTURE_RANK00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexRank(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRank(void)
{
	RANK *rank = &rankWk[0];

	// ���������
	if (pD3DTextureRank != NULL)
	{
		pD3DTextureRank->Release();
		pD3DTextureRank = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRank(void)
{
	RANK *rank = &rankWk[0];
	int *total = GetTotal();

	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		if (rank->bUse )
		{
			// �Q�[���N���A���̂݃g�[�^���X�R�A�{�[�i�X
			if (*total >= RANK_S)
			{
				// S�����N�\��
				rank->nPatternAnim = 0;
			}
			else if (*total >= RANK_A)
			{
				// A�����N�\��
				rank->nPatternAnim = 1;
			}
			else if (*total >= RANK_B)
			{
				// B�����N�\��
				rank->nPatternAnim = 2;
			}
			else if (*total >= RANK_C)
			{
				// C�����N�\��
				rank->nPatternAnim = 3;
			}
			else
			{
				// D�����N�\��
				rank->nPatternAnim = 4;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureRank(i, rank->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexRank(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RANK_MAX; i++, rank++)
	{
		if (rank->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, rank->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RANK, rank->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRank(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANK *rank = &rankWk[no];

	// ���_���W�̐ݒ�
	rank->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	rank->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANK00_SIZE_X, 100.0f, 0.0f);
	rank->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_RANK00_SIZE_Y, 0.0f);
	rank->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANK00_SIZE_X, 100.0f+TEXTURE_RANK00_SIZE_Y, 0.0f);
	//SetVertexRank();

	// rhw�̐ݒ�
	rank->vertexWk[0].rhw =
	rank->vertexWk[1].rhw =
	rank->vertexWk[2].rhw =
	rank->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	rank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	rank->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	rank->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANK, 0.0f );
	rank->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANK );
	rank->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANK );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRank( int no, int cntPattern )
{
	RANK *rank = &rankWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_RANK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_RANK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_RANK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_RANK;
	rank->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	rank->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	rank->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	rank->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexRank(int no)
{
	RANK *rank = &rankWk[no];

	rank->vertexWk[0].vtx.x = rank->pos.x - TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[0].vtx.y = rank->pos.y - TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[0].vtx.z = 0.0f;

	rank->vertexWk[1].vtx.x = rank->pos.x + TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[1].vtx.y = rank->pos.y - TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[1].vtx.z = 0.0f;

	rank->vertexWk[2].vtx.x = rank->pos.x - TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[2].vtx.y = rank->pos.y + TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[2].vtx.z = 0.0f;

	rank->vertexWk[3].vtx.x = rank->pos.x + TEXTURE_RANK00_SIZE_X;
	rank->vertexWk[3].vtx.y = rank->pos.y + TEXTURE_RANK00_SIZE_Y;
	rank->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
RANK *GetRank(int no)
{
	return(&rankWk[no]);
}

