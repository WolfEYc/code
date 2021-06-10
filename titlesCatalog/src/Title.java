
public class Title {

    private String callNumber;
    private String title;
    private String publisher;
    private int year;
    private int copies;

    public Title(){
        callNumber = "none";
        title ="none";
        publisher="none";
        year=0;
        copies=0;
    }
    public Title(String callNumber, String title, String publisher, int year, int copies){
        this.callNumber=callNumber;
        this.title=title;
        this.publisher=publisher;
        this.year=year;
        this.copies=copies;
    }
    public String getCallNumber(){
        return callNumber;
    }
    public String getTitle(){
        return title;
    }
    public String getPublisher(){
        return publisher;
    } 
    public int getYear(){
        return year;
    }
    public int getCopies(){
        return copies;
    }
    public String toString(){
        return callNumber + "\n"+ title + "\n"+ publisher + "\n" + year + "\n" + copies + "\n";
    }

    public void setCallNumber(){
        this.callNumber=callNumber;
    }
    public void setTitle(String title){
        this.title=title;
    }
    public void setPublisher(String publisher){
        this.publisher=publisher;
    }
    public void setYear(int year){
        this.year=year;
    }
    public void setCopies(int copies){
        this.copies=copies;
    }
}