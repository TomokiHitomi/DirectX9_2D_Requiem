//=============================================================================
//
// FRAME���� [frame.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "frame.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFrame(int no);
void SetTextureFrame( int no, int cntPattern );	//
void SetVertexFrame(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FRAME					frameWk[FRAME_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureFrame = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFrame(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_FRAME,				// �t�@�C���̖��O
			&pD3DTextureFrame);			// �ǂݍ��ރ������̃|�C���^
	}

	// FRAME�̏�����
	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		frame->bUse = true;
		frame->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		frame->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frame->nCountAnim = 0;
		frame->nPatternAnim = 0;

		frame->Texture = pD3DTextureFrame;			// �e�N�X�`���ւ�FRAME
		frame->size = D3DXVECTOR2(TEXTURE_FRAME_SIZE_X, TEXTURE_FRAME_SIZE_Y);

		// ���_���̍쐬
		MakeVertexFrame(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFrame(void)
{
	FRAME *frame = &frameWk[0];

	// ���������
	if (pD3DTextureFrame != NULL)
	{
		pD3DTextureFrame->Release();
		pD3DTextureFrame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFrame(void)
{
	FRAME *frame = &frameWk[0];
	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		if (frame->bUse == true)
		{
			// �A�j���[�V����
			frame->nCountAnim++;
			if ((frame->nCountAnim % TIME_ANIMATION_FRAME) == 0)
			{
				// �p�^�[���̐؂�ւ�
				frame->nPatternAnim = (frame->nPatternAnim + 1) % ANIM_PATTERN_NUM_FRAME;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureFrame(i, frame->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexFrame(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FRAME_MAX; i++, frame++)
	{
		if (frame->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, frame->Texture);

			// FRAME�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FRAME, frame->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexFrame(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FRAME *frame = &frameWk[no];

	// ���_���W�̐ݒ�
	frame->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	frame->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FRAME_SIZE_X, 100.0f, 0.0f);
	frame->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FRAME_SIZE_Y, 0.0f);
	frame->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FRAME_SIZE_X, 100.0f+TEXTURE_FRAME_SIZE_Y, 0.0f);
	//SetVertexFrame();

	// rhw�̐ݒ�
	frame->vertexWk[0].rhw =
	frame->vertexWk[1].rhw =
	frame->vertexWk[2].rhw =
	frame->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	frame->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);
	frame->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_FRAME_R, TEXTURE_FRAME_G, TEXTURE_FRAME_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	frame->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	frame->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FRAME, 0.0f );
	frame->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FRAME );
	frame->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FRAME, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FRAME );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureFrame( int no, int cntPattern )
{
	FRAME *frame = &frameWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FRAME;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FRAME;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FRAME;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FRAME;
	frame->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	frame->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	frame->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	frame->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexFrame(int no)
{
	FRAME *frame = &frameWk[no];

	frame->vertexWk[0].vtx.x = frame->pos.x - TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[0].vtx.y = frame->pos.y - TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[0].vtx.z = 0.0f;

	frame->vertexWk[1].vtx.x = frame->pos.x + TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[1].vtx.y = frame->pos.y - TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[1].vtx.z = 0.0f;

	frame->vertexWk[2].vtx.x = frame->pos.x - TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[2].vtx.y = frame->pos.y + TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[2].vtx.z = 0.0f;

	frame->vertexWk[3].vtx.x = frame->pos.x + TEXTURE_FRAME_SIZE_X;
	frame->vertexWk[3].vtx.y = frame->pos.y + TEXTURE_FRAME_SIZE_Y;
	frame->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// FRAME�擾�֐�
//=============================================================================
FRAME *GetFrame(int no)
{
	return(&frameWk[no]);
}

