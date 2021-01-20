#pragma once

namespace Tmpl8
{

class Rocket
{
  public:
    Rocket(vec2 position, vec2 direction, float collision_radius, alignments allignment, Sprite* rocket_sprite);
    ~Rocket();

    void tick();
    void draw(Surface* screen);

    bool intersects(vec2 position_other, float radius_other) const;

    vec2 position;
    vec2 speed;

    float collision_radius;

    bool active;

    alignments alignment;

    int current_frame;
    Sprite* rocket_sprite;
};

} // namespace Tmpl8