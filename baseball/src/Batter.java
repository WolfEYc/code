
/**
 * Write a description of class Batter here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Batter extends Player implements Comparable
{
private int YearID;
private String TeamID;
private int HomeRuns;
private int RBI;
//constructor
public Batter(Player p, int YearID, String TeamID, int HomeRuns, int RBI){
    super(p);
    this.YearID = YearID;
    this.TeamID = TeamID;
    this.HomeRuns = HomeRuns;
    this.RBI = RBI;
}
//getters
public int getYearID(){
    return YearID;
}
public String getTeamID(){
    return TeamID;
}
public int getHomeRuns(){
    return HomeRuns;
}
public int getRBI(){
    return RBI;
}

//Setters
public void setYearID(int YearID){
    this.YearID = YearID;
}
public void setTeamID(String TeamID){
    this.TeamID = TeamID;
}
public void setHomeRuns(int HomeRuns){
    this.HomeRuns = HomeRuns;
}
public void setRBI(int RBI){
    this.RBI = RBI;
}
public String toString(){
    return super.toString() +" "+ YearID + " " + TeamID + " " + HomeRuns + " " + RBI;
}

    @Override
    public int compareTo(Object o) {
        Batter b = (Batter) o;
        return this.RBI > b.RBI ? 1 : this.RBI < b.RBI ? -1 : this.HomeRuns > b.HomeRuns ? 1 : this.HomeRuns < b.HomeRuns ? -1 : 0;
    }
}
