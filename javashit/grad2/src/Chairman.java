public class Chairman extends Thread{

    public Chairman(){
        start();
        setName("Chairman");
    }

    public void run(){
        //chainman giving speech
        try {
            Main.allFamilySeated.acquire();
            Main.allStudentSeated.release();
            msg("giving speech");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //Chairman finished with speech
        try {
            Thread.sleep(10000);
            Main.chairmanDoneSpeech.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //will release students to get drinks after all diplomas are out
        try {
            Main.allDiplomasOut.acquire();
            msg("inviting people for refreshments");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //allows chairman to leave
        try {
            Main.allLeft.acquire();
            Main.allLeft.release();
            Main.leaveTicket.acquire();
            msg("has left");
            Main.leaveTicket.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void msg(String m) {
        System.out.println("[" + (System.currentTimeMillis() - Main.time) + "] " + getName() + " "+ m);
    }
}
