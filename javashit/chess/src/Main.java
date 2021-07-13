import org.w3c.dom.css.Rect;

import javax.swing.*;
import java.awt.*;
import java.util.Scanner;
/**
 * Write a description of class Runner here.
 *
 * @author (Isaac Wolf)
 * @version (1.0)
 */
public class Main
{

    public static void main(String[] args) {

        ImageIcon img = new ImageIcon("src/resources/Chess_qlt60.png");
        JFrame frame = new JFrame("Chess");
        frame.setIconImage(img.getImage());

        frame.setSize(640, 640);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();

        Insets frameInsets = frame.getInsets();
        int frameWidth = 640 + (frameInsets.left + frameInsets.right);
        int frameHeight = 640 + (frameInsets.top + frameInsets.bottom);
        frame.setPreferredSize(new Dimension(frameWidth, frameHeight));
        frame.setLayout(null);

        Panel myPanel = new Panel(640, 640);
        frame.add(myPanel);

        frame.pack();
        frame.setVisible(true);
        //beans

        //0=white 1=black 2=whitewins 3=blackwins
    }    
}

