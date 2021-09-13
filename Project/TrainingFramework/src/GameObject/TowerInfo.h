#pragma once
#include "Sprite2D.h"
#include "GameButton.h"
#include "Text.h"

class TowerInfo : public Sprite2D
{
protected:
	bool m_isActive;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::list<std::shared_ptr<Text>> m_listText;
public:
	TowerInfo(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~TowerInfo();

	void	Draw() override;
	void	SetActive(bool isActive);
	void	SetListButton(std::list<std::shared_ptr<GameButton>> listButton);
	void	SetListText(std::list<std::shared_ptr<Text>> listText);
};
