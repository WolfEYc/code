
public class Chairman extends Thread
{	
    public static long time = System.currentTimeMillis();
    public static boolean studentSignal;
    public volatile static boolean chairmanSignalToCoordinator;
    public volatile static boolean ceremonyOver = false;
	
    public Chairman()
    { 
       start();
    }

     public void run(){
        try {
            Thread.sleep(6000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
//        msg("Chairman thread: occupiedSeats: " +Student.occupiedSeats+ " total: "+Student.total );

        while(Graduation.occupiedSeats.get()!=44&&Graduation.occupiedSeats.get()!=Student.total){}

     	msg("Chairman giving speech");
     	try {
			Chairman.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
     	msg("Chairman ready to give diplomas");
     	Chairman.chairmanSignalToCoordinator = true;

         while(Graduation.totalDiplomaDistributed.get() < Graduation.numStudent){

         }

         try {
             Thread.sleep(1000);
         } catch (InterruptedException e) {
             e.printStackTrace();
         }

         msg("Chairman inviting people for refreshments");

         try {
             Thread.sleep(10000);
         } catch (InterruptedException e) {
             e.printStackTrace();
         }

         ceremonyOver = true;

         while(Student.studentsReleased.get() != Graduation.numStudent){

         }

         msg(" Chairman has left");

     	
     }

	private void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - time) + "] "   + m);
		
	}
}
