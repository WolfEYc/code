import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;


public class Panel extends JPanel implements MouseListener, Runnable {
    private BufferedImage bl,bd,nl,nd,kl,kd,ql,qd,pl,pd,rl,rd,selected;
    public Panel( int width, int height ) {
        super();
        setSize( width, height );
        addMouseListener(this);
        load();
        new Thread(this).start();
    }
   Pieces pieces = new Pieces();
   Grid thegriddy = new Grid();
   private boolean bcheck=false;
   private boolean wcheck=false;
   private boolean bwin=false;
   private boolean wwin=false;
   private boolean draw = false;
    private boolean nah=false;
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
    public void paint(Graphics g) {
        char notation = 'a';
        int c=0;
        int at=8;

        for(int i=0;i<640;i+=80){
            c++;
            for(int j=0;j<640;j+=80){
                c++;
                if(c%2!=0) {
                    g.setColor(Color.BLUE);
                }else {
                    g.setColor(Color.GRAY);

                }
                g.fillRect(j, i, 80, 80);
                int row = i/80;
                int col = j/80;
                int piece = thegriddy.getPiece(row,col);
                if(!(row==selectedRow && col ==selectedCol && !nah)){
                    if (held && (player == 0 && pieces.whiteCanMove(thegriddy.getCurrentGrid(), selectedRow, selectedCol, row, col)) || (player == 1 && pieces.blackCanMove(thegriddy.getCurrentGrid(), selectedRow, selectedCol, row, col))) {
                        g.setColor(Color.MAGENTA);
                        g.fillRect(j, i, 80, 80);
                    }

                    switch (piece) {
                        case 0: g.drawImage(pl, j + 8, i + 2, null); break;
                        case 1: g.drawImage(nl, j + 8, i + 2, null); break;
                        case 2: g.drawImage(bl, j + 8, i + 2, null); break;
                        case 3: g.drawImage(rl, j + 8, i + 2, null); break;
                        case 4: g.drawImage(ql, j + 8, i + 2, null); break;
                        case 5: {
                            if (wcheck) {
                                g.setColor(Color.ORANGE);
                                g.fillRect(j, i, 80, 80);
                            }
                            if (bwin) {
                                g.setColor(Color.RED);
                                g.fillRect(j, i, 80, 80);
                            }
                            if (draw) {
                                g.setColor(Color.GREEN);
                                g.fillRect(j, i, 80, 80);
                            }
                            g.drawImage(kl, j + 8, i + 2, null);  break;
                        }
                        case 6: g.drawImage(pd, j + 8, i + 2, null); break;
                        case 7: g.drawImage(nd, j + 8, i + 2, null); break;
                        case 8: g.drawImage(bd, j + 8, i + 2, null); break;
                        case 9: g.drawImage(rd, j + 8, i + 2, null); break;
                        case 10: g.drawImage(qd, j + 8, i + 2, null); break;
                        case 11: {
                            if (bcheck) {
                                g.setColor(Color.ORANGE);
                                g.fillRect(j, i, 80, 80);
                            }
                            if (wwin) {
                                g.setColor(Color.RED);
                                g.fillRect(j, i, 80, 80);
                            }
                            if (draw) {
                                g.setColor(Color.GREEN);
                                g.fillRect(j, i, 80, 80);
                            }
                            g.drawImage(kd, j + 8, i + 2, null); break;
                        }
                    }
                }

            }
        }
        if(getMousePosition()!=null) {
            try {
                int mx = getMousePosition().x - 30;
                int my = getMousePosition().y - 30;
                if (mx > 640) mx = 640;
                if (mx < 0) mx = 0;
                if (my > 640) my = 640;
                if (my < 0) my = 0;
                g.drawImage(selected, mx, my, null);
            }catch(Exception ignored){

            }
        }
        g.setColor(Color.BLACK);
        for(int f=0;f<=640;f+=80) {
            g.setColor(Color.WHITE);
            g.drawString(notation+"",f+10,12);
            g.drawString(notation+"",f+10,630);
            g.drawString(String.valueOf(at),10,f+40);
            g.drawString(String.valueOf(at),630,f+40);
            g.drawString("move: "+movecount,587,630);
            at--;
            notation++;
        }
        if(draw || bwin || wwin){
            g.setColor(Color.black);
            g.fillRect(20,618,40,15);
            g.setColor(Color.WHITE);
            g.drawString("reset",25,630);
        }
    }


    public boolean held = false;



    private synchronized void load(){
        try{
            bl = ImageIO.read(getClass().getResource("/resources/Chess_blt60.png"));
            bd = ImageIO.read(getClass().getResource("/resources/Chess_bdt60.png"));
            nl = ImageIO.read(getClass().getResource("/resources/Chess_nlt60.png"));
            nd = ImageIO.read(getClass().getResource("/resources/Chess_ndt60.png"));
            kl = ImageIO.read(getClass().getResource("/resources/Chess_klt60.png"));
            kd = ImageIO.read(getClass().getResource("/resources/Chess_kdt60.png"));
            ql = ImageIO.read(getClass().getResource("/resources/Chess_qlt60.png"));
            qd = ImageIO.read(getClass().getResource("/resources/Chess_qdt60.png"));
            pl = ImageIO.read(getClass().getResource("/resources/Chess_plt60.png"));
            pd = ImageIO.read(getClass().getResource("/resources/Chess_pdt60.png"));
            rl = ImageIO.read(getClass().getResource("/resources/Chess_rlt60.png"));
            rd = ImageIO.read(getClass().getResource("/resources/Chess_rdt60.png"));
        }catch(Exception e){
            e.printStackTrace();
        }

    }

    int player=0;

