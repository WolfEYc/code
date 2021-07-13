import java.awt.Image;
import javax.swing.ImageIcon;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.Arrays;

public class Player {
    private Point2D pos;
    private Point2D vel;
    private Point2D acc;
    private double accRate = 10;
    private double Cfric = 0.5;
    private Image image;

    private Point2D sub(Point2D p1, Point2D p2){
        double x = p1.getX() - p2.getX();
        double y = p1.getY() - p2.getY();
        return new Point2D.Double(x,y);
    }

    private Point2D mult(Point2D pt, double by){
        return new Point2D.Double(pt.getX()*by, pt.getY()*by);
    }

    private Point2D add(Point2D p1, Point2D p2){
        double x = p1.getX() + p2.getX();
        double y = p1.getY() + p2.getY();
        return new Point2D.Double(x,y);
    }

    private Point2D addX(Point2D pt, double by){
        return new Point2D.Double(pt.getX()+by, pt.getY());
    }

    private Point2D addY(Point2D pt, double by){
        return new Point2D.Double(pt.getX(), pt.getY()+by);
    }

    public Player(Point2D initPos, String image){
        ImageIcon ii = new ImageIcon(image);
        this.image = ii.getImage();
        pos = initPos;
        vel = new Point2D.Double(0,0);
        acc = new Point2D.Double(0,0);
    }

    public void friction(){
        vel = mult(vel, Cfric);
    }

    public Rectangle2D getBounds(){
        return new Rectangle2D.Double(pos.getX(), pos.getY(), image.getWidth(null), image.getHeight(null));
    }

    public Point2D getPos(){
        return pos;
    }

    public double getX(){
        return pos.getX();
    }

    public double getY(){
        return pos.getY();
    }

    // W A S D
    public void update(boolean[] buttons){


        acc = new Point2D.Double(0,0);
        if(buttons[0]){
            acc = addY(acc, -accRate);
        }
        if(buttons[1]){
            acc = addX(acc, -accRate);
        }
        if(buttons[2]){
            acc = addY(acc, accRate);
        }
        if(buttons[3]){
            acc = addX(acc, accRate);
        }
        vel = add(vel, acc);
        friction();
        pos = add(pos, vel);
    }

    public Image getImage() {
        return image;
    }
}
