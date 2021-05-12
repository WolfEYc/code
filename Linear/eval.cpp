#include <iostream>
using namespace std;

int Arows,Acols,Brows,Bcols;

void mult(float** A, float** B){
    cout << "--------------------------------"<<endl
         << "Product of first * second matrix"<<endl
         << "--------------------------------"<<endl;
    for(int aR = 0;aR<Arows;aR++){
        for(int bC = 0;bC<Bcols;bC++){
            float sum = 0;
            for(int bR = 0;bR<Bcols;bR++){
                sum+=A[aR][bR]*B[bR][bC];
            }
            cout << sum <<" ";
        }
        cout <<endl;
    }
}

void add(float** A, float** B){
    cout << "--------------------------------"<<endl
         << "Sum of first + second matrix"<<endl
         << "--------------------------------"<<endl;
    for(int aR = 0;aR<Arows;aR++){
        for(int aC = 0;aC<Acols;aC++){
            cout << A[aR][aC]+B[aR][aC] << " ";
        }
        cout<<endl;
    }
}

void scale(float** A, float s){
    cout << "--------------------------------"<<endl
        << "Scale of matrix * "<<s<<endl
        << "--------------------------------"<<endl;
    for(int r = 0;r<Arows;r++){
        for(int c = 0;c<Acols;c++){
            cout << A[r][c]*s << " ";
        }
        cout << endl;
    }
}

void transpose(float** A){
    cout << "--------------------------------"<<endl
        << "Transposition of matrix"<<endl
        << "--------------------------------"<<endl;
    for(int c = 0;c<Acols;c++){    
        for(int r = 0;r<Arows;r++){
            cout << A[r][c] << " ";
        }
        cout << endl;
    }
}

int main(){
    
    char op;
    float s;

    cout << "Operation? (+ * s t) ";
    cin >> op;

    if(op == '+' || op == '*'){
        cout << "Size (rows cols) of first matrix: ";
        cin >> Arows >> Acols;        
        cout << "Size (rows cols) of second matrix: ";
        cin >> Brows >> Bcols;
    }else if (op == 's'){
        cout << "Size (rows cols) of matrix: ";
        cin >> Arows >> Acols;
        cout << "Scale by: ";
        cin >> s;
    }else{
        cout << "Size (rows cols) of matrix: ";
        cin >> Arows >> Acols; 
    }    
    if((op=='+' && (Arows!=Brows || Acols != Bcols)) || (op=='*' && (Acols!= Brows)) ){
        cout << "Invalid Operation"<<endl;
        return 0;
    }
    float *A[Arows];
    for(int i = 0; i < Arows; ++i)
        A[i] = new float[Acols];
    if(op=='+' || op == '*'){
        float *B[Brows];
        for(int i = 0; i < Arows; ++i)
            B[i] = new float[Bcols];

        cout << "Enter each number in the first matrix:"<<endl;    
        for(int r = 0;r<Arows;r++)
            for(int c = 0;c<Acols;c++)
                cin >> A[r][c];

        cout << "Enter each number in the second matrix:"<<endl;
        for(int r = 0;r<Brows;r++)
            for(int c = 0;c<Bcols;c++)
                cin >> B[r][c];
        
        if(op=='*')
            mult(A,B);
        else add(A,B);
    }else{
        cout << "Enter each number in the matrix:"<<endl;    
        for(int r = 0;r<Arows;r++)
            for(int c = 0;c<Acols;c++)
                cin >> A[r][c];
        if(op=='s')
            scale(A,s);
        else transpose(A);
    }
    return 0;
}