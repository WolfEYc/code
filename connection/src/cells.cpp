#include "cells.hpp"

Cells::Cells(unsigned sx, unsigned sy, unsigned cellsize) : size(cellsize){
    unsigned x = sx / cellsize;
    unsigned y = sy / cellsize;

    cells = grid(y , vector<unsigned>(x,0));
    charge = zerogrid = cells;
}

Vector2u Cells::convertCoord(Vector2u pos){
    return {pos.x/size,pos.y/size};
}

void Cells::modify(Vector2u pos){
    if(isGate(pos) && charge[pos.y][pos.x]){
        nCharge(pos,pos);
        iterate();
    }
    
    if(cells[pos.y][pos.x] == 5){
        cells[pos.y][pos.x] = 0;     
        return;
    }

    cells[pos.y][pos.x]++;

    if(cells[pos.y][pos.x] == 2){
        charge[pos.y][pos.x] = 0;
    }

    
    if(isGate(pos)){
        pulseGate(pos);
    }else if(inputtable(pos)){
        pulseWire(pos);
    }
}

void Cells::toggleSwitch(Vector2u pos){
    if(cells[pos.y][pos.x] == 2){
        charge[pos.y][pos.x] = !charge[pos.y][pos.x];
        pulses.push({pos,pos,charge[pos.y][pos.x]});
    }
} 

unsigned Cells::getCharge(Vector2u pos){
    return charge[pos.y][pos.x];
}

unsigned Cells::getValue(Vector2u pos){
    return cells[pos.y][pos.x];
}

void Cells::pCharge(Vector2u prev, Vector2u pos){
    unsigned current = charge[pos.y][pos.x];
    
    if(isGate(pos)){
        if(current)
            return;

        charge[pos.y][pos.x] = 1;       
    }else
        charge[pos.y][pos.x]++;
    
    pulses.push({prev,pos,1});
}

void Cells::nCharge(Vector2u prev, Vector2u pos){
    if(!isGate(pos) && !charge[pos.y][pos.x])
        return;

    isGate(pos) ? charge[pos.y][pos.x] = 0 : charge[pos.y][pos.x]--;    
    pulses.push({prev,pos,0});
}

bool Cells::transmittable(Vector2u pos){
    return cells[pos.y][pos.x] != 0;
}

bool Cells::inputtable(Vector2u pos){
    return cells[pos.y][pos.x] != 0 && cells[pos.y][pos.x] != 2;
}

bool Cells::isGate(Vector2u pos){
    switch(cells[pos.y][pos.x]){
        case 3:
        case 4:
        case 5:
            return 1;
        default:
            return 0;
    }
}

vector<Vector2u> Cells::getInputs(Vector2u pos){
    vector<Vector2u> moves;
    Vector2i top, bot, left, right;
    top = bot = left = right = Vector2i(pos);
    top.y--;
    bot.y++;
    left.x--;
    right.x++;

    if(!isGate(pos) && unsigned(right.x) < cells[right.y].size())
        moves.push_back(Vector2u(right));
    if(top.y >= 0)
        moves.push_back(Vector2u(top));
    if(unsigned(bot.y) < cells.size())
        moves.push_back(Vector2u(bot));
    if(left.x >= 0)
        moves.push_back(Vector2u(left));

    return moves;
}

vector<Vector2u> Cells::getOutputs(Vector2u prev, Vector2u pos){
    vector<Vector2u> moves;
    Vector2i top, bot, right, left;
    top = bot = right = left =  Vector2i(pos);
    top.y--;
    bot.y++;
    left.x--;
    right.x++;

    if(!isGate(pos)){
        if(top.y >= 0 && prev != Vector2u(top))
            moves.push_back(Vector2u(top));
        if(unsigned(bot.y) < cells.size() && prev != Vector2u(bot))
            moves.push_back(Vector2u(bot));
        if(left.x >= 0 && prev != Vector2u(left))
            moves.push_back(Vector2u(left));
    }
    if(unsigned(right.x) < cells[right.y].size() && prev != Vector2u(right))
        moves.push_back(Vector2u(right));
    
    return moves;
}

