import java.awt.*;

/**
 * Write a description of class Grid here.
 *
 * @author (Isaac Wolf)
 * @version (1.0)
 */
public class Grid
{
    Pieces localPieces= new Pieces();

    private int[][] grid=new int[][]
            {{9,7,8,10,11,8,7,9},
            {6,6,6,6,6,6,6,6},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {0,0,0,0,0,0,0,0},
            {3,1,2,4,5,2,1,3}};

    public void setPiece(int x,int y, int newp){
        grid[x][y]=newp;
    }
    public int getPiece(int row,int col){
        return grid[row][col];
    }

    public int[][] getCurrentGrid(){
        return grid;
    }
    
    public void printGrid(int[][] grid){
        System.out.println("    0   1   2   3   4   5   6   7");
        for(int r=0;r<grid.length;r++){
            System.out.print(r);  
            for(int c=0;c<grid[r].length;c++){
                System.out.print("   "+grid[r][c]);
                
            }
            System.out.println();
        }
    }

    public boolean whitewin(){
        //first see if white is in check
        if(!localPieces.bCheck(grid))return false;

        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                for(int x=0;x<8;x++){
                    for(int y=0;y<8;y++){
                        if(localPieces.blackCanMove(grid,i,j,x,y))return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean blackwin(){
        if(!localPieces.wCheck(grid))return false;

        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                for(int x=0;x<8;x++){
                    for(int y=0;y<8;y++){
                        if(localPieces.whiteCanMove(grid,i,j,x,y))return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean draw(){
        if(localPieces.wCheck(grid)|| localPieces.bCheck(grid))return false;
        int c=0,b=0,a=0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                for(int x=0;x<8;x++){
                    for(int y=0;y<8;y++){
                        if(grid[i][j]!=-1 && grid[i][j]!=5 && grid[i][j]!=11) a=1;
                        if(localPieces.whiteCanMove(grid,i,j,x,y))c=1;
                        if(localPieces.blackCanMove(grid,i,j,x,y))b=1;
                    }
                }
            }
        }
        return b==0 || c==0 || a==0;
    }

    public void setGrid(int selectedRow,int selectedCol,int movedRow,int movedCol){//use to move piece
        int piece =grid[selectedRow][selectedCol];
        grid[selectedRow][selectedCol]=-1;
        if(piece==0 && movedRow==0)piece=4;
        if(piece==6 && movedRow==7)piece=10;
        grid[movedRow][movedCol]=piece;
    }

    public void resetGrid(){//use to reset the grid
        grid=new int[][]
            {{9,7,8,10,11,8,7,9},
            {6,6,6,6,6,6,6,6},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {0,0,0,0,0,0,0,0},
            {3,1,2,4,5,2,1,3}};

    }

    

    

    

    

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


    


}
