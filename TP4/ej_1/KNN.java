import javax.swing.*;

public class KNN {

    private int k;
    private String filename;

    private void get_args(String[] args){
        k = Integer.parseInt(args[0]);
        filename = args[1];
        System.out.println(filename);
        System.out.println(k);
    }

    public static void main(String[] args){
        KNN knn;
        knn = new KNN();
        knn.get_args(args);
        
    }
}