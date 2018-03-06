//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "parameter.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "score.h"
#include "funnel.h"
#include "barrier.h"

#include "effect_player_jump.h"
#include "effect_player_wing.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(int no);
void SetTexturePlayer( int no, int cntPattern );	//
void SetVertexPlayer(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER					playerWk[PLAYER_MAX];

LPDIRECTSOUNDBUFFER8 g_pVOICE[5];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTexturePlayer = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYER00,				// �t�@�C���̖��O
			&pD3DTexturePlayer);				// �ǂݍ��ރ������̃|�C���^
		g_pVOICE[0] = LoadSound(VOICE_00);
		g_pVOICE[1] = LoadSound(VOICE_01);
		g_pVOICE[2] = LoadSound(VOICE_02);
		g_pVOICE[3] = LoadSound(VOICE_03);
		g_pVOICE[4] = LoadSound(VOICE_04);
		for (int i = 0; i < 5; i++)
		{
			SetVol(g_pVOICE[i], VOLUME_SE);
		}
	}

	// �v���C���[�̏�����
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->bUse = true;
		player->bGravityFlag = true;
		player->bParameterUse = false;
		player->nJumpFlag = PLAYER_JUMP_MAX;
		player->bAlphaFlag = true;
		player->bInvisibleFlag = false;

		player->pos = D3DXVECTOR3(i*PLAYER_POS_X + PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		player->nCountAnim = 0;
		player->nPatternAnim = 0;
		player->nDirection = 1;
		player->nAlphaCount = PLAYER_ALPHA_MAX;
		player->nInvisibleCount = PLAYER_INVISIBLE_MAX;

		player->fMoveSlow = 0;
		player->fMove = 0;

		player->fHitPoint = (float)PLAYER_HPMAX;
		player->fManaPoint = PLAYER_MANAMAX;
		player->fGravity = PLAYER_GRAVITI;
		player->fAcceleration = 0.0f;

		player->Texture = pD3DTexturePlayer;			// �e�N�X�`���ւ̃G�l�~�[
		player->size = D3DXVECTOR2(PLAYER_CUSTOM_SIZE_X, PLAYER_CUSTOM_SIZE_Y);

		// ���_���̍쐬
		MakeVertexPlayer(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	PLAYER *player = &playerWk[0];

	// ���������
	if (pD3DTexturePlayer != NULL)
	{
		pD3DTexturePlayer->Release();
		pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	CLOSE *close = GetClose(0);
	int *count = GetCount();

	if (*count == 50)
	{
		SetPlayerVoice(3);
	}

	if (!close->bUse)
	{
		SetBgmVol(0, true);
		SetBgmVol(3, true);
	}

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->bUse)
		{
			// �A�j���[�V����
			player->nCountAnim++;
			if ((player->nCountAnim % TIME_ANIMATION_PLAYER) == 0)
			{
				// �p�^�[���̐؂�ւ�
				player->nPatternAnim = (player->nPatternAnim + 1) % (TEXTURE_PATTERN_DIVIDE_X_PLAYER) + (TEXTURE_PATTERN_DIVIDE_X_PLAYER * player->nDirection);
			}

			// �΂߈ړ��␳
			if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
			{
				if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
				{
					player->fMove = PLAYER_MOVE_SLANT;
				}
				else
				{
					player->fMove = PLAYER_MOVE_NORMAL;
				}
			}
			else
			{
				player->fMove = PLAYER_MOVE_NORMAL;
			}

			// ���ړ�
			if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))
			{
				player->nDirection = 2;
				if (!player->bGravityFlag)
				{
					player->pos.x -= (PLAYER_SPEED - player->fMoveSlow) * player->fMove;
				}
				else
				{
					player->pos.x -= PLAYER_SPEED - player->fMoveSlow;
				}
			}
			// �E�ړ�
			else if (GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->nDirection = 0;
				if (!player->bGravityFlag)
				{
					player->pos.x += (PLAYER_SPEED - player->fMoveSlow) * player->fMove;
				}
				else
				{
					player->pos.x += PLAYER_SPEED - player->fMoveSlow;
				}
			}
			else
			{
				player->nDirection = 1;
			}

			// �W�����v���[�V����
			if (player->nJumpFlag <= 1)
			{
				player->nDirection = 3;
			}


			// ���d�̓��[�h
			if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R) || GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L))
			{
				if (player->fManaPoint > 0)
				{
					if (player->bGravityFlag)
					{
						SetSe(4, E_DS8_FLAG_NONE, true);
						SetEffect_player_wing();
						player->bGravityFlag = false;
					}
					if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R))
					{
						// �t�@���l�����A�N�e�B�u
						SetFunnel(player->pos);
						player->fManaPoint--;
					}
					if (GetKeyboardPress(DIK_LCONTROL) || GetKeyboardPress(DIK_RCONTROL) || IsButtonPressed(0, BUTTON_L))
					{
						// �o���A���A�N�e�B�u
						SetBarrier(player->pos);
						player->fManaPoint--;
					}
					player->nDirection = 5;
					AddScore(1);
					if (player->fManaPoint < PLAYER_GRAVITI_ALERT)
					{
						SetSe(9, E_DS8_FLAG_NONE, false);
					}
					player->fMoveSlow = PLAYER_SLOW;
					player->fAcceleration = 0;
					if (!close->bUse)
					{
						SetBgmVol(4, true);
					}
					// ��ړ�
					if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP))
					{
						player->pos.y -= (PLAYER_SPEED - player->fMoveSlow) * player->fMove;
					}
					// ���ړ�
					else if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
					{
						player->pos.y += (PLAYER_SPEED - player->fMoveSlow) * player->fMove;
					}
				}
				else
				{
					// �t�@���l�����m���A�N�e�B�u�ɂ���
					ReleaseFunnel();
					ReleaseBarrier();
					player->fAcceleration -= player->fGravity;
					player->pos.y -= player->fAcceleration;
					if (!player->bGravityFlag)
					{
						SetSe(5, E_DS8_FLAG_NONE, true);
						ReleaseEffect_player_wing();
						player->bGravityFlag = true;
					}
				}
			}
			else
			{
				player->fManaPoint += PLAYER_MANARECOVERY;
				if (player->fManaPoint > PLAYER_MANAMAX)
				{
					player->fManaPoint = PLAYER_MANAMAX;
				}

				if (!player->bGravityFlag)
				{
					SetSe(5, E_DS8_FLAG_NONE, true);
					ReleaseEffect_player_wing();
					player->bGravityFlag = true;
				}

				player->fMoveSlow = 0.0f;
				SetBgmVol(4, false);

				// �W�����v����
				if (player->nJumpFlag != 0)
				{
					if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, BUTTON_UP) || GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
					{
						player->fAcceleration = PLAYER_JUMP_POWER;
						player->nJumpFlag--;
						SetEffect_player_jump(player->pos);
						SetSe(10, E_DS8_FLAG_NONE, CONTINUITY_ON);
					}
				}
				player->fAcceleration -= player->fGravity;
				player->pos.y -= player->fAcceleration;
			}

			// �㕔�̌��E�ړ��ݒ�
			if (player->pos.y < 0 + TEXTURE_PLAYER00_SIZE_Y)
			{
				player->pos.y = 0 + TEXTURE_PLAYER00_SIZE_Y;
			}

			// �����̌��E�ړ��ݒ�
			if (player->pos.y >= SCREEN_HEIGHT - TEXTURE_PLAYER00_SIZE_Y- PLAYER_GROUND)
			{
				player->pos.y = SCREEN_HEIGHT - TEXTURE_PLAYER00_SIZE_Y- PLAYER_GROUND;
				player->nJumpFlag = PLAYER_JUMP_MAX;
			}

			// �E���̌��E�ړ��ݒ�
			eStage eCheck = CheckStage();
			if (eCheck == STAGE_TUTORIAL)
			{
				if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_START))
				{
					SetSe(3, E_DS8_FLAG_NONE, true);
					InitGame(1);
					SetStage(STAGE_TITLE);
				}
				if (player->pos.x > PLAYER_TUTORIAL_MOVE_X - TEXTURE_PLAYER00_SIZE_X)
				{
					player->pos.x = PLAYER_TUTORIAL_MOVE_X - TEXTURE_PLAYER00_SIZE_X;
				}
			}
			else
			{
				if (player->pos.x > SCREEN_WIDTH - TEXTURE_PLAYER00_SIZE_X)
				{
					player->pos.x = SCREEN_WIDTH - TEXTURE_PLAYER00_SIZE_X;
				}
			}


			// �����̌��E�ړ��ݒ�
			if (player->pos.x < 0 + TEXTURE_PLAYER00_SIZE_X)
			{
				player->pos.x = 0 + TEXTURE_PLAYER00_SIZE_X;
			}

			// �o���b�g����
			if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_B) || IsButtonPressed(0, BUTTON_A))
			{
				SetBullet(player->pos, 0);
				SetBullet(player->pos, 1);
				SetBullet(player->pos, 2);
				SetSe(8, E_DS8_FLAG_NONE, false);
				if (!close->bUse)
				{
					SetBgmVol(1, true);
				}
				AddScore(1);
			}
			else
			{
				SetBgmVol(1, false);
				SetBgmVol(2, false);
			}

			// ���G����
			if(player->bInvisibleFlag)
			{
				player->nInvisibleCount--;
				if (player->nInvisibleCount % PLAYER_INVISIBLE_FREQUENCY == 0)
				{
					if (player->bAlphaFlag)
					{
						player->nAlphaCount = 0;
						player->bAlphaFlag = false;
					}
					else
					{
						player->nAlphaCount = PLAYER_ALPHA_MAX;
						player->bAlphaFlag = true;
					}
				}
				if (player->nInvisibleCount < 0)
				{
					player->nInvisibleCount = PLAYER_INVISIBLE_MAX;
					player->bInvisibleFlag = false;
				}
			}

			// HP�EMP�Q�[�W�̐ݒ�
			if (!player->bParameterUse)
			{
				SetParameter(0, player->pos, i);
				SetParameter(1, player->pos, i);
				player->bParameterUse = true;
			}

			// �e�N�X�`�����W��ݒ�
			SetTexturePlayer(i, player->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer(i);
		}
		else
		{
			close->bUse = true;
			close->bClearFlag = false;
			ReleaseEffect_player_wing();
			// �t�@���l�����m���A�N�e�B�u�ɂ���
			ReleaseFunnel();
			// �o���A���m���A�N�e�B�u�ɂ���
			ReleaseBarrier();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, player->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// ���_���W�̐ݒ�
	player->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	player->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PLAYER00_SIZE_X, 100.0f, 0.0f);
	player->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PLAYER00_SIZE_Y, 0.0f);
	player->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PLAYER00_SIZE_X, 100.0f+TEXTURE_PLAYER00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PLAYER, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PLAYER );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PLAYER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PLAYER );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER;
	player->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	player->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	player->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	player->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];

	player->vertexWk[0].vtx.x = player->pos.x - TEXTURE_PLAYER00_SIZE_X;
	player->vertexWk[0].vtx.y = player->pos.y - TEXTURE_PLAYER00_SIZE_Y;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + TEXTURE_PLAYER00_SIZE_X;
	player->vertexWk[1].vtx.y = player->pos.y - TEXTURE_PLAYER00_SIZE_Y;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - TEXTURE_PLAYER00_SIZE_X;
	player->vertexWk[2].vtx.y = player->pos.y + TEXTURE_PLAYER00_SIZE_Y;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + TEXTURE_PLAYER00_SIZE_X;
	player->vertexWk[3].vtx.y = player->pos.y + TEXTURE_PLAYER00_SIZE_Y;
	player->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̍X�V
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, player->nAlphaCount);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, player->nAlphaCount);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, player->nAlphaCount);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, player->nAlphaCount);
}

//=============================================================================
// �v���C���[�{�C�X�Đ��֐�
//=============================================================================
void SetPlayerVoice(int nVoice)
{
	PlaySound(g_pVOICE[nVoice], E_DS8_FLAG_NONE);
}


//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