    private int selectedRow=-1;
    private int selectedCol=-1;
    private int movedRow=-1;
    private int movedCol=-1;
    private int passantrack=-1;
    private int movecount=0;
    private int passantcount=0;

    @Override
    public void mouseClicked(MouseEvent e) {
        if(bwin || draw || wwin ){
            if( (e.getX()>=20 && e.getX()<=60) && (e.getY()>=618 && e.getY()<=633)){
                thegriddy.resetGrid();
                bwin = false;
                draw = false;
                wwin=false;
                bcheck=false;
                wcheck= false;
                selectedRow=-1;
                selectedCol=-1;
                movedRow=-1;
                movedCol=-1;
                passantrack=-1;
                movecount=0;
                passantcount=0;
                player=0;
                nah=false;
            }
        }
        //g.fillRect(20,618,40,15);

    }

    @Override
    public void mousePressed(MouseEvent e) {
        if(!draw && !bwin && !wwin) {
            selectedRow = e.getY() / 80;
            selectedCol = e.getX() / 80;
            held = true;
            int piece = thegriddy.getPiece(selectedRow, selectedCol);
            if ((piece > 5 && player == 1) || (piece < 6 && player == 0)) {
                nah = false;
                switch (piece) {
                    case 0: selected = pl; break;
                    case 1: selected = nl; break;
                    case 2: selected = bl; break;
                    case 3: selected = rl; break;
                    case 4: selected = ql; break;
                    case 5: selected = kl; break;
                    case 6: selected = pd; break;
                    case 7: selected = nd; break;
                    case 8: selected = bd; break;
                    case 9: selected = rd; break;
                    case 10: selected = qd; break;
                    case 11: selected = kd; break;
                }
            } else {
                nah = true;
            }
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {

        if(!draw && !bwin && !wwin) {
            movedRow = e.getY() / 80;
            movedCol = e.getX() / 80;
            draw = thegriddy.draw();
            selected = null;
            held = false;
            if (player == 0 && pieces.whiteCanMove(thegriddy.getCurrentGrid(), selectedRow, selectedCol, movedRow, movedCol)) {
                if (selectedRow == 7 && selectedCol == 4 && movedRow == 7 && movedCol == 6 && thegriddy.getPiece(7, 4) == 5) {
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                    thegriddy.setGrid(7, 7, 7, 5);
                } else if (selectedRow == 7 && selectedCol == 4 && movedRow == 7 && movedCol == 2 && thegriddy.getPiece(7, 4) == 5) {
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                    thegriddy.setGrid(7, 0, 7, 3);
                }else if(selectedRow==7 && selectedCol==7){
                    pieces.wkr=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }
                else if(selectedRow==7 && selectedCol==0){
                    pieces.wqr=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }else if(selectedRow==7 && selectedCol==4){
                    pieces.wk=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }else if(movedRow==selectedRow-1 &&(movedCol==pieces.passantcol && selectedRow==3 && thegriddy.getPiece(selectedRow,selectedCol) ==0 && thegriddy.getCurrentGrid()[selectedRow][pieces.passantcol]==6)){
                    thegriddy.setPiece(selectedRow, pieces.passantcol, -1);
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }
                else {
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }
                movecount++;
                player = 1;

            } else if (player == 1 && pieces.blackCanMove(thegriddy.getCurrentGrid(), selectedRow, selectedCol, movedRow, movedCol)) {
                if (selectedRow == 0 && selectedCol == 4 && movedRow == 0 && movedCol == 6 && thegriddy.getPiece(0, 4) == 11) {
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                    thegriddy.setGrid(0, 7, 0, 5);
                } else if (selectedRow == 0 && selectedCol == 4 && movedRow == 0 && movedCol == 2 && thegriddy.getPiece(0, 4) == 11) {
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                    thegriddy.setGrid(0, 0, 0, 3);
                } else if(selectedRow==0 && selectedCol==7){
                    pieces.bkr=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }
                else if(selectedRow==0 && selectedCol==0){
                    pieces.bqr=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }else if(selectedRow==0 && selectedCol==4){
                    pieces.bk=true;
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }else if(movedRow==selectedRow+1 &&(movedCol==pieces.passantcol && selectedRow==4 && thegriddy.getPiece(selectedRow,selectedCol) ==6 && thegriddy.getCurrentGrid()[selectedRow][pieces.passantcol]==0)){
                    thegriddy.setPiece(selectedRow, pieces.passantcol, -1);
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }
                else{
                    thegriddy.setGrid(selectedRow, selectedCol, movedRow, movedCol);
                }

                player = 0;
            }else{
                selectedRow = -1;
                selectedCol = -1;
                movedRow = -1;
                movedCol = -1;
                return;
            }
            bcheck = pieces.bCheck(thegriddy.getCurrentGrid());
            wcheck = pieces.wCheck(thegriddy.getCurrentGrid());

            if (passantrack != pieces.passantcol) {
                passantcount = 0;
            }
            passantrack = pieces.passantcol;
            passantcount++;
            if (passantcount == 2) {
                pieces.passantcol = -1;
                passantcount = 0;
            }


            if (thegriddy.whitewin()) wwin = true;
            if (thegriddy.blackwin()) bwin = true;
            selectedRow = -1;
            selectedCol = -1;
            movedRow = -1;
            movedCol = -1;
        }else{
            selected = null;
            held = false;
        }


    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void run() {
        int waitToPaint = 1000/60;
        long lastPaint = System.nanoTime();

        while(true) {

            int framesNeeded = ((int) (System.nanoTime() - lastPaint)/1000000)/waitToPaint;

            if(framesNeeded >= 1) {
                repaint();
                lastPaint = System.nanoTime();
            }

            try {
                Thread.sleep(5);
            } catch(Exception e) {
                System.out.println("Error sleeping in run method: " + e.getMessage());
            }
        }
    }
}