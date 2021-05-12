
/**
 * 
 * used to track which moves are allowed for the pieces
 * @author (Isaac wolf i guess)
 * @version (1.0)
 */
public class Pieces
{
    
    
        //white player
        //0=pawn
        //1=knight
        //2=bishop
        //3=rook
        //4=queen
        //5=king

        //black player
        //6=pawn
        //7=knight
        //8=bishop
        //9=rook
        //10=queen
        //11=king
     public boolean wCheck(int[][] grid){
         //find the white king's location
         boolean wkg=false;
         int kr=-1,kc=-1;
         for(int r=0;r<8;r++){
             for(int c=0;c<8;c++){
                 if(grid[r][c]==5){
                    kr=r;
                    kc=c;
                 }
                 if(grid[r][c]==11)wkg = true;
             }
         }
         if(!wkg)return false;
        //see if black can move there
        for(int r=0;r<8;r++){
            for(int c=0;c<8;c++){
                if(blackCanMove(grid,r,c,kr,kc)){
                    return true;
                }
            }
        }
        return false;
    }
    public boolean wk=false, wkr=false,wqr=false,bk=false,bkr=false,bqr=false;

     public int passantcol=-1;
     //remember to wipe after next players turn


public boolean bCheck(int[][]grid){

    boolean wkg=false;

    //find the black king's location
    int kr=-1,kc=-1;
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            if(grid[r][c]==11){
                kr=r;
                kc=c;
            }
            if(grid[r][c]==5)wkg = true;
        }
    }
    if(!wkg)return false;
    //see if white can move there
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            if(whiteCanMove(grid,r,c,kr,kc)){
                return true;
            }
        }
    }
    return false;
    }
    

    public boolean whiteCanMove(int[][]grid,int selectedRow,int selectedCol,int movedRow,int movedCol){
        int[][] tgrid=new int[8][8];
        for(int i=0;i<8;i++){
            System.arraycopy(grid[i], 0, tgrid[i], 0, 8);
        }


        if (selectedRow < 0 || selectedRow >= 8 || movedRow < 0 || movedRow >= 8) return false;
        if(selectedCol<0 || selectedCol>=8)return false;
        if(movedCol<0 || movedCol>=8)return false;
        if(selectedRow==movedRow && selectedCol==movedCol)return false;

        int piece = grid[selectedRow][selectedCol];
        int landPiece = grid[movedRow][movedCol];
        if(piece>5)return false;
        if(piece<0)return false;
        if(landPiece<=5 && landPiece!=-1)return false;

        tgrid[selectedRow][selectedCol] = -1;
        tgrid[movedRow][movedCol]=piece;
        if(wCheck(tgrid))return false;


        //white pawn
        if(piece==0){
            if(selectedCol==movedCol){
                if(landPiece==-1){
                    if(movedRow==selectedRow-1){
                        return true;
                    }
                    if(selectedRow==6 && movedRow==selectedRow-2 && grid[selectedRow-1][selectedCol]==-1){
                        passantcol = movedCol;
                        return true;
                    }
                }                
            }
            if(selectedCol==movedCol-1){
                if(movedRow==selectedRow-1 && (landPiece>5)){
                    return true;
                }
                if(movedRow==selectedRow-1 &&(movedCol==passantcol && selectedRow==3 )){

                    return true;
                }
            }            
            if(selectedCol==movedCol+1){
                if(movedRow==selectedRow-1 && (landPiece>5)){
                    return true;
                }
                if(movedRow==selectedRow-1 &&(movedCol==passantcol && selectedRow==3 )){

                    return true;
                }
            }
        }

        //white knight
        if(piece==1){
            if(movedRow==selectedRow-2){
                if(selectedCol==movedCol-1){
                    return true;
                }
                if(selectedCol==movedCol+1){
                    return true;
                }
            }
            if(movedRow==selectedRow-1){
                if(selectedCol==movedCol-2){
                    return true;
                }
                if(selectedCol==movedCol+2){
                    return true;
                }
            }
            if(movedRow==selectedRow+1){
                if(selectedCol==movedCol-2){
                    return true;
                }
                if(selectedCol==movedCol+2){
                    return true;
                }
            }
            if(movedRow==selectedRow+2){
                if(selectedCol==movedCol-1){
                    return true;
                }
                if(selectedCol==movedCol+1){
                    return true;
                }
            }
        }

        //white bishop
        if(piece==2){
            if(movedRow<selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow-1;rows>=0;rows-=1){//up and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols-=1;

                }
            }
            if(movedRow<selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow-1;rows>=0;rows=rows-1){//up and to the right

                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols=cols+1;

                }
            }
            if(movedRow>selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols-1;

                }
            }
            if(movedRow>selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the right
                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols+1;

                }
            }
        }

        //white rook
        if(piece==3){
            if(movedRow<selectedRow && movedCol==selectedCol){
                for(int r=selectedRow-1;r>=0;r=r-1){
                    if(movedRow==r){

                        return true;
                    }
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow>selectedRow && movedCol==selectedCol){
                for(int r=selectedRow+1;r<8;r=r+1){
                    if(movedRow==r){
                        return true;
                    }
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol>selectedCol){
                for(int c=selectedCol+1;c<8;c=c+1){
                    if(movedCol==c){

                        return true;
                    }
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol<selectedCol){
                for(int c=selectedCol-1;c>=0;c=c-1){
                    if(movedCol==c){

                        return true;
                    }
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
        }

        //white queen
        if(piece==4){
            //rook moves
            if(movedRow<selectedRow && movedCol==selectedCol){
                for(int r=selectedRow-1;r>=0;r=r-1){
                    if(movedRow==r)return true;
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow>selectedRow && movedCol==selectedCol){
                for(int r=selectedRow+1;r<8;r=r+1){
                    if(movedRow==r)return true;
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol>selectedCol){
                for(int c=selectedCol+1;c<8;c=c+1){
                    if(movedCol==c)return true;
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol<selectedCol){
                for(int c=selectedCol-1;c>=0;c=c-1){
                    if(movedCol==c)return true;
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            //bishop moves
            if(movedRow<selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow-1;rows>=0;rows-=1){//up and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols-=1;

                }
            }
            if(movedRow<selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow-1;rows>=0;rows=rows-1){//up and to the right

                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols=cols+1;

                }
            }
            if(movedRow>selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols-1;

                }
            }
            if(movedRow>selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the right
                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols+1;

                }
            }
        }

        //white king
        if(piece==5){
            for(int r=selectedRow-1;r<=selectedRow+1;r++){//used to remove pawns
                for(int c=selectedCol-1;c<=selectedCol+1;c++){
                    if(movedRow==r && movedCol==c){

                        return true;
                    }
                }
            }
            if((movedRow==7 && movedCol==6) && grid[7][5]==-1 && grid[7][6]==-1 && !wk && !wkr && !wCheck(grid)){
                if(whiteCanMove(grid,7,4,7,5)){
                    return true;
                }
            }
            if((movedRow==7 && movedCol==2) && grid[7][1]==-1 &&grid[7][2]==-1 && grid[7][3]==-1 && !wk && !wqr && !wCheck(grid)){
                if(whiteCanMove(grid,7,4,7,3)){
                    return true;
                }
            }
        }
        
        return false;
    }
    
    public boolean blackCanMove(int[][] grid,int selectedRow,int selectedCol,int movedRow,int movedCol){
        int[][] tgrid=new int[8][8];
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                tgrid[i][j]=grid[i][j];
            }
        }


        if(selectedRow<0 || selectedRow>=8)return false;
        if(movedRow<0 || movedRow>=8)return false;
        if(selectedCol<0 || selectedCol>=8)return false;
        if(movedCol<0 || movedCol>=8)return false;
        if(selectedRow==movedRow && selectedCol==movedCol)return false;

        int piece = grid[selectedRow][selectedCol];
        int landPiece = grid[movedRow][movedCol];
        if(piece<6)return false;
        if(landPiece>=6)return false;


        tgrid[selectedRow][selectedCol] = -1;
        tgrid[movedRow][movedCol]=piece;
        if(bCheck(tgrid))return false;

        //black pawn
        if(piece==6){
            if(selectedCol==movedCol){
                if(landPiece==-1){
                    if(movedRow==selectedRow+1){
                        return true;
                    }
                    if(selectedRow==1 && movedRow==selectedRow+2&& grid[selectedRow+1][selectedCol]==-1){
                        passantcol = selectedCol;
                        return true;

                    }
                }                
            }
            if(selectedCol==movedCol-1){
                if(movedRow==selectedRow+1 && (landPiece!=-1)){
                    return true;
                }
                if(movedRow==selectedRow+1 &&(movedCol==passantcol && selectedRow==4) ){

                    return true;
                }
            }
            if(selectedCol==movedCol+1){
                if(movedRow==selectedRow+1 && (landPiece!=-1)){
                    return true;
                }
                if(movedRow==selectedRow+1 &&(movedCol==passantcol && selectedRow==4 )){
                    grid[selectedRow][passantcol]=-1;
                    return true;
                }
            }
        }

        //black knight
        if(piece==7){
            if(movedRow==selectedRow-2){
                if(selectedCol==movedCol-1){
                    return true;
                }
                if(selectedCol==movedCol+1){
                    return true;
                }
            }
            if(movedRow==selectedRow-1){
                if(selectedCol==movedCol-2){
                    return true;
                }
                if(selectedCol==movedCol+2){
                    return true;
                }
            }
            if(movedRow==selectedRow+1){
                if(selectedCol==movedCol-2){
                    return true;
                }
                if(selectedCol==movedCol+2){
                    return true;
                }
            }
            if(movedRow==selectedRow+2){
                if(selectedCol==movedCol-1){
                    return true;
                }
                if(selectedCol==movedCol+1){
                    return true;
                }
            }
        }

        //black bishop
        if(piece==8){
            if(movedRow<selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow-1;rows>=0;rows-=1){//up and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols-=1;

                }
            }
            if(movedRow<selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow-1;rows>=0;rows=rows-1){//up and to the right

                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols=cols+1;

                }
            }
            if(movedRow>selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols-1;

                }
            }
            if(movedRow>selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the right
                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols+1;

                }
            }            
        }

        //black rook
        if(piece==9){
            if(movedRow<selectedRow && movedCol==selectedCol){
                for(int r=selectedRow-1;r>=0;r=r-1){
                    if(movedRow==r)return true;
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow>selectedRow && movedCol==selectedCol){
                for(int r=selectedRow+1;r<8;r=r+1){
                    if(movedRow==r){

                        return true;
                    }
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol>selectedCol){
                for(int c=selectedCol+1;c<8;c=c+1){
                    if(movedCol==c){

                        return true;
                    }
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol<selectedCol){
                for(int c=selectedCol-1;c>=0;c=c-1){
                    if(movedCol==c){

                        return true;
                    }
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
        }

        //black queen
        if(piece==10){
            //rook moves
            if(movedRow<selectedRow && movedCol==selectedCol){
                for(int r=selectedRow-1;r>=0;r=r-1){
                    if(movedRow==r)return true;
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow>selectedRow && movedCol==selectedCol){
                for(int r=selectedRow+1;r<8;r=r+1){
                    if(movedRow==r)return true;
                    if(grid[r][selectedCol]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol>selectedCol){
                for(int c=selectedCol+1;c<8;c=c+1){
                    if(movedCol==c)return true;
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            if(movedRow==selectedRow && movedCol<selectedCol){
                for(int c=selectedCol-1;c>=0;c=c-1){
                    if(movedCol==c)return true;
                    if(grid[selectedRow][c]!=-1)return false;//checks for jumping a piece
                }
            }
            //bishop moves
            if(movedRow<selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow-1;rows>=0;rows-=1){//up and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols-=1;

                }
            }
            if(movedRow<selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow-1;rows>=0;rows=rows-1){//up and to the right

                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping
                    cols=cols+1;

                }
            }
            if(movedRow>selectedRow && movedCol<selectedCol){
                int cols=selectedCol-1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the left
                    if(cols<0)return false;//col capper
                    if(movedRow==rows && movedCol==cols )return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols-1;

                }
            }
            if(movedRow>selectedRow && movedCol>selectedCol){
                int cols=selectedCol+1;
                for(int rows =selectedRow+1;rows<8;rows=rows+1){//down and to the right
                    if(cols>7)return false;//col capper
                    if(movedRow==rows && movedCol==cols)return true;
                    if(grid[rows][cols]!=-1)return false;//checks for jumping a piece
                    cols=cols+1;

                }
            }
        }

        //black king
        if(piece==11){
            for(int r=selectedRow-1;r<=selectedRow+1;r++){//used to remove pawns
                for(int c=selectedCol-1;c<=selectedCol+1;c++){
                    if(movedRow==r && movedCol==c){

                        return true;
                    }
                }
            }
            if((movedRow==0 && movedCol==6) && grid[0][5]==-1 && grid[0][6]==-1 && !bk && !bkr &&!bCheck(grid)){
                if(blackCanMove(grid,0,4,0,5)){
                    return true;
                }
            }
            if((movedRow==0 && movedCol==2) && grid[0][1]==-1 &&grid[0][2]==-1 && grid[0][3]==-1 && !bk && !bqr && !bCheck(grid)){
                if(blackCanMove(grid,0,4,0,3)){
                    return true;
                }
            }
        }
        
        return false;
    }

}
