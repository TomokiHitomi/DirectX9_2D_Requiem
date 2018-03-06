//=============================================================================
//
// �^�C�g������ [rankboard.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "rankboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRankboard(int no);
void SetTextureRankboard( int no, int cntPattern );	//
void SetVertexRankboard(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
RANKBOARD					rankboardWk[RANKBOARD_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureRankboard = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRankboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANKBOARD00,				// �t�@�C���̖��O
			&pD3DTextureRankboard);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		rankboard->bUse = true;

		rankboard->pos = D3DXVECTOR3((float)RANKBOARD_POS_X, (float)RANKBOARD_POS_Y, 0.0f);
		rankboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rankboard->nCountAnim = 0;
		rankboard->nPatternAnim = 0;

		rankboard->Texture = pD3DTextureRankboard;			// �e�N�X�`���ւ̃G�l�~�[
		rankboard->size = D3DXVECTOR2(TEXTURE_RANKBOARD00_SIZE_X, TEXTURE_RANKBOARD00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexRankboard(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankboard(void)
{
	RANKBOARD *rankboard = &rankboardWk[0];

	// ���������
	if (pD3DTextureRankboard != NULL)
	{
		pD3DTextureRankboard->Release();
		pD3DTextureRankboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankboard(void)
{
	RANKBOARD *rankboard = &rankboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		if (rankboard->bUse == true)
		{
			// �A�j���[�V����
			rankboard->nCountAnim++;
			if ((rankboard->nCountAnim % TIME_ANIMATION_RANKBOARD) == 0)
			{
				// �p�^�[���̐؂�ւ�
				rankboard->nPatternAnim = (rankboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_RANKBOARD;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureRankboard(i, rankboard->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexRankboard(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RANKBOARD_MAX; i++, rankboard++)
	{
		if (rankboard->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, rankboard->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RANKBOARD, rankboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRankboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKBOARD *rankboard = &rankboardWk[no];

	// ���_���W�̐ݒ�
	rankboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	rankboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANKBOARD00_SIZE_X, 100.0f, 0.0f);
	rankboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_RANKBOARD00_SIZE_Y, 0.0f);
	rankboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_RANKBOARD00_SIZE_X, 100.0f+TEXTURE_RANKBOARD00_SIZE_Y, 0.0f);
	//SetVertexRankboard();

	// rhw�̐ݒ�
	rankboard->vertexWk[0].rhw =
	rankboard->vertexWk[1].rhw =
	rankboard->vertexWk[2].rhw =
	rankboard->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	rankboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	rankboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	rankboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	rankboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANKBOARD, 0.0f );
	rankboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD );
	rankboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_RANKBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRankboard( int no, int cntPattern )
{
	RANKBOARD *rankboard = &rankboardWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_RANKBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD;
	rankboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	rankboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	rankboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	rankboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexRankboard(int no)
{
	RANKBOARD *rankboard = &rankboardWk[no];

	rankboard->vertexWk[0].vtx.x = rankboard->pos.x - TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[0].vtx.y = rankboard->pos.y - TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[0].vtx.z = 0.0f;

	rankboard->vertexWk[1].vtx.x = rankboard->pos.x + TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[1].vtx.y = rankboard->pos.y - TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[1].vtx.z = 0.0f;

	rankboard->vertexWk[2].vtx.x = rankboard->pos.x - TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[2].vtx.y = rankboard->pos.y + TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[2].vtx.z = 0.0f;

	rankboard->vertexWk[3].vtx.x = rankboard->pos.x + TEXTURE_RANKBOARD00_SIZE_X;
	rankboard->vertexWk[3].vtx.y = rankboard->pos.y + TEXTURE_RANKBOARD00_SIZE_Y;
	rankboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
RANKBOARD *GetRankboard(int no)
{
	return(&rankboardWk[no]);
}

