//=============================================================================
//
// �t�@���l������ [barrier.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
//#include "main.h"
#include "barrier.h"
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBarrier(int no);
void SetTextureBarrier( int no, int cntPattern );
void SetVertexBarrier(int no);

void SetBarrierType(int nBarrier);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BARRIER					barrierWk[BARRIER_MAX];
int						g_nTotalBarrier;					// �t�@���l��01�̑����ː�
int						g_nTotalBarrier02;					// �t�@���l��01�̑����ː�

int						g_nReloadBarrier00;
int						g_nReloadBarrier;
int						g_nReloadBarrier02;

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureBarrier = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBarrier(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[0];

	g_nTotalBarrier = 0;
	g_nTotalBarrier02 = 0;

	g_nReloadBarrier00 = 0;
	g_nReloadBarrier = 0;
	g_nReloadBarrier02 = 0;

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BARRIER,				// �t�@�C���̖��O
			&pD3DTextureBarrier);			// �ǂݍ��ރ������̃|�C���^
	}

	// �t�@���l���̏�����
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		barrier->size = D3DXVECTOR2(BARRIER_CUSTOM_SIZE_X, BARRIER_CUSTOM_SIZE_Y);
		barrier->Texture = pD3DTextureBarrier;	// �e�N�X�`���ւ̃t�@���l��

		barrier->fBaseAngle = 0.0f;
		barrier->fRadius = 0.0f;

		// �t�@���l���X�e�[�^�X�̏�����
		InitStatusBarrier(i);

		// ���_���̍쐬
		MakeVertexBarrier(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];
	// ���������
	if (pD3DTextureBarrier != NULL)
	{
		pD3DTextureBarrier->Release();
		pD3DTextureBarrier = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];
	ENEMY *enemy;
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse == true)
		{
			// �e�N�X�`���[�ݒ�
			barrier->nCountAnim++;
			if (barrier->nCountAnim % TIME_ANIMATION_BARRIER == 0)
			{
				// �p�^�[���̐؂�ւ�
				barrier->nPatternAnim = (barrier->nPatternAnim + 1) % ANIM_PATTERN_NU_BARRIER;
			}

			// ���d�̓��[�h�̓t�@���l����W�J�E�o���b�g����
			if (GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L))
			{
				barrier->fDistance += BARRIER_INJECTION_SPEED;
				if (barrier->fDistance > BARRIER_DISTANCE_MAX)
				{
					barrier->fDistance = BARRIER_DISTANCE_MAX;
				}
			}
			else
			{
				barrier->fDistance -= BARRIER_INJECTION_SPEED;
				if (barrier->fDistance < 0.0f)
				{
					barrier->bUse = false;
				}
			}

			SetBarrierType(i);

			// �t�@���l���̓����x��MP�{���ŕύX
			barrier->nAlpha = BARRIER_ALPHA_MIN + (BARRIER_ALPHA / (float)PLAYER_MANAMAX * player->fManaPoint);

			// ���G�_�ł̓K�p
			barrier->nAlpha = barrier->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if (barrier->nAlpha < 0)
			{
				barrier->nAlpha = 0;
			}
			
			// �e�N�X�`�����W��ݒ�
			SetTextureBarrier(i, barrier->nPatternAnim);

			// ��]����
			if (barrier->nPatternHoming)
			{
				barrier->rot.z -= BARRIER01_ROTATION;
			}
			else
			{
				barrier->rot.z += BARRIER01_ROTATION;
			}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBarrier(i);

			// �A�ˑ��x����
			barrier->nReloadBullet--;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, barrier->Texture);

			// �t�@���l���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BARRIER, barrier->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBarrier(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[no];

	// �p�x�Ɣ��a�����߂�
	barrier->fBaseAngle = atan2f(TEXTURE_BARRIER_SIZE_Y, TEXTURE_BARRIER_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BARRIER_SIZE_X, TEXTURE_BARRIER_SIZE_Y);
	barrier->fRadius = D3DXVec2Length(&temp);

	// ���_���W�̐ݒ�
	barrier->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	barrier->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BARRIER_SIZE_X, 100.0f, 0.0f);
	barrier->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BARRIER_SIZE_Y, 0.0f);
	barrier->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BARRIER_SIZE_X, 100.0f+TEXTURE_BARRIER_SIZE_Y, 0.0f);
	//SetVertexBarrier();

	// rhw�̐ݒ�
	barrier->vertexWk[0].rhw =
	barrier->vertexWk[1].rhw =
	barrier->vertexWk[2].rhw =
	barrier->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	barrier->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);

	// �e�N�X�`�����W�̐ݒ�
	barrier->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	barrier->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BARRIER, 0.0f );
	barrier->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BARRIER );
	barrier->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BARRIER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BARRIER );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBarrier( int no, int cntPattern )
{
	BARRIER *barrier = &barrierWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BARRIER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BARRIER;
	barrier->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	barrier->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	barrier->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	barrier->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexBarrier(int no)
{
	BARRIER *barrier = &barrierWk[no];
	// ���_0:��]����
	barrier->vertexWk[0].vtx.x = barrier->pos.x - cosf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[0].vtx.y = barrier->pos.y - sinf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[0].vtx.z = 0.0f;

	// ���_1:��]����
	barrier->vertexWk[1].vtx.x = barrier->pos.x + cosf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[1].vtx.y = barrier->pos.y - sinf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[1].vtx.z = 0.0f;

	// ���_2:��]����
	barrier->vertexWk[2].vtx.x = barrier->pos.x - cosf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[2].vtx.y = barrier->pos.y + sinf(barrier->fBaseAngle - barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[2].vtx.z = 0.0f;

	// ���_3:��]����
	barrier->vertexWk[3].vtx.x = barrier->pos.x + cosf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[3].vtx.y = barrier->pos.y + sinf(barrier->fBaseAngle + barrier->rot.z) * barrier->fRadius;
	barrier->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̐ݒ�
	barrier->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
	barrier->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, barrier->nAlpha);
}

//=============================================================================
// �t�@���l�����v���C���[�ɐݒu
//=============================================================================
void SetBarrier(D3DXVECTOR3 pos)
{
	BARRIER *barrier = &barrierWk[0];

	// �S�t�@���l���𓙊Ԋu�ɃZ�b�g
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (!barrier->bUse)
		{
			// �t�@���l�����W��ΏۂɃZ�b�g
			barrier->pos.x = pos.x;
			barrier->pos.y = pos.y;
			// �t�@���l���̃^�C�v���Z�b�g
			barrier->nBarrierType = i % BARRIER_TYPE_MAX;
			// �t�@���l���ˏo�p�x���Z�b�g
			barrier->fAngle = ((D3DX_PI * 2.0f) / BARRIER_MAX) * i;
			// �t�@���l�����A�N�e�B�u�ɂ���
			barrier->bUse = true;
		}
	}
}

