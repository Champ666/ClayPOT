#pragma once
#include "MeleeWeapon.h"

class MeleeWeapon;


class Sword :
    public MeleeWeapon
{
private:
    //Initialzers:
    void initSword();

public:

    Sword();
    ~Sword();

    //Updates:
    virtual void update(sf::Vector2f mousePosView, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target);

};

