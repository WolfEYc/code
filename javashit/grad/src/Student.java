import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;


public class Student extends Thread
{
    public int num;
    private int seatNumber;
    private int rowNumber;
    public int familyMembers;
    public String[] familyNames;
    public static ArrayList<Thread> familyThreads;
    public volatile static AtomicInteger totalFamilyMembers = new AtomicInteger();
    public static int numOfStudentsSeated = 0;
    public static boolean present=false;
    public static boolean seated;
    private boolean gotDiploma;
    public static int total;
    public volatile static AtomicInteger membersReleased = new AtomicInteger();
    public volatile static AtomicInteger studentsReleased = new AtomicInteger();
    public static long time = System.currentTimeMillis();
    public static Random r = new Random();


    public Student(int num)
    {
        setName("Student"+ num);
        familyMembers = numFamilyMembers();
        familyNames = getFamilyNames(familyMembers);
        familyThreads = new ArrayList<Thread>();
        present=true;
        seated = false;
        gotDiploma=false;
        start();
    }

    public void run()
    {
        try {
            Thread.sleep(5000);
            Graduation.studentsArriving.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        msg( " is arriving.");

        if(present) {
            Graduation.occupiedSeats.getAndIncrement();
            numOfStudentsSeated++;
            seatNumber = Graduation.occupiedSeats.get();
            int rowFinder= seatNumber%4;
            if(rowFinder==0) {rowNumber = seatNumber/4;}
            else rowNumber = (seatNumber/4)+1;
            seated=true;
            msg( " is seated at seat number "+seatNumber + " and row number "+rowNumber + " and has brought "+ familyMembers + " family members ");
            Graduation.studentsArriving.release();
        }

        if(numOfStudentsSeated == Graduation.numStudent) {
            Graduation.studentsdoneArriving.release();
        }

        try {
            Graduation.studentsdoneArriving.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        total=totalFamilyMembers.get()+13;
        if(Graduation.occupiedSeats.get()<44 && Graduation.occupiedSeats.get()<total){
            for(int i = 0; i< familyMembers; i++){
                if(Student.familyThreads!=null)
                    msg(familyNames[i] + " is seated at seat number "+ Graduation.occupiedSeats.incrementAndGet());
            }
        }
        msg(" is now fillingMain.familySeated++; the form.");
        while( Graduation.occupiedSeats.get()!=total) {}

        try {
            Thread.sleep(8000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        while(Coordinator.signalseat.get() < seatNumber){

        }

        if(!gotDiploma){
            gotDiploma=true;
            msg(" is receiving the diploma now");
            Graduation.totalDiplomaDistributed.getAndIncrement();
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            seated = true;
        }

        while(!Chairman.ceremonyOver){

        }

        for(int i = 0; i < familyMembers; i++){
            msg(familyNames[i] + "has left");
            membersReleased.getAndIncrement();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        while(membersReleased.get() != totalFamilyMembers.get()){}


        try {
            Thread.sleep(r.nextInt(1000) + 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }



        msg(" has left");
        studentsReleased.getAndIncrement();
    }

    public static int numFamilyMembers()
    {

        int numFam = r.nextInt(3);
        return numFam;
    }

    public String[] getFamilyNames(int numFam)
    {
        String[] fam = new String[numFam];
        for (int i = 0; i < numFam; i++)
        {
            String name = "family" + i;
            fam[i] = name;
            familyThreads.add(this);
            Student.totalFamilyMembers.getAndIncrement();
        }
        return fam;
    }


    public void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - time) + "] "+ getName()  + m);
    }

    public void setFamilyThreads(ArrayList<Thread> familyThreads)
    {
        Student.familyThreads = familyThreads;
    }

    public ArrayList<Thread> getFamilyThreads()
    {
        return familyThreads;
    }
}