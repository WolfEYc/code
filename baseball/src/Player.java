
/**
 * Write a description of class Player here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Player
{
    
private String PlayerID;
private String FirstName;
private String LastName;
private String BirthDate;
private String BirthLocation;
private int Height;
private int Weight;
//contructor
public Player(String PlayerID,String FirstName,String LastName,String BirthDate,
String BirthLocation,int Height,int Weight)
{
    this.PlayerID = PlayerID;
    this.FirstName = FirstName;
    this.LastName = LastName;
    this.BirthDate = BirthDate;
    this.BirthLocation = BirthLocation;
    this.Height = Height;
    this.Weight = Weight;
}

public Player(Player p){
    this.PlayerID = p.getPlayerID();
    this.FirstName = p.getFirstName();
    this.LastName = p.getLastName();
    this.BirthDate = p.getBirthDate();
    this.BirthLocation = p.getBirthLocation();
    this.Height = p.getHeight();
    this.Weight = p.getWeight();
}

//getters
public String getPlayerID(){
    return PlayerID;
}
public String getFirstName(){
    return FirstName;
}
public String getLastName(){
    return LastName;
}
public String getBirthDate(){
    return BirthDate;
}
public String getBirthLocation(){
    return BirthLocation;
}
public int getHeight(){
    return Height;
}
public int getWeight(){
    return Weight;
}

//setters
public void setPlayerID(String PlayerID){
    this.PlayerID = PlayerID;
}
public void setFirstName(String FirstName){
    this.FirstName = FirstName;
}
public void setBirthDate(String BirthDate){
    this.BirthDate = BirthDate;
}
public void setBirthLocation(String BirthLocation){
    this.BirthLocation = BirthLocation;
}
public void setHeight(int Height){
    this.Height = Height;
}
public void setWeight(int Weight){
    this.Weight = Weight;
}
public String toString(){
    return PlayerID + " " + FirstName + " " + BirthDate + " " + BirthLocation +
    " " + BirthLocation + " " + Height + " " + Weight;
}
}

