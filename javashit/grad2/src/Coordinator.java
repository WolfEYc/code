import java.util.concurrent.atomic.AtomicInteger;

public class Coordinator extends Thread{


    public Coordinator(){ start(); }


    public void run(){

        //waits for chairman to finish speech
        try {
            Main.chairmanDoneSpeech.acquire();
            Main.chairmanDoneSpeech.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        msg("Students get ready to receive your diplomas");


        for(Student s : Main.students) {
            try {
                s.aquireDiploma();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        try {
            Main.allLeft.acquire();
            Main.allLeft.release();
            Main.leaveTicket.acquire();
            msg("Coordinator has left");
            Main.leaveTicket.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    private void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - Main.time) + "] "   + m);
    }

}
