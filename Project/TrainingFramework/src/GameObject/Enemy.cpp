#include "Enemy.h"
#include "Texture.h"
#include <iostream>

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Direction dir,
	int HP, int Damage, float speed,int gold) : AnimationSprite(model,shader,texture), m_fVelocityX(0.0f), m_fVelocityY(0.0f),m_rand(rand()%2),
	m_dir(dir),m_HP(HP),m_Damage(Damage), m_fSpeed(speed), m_gold(gold),m_originalSpeed(speed)
{
	Init();
}
Enemy::~Enemy()
{
}
void Enemy::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

float Enemy::GetSpeed() {
	return m_fSpeed;
}
int Enemy::GetHP() {
	return m_HP;
}

void Enemy::SetHP(int HP) {
	m_HP = HP;
}

bool Enemy::IsGoal()
{
	return m_IsGoal;
}

int Enemy::GetDamage() {
	return m_Damage;
}
int Enemy::GetGold()
{
	return m_gold;
}
float Enemy::GetOriginalSpeed()
{
	return m_originalSpeed;
}
void Enemy::Update(GLfloat deltatime)
{
	m_currentFrameTime += deltatime;
	if (m_currentFrameTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
		{
			m_currentFrame = 0;
		}
		m_currentFrameTime -= m_frameTime;
	}
}
void Enemy::SetGoal(bool isGoal)
{
	m_IsGoal = isGoal;
}

void Enemy::SetSlow(bool isSlow) {
	m_isSlow = isSlow;
}
bool Enemy::IsSlow() {
	return m_isSlow;
}
void Enemy::SetSlowTime(float slowtime) {
	m_slowTime = slowtime;
}
float Enemy::GetSlowTime() {
	return m_slowTime;
}


void Enemy::Draw()
{
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

