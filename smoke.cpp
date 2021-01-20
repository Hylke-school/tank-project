#include "smoke.h"
#include "precomp.h"
namespace Tmpl8
{

void Smoke::tick()
{
    if (++current_frame == 60) current_frame = 0;
}

void Smoke::draw(Surface* screen)
{
    smoke_sprite.set_frame(current_frame / 15);

    smoke_sprite.draw(screen, (int)position.x, (int)position.y);
}

} // namespace Tmpl8