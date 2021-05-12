#include <bits/stdc++.h>
#include "konstants.h"
#include <pthread.h>
using namespace std;

#define size 32


void SHR(vector<bool> bits,vector<bool> &result, int amt){
    for(int i = 0; i<size; i++)
        result[i] = bits[i];

    for(int i = 0; i < amt; i++){
        for(int bit = size-1; bit>0 ; bit--)
            result[bit] = result[bit-1];        
        result[0] = 0;
    }
}

void ROTR(vector<bool> bits,vector<bool> &result, int amt){
    for(int i = 0; i < size;i++)
        result[i] = bits[i];
    
    for(int i = 0; i < amt; i++){
        bool carrybit = result[size-1];
        for(int bit = size-1; bit>0 ; bit--)
            result[bit] = result[bit-1];        
        result[0] = carrybit;
    }
}

void XOR(vector<bool> bits,vector<bool> bits1,vector<bool> &result){
    for(int i = 0; i<size; i++)
        result[i] = bits[i] xor bits1[i];    
}

void add(vector<bool> bits, vector<bool> bits1, vector<bool> &result){
    bool carrybit = 0;
    for(int i = size-1; i>=0; i--){
        result[i] = bits[i] xor bits1[i] xor carrybit;
        carrybit = (bits[i] + bits1[i] + carrybit)>1;
    }
}

void sigmaZero(vector<bool> bits,vector<bool> &result){
    vector<bool> rotr7 (size), rotr18 (size), shr3 (size);
    vector<bool> temp (size);  

    ROTR(bits,rotr7,7);
    ROTR(bits,rotr18,18);
    SHR(bits,shr3, 3);

    XOR(rotr7,rotr18,temp);
    XOR(temp,shr3,result);

}

void sigmaOne(vector<bool> bits,vector<bool> &result){
    vector<bool> rotr17 (size), rotr19 (size), shr10 (size);
    vector<bool> temp (size);    

    ROTR(bits,rotr17,17);
    ROTR(bits,rotr19,19);
    SHR(bits,shr10, 10);

    XOR(rotr17,rotr19,temp);
    XOR(temp,shr10,result);
}

void SIGMAzero(vector<bool> bits,vector<bool> &result){
    vector<bool> rotr2(size), rotr13 (size), rotr22 (size);
    vector<bool> temp (size);    

    ROTR(bits, rotr2, 2);
    ROTR(bits, rotr13, 13);
    ROTR(bits, rotr22, 22);

    XOR(rotr2,rotr13,temp);
    XOR(temp,rotr22,result);
}

void SIGMAone(vector<bool> bits,vector<bool> &result){
    vector<bool> rotr6 (size), rotr11 (size), rotr25 (size);
    vector<bool> temp(size);    

    ROTR(bits, rotr6, 6);
    ROTR(bits, rotr11, 11);
    ROTR(bits, rotr25, 25);

    XOR(rotr6,rotr11,temp);
    XOR(temp,rotr25,result);
}

void choice(vector<bool> x, vector<bool> y, vector<bool> z, vector<bool> &result){
    for(int i = 0; i<size;i++){
        if(x[i])
            result[i] = y[i];
        else
            result[i] = z[i];
    }
}

void maj(vector<bool> x, vector<bool> y, vector<bool> z, vector<bool> &result){    
    for(int i = 0; i < size; i++){
        result[i] = (x[i] + y[i] + z[i])>1;
    }
}

void biDec(vector<bool> &bits, int n, int dec){
    for(int i = n-1; i>=0; i--){      
        if(dec > 0){
            bits[i] = dec%2;
            dec /= 2;
        }else
            bits[i] = 0;        
    }
}

void Clear(){
    cout << "\x1B[2J\x1B[H";
}

void printWord(bool* bits){
    for(int i = 0; i < size; i++)
        cout << bits[i];
}

string fromFile(string file){
    ifstream in(file);
    char temp;
    string out = "";
    while(in.get(temp)){
        out += temp;
    }

    return out;
}


void convertInputToBinary(vector<bool> &message, int& msgsize, string input){
    unsigned int mlen = input.length();
    unsigned int numBits = mlen*8;
    unsigned int msgCount = numBits/512+1;
    msgsize = msgCount*512;

    vector<bool> ibits (numBits);
    vector<bool> sizebits (64);
    biDec(sizebits,64,numBits);
    message = vector<bool>(msgsize);

    for(unsigned int i = 0 ; i < mlen; i++){
        int c = abs(input[i]);

        vector<bool> byte(8);

        biDec(byte,8,c);

        for(int bit = 0; bit<8; bit++)            
            ibits[i*8+bit] = byte[bit];

    }  
    
    for(int i = 0; i < numBits; i++)
        message[i] = ibits[i];    

    message[numBits] = 1; //endbit or whatever (after msg itself before padding)

    for(int i = numBits+1; i < msgsize-64; i++)//padding
        message[i] = 0;

    for(int i = 0; i < 64; i++)
        message[i+msgsize-64] = sizebits[i];

}

