//=============================================================================
//
// �^�C�g������ [scoreboard.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "scoreboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScoreboard(int no);
void SetTextureScoreboard( int no, int cntPattern );	//
void SetVertexScoreboard(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SCOREBOARD					scoreboardWk[SCOREBOARD_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureScoreboard = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScoreboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SCOREBOARD00,				// �t�@�C���̖��O
			&pD3DTextureScoreboard);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		scoreboard->bUse = true;
		scoreboard->bPosMoveFlag = true;

		scoreboard->pos = D3DXVECTOR3((float)SCOREBOARD_POS_X, (float)SCOREBOARD_POS_Y, 0.0f);
		scoreboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreboard->nCountAnim = 0;
		scoreboard->nPatternAnim = 0;

		scoreboard->Texture = pD3DTextureScoreboard;			// �e�N�X�`���ւ̃G�l�~�[
		scoreboard->size = D3DXVECTOR2(TEXTURE_SCOREBOARD00_SIZE_X, TEXTURE_SCOREBOARD00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexScoreboard(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScoreboard(void)
{
	SCOREBOARD *scoreboard = &scoreboardWk[0];

	// ���������
	if (pD3DTextureScoreboard != NULL)
	{
		pD3DTextureScoreboard->Release();
		pD3DTextureScoreboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScoreboard(void)
{
	SCOREBOARD *scoreboard = &scoreboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		if (scoreboard->bUse == true)
		{
			// �A�j���[�V����
			scoreboard->nCountAnim++;
			if ((scoreboard->nCountAnim % TIME_ANIMATION_SCOREBOARD) == 0)
			{
				// �p�^�[���̐؂�ւ�
				scoreboard->nPatternAnim = (scoreboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_SCOREBOARD;
			}

			if (scoreboard->bPosMoveFlag && !result->bPosMoveFlag)
			{
				scoreboard->pos += result->vecPosMove;
				scoreboard->bPosMoveFlag = false;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureScoreboard(i, scoreboard->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexScoreboard(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScoreboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SCOREBOARD_MAX; i++, scoreboard++)
	{
		if (scoreboard->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, scoreboard->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SCOREBOARD, scoreboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScoreboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	// ���_���W�̐ݒ�
	scoreboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	scoreboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_SCOREBOARD00_SIZE_X, 100.0f, 0.0f);
	scoreboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_SCOREBOARD00_SIZE_Y, 0.0f);
	scoreboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_SCOREBOARD00_SIZE_X, 100.0f+TEXTURE_SCOREBOARD00_SIZE_Y, 0.0f);
	//SetVertexScoreboard();

	// rhw�̐ݒ�
	scoreboard->vertexWk[0].rhw =
	scoreboard->vertexWk[1].rhw =
	scoreboard->vertexWk[2].rhw =
	scoreboard->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	scoreboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	scoreboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	scoreboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	scoreboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD, 0.0f );
	scoreboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD );
	scoreboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScoreboard( int no, int cntPattern )
{
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD;
	scoreboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	scoreboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	scoreboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	scoreboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexScoreboard(int no)
{
	SCOREBOARD *scoreboard = &scoreboardWk[no];

	scoreboard->vertexWk[0].vtx.x = scoreboard->pos.x - TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[0].vtx.y = scoreboard->pos.y - TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[0].vtx.z = 0.0f;

	scoreboard->vertexWk[1].vtx.x = scoreboard->pos.x + TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[1].vtx.y = scoreboard->pos.y - TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[1].vtx.z = 0.0f;

	scoreboard->vertexWk[2].vtx.x = scoreboard->pos.x - TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[2].vtx.y = scoreboard->pos.y + TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[2].vtx.z = 0.0f;

	scoreboard->vertexWk[3].vtx.x = scoreboard->pos.x + TEXTURE_SCOREBOARD00_SIZE_X;
	scoreboard->vertexWk[3].vtx.y = scoreboard->pos.y + TEXTURE_SCOREBOARD00_SIZE_Y;
	scoreboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
SCOREBOARD *GetScoreboard(int no)
{
	return(&scoreboardWk[no]);
}