gateinfo Cells::getGateInfo(Vector2u pos){
    unsigned num_inputs = 0, num_on = 0;
    
    if(!isGate(pos))
        throw new exception;

    vector<Vector2u> moves = getInputs(pos);

    for(Vector2u move : moves){
        if(transmittable(move)){
            num_inputs++;
            if(charge[move.y][move.x] > 0)
                num_on++;
        }
    }

    return {num_on,num_inputs};
}

void Cells::pulseWire(Vector2u pos){
    vector<Vector2u> inputs = getInputs(pos);
    unsigned highestCharge = 0;
    Vector2u prev;
    for(Vector2u input : inputs){

        if(transmittable(input)){
            if(isGate(input) && input.x != pos.x-1 ){
                continue;
            }

            if(charge[input.y][input.x] > highestCharge){
                highestCharge = charge[input.y][input.x];
                prev = input;
            }
        }
    }

    if(!highestCharge)
        return;

    charge[pos.y][pos.x] = highestCharge-1;

    pCharge(prev,pos);
}

void Cells::pulseWire(Vector2u prev, Vector2u pos, bool current){
    //int prevc = charge[prev.y][prev.x];
    //int currc = charge[pos.y][pos.x];
    if(current)
        pCharge(prev,pos);
    else
        nCharge(prev,pos);
    
}

void Cells::pulseGate(Vector2u pos){
    if(!isGate(pos))
        throw new exception;

    int gate = cells[pos.y][pos.x];
        
    gateinfo ginfo = getGateInfo(pos);
    //cout << "num on: " << ginfo.first << " num total: " << ginfo.second<< " Gate type: "  << gate << " Gate pos: " << pos.x << "," << pos.y << endl;
    switch (gate){
        case 3:
            ginfo.first == 0 ? pCharge(pos,pos) : nCharge(pos,pos);
            break;
        case 4:
            ginfo.first == ginfo.second ? pCharge(pos,pos) : nCharge(pos,pos);
            break;
        case 5:
            ginfo.first == 0 || ginfo.first == ginfo.second ? pCharge(pos,pos) : nCharge(pos,pos);
            break;
    }

}

void Cells::iterate(){
    
    unsigned p_size = pulses.size();
    for(unsigned p = 0; p != p_size; ++p){

        pulse pls = pulses.front();
        pulses.pop();

        Vector2u prev = get<0>(pls);
        Vector2u pos = get<1>(pls); 
        bool current = get<2>(pls);       

        //big nasty
        vector<Vector2u> outputs = getOutputs(prev,pos);

        for(Vector2u output : outputs){
            if(isGate(output))
                pulseGate(output);
            else if(inputtable(output)){
                pulseWire(pos,output,current);
            }
        }  
    }
}

void Cells::draw(RenderWindow &window){
    RectangleShape cell(Vector2f(size,size));
    Color divider;
    
    for(unsigned y = 0; y < cells.size(); y++){
        for(unsigned x = 0; x < cells[y].size(); x++){
            bool next = 0;
            switch(cells[y][x]){
                case 0:
                    next = 1;
                    break;
                case 1:
                    cell.setFillColor(Color::Red);
                    break;
                case 2:
                    cell.setFillColor(Color::White);
                    break;
                case 3: 
                    cell.setFillColor(Color::Green);
                    break;
                case 4:
                    cell.setFillColor(Color::Magenta);
                    break;
                case 5:
                    cell.setFillColor(Color::Blue);
                    break;
            }

            if(next)
                continue;

            cell.setPosition(x*size,y*size);
            
            
            unsigned watts = charge[y][x];
            divider = cell.getFillColor();
            if(divider.r){
                divider.r-=200;
                divider.r += clamp(int(watts*25),0,200);
            }
            if(divider.g){
                divider.g-=200;
                divider.g += clamp(int(watts*25),0,200);
            }
            if(divider.b){
                divider.b-=200;
                divider.g += clamp(int(watts*25),0,200);
            }

            
            
            //divider = divider + divider*Color(watts,watts,watts);            
            cell.setFillColor(divider);

            divider = cell.getFillColor();

            

            window.draw(cell);
            //cout << cell.getPosition().x << " " << cell.getPosition().y << endl;
            //cout << int(divider.r) << " " << int(divider.g) << " " << int(divider.b) << endl;

        }
    }


}
