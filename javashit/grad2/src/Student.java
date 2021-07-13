import java.util.ArrayList;
import java.util.Random;

public class Student extends Thread{
    public int num;
    public int seatNum;
    private Family[] family;
    public Random r = new Random();

    public Student(int num){
        this.num = num;
        setName("Student"+num);
        generateFamily();
        start();
    }

    public void run(){
        // arrives and tries to find a seat, will be placed in order
        try {
            Thread.sleep(2500 + r.nextInt(2500));
            msg( " is arriving.");
            aquireSeat();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //to know when we are going to get drinks
        try {
            Main.allDiplomasOut.acquire();
            Main.allDiplomasOut.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //leave after some time
        try {
            Thread.sleep(2500 + r.nextInt(2500));
            leave();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    public void aquireSeat() throws InterruptedException {
        Main.seatTicket.acquire();
        seatNum = ++Main.seatsOccupied;
        msg( " is seated at seat number "+ seatNum + " and has brought "+ family.length + " family members ");
        Main.seatTicket.release();
        if(Main.seatsOccupied == Main.numStudents){
            Main.allStudentSeated.release();
        }
    }

    public void aquireDiploma() throws InterruptedException{
        Main.diplomaOut.acquire();
        msg( " is Receiving diploma");
        Thread.sleep(1000);
        Main.diplomaOut.release();
        if(Main.numStudents == ++Main.studentsWithDiplomas)
            Main.allDiplomasOut.release();
    }

    public void generateFamily()
    {
        int numFam = r.nextInt(3);
        Main.total+=numFam;
        Main.numFamily+=numFam;
        family = new Family[numFam];
        for (int i = 0; i < numFam; i++){
            family[i] = new Family("family"+(i+1), getName());
        }
    }

    public void leave() throws InterruptedException {
        Main.leaveTicket.acquire();
        for(Family t : family)
            t.leave();
        msg(" has left");
        Main.totalLeft += 1 + family.length;
        Main.leaveTicket.release();
        if(Main.totalLeft == Main.total){
            Main.allLeft.release();
        }
    }

    public void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - Main.time) + "] "+ getName()  + m);
    }

}
