#include "GSEnd.h"

GSEnd::GSEnd() : GameStateBase(StateType::STATE_END)
{
}


GSEnd::~GSEnd()
{
}


void GSEnd::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Texture> texture;
	if (Globals::result == "Defeat") {
		texture = ResourceManagers::GetInstance()->GetTexture("defeat.tga");
	}
	else if (Globals::result == "Victory") {
		texture = ResourceManagers::GetInstance()->GetTexture("victory.tga");
	}
	m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_button->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Minecraft.ttf");
	m_text = std::make_shared< Text>(shader, font, "Click to go back to main menu", TextColor::WHITE, 2.0);
	m_text->Set2DPosition(Vector2(300, 640));
}

void GSEnd::Exit()
{
}


void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}


void GSEnd::HandleEvents()
{
}

void GSEnd::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSEnd::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_button->HandleTouchEvents(x, y, bIsPressed);
}

void GSEnd::HandleMouseMoveEvents(int x, int y)
{
}

void GSEnd::Update(float deltaTime)
{
}

void GSEnd::Draw()
{
	m_button->Draw();
	m_text->Draw();
}