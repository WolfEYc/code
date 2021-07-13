public class Family extends Thread{
    public int seatNum;
    private final String studentName;

    public Family(String name, String studentName){
        setName(name);
        this.studentName = studentName;
        start();
    }

    public void run(){
        try {
            aquireSeat();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void aquireSeat() throws InterruptedException {
        Main.allStudentSeated.acquire();
        Main.allStudentSeated.release();
        Main.seatTicket.acquire();
        seatNum = ++Main.seatsOccupied;
        msg( " is seated at seat number " + seatNum);
        Thread.sleep(100);
        Main.seatTicket.release();
        //last family has been seated
        if(Main.seatsOccupied == Main.total){
            Main.allFamilySeated.release();
        }
    }

    public void leave() {
        msg(" has left");
    }

    public void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - Main.time) + "] "+ studentName + getName()  + m);
    }
}
