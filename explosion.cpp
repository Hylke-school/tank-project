#include "precomp.h"
#include "explosion.h"

bool Tmpl8::Explosion::done() const
{
    return current_frame > 17;
}

void Tmpl8::Explosion::tick()
{
    if (current_frame < 18) current_frame++;
}

void Tmpl8::Explosion::draw(Surface* screen)
{
    explosion_sprite->set_frame(current_frame / 2);
    explosion_sprite->draw(screen, (int)position.x, (int)position.y);
}
