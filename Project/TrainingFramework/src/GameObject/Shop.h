#pragma once
#include "Sprite2D.h"
#include "GameButton.h"
#include "Text.h"

class Shop : public Sprite2D
{
protected:
	bool m_isActive;
	std::shared_ptr<GameButton> m_closeButton;
	std::list<std::shared_ptr<GameButton>> m_listItem;
	std::shared_ptr<Text> m_message;
public:
	Shop(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Shop();

	void	Draw() override;
	void	SetActive(bool isActive);
	void	SetCloseButton(std::shared_ptr<GameButton> closeButton);
	void	SetListItem(std::list<std::shared_ptr<GameButton>> listItem);
	void	SetMessage(std::shared_ptr<Text> message);
};
