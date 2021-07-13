#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

using surface = std::pair<Vector2f,Vector2f>;

using l_equation = std::pair<float,float>;

void scale(Vector2f &v, const float by);

float dist(Vector2f v);

float dotprod(Vector2f first, Vector2f second);

float nonzero(float num);

float rads2degs(float rads);

float degs2rads(float degs);

void printVector2f(Vector2f v);

void printVector2f(Vector2f v, std::ofstream &out);

bool sameSigns(Vector2f p1, Vector2f p2);

l_equation eqFrom2Pts(Vector2f p1, Vector2f p2);

Vector2f calcIntersectVector(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2);

bool segmentIntersectsRectangle(const sf::FloatRect& rect, const sf::Vector2f& a_p1, const sf::Vector2f& a_p2);

float rotationAngle(Vector2f origin, Vector2f currPos);

Vector2f pivotfromangle(float mirrorangle, float shotangle, Vector2f rotationPoint, float force);

Vector2f newPivot(Vector2f a1, Vector2f pivot, surface wall);

Vector2f midpoint(Vector2f p1, Vector2f p2);

bool segIntersectSeg(surface a, surface b);

Vector2f signsVector(Vector2f origin, Vector2f pivot);

Vector2f signVector(Vector2f signs, Vector2f point);

surface extendLine(const Vector2f p1, const Vector2f p2, const float scale);