//=============================================================================
// �t�@���l�����v���C���[�Ɋi�[
//=============================================================================
void ReleaseBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];

	// �S�t�@���l�����m���A�N�e�B�u
	for (int i = 0; i < BARRIER_MAX; i++, barrier++)
	{
		if (barrier->bUse)
		{
			InitStatusBarrier(i);
			barrier->bUse = false;
		}
	}
}

//=============================================================================
// �t�@���l���p�^�[��00 �t�@���l��
//=============================================================================
void SetBarrierType(int nBarrier)
{
	BARRIER *barrier = &barrierWk[nBarrier];
	PLAYER *player = GetPlayer(0);

	// �p�x�ύX
	barrier->fAngle -= D3DX_PI / BARRIER_ROTATIONAL_SPEED;

	// 360�x�𒴂�����360�x������
	if (barrier->fAngle <= D3DX_PI * 2.0f)
	{
		barrier->fAngle += D3DX_PI * 2.0f;
	}

	// �ړ��ʓK�p
	barrier->pos.x = player->pos.x + (cos(barrier->fAngle) * barrier->fDistance);
	barrier->pos.y = player->pos.y + (sin(barrier->fAngle) * barrier->fDistance);
}

//=============================================================================
// �t�@���l���̍ė��p����
//=============================================================================
void InitStatusBarrier(int nBarrier)
{
	BARRIER *barrier = &barrierWk[nBarrier];

	// �t�@���l���X�e�[�^�X�̏�����
	barrier->bUse = false;
	barrier->bTextureUse = false;
	barrier->bReload = false;

	barrier->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
	barrier->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	barrier->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	barrier->nCountAnim = 0;
	barrier->nPatternAnim = 0;
	barrier->nBarrierType = 0;
	barrier->nBarrierCount = 0;
	barrier->nAngleType = 0;
	barrier->nPatternHoming = 0;
	barrier->nHomingFlag = 0;
	barrier->nTarget = 0;
	barrier->nReloadBullet = 0;
	barrier->nAlpha = BARRIER_ALPHA_MAX;

	barrier->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	barrier->nDirection = 0;

	barrier->fBarrierSpeed = 0.0f;
	barrier->fAngle = 0.0f;
	barrier->fDistance = 0.0f;
		

	return;
}

//=============================================================================
// �t�@���l���擾�֐�
//=============================================================================
BARRIER *GetBarrier(int no)
{
	return(&barrierWk[no]);
}
