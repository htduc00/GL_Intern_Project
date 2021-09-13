#include "MoonBullet.h"
#include "Enemy.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "ObjectPool.h"
#include <ctime>

MoonBullet::MoonBullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
	int damage, float speed) : AnimationSprite(model, shader, texture), m_damage(damage), m_speed(speed), m_isActive(false)
{
	setNumFrames(4);
}

MoonBullet::~MoonBullet()
{
}

void MoonBullet::OnCollision()
{
	if (!m_isActive) return;
	Vector2 targetPos = { m_target->GetPosition().x, m_target->GetPosition().y };
	if (targetPos.x - 30 <= m_position.x && targetPos.x + 30 >= m_position.x &&
		targetPos.y - 30 <= m_position.y && targetPos.y + 30 >= m_position.y)
	{
		Reset();
		srand(time(NULL));
		int random = rand() % 100 + 1;
		if(random <= m_crit)
			m_target->SetHP(m_target->GetHP() - m_damage*1.5);
		else
			m_target->SetHP(m_target->GetHP() - m_damage);
	}
}

void MoonBullet::Draw()
{
	if (!m_isActive) return;
	if (m_pCamera == nullptr) return;
	glUseProgram(m_pShader->m_program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix wvpMatrix;

	wvpMatrix = m_worldMatrix * m_pCamera->GetLookAtCameraMatrix();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->m_iTextureLoc[0] != -1)
			glUniform1i(m_pShader->m_iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_color.x, m_color.y, m_color.z, m_color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_wvpMatrix");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, wvpMatrix.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);



	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MoonBullet::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool MoonBullet::GetActive()
{
	return m_isActive;
}

void MoonBullet::Move(GLfloat deltatime)
{
	if (!m_isActive) return;
	Vector2 targetPos = { m_target->GetPosition().x, m_target->GetPosition().y };
	Vector2 dir = { targetPos.x - m_position.x, targetPos.y - m_position.y };
	m_velocity = dir.Normalize() * m_speed;
	Set2DPosition(m_position.x + m_velocity.x * deltatime, m_position.y + m_velocity.y * deltatime);
	Update(deltatime);
}

void MoonBullet::Reset()
{
	m_isActive = false;
	Set2DPosition(0, 0);
}

void MoonBullet::SetDamage(int damage)
{
	m_damage = damage;
}

void MoonBullet::SetCrit(int crit)
{
	m_crit = crit;
}

void MoonBullet::SetTarget(std::shared_ptr<Enemy> target)
{
	m_target = target;
}
