//=============================================================================
//
// �^�C�g������ [totalboard.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "totalboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTotalboard(int no);
void SetTextureTotalboard( int no, int cntPattern );	//
void SetVertexTotalboard(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TOTALBOARD					totalboardWk[TOTALBOARD_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureTotalboard = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTotalboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TOTALBOARD00,				// �t�@�C���̖��O
			&pD3DTextureTotalboard);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		totalboard->bUse = true;

		totalboard->pos = D3DXVECTOR3((float)TOTALBOARD_POS_X, (float)TOTALBOARD_POS_Y, 0.0f);
		totalboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		totalboard->nCountAnim = 0;
		totalboard->nPatternAnim = 0;

		totalboard->Texture = pD3DTextureTotalboard;			// �e�N�X�`���ւ̃G�l�~�[
		totalboard->size = D3DXVECTOR2(TEXTURE_TOTALBOARD00_SIZE_X, TEXTURE_TOTALBOARD00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexTotalboard(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTotalboard(void)
{
	TOTALBOARD *totalboard = &totalboardWk[0];

	// ���������
	if (pD3DTextureTotalboard != NULL)
	{
		pD3DTextureTotalboard->Release();
		pD3DTextureTotalboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTotalboard(void)
{
	TOTALBOARD *totalboard = &totalboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		if (totalboard->bUse == true)
		{
			// �A�j���[�V����
			totalboard->nCountAnim++;
			if ((totalboard->nCountAnim % TIME_ANIMATION_TOTALBOARD) == 0)
			{
				// �p�^�[���̐؂�ւ�
				totalboard->nPatternAnim = (totalboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_TOTALBOARD;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureTotalboard(i, totalboard->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexTotalboard(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTotalboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TOTALBOARD_MAX; i++, totalboard++)
	{
		if (totalboard->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, totalboard->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TOTALBOARD, totalboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTotalboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TOTALBOARD *totalboard = &totalboardWk[no];

	// ���_���W�̐ݒ�
	totalboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	totalboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TOTALBOARD00_SIZE_X, 100.0f, 0.0f);
	totalboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TOTALBOARD00_SIZE_Y, 0.0f);
	totalboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TOTALBOARD00_SIZE_X, 100.0f+TEXTURE_TOTALBOARD00_SIZE_Y, 0.0f);
	//SetVertexTotalboard();

	// rhw�̐ݒ�
	totalboard->vertexWk[0].rhw =
	totalboard->vertexWk[1].rhw =
	totalboard->vertexWk[2].rhw =
	totalboard->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	totalboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	totalboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	totalboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	totalboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD, 0.0f );
	totalboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD );
	totalboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTotalboard( int no, int cntPattern )
{
	TOTALBOARD *totalboard = &totalboardWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD;
	totalboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	totalboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	totalboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	totalboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexTotalboard(int no)
{
	TOTALBOARD *totalboard = &totalboardWk[no];

	totalboard->vertexWk[0].vtx.x = totalboard->pos.x - TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[0].vtx.y = totalboard->pos.y - TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[0].vtx.z = 0.0f;

	totalboard->vertexWk[1].vtx.x = totalboard->pos.x + TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[1].vtx.y = totalboard->pos.y - TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[1].vtx.z = 0.0f;

	totalboard->vertexWk[2].vtx.x = totalboard->pos.x - TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[2].vtx.y = totalboard->pos.y + TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[2].vtx.z = 0.0f;

	totalboard->vertexWk[3].vtx.x = totalboard->pos.x + TEXTURE_TOTALBOARD00_SIZE_X;
	totalboard->vertexWk[3].vtx.y = totalboard->pos.y + TEXTURE_TOTALBOARD00_SIZE_Y;
	totalboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
TOTALBOARD *GetTotalboard(int no)
{
	return(&totalboardWk[no]);
}

