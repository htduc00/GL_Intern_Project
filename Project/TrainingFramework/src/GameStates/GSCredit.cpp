#include "GSCredit.h"

GSCredit::GSCredit()
{
}

GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("menu_bg.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 80, 50);
	button->SetSize(80, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// name
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("gill.ttf");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Hoang Trung Duc - PTIT", TextColor::WHITE, 1.0);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2 - 130, 400));
	m_listText.push_back(text);

}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCredit::Draw()
{
	m_background->Draw();
	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}