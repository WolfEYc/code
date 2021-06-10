
import java.util.*;
import java.io.*;

public class LibraryManager {

    public static void checkCallNumber(String inputNumber) throws InvalidCallNumber{
        try {
            if(inputNumber.length() != 13 || (inputNumber.charAt(0) != 'B' && inputNumber.charAt(0) != 'P'))
                throw new InvalidCallNumber();

            for(int i = 1; i < 13; i++) {
                if (i % 4 == 1 && inputNumber.charAt(i) != '-')
                    throw new InvalidCallNumber();
                if (i % 4 != 1 && !Character.isDigit(inputNumber.charAt(i)))
                    throw new InvalidCallNumber();
            }
        } catch(InvalidCallNumber e){
            e.printStackTrace();
        }
    }

    public static void checkYear(int inputYear) throws InvalidDate{
        if(inputYear > 2021 || inputYear < 1900)
            throw new InvalidDate();
    }

    public static void main(String[] args) throws IOException {
        Catalog myLibrary = new Catalog();
        myLibrary.loadFromFile("titles.txt");
        Scanner cin = new Scanner(System.in);

        int op = 0;

        do{
            System.out.println("Choose an option");
            System.out.println("1. Find by Call #");
            System.out.println("2. Find by Title");
            System.out.println("3. Find by Year");
            System.out.println("4. Add a new title");
            System.out.println("5. Remove by Call #");
            System.out.println("6. View all Titles");
            System.out.println("7. Exit");

            op = cin.nextInt();

            System.out.println();


            Title[] results;

            String callNumber, title, publisher, author, ISBN;
            int year, copies, issue, month;

            switch (op){
                case 1:
                    System.out.println("Enter Call #:");
                    callNumber = cin.next();
                    checkCallNumber(callNumber);
                    Title t = myLibrary.searchCallNumber(callNumber);
                    if(t!=null)
                        System.out.println(t);
                    else
                        System.out.println("Title not found\n");
                    break;
                case 2:
                    cin = new Scanner(System.in);
                    title = cin.nextLine();
                    results = myLibrary.searchTitle(title);
                    if(results.length != 0)
                        for(Title result : results){
                            System.out.println(result);
                        }
                    else
                        System.out.println("Title not found\n");
                    break;
                case 3:
                    System.out.println("Enter Year:");
                    year = cin.nextInt();
                    results = myLibrary.searchYear(year);
                    if(results.length != 0)
                        for(Title result : results){
                            System.out.println(result);
                        }
                    else
                        System.out.println("No titles found\n");
                    break;
                case 4:
                    System.out.println("Call #:");
                    callNumber = cin.next();
                    checkCallNumber(callNumber);
                    System.out.println("Title: ");
                    cin = new Scanner(System.in);
                    title =  cin.nextLine();
                    System.out.println("Publisher: ");
                    cin = new Scanner(System.in);
                    publisher = cin.nextLine();
                    System.out.println("Year:");
                    year = cin.nextInt();
                    checkYear(year);
                    System.out.println("# of Copies:");
                    copies = cin.nextInt();
                    if(callNumber.charAt(0) == 'P'){
                        System.out.println("Issue #:");
                        issue = cin.nextInt();
                        System.out.println("Month:");
                        month = cin.nextInt();
                        if(month < 1 || month > 12)
                            throw new InvalidDate("Invalid Month");

                        myLibrary.addItem(new Perodical(callNumber,title,publisher,year,copies,issue,month));
                    }else{
                        System.out.println("Author: ");
                        cin = new Scanner(System.in);
                        author = cin.nextLine();
                        System.out.println("ISBN: ");
                        cin = new Scanner(System.in);
                        ISBN = cin.nextLine();
                        myLibrary.addItem(new Book(callNumber,title,publisher,year,copies,author,ISBN));
                    }
                    break;
                case 5:
                    System.out.println("Enter Call #:");
                    callNumber = cin.next();
                    checkCallNumber(callNumber);
                    myLibrary.removeItem(callNumber);
                    break;
                case 6:
                    myLibrary.viewAll();
                    break;
            }


        }while(op!=7);



        myLibrary.saveToFile("titles.txt");
    }
}
