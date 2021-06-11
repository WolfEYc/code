import java.io.File;
import java.io.IOException;
import java.util.*;

public class Recursion {
    private static String currentDir;

    public static void main(String[] args) throws IOException {
        Scanner scnr = new Scanner(System.in);

        currentDir = System.getProperty("user.home");
        System.out.println("Current dir using System:" + currentDir);

        System.out.println("Please enter a directory name: ");
        String name = scnr.nextLine();

        System.out.println("size = " + convert(getSize(currentDir+"/"+name)));
        System.out.println("files = " + fileCount(currentDir+"/"+name));
    }
    public static String convert(long bytes){
        int down = 0;
        while(bytes/1000 > 1){
            bytes/=1000;
            down++;
        }
        switch(down){
            case 0:
                return bytes + " bytes";
            case 1:
                return bytes + " Kbytes";
            case 2:
                return bytes + " Mbytes";
            case 3:
                return bytes + " Gbytes";
        }
        return bytes + " bytes";
    }
    public static long getSize(String name){
        File file = new File("/"+name);
        //System.out.println(file.getPath());
        if(file.isFile())
            return file.length();

        File[] subFiles = file.listFiles();

        if(subFiles == null )
            return 0;


        long sum = 0;

        for (File f : subFiles)
            sum += getSize(f.getPath());

        return sum;
    }

    public static int fileCount(String name){
        File file = new File("/"+name);

        if(file.isFile())
            return 1;

        int sum = 0;

        File[] subFiles = file.listFiles();

        if(subFiles == null)
            return 0;

        for (File f : subFiles)
            sum += fileCount(f.getPath());

        return sum;

    }

}
