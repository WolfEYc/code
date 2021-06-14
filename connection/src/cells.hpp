#include "wire.hpp"
#include "gate.hpp"


class cells{
private:
    unsigned size;
    map<Vector2u, cell*> cellmap;
public:
    cells(unsigned cellsize) : size(cellsize){};

    void add(Vector2u pos, String type){

        if(type == "lever"){

        }            
        else if (type == "wire"){
            cellmap[pos] = new wire(size, pos);
        }else
            cellmap[pos] = new gate(size, pos, type);
        }
        
            
        

        for(Vector2u signal : c->out){
            if(cellmap.find(c->pos)->second->type == "gate" && signal.x != c->pos.x - 1){
                ((gate*) (cellmap.find(c->pos)->second))->num_inputs++;
            }  
        }
    }

    void pulse(){
        vector<unsigned> times_visited(cellmap.size(),0);
        queue<Vector2u> open;



    }

    void pulse(cell* &c){


        
        for(Vector2u signal : c->out){

            if(cellmap.find(signal) == cellmap.end())
                continue;

            cell*& into = cellmap[signal];

            if(into->type == "wire" && !into->charge){
                into->charge = 1;
                pulse(into,nextPulses);
                continue;
            }
            
            if(into->type == "gate" && signal.x != c->pos.x - 1){
                ((gate*)(into))->on_inputs++;
                ((gate*)(into))->setCharge();
                nextPulses[into->pos] = into;                
                continue;
            }




        }


    }


};
