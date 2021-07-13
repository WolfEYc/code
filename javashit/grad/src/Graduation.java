
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

/*
Use a return statement within each Threads run() method to terminate the Thread instance.
 */

public class Graduation
{
    public static long time = System.currentTimeMillis();
    public volatile static Thread[] students;
    public volatile static Thread chairman;
    public volatile static Thread coordinator;
    public volatile static AtomicInteger totalDiplomaDistributed = new AtomicInteger();
    public volatile static AtomicInteger occupiedSeats = new AtomicInteger();
    public static Semaphore studentsArriving = new Semaphore(1);
    public static Semaphore studentsdoneArriving = new Semaphore(0);


    public static int numStudent ;
    public static int rowCapacity;
    public static int numRows ;

    // FCFS should be implemented in a queue or other data structure.

    public static void main(String[] args) throws InterruptedException
    {
    	  numStudent = 13;
    	  rowCapacity = 4;
    	  numRows = 11;

    	  
    	  students = new Thread[numStudent];
          for (int i = 0; i <numStudent; i++) {
              students[i] = new Student(i);
          }
          chairman = new Chairman();

          coordinator = new Coordinator();

    }        
    public int getNumRows()
    {
        return numRows;
    }

    public void setNumRows(int numRows)
    {
        this.numRows = numRows;
    }

    public int getRowCapacity()
    {
        return rowCapacity;
    }

    public void setRowCapacity(int rowCapacity)
    {
        this.rowCapacity = rowCapacity;
    }

    public int getNumStudent()
    {
        return numStudent;
    }

    public void setNumStudent(int numStudent)
    {
        this.numStudent = numStudent;
    }
}