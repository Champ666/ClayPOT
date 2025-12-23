#pragma once
class Renderable
{
private:
	std::function<void (sf::RenderTarget&, sf::Shader* shader)> display;

public:
	template <typename T>
	Renderable(T* obj) {
		display = [obj](sf::RenderTarget& target, sf::Shader* shader) {obj->render(target, shader); };
	}
	void render(sf::RenderTarget& target, sf::Shader* shader);
};

