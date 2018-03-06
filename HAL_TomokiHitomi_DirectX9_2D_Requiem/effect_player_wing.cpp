//=======================================================================Hitcircle======
//
// �v���C���[���� [effect_player_wing.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "effect_player_wing.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect_player_wing(int no);
void SetTextureEffect_player_wing( int no, int cntPattern );
void SetVertexEffect_player_wing(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EFFECT_PLAYER_WING					effect_player_wingWk[EFFECT_PLAYER_WING_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureEffect_player_wing = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect_player_wing(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT_PLAYER_WING,				// �t�@�C���̖��O
			&pD3DTextureEffect_player_wing);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		effect_player_wing->bUse = false;
		effect_player_wing->bLoop = false;
		effect_player_wing->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		effect_player_wing->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_player_wing->nCountAnim = 0;
		effect_player_wing->nPatternAnim = 0;
		effect_player_wing->nAlpha = EFFECT_PLAYER_WING_ALPHA_MAX;
		effect_player_wing->Texture = pD3DTextureEffect_player_wing;			// �e�N�X�`���ւ̃G�l�~�[
		effect_player_wing->size = D3DXVECTOR2(TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexEffect_player_wing(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect_player_wing(void)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// ���������
	if (pD3DTextureEffect_player_wing != NULL)
	{
		pD3DTextureEffect_player_wing->Release();
		pD3DTextureEffect_player_wing = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect_player_wing(void)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		if (effect_player_wing->bUse)
		{
			// �A�j���[�V����
			effect_player_wing->nCountAnim++;
			if ((effect_player_wing->nCountAnim % TIME_ANIMATION_EFFECT_PLAYER_WING) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect_player_wing->nPatternAnim = (effect_player_wing->nPatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT_PLAYER_WING;
			}

			// �p�^�[�����[�v
			if (effect_player_wing->nPatternAnim >= EFFECT_PLAYER_WING_LOOP_MAX && effect_player_wing->bLoop)
			{
				effect_player_wing->nPatternAnim = EFFECT_PLAYER_WING_LOOP_MIN;
			}

			// ���X�g�p�^�[���ŏI��
			if (effect_player_wing->nPatternAnim == ANIM_PATTERN_NUM_EFFECT_PLAYER_WING-1)
			{
				effect_player_wing->bUse = false;
			}

			// �E�C���O�̓����x��MP�{���ŕύX
			effect_player_wing->nAlpha = EFFECT_PLAYER_WING_ALPHA_MAX / (float)PLAYER_MANAMAX * player->fManaPoint;

			effect_player_wing->nAlpha = effect_player_wing->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if(effect_player_wing->nAlpha < 0)
			{
				effect_player_wing->nAlpha = 0;
			}

			// �Ώۍ��W�ɃZ�b�g
			effect_player_wing->pos.x = player->pos.x + EFFECT_PLAYER_WING_ADJUSTMENT_X;
			effect_player_wing->pos.y = player->pos.y + EFFECT_PLAYER_WING_ADJUSTMENT_Y;

			// �e�N�X�`�����W��ݒ�
			SetTextureEffect_player_wing(i, effect_player_wing->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEffect_player_wing(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect_player_wing(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_PLAYER_WING_MAX; i++, effect_player_wing++)
	{
		if (effect_player_wing->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, effect_player_wing->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_PLAYER_WING, effect_player_wing->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect_player_wing(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];

	// ���_���W�̐ݒ�
	effect_player_wing->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_player_wing->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, 100.0f, 0.0f);
	effect_player_wing->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y, 0.0f);
	effect_player_wing->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_X, 100.0f+TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y, 0.0f);
	//SetVertexEffect_player_wing();

	// rhw�̐ݒ�
	effect_player_wing->vertexWk[0].rhw =
	effect_player_wing->vertexWk[1].rhw =
	effect_player_wing->vertexWk[2].rhw =
	effect_player_wing->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect_player_wing->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_player_wing->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect_player_wing->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_player_wing->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING, 0.0f );
	effect_player_wing->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING );
	effect_player_wing->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect_player_wing( int no, int cntPattern )
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING;
	effect_player_wing->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_player_wing->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_player_wing->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_player_wing->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexEffect_player_wing(int no)
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[no];
	PLAYER *player = GetPlayer(0);

	effect_player_wing->vertexWk[0].vtx.x = effect_player_wing->pos.x - TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[0].vtx.y = effect_player_wing->pos.y - TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[0].vtx.z = 0.0f;

	effect_player_wing->vertexWk[1].vtx.x = effect_player_wing->pos.x + TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[1].vtx.y = effect_player_wing->pos.y - TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[1].vtx.z = 0.0f;

	effect_player_wing->vertexWk[2].vtx.x = effect_player_wing->pos.x - TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[2].vtx.y = effect_player_wing->pos.y + TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[2].vtx.z = 0.0f;

	effect_player_wing->vertexWk[3].vtx.x = effect_player_wing->pos.x + TEXTURE_EFFECT_PLAYER_WING00_SIZE_X;
	effect_player_wing->vertexWk[3].vtx.y = effect_player_wing->pos.y + TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y;
	effect_player_wing->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̐ݒ�
	effect_player_wing->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
	effect_player_wing->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect_player_wing->nAlpha);
}

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void SetEffect_player_wing()
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// �L���ɂ���
	effect_player_wing->bUse = true;
	// ���[�v�t���O��L���ɂ���
	effect_player_wing->bLoop = true;
	// �A�j���[�V�����J�E���^�̏�����
	effect_player_wing->nCountAnim = 0;
	// �A�j���[�V�����p�^�[���̏�����
	effect_player_wing->nPatternAnim = 0;
}

//=============================================================================
// �f�B�Z�[�u���֐�
//=============================================================================
void ReleaseEffect_player_wing()
{
	EFFECT_PLAYER_WING *effect_player_wing = &effect_player_wingWk[0];

	// ���[�v�t���O�𖳌��ɂ���
	effect_player_wing->bLoop = false;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
EFFECT_PLAYER_WING *GetEffect_player_wing(int no)
{
	return(&effect_player_wingWk[no]);
}

