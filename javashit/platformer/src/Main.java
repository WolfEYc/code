import javax.swing.*;

public class Main {

    public static int height = 720;
    public static int width = 1280;

    public static void main(String[] args) {

        ImageIcon img = new ImageIcon("medicine.png");
        JFrame frame = new JFrame("Platformer");
        frame.setIconImage(img.getImage());



        frame.setSize(width, height);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();

        java.awt.Insets frameInsets = frame.getInsets();
        int frameWidth = width + (frameInsets.left + frameInsets.right);
        int frameHeight = height + (frameInsets.top + frameInsets.bottom);
        frame.setPreferredSize(new java.awt.Dimension(frameWidth, frameHeight));
        frame.setLayout(null);

        Panel myPanel = new Panel(width, height);
        frame.add(myPanel);

        frame.pack();
        frame.setVisible(true);
        //beans

        //0=white 1=black 2=whitewins 3=blackwins
    }


}
