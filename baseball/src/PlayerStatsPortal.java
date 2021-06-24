import java.io.FileNotFoundException;
import java.util.Scanner;

public class PlayerStatsPortal {
    public static void main(String[] args) throws FileNotFoundException {
        Players players = new Players("Pitching.csv", "Batting.csv", "Master.csv");
        Scanner keyboard = new Scanner(System.in);

        int op, n;

        while(true){

            System.out.println("\n1. Top Batters sorted by RBI");
            System.out.println("2. Top Pitchers sorted by W/L");
            System.out.println("3. Find player by ID");
            System.out.println("4. Top Batters sorted by Homeruns");
            System.out.println("5. Top Pitchers sorted by ERA");
            System.out.println("6. Quit");

            do {
                op = keyboard.nextInt();
            } while (op < 0 || op > 6);

            if(op == 6){
                System.out.println("Goodbye!");
                break;
            }

            switch(op){
                case 1:
                    System.out.println("Enter # of batters: ");
                    for(Batter b : players.getTopBattersSorted(keyboard.nextInt()))
                        System.out.println(b);
                    break;
                case 2:
                    System.out.println("Enter # of Pitchers: ");
                    for(Pitcher p : players.getTopPitchersSorted(keyboard.nextInt()))
                        System.out.println(p);
                    break;
                case 3:
                    System.out.println("Enter PlayerID: ");
                    System.out.println(players.getPlayer(keyboard.next()));
                    break;
                case 4:
                    System.out.println("Enter # of batters: ");
                    for(Batter b : players.getTopHomerunHittersSorted(keyboard.nextInt()))
                        System.out.println(b);
                    break;
                case 5:
                    System.out.println("Enter # of Pitchers: ");
                    for(Pitcher p : players.getLowestERASorted(keyboard.nextInt()))
                        System.out.println(p);
                    break;
                default:
                    break;
            }
        }
    }
}
