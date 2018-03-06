//=============================================================================
//
// �v���C���[���� [motion_result.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "motion_result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMotion_result(int no);
void SetTextureMotion_result( int no, int cntPattern );
void SetVertexMotion_result(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
MOTION_RESULT					motion_resultWk[MOTION_RESULT_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureMotion_result = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMotion_result(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MOTION_RESULT,				// �t�@�C���̖��O
			&pD3DTextureMotion_result);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		motion_result->bUse = false;
		motion_result->pos = D3DXVECTOR3((float)MOTION_RESULT_POS_X, (float)MOTION_RESULT_POS_Y, 0.0f);
		motion_result->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		motion_result->nCountAnim = 0;
		motion_result->nPatternAnim = 0;
		motion_result->Texture = pD3DTextureMotion_result;			// �e�N�X�`���ւ̃G�l�~�[
		motion_result->size = D3DXVECTOR2(TEXTURE_MOTION_RESULT00_SIZE_X, TEXTURE_MOTION_RESULT00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexMotion_result(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// ���������
	if (pD3DTextureMotion_result != NULL)
	{
		pD3DTextureMotion_result->Release();
		pD3DTextureMotion_result = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (motion_result->bUse)
		{
			// �A�j���[�V����
			motion_result->nCountAnim++;
			if (motion_result->nCountAnim % TIME_ANIMATION_MOTION_RESULT == 0)
			{	// �p�^�[���̐؂�ւ�
				motion_result->nPatternAnim = (motion_result->nPatternAnim + 1) % ANIM_PATTERN_NUM_MOTION_RESULT;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureMotion_result(i, motion_result->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexMotion_result(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMotion_result(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (motion_result->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, motion_result->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MOTION_RESULT, motion_result->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMotion_result(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	// ���_���W�̐ݒ�
	motion_result->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	motion_result->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_RESULT00_SIZE_X, 100.0f, 0.0f);
	motion_result->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_MOTION_RESULT00_SIZE_Y, 0.0f);
	motion_result->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_MOTION_RESULT00_SIZE_X, 100.0f+TEXTURE_MOTION_RESULT00_SIZE_Y, 0.0f);
	//SetVertexMotion_result();

	// rhw�̐ݒ�
	motion_result->vertexWk[0].rhw =
	motion_result->vertexWk[1].rhw =
	motion_result->vertexWk[2].rhw =
	motion_result->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	motion_result->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	motion_result->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	motion_result->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	motion_result->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT, 0.0f );
	motion_result->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT );
	motion_result->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMotion_result( int no, int cntPattern )
{
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT;
	motion_result->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	motion_result->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	motion_result->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	motion_result->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexMotion_result(int no)
{
	MOTION_RESULT *motion_result = &motion_resultWk[no];

	motion_result->vertexWk[0].vtx.x = motion_result->pos.x - TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[0].vtx.y = motion_result->pos.y - TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[0].vtx.z = 0.0f;

	motion_result->vertexWk[1].vtx.x = motion_result->pos.x + TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[1].vtx.y = motion_result->pos.y - TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[1].vtx.z = 0.0f;

	motion_result->vertexWk[2].vtx.x = motion_result->pos.x - TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[2].vtx.y = motion_result->pos.y + TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[2].vtx.z = 0.0f;

	motion_result->vertexWk[3].vtx.x = motion_result->pos.x + TEXTURE_MOTION_RESULT00_SIZE_X;
	motion_result->vertexWk[3].vtx.y = motion_result->pos.y + TEXTURE_MOTION_RESULT00_SIZE_Y;
	motion_result->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetMotion_result(void)
{
	MOTION_RESULT *motion_result = &motion_resultWk[0];

	// ���g�p����
	for (int i = 0; i < MOTION_RESULT_MAX; i++, motion_result++)
	{
		if (!motion_result->bUse)
		{
			// �L���ɂ���
			motion_result->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			motion_result->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			motion_result->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
MOTION_RESULT *GetMotion_result(int no)
{
	return(&motion_resultWk[no]);
}

