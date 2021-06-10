import java.util.*;

public class InvalidCallNumber extends InputMismatchException{
    public InvalidCallNumber(){
        super("Invalid Call number");
    }
    public InvalidCallNumber(String message){
        super(message);
    }
}