import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Point2D;

public class Panel extends JPanel implements Runnable {
    private Player player;
    private boolean[] keys;
    private TAdapter tAdapter;

    public class TAdapter extends KeyAdapter{
        @Override
        public void keyPressed(KeyEvent keyEvent) {
            int key = keyEvent.getKeyCode();

            if (key == KeyEvent.VK_UP) {
                keys[0] = true;
            }

            if (key == KeyEvent.VK_LEFT) {
                keys[1] = true;
            }

            if (key == KeyEvent.VK_DOWN) {
                keys[2] = true;
            }

            if (key == KeyEvent.VK_RIGHT) {
                keys[3] = true;
            }
        }

        @Override
        public void keyReleased(KeyEvent keyEvent) {
            int key = keyEvent.getKeyCode();

            if (key == KeyEvent.VK_UP) {
                keys[0] = false;
            }

            if (key == KeyEvent.VK_LEFT) {
                keys[1] = false;
            }

            if (key == KeyEvent.VK_DOWN) {
                keys[2] = false;
            }

            if (key == KeyEvent.VK_RIGHT) {
                keys[3] = false;
            }
        }
    }



    public Panel( int width, int height ) {
        super();
        player = new Player(new Point2D.Double(width/2,height/2), "medicine.png");
        keys = new boolean[4];
        setSize( width, height );
        setBackground(Color.black);
        tAdapter = new TAdapter();
        addKeyListener(tAdapter);
        setFocusable(true);
        new Thread(this).start();
    }

    public void paint(Graphics g) {
        player.update(keys);
        g.setColor(Color.BLACK);
        g.fillRect(0,0, getWidth(), getHeight());

        g.drawImage(player.getImage(), (int)player.getX(), (int)player.getY(), this);

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

            try { Thread.sleep(2); }
            catch(Exception e) { System.out.println("Error sleeping in run method: " + e.getMessage()); }
        }
    }


}
