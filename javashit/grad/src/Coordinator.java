import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

@SuppressWarnings("unused")
public class Coordinator extends Thread
{
	public static boolean chairmanSignal = false;
    public volatile static boolean coordinatorSignalForRow1 = false;
    public static long time = System.currentTimeMillis();
    public volatile static AtomicInteger signalseat;
   

  
    public Coordinator()
    {
        chairmanSignal = false;
        signalseat = new AtomicInteger();
        start();
    }

     public void run(){

        try {
            Thread.sleep(12000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        
     	while(!Chairman.chairmanSignalToCoordinator){ //coordinator busy waits until gets signal from chairman

     	}

            msg("Students get ready for the diploma");
            Coordinator.coordinatorSignalForRow1 = true;

        for(int i = 0; i < Student.numOfStudentsSeated; i++){
            signalseat.getAndIncrement();
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

         while(Student.studentsReleased.get() != Graduation.numStudent){

         }

         msg(" Coordinator has left");

     }
    private void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - time) + "] "   + m);
        
    }
}