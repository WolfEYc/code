import java.util.Random;
import java.util.concurrent.Semaphore;

public class Main {
    public static long time = System.currentTimeMillis();

    public static Semaphore seatTicket = new Semaphore(1,true),
    allStudentSeated = new Semaphore(0),
    allFamilySeated = new Semaphore(0),
    chairmanDoneSpeech = new Semaphore(0),
    diplomaOut = new Semaphore(1, true),
    allDiplomasOut = new Semaphore(0),
    leaveTicket = new Semaphore(1),
    allLeft = new Semaphore(0);


    public static Student[] students;
    public static Chairman chairman;
    public static Coordinator coordinator;


    public static int studentsWithDiplomas = 0, total = 13, totalLeft = 0,
    numFamily = 0, seatsOccupied = 0, numStudents = 13;

    public static void main(String[] args){
        students = new Student[numStudents];
        for(int i = 0; i < numStudents; i++)
            students[i] = new Student(i+1);

        chairman = new Chairman();
        coordinator = new Coordinator();
    }
}
