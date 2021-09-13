#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "SkeletonEnemy.h"
#include "SlingerEnemy.h"
#include "WarriorEnemy.h"
#include "PossessedEnemy.h"
#include "ShadowEnemy.h"

#include "Text.h"
#include "Shop.h"
#include "GameButton.h"
#include "AnimationSprite.h"
#include "TowerInfo.h"

#include "Tower.h"
#include "LightTower.h"
#include "MagicTower.h"
#include "MoonTower.h"

#include <iostream>
#include <fstream>
#include <math.h>

#include "ObjectPool.h"

//--------wave control------------
int totalWave = 10;
int currentWave = 0;
int timer = 600;
std::shared_ptr<Text> next_wave;
int remaining_mob = 94;
Vector2 gate1(17 * 32 + 16, 23 * 32);
Vector2 gate2(0, 13 * 32);
std::vector<std::shared_ptr<Enemy>> listEnemy;
//-----------shop-----------------
std::shared_ptr<Shop> shop;
std::shared_ptr<GameButton> shopCloseButton;
std::list<std::shared_ptr<GameButton>> listShopItem;
Vector2 selectedPos = {0,0};
int	selectedTowerPos = 0;
std::shared_ptr<Text> shop_message;
int money = 150;
std::shared_ptr<Text> money_str;
std::shared_ptr<Sprite2D> coin;
//-------------tower-----------------
std::vector<std::shared_ptr<GameButton>> listTowerPos;
std::vector<std::shared_ptr<Tower>> listTower;
std::shared_ptr<TowerInfo> tower_info;
std::list<std::shared_ptr<GameButton>> listInfoButton;
std::list<std::shared_ptr<Text>> listInfoText;
POINT p;
std::shared_ptr<GameButton> upgrade_button, sell_button, info_close;
std::shared_ptr<Text> name, damage, range, effectRaito;
Tower* currentSelectedTower;
//------------------
std::shared_ptr<Text> currentHealth;
int totalHealth = 50;

