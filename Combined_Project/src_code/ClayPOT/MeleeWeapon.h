#pragma once
#include "Item.h"
class MeleeWeapon :
    public Item
{
private:



protected:
	sf::Texture weapon_Texture;
	sf::Sprite* weapon_Sprite;


public:

    //Initializers:
    

    MeleeWeapon();
    virtual ~MeleeWeapon();


    //Virtaul Fucntions:
	virtual void update(sf::Vector2f mousePosView, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

};

