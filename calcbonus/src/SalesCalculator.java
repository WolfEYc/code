import java.util.Scanner;

public class SalesCalculator {

    public static double calcBonus(double sales){
        if(sales<3000){
            return sales*.04;
        }
        if(sales<8000){
            return sales*.075;
        }
        return sales*.1;
    }

    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int salesReps;
        System.out.print("How many sales reps? ");
        salesReps = Integer.parseInt(input.nextLine());

        while(salesReps<1){
            System.out.print("Invalid, re-enter: ");
            salesReps = Integer.parseInt(input.nextLine());
        }

        System.out.println();

        for(int i = 0; i < salesReps;i++){
            System.out.print("Enter name: ");
            String name = input.nextLine();
            System.out.print("Enter amount of sales: ");
            double sales = Double.parseDouble(input.nextLine());
            System.out.print("Bonus for "+name+"  $");
            System.out.printf("%.2f", calcBonus(sales));
            System.out.println("\n");
        }
    }
}
