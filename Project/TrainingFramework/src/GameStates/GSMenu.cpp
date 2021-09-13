#include "GSMenu.h"
#include "Camera.h"

SoLoud::Wav m_wav;

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}


GSMenu::~GSMenu()
{
}


void func(std::shared_ptr<GameButton> button, std::shared_ptr<Texture> texture) {
	button->SetTexture(texture);
}

void GSMenu::Init()
{

	m_wav.load("..\\Data\\Sounds\\bg_sound.wav");
	m_wav.setLooping(true);
	m_wav.setVolume(0.4f);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("menu_bg1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// start button
	texture = ResourceManagers::GetInstance()->GetTexture("text_play1.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 350);
	button->SetSize(113, 45);
	button->SetOnClick([]() {
		Application::GetInstance()->GetSoloud()->play(m_wav);
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);


	// setting button
	texture = ResourceManagers::GetInstance()->GetTexture("text_setting1.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 410);
	button->SetSize(220, 45);
	button->SetOnClick([]() {
		});
	m_listButton.push_back(button);

	// credit button
	texture = ResourceManagers::GetInstance()->GetTexture("text_credit1.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 470);
	button->SetSize(200, 45);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(button);

	// quit button
	texture = ResourceManagers::GetInstance()->GetTexture("text_exit1.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 530);
	button->SetSize(110, 45);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// game title
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	//m_textGameName = std::make_shared< Text>(shader, font, "Epic Game", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	//m_textGameName->Set2DPosition(Vector2(60, 200));
}
void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{	
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
