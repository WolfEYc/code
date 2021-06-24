
public class Pitcher extends Player implements Comparable
{
private int YearID;
private String TeamID;
private int Wins;
private int Losses;
private double ERA;
//constructor
public Pitcher(Player p, int YearID, String TeamID, int Wins, int Losses, double ERA){
    super(p);
    this.YearID = YearID;
    this.TeamID = TeamID;
    this.Wins = Wins;
    this.Losses = Losses;
    this.ERA = ERA;
}

//getters
public int getYearID(){
    return YearID;
}
public String getTeamID(){
    return TeamID;
}
public int getWins(){
    return Wins;
}
public int getLosses(){
    return Losses;
}
public double getERA(){
    return ERA;
}

//setters
public void setYearID(int YearID){
    this.YearID = YearID;
}
public void setTeamID(String TeamID){
    this.TeamID = TeamID;
}
public void setWins(int Wins){
    this.Wins = Wins;
}
public void setLosses(int Losses){
    this.Losses = Losses;
}
public void setERA(double ERA){
    this.ERA = ERA; 
}
public String toString(){
    return super.toString() +" "+ YearID + " " + TeamID + " " + Wins + " " + Losses + " " + ERA;
}

    @Override
    public int compareTo(Object o) {
        Pitcher p = (Pitcher) o;
        int tdiff = this.Wins - this.Losses;
        int pdiff = p.Wins - p.Losses;
        if(tdiff > pdiff)
            return 1;
        if(pdiff > tdiff)
            return -1;
        if(this.ERA < p.ERA)
            return 1;
        if(this.ERA > p.ERA)
            return -1;
        return 0;
    }
}
