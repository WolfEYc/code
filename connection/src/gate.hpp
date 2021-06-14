#include "cell.hpp"
using namespace sf;
using namespace std;

Color on = Color::Red, off = Color(100,0,0);

class gate : public cell{   
public:    
    int logic;
    unsigned num_inputs, on_inputs;

    gate(unsigned cellsize, Vector2u position, string logic) : cell(cellsize, position) {
        this->type = "gate";
        this->num_inputs = 0;
        this->on_inputs = 0;      

        if(logic == "and"){
            this->logic = 0;
            off = on = Color::Green;
            off.g /= 2;           
        }else if (logic == "or"){
            this->logic = 1;
            off = on = Color::Cyan;
            off.g /= 2;
            off.b /= 2;
        }else if (logic == "xor"){
            this->logic = 2;
            off = on = Color::Yellow;
            off.g /= 2;
            off.r /= 2;
        }else if (logic == "not"){
            this->logic = 3;
            off = on = Color::Magenta;
            off.r /= 2;
            off.b /= 2;
        }else if (logic == "equals"){
            this->logic = 4;
            off = on = Color::Blue;            
            off.b /= 2;
        }

        visual.setFillColor(off);
    }

    void setCharge(){
        charge = 0;
        switch (logic)
        {
        case 0:
            if(on_inputs == num_inputs)
                charge = 1;
            break;

        case 1:
            if(on_inputs)
                charge = 1;
            break;

        case 2:
            if(on_inputs == 1)
                charge = 1;
            break;

        case 3:
            if(!on_inputs)
                charge = 1;
            break;
        
        case 4:
            if(on_inputs == num_inputs || !on_inputs)
                charge = 1;
            break;       
        default:            
            throw new exception;
        }
    }

    

};