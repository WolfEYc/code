#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

using gateinfo = pair<unsigned,unsigned>;
using grid = vector<vector<unsigned>>;
using pulse = tuple<Vector2u,Vector2u,bool>;

class Cells{
private:
    queue<pulse> pulses;
    grid charge;
    grid zerogrid;
    grid cells;
    unsigned size;
public:
    Cells(unsigned sx, unsigned sy, unsigned cellsize);
    void modify(Vector2u pos);
    void toggleSwitch(Vector2u pos);
    void pCharge(Vector2u prev,Vector2u pos);
    void nCharge(Vector2u prev,Vector2u pos);
    void iterate();
    void draw(RenderWindow &window);
    bool isSwitch(Vector2u pos);
    bool isGate(Vector2u pos);
    bool transmittable(Vector2u pos);
    vector<Vector2u> getInputs(Vector2u pos);
    vector<Vector2u> getOutputs(Vector2u prev, Vector2u pos);
    Vector2u convertCoord(Vector2u pos);
    gateinfo getGateInfo(Vector2u pos);
    void pulseGate(Vector2u pos);
    void pulseWire(Vector2u pos);  
    void pulseWire(Vector2u prev, Vector2u pos, bool charge);
    bool inputtable(Vector2u pos);
    unsigned getCharge(Vector2u pos);
    unsigned getValue(Vector2u pos);
};

/* 
    negative is off, pos is on

    0 = empty (black)
    1 = wire (red)
    2 = not (green)
    3 = and (purple)
    4 = equals (blue)
    5 = lever (white)
*/

