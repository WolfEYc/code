import java.io.FileNotFoundException;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

public class Catalog {
    private Title[] titles;
    private int count;

    public Catalog(){
        count = 0;
        titles = new Title[1000];
    }
    public void loadFromFile(String filename) throws FileNotFoundException {
        Scanner in = null;
        String callNumber, title, publisher, author, ISBN;
        int year, copies, issue, month;

        try{
            in = new Scanner(new BufferedReader(new FileReader(filename)));
            String line;
            while(in.hasNextLine()){
                line = in.nextLine();
                callNumber = line;
                title = in.nextLine();
                publisher = in.nextLine();
                year = Integer.parseInt(in.nextLine());
                copies = Integer.parseInt(in.nextLine());

                if(line.charAt(0) == 'P'){
                    issue = Integer.parseInt(in.nextLine());
                    month = Integer.parseInt(in.nextLine());
                    titles[count] = new Perodical(callNumber,title,publisher,year,copies,issue,month);
                }else{
                    author = in.nextLine();
                    ISBN = in.nextLine();
                    titles[count] = new Book(callNumber,title,publisher,year,copies,author,ISBN);
                }
                count++;

            }


        }finally {
            if(in != null)
                in.close();
        }

    }

    public void saveToFile(String filename) throws IOException {
        String out = "";
        Path filePath = null;
        try {
            filePath = Path.of(filename);
        } finally {
            for(int i = 0; i < count; i++){
                out += titles[i].toString();
            }
            assert filePath != null;
            Files.writeString(filePath,out);
        }

    }

    public void addItem(Title title){
        titles[count++] = title;
    }
    public void removeItem(String callNumber){
        boolean shifting = false;
        for(int i = 0; i < count; i++){
            if(shifting || titles[i].getCallNumber().equals(callNumber)){
                shifting = true;
                titles[i] = titles[i+1];
            }
        }
        if(shifting){
            count--;
            titles[count] = null;
        }
    }
    public Title[] searchTitle(String title){
        int size = 0, it = 0;
        for(int i = 0; i < count; i++){
            if(titles[i].getTitle().equals(title))
                size++;
        }
        Title[] searchlist = new Title[size];
        for(int i = 0; i < count; i++){
            if(titles[i].getTitle().equals(title)) {
                searchlist[it++] = titles[i];
            }
        }
        return searchlist;
    }

    public Title searchCallNumber(String callNumber){
        for(int i = 0; i < count; i++){
            if(titles[i].getCallNumber().equals(callNumber))
                return titles[i];
        }
        return null;
    }

    public Title[] searchYear(int year){
        int size = 0, it = 0;
        for(int i = 0; i < count; i++){
            if(titles[i].getYear() == year)
                size++;
        }
        Title[] searchlist = new Title[size];
        for(int i = 0; i < count; i++){
            if(titles[i].getYear() == year) {
                searchlist[it++] = titles[i];
            }
        }
        return searchlist;
    }

    public void viewAll(){
        for(int i = 0; i < count; i++){
            System.out.println("\nCall Number: " +titles[i].getCallNumber() + "\nTitle: "+ titles[i].getTitle() + "\nPublisher: "+titles[i].getPublisher() + "\nYear: "+titles[i].getYear() +"\n");
        }
    }

}