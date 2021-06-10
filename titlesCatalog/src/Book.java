
public class Book extends Title {

    private String author;
    private String ISBN;

    public Book(){
        super();
        author="none";
        ISBN="none";
    }
    public Book(String callNumber, String title, String publisher, int year, int copies, String author, String ISBN ){
        super(callNumber,title,publisher,year,copies);
        this.author=author;
        this.ISBN=ISBN;
    }
    public String getAuthor(){
        return author;
    }
    public String getISBN(){
        return ISBN;
    }
    public String toString(){
        return super.toString() + author + "\n" + ISBN + "\n";
    }

    public void setAuthors(String author){
        this.author=author;
    }
    public void setISBN(String ISBN){
        this.ISBN=ISBN;
    }
}