void intoBlocks(vector<bool> msg, vector<vector<bool>> &blocks, int msgSize, int& numBlocks){
    numBlocks = msgSize/512;
    blocks = vector<vector<bool>>(numBlocks);
    for(int i = 0; i < numBlocks; i++){
        blocks[i] = vector<bool>(512);
        for(int bit = 0; bit < 512; bit++)
            blocks[i][bit] = msg[i*512+bit];
    }
}

void messageSchedule(vector<bool> block, vector<vector<bool>> &result){
    result = vector<vector<bool>>(64);
    for(int w = 0, i = 0; w < 16; w++){ //first 16 from block
        result[w] = vector<bool>(size);
        for(int b = 0; b < size; b++,i++){
            result[w][b] = block[i];
        }
    }

    for(int w = 16; w < 64; w++){ //fill da rest
        vector<bool> s1 (size), s0(size);
        result[w]=vector<bool>(size);

        sigmaOne(result[w-2],s1);
        sigmaZero(result[w-15],s0);
        add(result[w-16],s0,result[w]);
        add(result[w],result[w-7],result[w]);
        add(result[w], s1, result[w]);
    }
}

void compression(vector<vector<bool>> &H0,vector<vector<bool>> W){
    vector<vector<bool>> H1 = H0;

    for(int w = 0; w < 64; w++){
        vector<bool> T1 (size), T2 (size),
        S1E(size), S0A (size),
        Chefg(size), Majabc (size),
        temp (size), temp1 (size),
        temp2(size);

        //T1
        SIGMAone(H1[4], S1E);
        choice(H1[4],H1[5],H1[6],Chefg);

        add(W[w],konstants[w],temp);  
        
        add(Chefg,S1E,temp1);
        add(temp1,H1[7],temp2);
        add(temp,temp2,T1);     

        //T2
        SIGMAzero(H1[0], S0A);   
        maj(H1[0],H1[1],H1[2],Majabc);
        add(S0A, Majabc, T2);

        for(int s = 7; s > 0; s--)
            H1[s] = H1[s-1];

        add(T1,T2,H1[0]);
        add(T1,H1[4],H1[4]);
        
    }

    for(int i = 0; i < 8; i++)
        add(H0[i],H1[i],H0[i]);

}

string biHex(vector<vector<bool>> bits){
    string ret = "";
    for(int l = 0; l < 8; l++){
        int dec = 0;
        string curr = "";
        for(int b = size-1, i = 1; b >= 0; b--){
            if(bits[l][b])
                dec+=i;

            if(i==8){
                i = 1;
                char c;
                if(dec < 10)
                    c = dec+48;
                else
                    c = dec+55;

                curr = c + curr;
                dec = 0;            
            }else
                i*=2;
        }
        //cout << curr << endl;
        ret = ret + curr;
    }
    return ret;
}

string Sha256(string input){
    int msgSize, numBlocks;
    vector<bool> msgbits;
    vector<vector<bool>> msgblocks;

    convertInputToBinary(msgbits,msgSize,input);

    intoBlocks(msgbits,msgblocks,msgSize,numBlocks);

    vector<vector<vector<bool>>> Words (numBlocks);

    for(int bl = 0; bl < numBlocks; bl++)
        messageSchedule(msgblocks[bl],Words[bl]);

    vector<vector<bool>> H0 = initial;

    for(int i = 0; i < numBlocks; i++){
        compression(H0, Words[i]);
    }

    string output = biHex(H0);

    return output;   
}

char genRandom()  // Random string generator function.
{
    return alphanum[rand() % 70];
}

string makeRandom(){
    string out = "";
    for(int i = 0; i < 45; i++)
        out+=genRandom();
    return out;
}

void mine(int diff){
    while(true){
        string input = makeRandom();        
        string output = Sha256(input);
        if(output.find_first_not_of('0')>=diff){
            cout << input << " " << output << endl;
        }
    }
}

int main(int argc, char** argv){
    
    string input;
    int diff;
    srand(time(NULL));

    if(argc==2){
        input = argv[1];
    }else if (argc == 3){
        input = argv[1];
        diff = stoi(argv[2]);
    }

    if(input == "mine"){
        int cores = thread::hardware_concurrency();  
        vector<thread> threads;

        for(int i = 0; i < cores; i++){
            threads.push_back(thread(mine,diff));
        }

        for(auto &th: threads)
            th.join();
    }

    if(input.find(".txt")!=string::npos && input.find(".txt")==input.length()-4){ //has .txt at end
        input = fromFile(input);
    }

    if(input.find(".png")!=string::npos && input.find(".png")==input.length()-4){ //has .txt at end
        input = fromFile(input);
    }

    if(input.find(".jpg")!=string::npos && input.find(".jpg")==input.length()-4){ //has .txt at end
       input = fromFile(input);
    }

    string output = Sha256(input);

    cout << output << endl;

    return 0;

}
