import java.util.*;

public class InvalidDate extends InputMismatchException{
    public InvalidDate(){
        super("Invalid Date");
    }
    public InvalidDate(String message){
        super(message);
    }
}