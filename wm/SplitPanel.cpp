#include "SplitPanel.h"


SplitPanel::SplitPanel()
{
}

void SplitPanel::addPanel(Component * panel)
{
	components.push_back(panel);
	sizes.push_back(100);
}


void SplitPanel::onReposition()
{
	glm::ivec2 pos = position;
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->position = pos;
		components[i]->size = glm::ivec2(sizes[i], size.y);
		pos.x += sizes[i];
	}
	components[components.size() - 1]->size.x += (size.x - pos.x); //make last one as large as possible
	for (auto p : components)
		p->onReposition();
}

void SplitPanel::draw(MenuOverlay * overlay)
{
	for (auto p : components)
		p->draw(overlay);
}

bool SplitPanel::click(bool leftButton, const glm::ivec2 & clickPos)
{
	if (!inComponent(clickPos))
		return false;

	for (auto p : components)
		if (p->inComponent(clickPos))
			return p->click(leftButton, clickPos);
	return false;
}
