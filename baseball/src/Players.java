
/**
 * Write a description of class Players here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
public class Players
{
 public ArrayList<Player> playerList = new ArrayList<Player>();


 public Players(String PitData, String BatData, String MasterData) throws FileNotFoundException
 {
     String line = " ";
     
     File pitFile = new File(PitData);
     File batFile = new File(BatData);
     File masterFile = new File(MasterData);
     
     Scanner pitScanner = new Scanner(pitFile);
     Scanner batScanner = new Scanner(batFile);
     Scanner masterScanner = new Scanner(masterFile);
     
     ArrayList<Player> masterList = new ArrayList<Player>();

     if(masterScanner.hasNextLine())
         masterScanner.nextLine();

     while(masterScanner.hasNextLine()) {
         line = masterScanner.nextLine();
         String [] data = line.split(",");

         if(data.length != 24)
             continue;

         String ID = data[0], firstName = data[13], lastName = data[14], birthDate, birthLocation;


         int weight = -1, height = -1;

         try {
             weight = Integer.parseInt(data[16]);
         } catch (final NumberFormatException ignored) {

         }

         try {
             height = Integer.parseInt(data[17]);
         } catch (final NumberFormatException ignored) {

         }



         birthDate = data[2] + "/" + data[3] + "/" + data[1];
         birthLocation = data[6] + " " + data[5] + ", " + data[4];

         masterList.add(new Player(ID, firstName, lastName, birthDate, birthLocation, height, weight));
     }

     if(pitScanner.hasNextLine())
         pitScanner.nextLine();

     while(pitScanner.hasNextLine()){
         line = pitScanner.nextLine();
         String [] data = line.split(",");

         if(data.length != 30)
             continue;

         String playerID; int YearID = -1; String TeamID; int Wins = 0; int Losses = 0; double ERA = 0.0;
         playerID = data[0];
         try {
             YearID = Integer.parseInt(data[1]);
         } catch (final NumberFormatException ignored) {}
         TeamID = data[3];
         try {
             Wins = Integer.parseInt(data[5]);
         } catch (final NumberFormatException ignored) {}
         try {
             Losses = Integer.parseInt(data[6]);
         } catch (final NumberFormatException ignored) {}
         try {
             ERA = Double.parseDouble(data[19]);
         } catch (final NumberFormatException ignored) {}


         for(Player p : masterList){
             if(p.getPlayerID().equals(playerID)){
                 playerList.add(new Pitcher(p, YearID, TeamID, Wins, Losses, ERA));
                 break;
             }
         }

     }

     if(batScanner.hasNextLine())
         batScanner.nextLine();

     while(batScanner.hasNextLine()){
         line = batScanner.nextLine();
         String [] data = line.split(",");

         if(data.length != 22)
             continue;

         String playerID = data[0]; int YearID = -1; String TeamID = data[3]; int HomeRuns = -1; int RBI = -1;

         try {
             YearID = Integer.parseInt(data[1]);
         } catch (final NumberFormatException ignored) {}

         try {
             HomeRuns = Integer.parseInt(data[5]);
         } catch (final NumberFormatException ignored) {}
         try {
             RBI = Integer.parseInt(data[6]);
         } catch (final NumberFormatException ignored) {}

         for(Player p : masterList){
             if(p.getPlayerID().equals(playerID)){
                 playerList.add(new Batter(p, YearID, TeamID, HomeRuns, RBI));
                 break;
             }
         }
     }

 }

 public ArrayList<Batter> getTopBattersSorted(int n){
     ArrayList<Batter> batterList = new ArrayList<Batter>();

     for(int i = 0; i < n; i++) {
         Batter max = null;
         for (Player p : playerList) {
             if (p instanceof Batter) {
                 if (batterList.contains((Batter) p)) {
                     continue;
                 }
                 if (max == null) {
                     max = (Batter) p;
                 } else if (((Batter) p).compareTo(max) > 0) {
                     max = (Batter) p;
                 }
             }
         }
         batterList.add(max);
     }
     return batterList;
 }
 public ArrayList<Pitcher> getTopPitchersSorted(int n){
     ArrayList<Pitcher> pitchersList = new ArrayList<Pitcher>();
     for(int i = 0; i < n; i++) {
         Pitcher max = null;
         for (Player p : playerList) {
             if (p instanceof Pitcher) {
                 if (pitchersList.contains((Pitcher) p)) {
                     continue;
                 }
                 if (max == null) {
                     max = (Pitcher) p;
                 } else if (((Pitcher) p).compareTo(max) > 0) {
                     max = (Pitcher) p;
                 }
             }
         }
         pitchersList.add(max);
     }
     return pitchersList;
 }
 public Player getPlayer(String PlayerID){
     for(Player p : playerList){
         if(p.getPlayerID().equals(PlayerID)){
             return p;
         }
     }
     return null;
 }
 public ArrayList<Batter> getTopHomerunHittersSorted(int n){
     ArrayList<Batter> batterList = new ArrayList<Batter>();

     for(int i = 0; i < n; i++) {
         Batter max = null;
         for (Player p : playerList) {
             if (p instanceof Batter) {
                 if (batterList.contains((Batter) p)) {
                     continue;
                 }
                 if (max == null) {
                     max = (Batter) p;
                 } else if (((Batter) p).getHomeRuns() > max.getHomeRuns()) {
                     max = (Batter) p;
                 }
             }
         }
         batterList.add(max);
     }
     return batterList;
 }
 public ArrayList<Pitcher> getLowestERASorted(int n){
     ArrayList<Pitcher> pitchersList = new ArrayList<Pitcher>();
     for(int i = 0; i < n; i++) {
         Pitcher max = null;
         for (Player p : playerList) {
             if (p instanceof Pitcher) {
                 if (pitchersList.contains((Pitcher) p)) {
                     continue;
                 }
                 if (max == null) {
                     max = (Pitcher) p;
                 } else if (((Pitcher) p).getERA() < max.getERA()) {
                     max = (Pitcher) p;
                 }
             }
         }
         pitchersList.add(max);
     }
     return pitchersList;
 }
}
