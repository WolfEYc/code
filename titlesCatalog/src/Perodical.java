
public class Perodical extends Title {

    private int issue;
    private int month;

    public Perodical(){
        super();
        issue=0;
        month=0;
    }
    public Perodical(String callNumber, String title, String publisher, int year, int copies, int issue, int month){
        super(callNumber,title,publisher,year,copies);
        this.issue=issue;
        this.month=month;
    }
    public int getIssue(){ 
        return issue; 
    }
    public int getMonth(){
        return month; 
    }
    public String toString(){
        return super.toString() + issue + "\n" + month + "\n";
    }

    public void setIssue(int issue){
        this.issue=issue;
    }
    public void setMonth(int month){
        this.month = month;
    }
    
}