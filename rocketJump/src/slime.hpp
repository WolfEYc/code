#include "vecmath.hpp"


class slime {
private:
    Texture texture;
    Sprite sprite;
    Vector2f pos;
    Vector2f vel;
    Vector2f acc;
    float coefric;
    float grav;
    float radius;
    vector<surface> hitreg;
    bool cd;
    float bouncyness;
    float movespeed;
public:
    bool bound;
    //default construct
    slime();
    //construct with texture and position
    slime(Vector2f pos, string texture);
    //returns true if successful
    void setTexture(string texture);
    void setPosition(Vector2f pos);
    void setRadius(const float radius);
    const float getRadius() const;
    const FloatRect getBounds() const;
    const FloatRect getNextBounds() const;
    const Vector2f getPosition() const;
    const Vector2f getNextPosition() const;
    vector<surface> getHitReg();
    void friction();
    void collideWith(const int collider);
    void updateForces(bool* movement);
    void updatePos();
    void reactTo(const Vector2f force);
    void drawSlime(RenderWindow& window);
    void cooldown();
    void shoot(const Vector2f mousepos);
    void reset(const Vector2f pos);
    bool onCd();
    void aim(const Vector2f mousepos);
    void tipOrigin();
};