void Reset();

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("map1_bg.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//foreground
	texture = ResourceManagers::GetInstance()->GetTexture("map1_fg.tga");
	m_foreground = std::make_shared<Sprite2D>(model, shader, texture);
	m_foreground->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_foreground->SetSize(Globals::screenWidth, Globals::screenHeight);

	//shop
	texture = ResourceManagers::GetInstance()->GetTexture("shop.tga");
	shop = std::make_shared<Shop>(model, shader, texture);
	shop->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	shop->SetSize(500, 300);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	shopCloseButton = std::make_shared<GameButton>(model, shader, texture);
	shopCloseButton->Set2DPosition(890 - 25, 234 + 30);
	shopCloseButton->SetSize(30, 30);
	shopCloseButton->SetOnClick([]() {
		shop->SetActive(false);
		shop_message->SetText("");
	});
	shop->SetCloseButton(shopCloseButton);

	texture = ResourceManagers::GetInstance()->GetTexture("shop_LightTower.tga");
	std::shared_ptr<GameButton> shop_LightTower = std::make_shared<GameButton>(model, shader, texture);
	shop_LightTower->Set2DPosition(473 , 384);
	shop_LightTower->SetSize(100, 100);
	shop_LightTower->SetOnClick([]() {
		if (money < 50) {
			shop_message->SetText("Not enough money");
			return;
		}
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("LightTower1.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Tower> tower = std::make_shared<LightTower>(model, shader, texture, 400, 200,50);
		tower->Set2DPosition(selectedPos.x, selectedPos.y - 45);
		tower->SetSize(128, 156);
		tower->setNumFrames(14);
		tower->SetOnClick([](Tower* tw) {
			currentSelectedTower = tw;
			GetCursorPos(&p);
			tower_info->Set2DPosition(p.x + 100, p.y - 40);

			info_close->Set2DPosition(p.x + 140, p.y - 95);
			upgrade_button->Set2DPosition(p.x + 85,p.y + 10);
			sell_button->Set2DPosition(p.x + 140, p.y + 10);

			name->SetText("LightTower Lv"+std::to_string(tw->getLevel()));
			name->Set2DPosition(p.x + 48, p.y - 90);
			damage->SetText("Damage: "+std::to_string(tw->getDamage()));
			damage->Set2DPosition(p.x + 48, p.y - 65);
			range->SetText("Range: "+std::to_string(tw->getRange()));
			range->Set2DPosition(p.x + 48, p.y - 45);
			effectRaito->SetText("50%");
			effectRaito->Set2DPosition(p.x + 48, p.y - 25);
			tower_info->SetActive(true);
			});
		listTower.push_back(tower);
		shop->SetActive(false);
		listTowerPos.at(selectedTowerPos)->SetActive(false);
		tower->SetTowerPos(selectedTowerPos);
		money -= 50;
		money_str->SetText(std::to_string(money));
		shop_message->SetText("");
	});
	listShopItem.push_back(shop_LightTower);

	texture = ResourceManagers::GetInstance()->GetTexture("shop_MagicTower.tga");
	std::shared_ptr<GameButton> shop_MagicTower = std::make_shared<GameButton>(model, shader, texture);
	shop_MagicTower->Set2DPosition(639, 384);
	shop_MagicTower->SetSize(100, 100);
	shop_MagicTower->SetOnClick([]() {
		if (money < 100) {
			shop_message->SetText("Not enough money");
			return;
		}
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("MagicTower1.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Tower> tower = std::make_shared<MagicTower>(model, shader, texture, 400, 200,100);
		tower->Set2DPosition(selectedPos.x, selectedPos.y - 45);
		tower->SetSize(150, 125);
		tower->setNumFrames(6);
		tower->SetOnClick([](Tower* tw) {
			currentSelectedTower = tw;
			GetCursorPos(&p);
			tower_info->Set2DPosition(p.x + 100, p.y - 40);

			info_close->Set2DPosition(p.x + 140, p.y - 95);
			upgrade_button->Set2DPosition(p.x + 85, p.y + 10);
			sell_button->Set2DPosition(p.x + 140, p.y + 10);

			name->SetText("MagicTower Lv" + std::to_string(tw->getLevel()));
			name->Set2DPosition(p.x + 48, p.y - 90);
			damage->SetText("Damage: " + std::to_string(tw->getDamage()));
			damage->Set2DPosition(p.x + 48, p.y - 65);
			range->SetText("Range: " + std::to_string(tw->getRange()));
			range->Set2DPosition(p.x + 48, p.y - 45);
			effectRaito->SetText("50%");
			effectRaito->Set2DPosition(p.x + 48, p.y - 25);

			tower_info->SetActive(true);
			});
		listTower.push_back(tower);
		shop->SetActive(false);
		listTowerPos.at(selectedTowerPos)->SetActive(false);
		tower->SetTowerPos(selectedTowerPos);
		money -= 100;
		money_str->SetText(std::to_string(money));
		shop_message->SetText("");
		});
	listShopItem.push_back(shop_MagicTower);

	texture = ResourceManagers::GetInstance()->GetTexture("shop_bloodmoon.tga");
	std::shared_ptr<GameButton> shop_bloodmoon = std::make_shared<GameButton>(model, shader, texture);
	shop_bloodmoon->Set2DPosition(805, 384);
	shop_bloodmoon->SetSize(100, 100);
	shop_bloodmoon->SetOnClick([]() {
		if (money < 200) {
			shop_message->SetText("Not enough money");
			return;
		}
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("BloodMoonTower1.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Tower> tower = std::make_shared<MoonTower>(model, shader, texture, 400,200,200);
		tower->Set2DPosition(selectedPos.x,selectedPos.y - 55);
		tower->SetSize(128,156);
		tower->setNumFrames(11);
		tower->SetOnClick([](Tower* tw) {
			currentSelectedTower = tw;
			GetCursorPos(&p);
			tower_info->Set2DPosition(p.x + 100, p.y - 40);

			info_close->Set2DPosition(p.x + 140, p.y - 95);
			upgrade_button->Set2DPosition(p.x + 85, p.y + 10);
			sell_button->Set2DPosition(p.x + 140, p.y + 10);

			name->SetText("MoonTower Lv" + std::to_string(tw->getLevel()));
			name->Set2DPosition(p.x + 48, p.y - 90);
			damage->SetText("Damage: " + std::to_string(tw->getDamage()));
			damage->Set2DPosition(p.x + 48, p.y - 65);
			range->SetText("Range: " + std::to_string(tw->getRange()));
			range->Set2DPosition(p.x + 48, p.y - 45);
			effectRaito->SetText("50%");
			effectRaito->Set2DPosition(p.x + 48, p.y - 25);

			tower_info->SetActive(true);
			});
		listTower.push_back(tower);
		shop->SetActive(false);
		listTowerPos.at(selectedTowerPos)->SetActive(false);
		tower->SetTowerPos(selectedTowerPos);
		money -= 200;
		money_str->SetText(std::to_string(money));
		shop_message->SetText("");
	});
	listShopItem.push_back(shop_bloodmoon);
	shop->SetListItem(listShopItem);

	//tower infomation
	texture = ResourceManagers::GetInstance()->GetTexture("Tower_Info.tga");
	tower_info = std::make_shared<TowerInfo>(model, shader, texture);
	tower_info->SetSize(120, 150);

	texture = ResourceManagers::GetInstance()->GetTexture("upgrade_button.tga");
	upgrade_button = std::make_shared<GameButton>(model, shader, texture);
	upgrade_button->SetSize(90, 30);
	upgrade_button->SetOnClick([]() {
		if (currentSelectedTower->getLevel() * currentSelectedTower->getGoldUpgrade() > money) {
			return;
		}
		money -= currentSelectedTower->getLevel() * currentSelectedTower->getGoldUpgrade();
		money_str->SetText(std::to_string(money));
		currentSelectedTower->Upgrade();
		name->SetText(name->GetText().substr(0,name->GetText().length() -1 ) + std::to_string(currentSelectedTower->getLevel()));
		damage->SetText("Damage: " + std::to_string(currentSelectedTower->getDamage()));
		range->SetText("Range: " + std::to_string(currentSelectedTower->getRange()));
		});
	texture = ResourceManagers::GetInstance()->GetTexture("sell_button.tga");
	sell_button = std::make_shared<GameButton>(model, shader, texture);
	sell_button->SetSize(30, 30);
	sell_button->SetOnClick([]() {
		money += (int)(currentSelectedTower->getLevel() * currentSelectedTower->getGoldUpgrade() + currentSelectedTower->getGoldUpgrade()) * 7 / 10;
		money_str->SetText(std::to_string(money));
		listTowerPos.at(currentSelectedTower->GetTowerPos())->SetActive(true);
		tower_info->SetActive(false);
		for (auto tower : listTower) {
			if (tower->GetTowerPos() == currentSelectedTower->GetTowerPos()) {
				listTower.erase(std::remove(listTower.begin(), listTower.end(), tower), listTower.end());
				break;
			}
		}
		});

	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	info_close = std::make_shared<GameButton>(model, shader, texture);
	info_close->SetOnClick([]() {
		tower_info->SetActive(false);
		});
	info_close->SetSize(20, 20);

	listInfoButton.push_back(upgrade_button);
	listInfoButton.push_back(sell_button);
	listInfoButton.push_back(info_close);
	tower_info->SetListButton(listInfoButton);

	//tower pos
	texture = ResourceManagers::GetInstance()->GetTexture("tower_pos.tga");
	std::shared_ptr<GameButton> pos1 = std::make_shared<GameButton>(model, shader, texture);
	pos1->Set2DPosition(2 * 32, 18*32);
	pos1->SetSize(64, 64);
	pos1->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 2 * 32, 18 * 32 };
		selectedTowerPos = 0;
		});
	std::shared_ptr<GameButton> pos2 = std::make_shared<GameButton>(model, shader, texture);
	pos2->Set2DPosition(6 * 32, 18 * 32);
	pos2->SetSize(64, 64);
	pos2->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 6 * 32, 18 * 32 };
		selectedTowerPos = 1;
		});
	std::shared_ptr<GameButton> pos3 = std::make_shared<GameButton>(model, shader, texture);
	pos3->Set2DPosition(10 * 32, 18 * 32);
	pos3->SetSize(64, 64);
	pos3->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 10 * 32, 18 * 32 };
		selectedTowerPos = 2;
		});
	std::shared_ptr<GameButton> pos4 = std::make_shared<GameButton>(model, shader, texture);
	pos4->Set2DPosition(14 * 32, 18 * 32);
	pos4->SetSize(64, 64);
	pos4->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 14 * 32, 18 * 32 };
		selectedTowerPos = 3;
		});
	std::shared_ptr<GameButton> pos5 = std::make_shared<GameButton>(model, shader, texture);
	pos5->Set2DPosition(22 * 32, 18 * 32);
	pos5->SetSize(64, 64);
	pos5->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 22 * 32, 18 * 32 };
		selectedTowerPos = 4;
		});
	std::shared_ptr<GameButton> pos6 = std::make_shared<GameButton>(model, shader, texture);
	pos6->Set2DPosition(28 * 32, 18 * 32);
	pos6->SetSize(64, 64);
	pos6->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 28 * 32, 18 * 32 };
		selectedTowerPos = 5;
		});
	std::shared_ptr<GameButton> pos7 = std::make_shared<GameButton>(model, shader, texture);
	pos7->Set2DPosition(35 * 32, 17 * 32);
	pos7->SetSize(64, 64);
	pos7->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 35 * 32, 17 * 32 };
		selectedTowerPos = 6;
		});

	std::shared_ptr<GameButton> pos8 = std::make_shared<GameButton>(model, shader, texture);
	pos8->Set2DPosition(4 * 32, 2 * 32);
	pos8->SetSize(64, 64);
	pos8->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 4 * 32, 2 * 32 };
		selectedTowerPos = 7;
		});
	std::shared_ptr<GameButton> pos9 = std::make_shared<GameButton>(model, shader, texture);
	pos9->Set2DPosition(8 * 32, 2 * 32);
	pos9->SetSize(64, 64);
	pos9->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 8 * 32, 2 * 32 };
		selectedTowerPos = 8;
		});
	std::shared_ptr<GameButton> pos10 = std::make_shared<GameButton>(model, shader, texture);
	pos10->Set2DPosition(12 * 32, 2 * 32);
	pos10->SetSize(64, 64);
	pos10->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 12 * 32, 2 * 32 };
		selectedTowerPos = 9;
		});
	std::shared_ptr<GameButton> pos11 = std::make_shared<GameButton>(model, shader, texture);
	pos11->Set2DPosition(16 * 32, 2 * 32);
	pos11->SetSize(64, 64);
	pos11->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 16 * 32, 2 * 32 };
		selectedTowerPos = 10;
		});
	std::shared_ptr<GameButton> pos12 = std::make_shared<GameButton>(model, shader, texture);
	pos12->Set2DPosition(4 * 32, 8 * 32);
	pos12->SetSize(64, 64);
	pos12->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 4 * 32, 8 * 32 };
		selectedTowerPos = 11;
		});
	std::shared_ptr<GameButton> pos13 = std::make_shared<GameButton>(model, shader, texture);
	pos13->Set2DPosition(27 * 32, 9 * 32);
	pos13->SetSize(64, 64);
	pos13->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 27 * 32, 9 * 32 };
		selectedTowerPos = 12;
		});
	std::shared_ptr<GameButton> pos14 = std::make_shared<GameButton>(model, shader, texture);
	pos14->Set2DPosition(29 * 32, 11 * 32);
	pos14->SetSize(64, 64);
	pos14->SetOnClick([]() {
		shop->SetActive(true);
		selectedPos = { 29 * 32, 11 * 32 };
		selectedTowerPos = 13;
		});

	listTowerPos.push_back(pos1);
	listTowerPos.push_back(pos2);
	listTowerPos.push_back(pos3);
	listTowerPos.push_back(pos4);
	listTowerPos.push_back(pos5);
	listTowerPos.push_back(pos6);
	listTowerPos.push_back(pos7);
	listTowerPos.push_back(pos8);
	listTowerPos.push_back(pos9);
	listTowerPos.push_back(pos10);
	listTowerPos.push_back(pos11);
	listTowerPos.push_back(pos12);
	listTowerPos.push_back(pos13);
	listTowerPos.push_back(pos14);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	m_buttonClose = std::make_shared<GameButton>(model, shader, texture);
	m_buttonClose->Set2DPosition(Globals::screenWidth - 50, 50);
	m_buttonClose->SetSize(50, 50);
	m_buttonClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Coin.tga");
	coin = std::make_shared<Sprite2D>(model, shader, texture);
	coin->SetSize(40, 40);
	coin->Set2DPosition(25, 25);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Minecraft.ttf");
	money_str = std::make_shared< Text>(shader, font,std::to_string(money), TextColor::BLACK, 1.35);
	money_str->Set2DPosition(Vector2(50, 35));
	
	font = ResourceManagers::GetInstance()->GetFont("gill.ttf");
	currentHealth = std::make_shared< Text>(shader, font,std::to_string(totalHealth)+"/50", TextColor::RED, 1.0);
	currentHealth->Set2DPosition(Vector2(1108, 80));

	shop_message = std::make_shared< Text>(shader, font, "", TextColor::WHITE, 1.0);
	shop_message->Set2DPosition(Vector2(545, 484));
	shop->SetMessage(shop_message);

	 name = std::make_shared< Text>(shader, font, "", TextColor::WHITE, 0.7);
	 damage = std::make_shared< Text>(shader, font, "", TextColor::WHITE, 0.7);
	 range = std::make_shared< Text>(shader, font, "", TextColor::WHITE, 0.7);
	 effectRaito = std::make_shared< Text>(shader, font, "", TextColor::WHITE, 0.7);
	 listInfoText.push_back(name);
	 listInfoText.push_back(damage);
	 listInfoText.push_back(range);
	 listInfoText.push_back(effectRaito);
	 tower_info->SetListText(listInfoText);

	next_wave = std::make_shared< Text>(shader, font, "Next wave: "+std::to_string(timer), TextColor::RED, 2.0);
	next_wave->Set2DPosition(Vector2(480, 100));

}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_buttonClose->HandleTouchEvents(x, y, bIsPressed);
	for (auto pos : listTowerPos)
	{
		pos->HandleTouchEvents(x, y, bIsPressed);
	}
	for (auto item : listShopItem)
	{
		item->HandleTouchEvents(x, y, bIsPressed);
	}
	shopCloseButton->HandleTouchEvents(x, y, bIsPressed);
	for (auto tower : listTower) {
		tower->HandleTouchEvents(x, y, bIsPressed);
	}
	for (auto button : listInfoButton) {
		button->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void SpawnEnemy(int currentWave) {
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	std::shared_ptr<Enemy> enemy = nullptr;

	std::string wave;
	std::ifstream WaveConfig("D:\\GL_Intern_Project\\Project\\Data\\WaveConfig.txt");
	while (wave != "wave" + std::to_string(currentWave)) {
		std::getline(WaveConfig, wave);
	}
	std::string gate1, gate2, mob1, mob2;
	std::getline(WaveConfig, gate1);
	std::getline(WaveConfig, gate2);
	std::stringstream ss1(gate1), ss2(gate2);
	while (ss1 >> mob1 && ss2 >> mob2) {
		if (mob1 == "skeleton") {
			enemy = std::make_shared<SkeletonEnemy>(model, shader, nullptr, Direction::UP, 1500, 1, 40.0f, 10);
			enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->SetSize(50, 64);
			//m_enemy->Set2DPosition(0, 13 * 32);
			listEnemy.push_back(enemy);
		}
		if (mob2 == "skeleton") {
			enemy = std::make_shared<SkeletonEnemy>(model, shader, nullptr, Direction::RIGHT, 1500, 1, 40.0f, 10);
			//enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob1 == "slinger") {
			enemy = std::make_shared<SlingerEnemy>(model, shader, nullptr, Direction::UP, 1000, 2, 50.0f, 10);
			enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			//enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob2 == "slinger") {
			enemy = std::make_shared<SlingerEnemy>(model, shader, nullptr, Direction::RIGHT, 1000, 2, 50.0f, 10);
			//enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob1 == "warrior") {
			enemy = std::make_shared<WarriorEnemy>(model, shader, nullptr, Direction::UP, 2500, 2, 30.0f, 20);
			enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			//enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob2 == "warrior") {
			enemy = std::make_shared<WarriorEnemy>(model, shader, nullptr, Direction::RIGHT, 2500, 2, 30.0f, 20);
			//enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob1 == "possessed") {
			enemy = std::make_shared<PossessedEnemy>(model, shader, nullptr, Direction::UP, 1750, 3, 55.0f, 30);
			enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			//enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob2 == "possessed") {
			enemy = std::make_shared<PossessedEnemy>(model, shader, nullptr, Direction::RIGHT, 1750, 3, 55.0f, 30);
			//enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(50, 64);
			listEnemy.push_back(enemy);
		}
		if (mob1 == "shadow") {
			enemy = std::make_shared<ShadowEnemy>(model, shader, nullptr, Direction::UP, 3500, 4, 60.0f, 50);
			enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			//enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(75, 96);
			listEnemy.push_back(enemy);
		}
		if (mob2 == "shadow") {
			enemy = std::make_shared<ShadowEnemy>(model, shader, nullptr, Direction::RIGHT, 3500, 4, 60.0f, 50);
			//enemy->Set2DPosition(17 * 32 + 16, 23 * 32);
			enemy->Set2DPosition(0, 13 * 32);
			enemy->SetSize(75, 96);
			listEnemy.push_back(enemy);
		}
	}
	WaveConfig.close();
}

void GSPlay::Update(float deltaTime)
{
	//timer
	if (currentWave < totalWave) {
		timer -= deltaTime;
		next_wave->SetText("Next wave: " + std::to_string((int)timer / 60));
		if (timer <= 0) {
			timer = 600;
			currentWave += 1;
			SpawnEnemy(currentWave);
		}
	}
	for (auto enemy : listEnemy)
	{
		if (enemy->GetHP() <= 0 ) {
			money += enemy->GetGold();
			money_str->SetText(std::to_string(money));
			listEnemy.erase(std::remove(listEnemy.begin(), listEnemy.end(), enemy), listEnemy.end());
			break;
		}
		if (enemy->IsGoal()) {
			totalHealth -= enemy->GetDamage();
			if (totalHealth <= 0) {
				Globals::result = "Defeat";
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END);
				Reset();
				break;
			}
			currentHealth->SetText(std::to_string(totalHealth) + "/50");
			listEnemy.erase(std::remove(listEnemy.begin(), listEnemy.end(), enemy), listEnemy.end());
			if (listEnemy.size() == 0 && totalHealth >0 ) {
				Globals::result = "Victory";
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END);
				Reset();
				break;
			}
			break;
		}
		enemy->Move(deltaTime);
		enemy->Update(deltaTime);
	}
	for (auto tower : listTower) {
		tower->Update(deltaTime);
		tower->setDelay(tower->getDelay() + deltaTime);
		for (auto enemy : listEnemy) {
			int d = sqrt(
				(tower->GetPosition().x - enemy->GetPosition().x) * (tower->GetPosition().x - enemy->GetPosition().x) +
				(tower->GetPosition().y - enemy->GetPosition().y) * (tower->GetPosition().y - enemy->GetPosition().y)
			);

			if (d <= tower->getRange() && tower->getDelay() >= 1.0f ) {
				tower->Fire(enemy);
				tower->setDelay(0.0f);
				break;
			}
		}
	}
	for (auto it : ObjectPool::GetInstance()->getListLightBullet()) {
			it->Move(deltaTime);
			it->OnCollision();
	}
	for (auto it : ObjectPool::GetInstance()->getListMagicBullet()) {
		it->Move(deltaTime);
		it->OnCollision();
	}
	for (auto it : ObjectPool::GetInstance()->getListMoonBullet()) {
		it->Move(deltaTime);
		it->OnCollision();
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	for (auto pos : listTowerPos)
	{
		pos->Draw();
	}
	for (auto enemy : listEnemy)
	{
		enemy->Draw();
	}
	for (auto tower : listTower) {
		tower->Draw();
	}
	for (auto it : ObjectPool::GetInstance()->getListLightBullet()) {
		it->Draw();
	}
	for (auto it : ObjectPool::GetInstance()->getListMagicBullet()) {
		it->Draw();
	}
	for (auto it : ObjectPool::GetInstance()->getListMoonBullet()) {
		it->Draw();
	}
	m_foreground->Draw();
	next_wave->Draw();
	currentHealth->Draw();
	m_buttonClose->Draw();
	shop->Draw();
	tower_info->Draw();
	coin->Draw();
	money_str->Draw();
}

void Reset()
{
	totalHealth = 50;
	listEnemy.clear();
	listTower.clear();
	currentWave = 0;
	money = 150;
	timer = 600;
	for (auto pos : listTowerPos) {
		pos->SetActive(true);
	}
	shop->SetActive(false);
	shop_message->SetText("");
	tower_info->SetActive(false);

}
