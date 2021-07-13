#include "slime.hpp"

class grid{
private:
    unsigned cellsize;
    vector<pair<Vector2i, RectangleShape>> blocks;
    Vector2i lastblock;
    FloatRect lastBounds;
    int closest;
    vector<surface> lastCollider;
    Color color;
    Vector2f gaypoint;
protected:
    bool collides(const Vector2f p1, const Vector2f p2);

    void getWalls(const Vector2i block);

    void convertToBlock(int &pos);
public:
    Vector2f getGaypoint();

    grid(const unsigned cellsize);

    void add(const Vector2i block);

    int collisionSurface(vector<surface> hitreg, Vector2f pos, Vector2f nextpos, const float radius, bool gay);

    void draw(RenderWindow& window);

};
