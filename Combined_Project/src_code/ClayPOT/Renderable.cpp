#include "stdafx.h"
#include "Renderable.h"


void Renderable::render(sf::RenderTarget& target, sf::Shader* shader)
{
	this->display(target, shader);
}
