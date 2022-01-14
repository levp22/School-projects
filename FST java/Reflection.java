import java.util.Scanner;
public class Reflection extends Position{
    //This class is not used directly, but is needed to run the code
    //it is all used in the main optics class

    private int MType;
    /*
    MType=-1 -> plane
    MType=0 -> concave
    MType=1 -> convex
     */


    public Reflection(double Dx, double Dy, int M){
        super(Dx, Dy);
        setMType(M);
    }

    public Reflection(int M){

    }

    public void setMType(int M){
        boolean badData = true;//try catch for MType
        int x = 0;
        do {
            Scanner sc = new Scanner(System.in);
            try {
                System.out.println("Which mirror would you like to use? (-ve for plane, 0 for concave, +ve for convex)");
                x = sc.nextInt();
                badData = false;
            } catch (Exception e) {
                System.out.println("That was not a legitimate integer. Please enter again");
            }//end of catch
        } while (badData);

        if (x<0){
            this.MType=-1;
        }
        else if (x==0){
            this.MType=0;
        }
        else{
            this.MType=1;
        }
    }

    public int getMType(){
        return this.MType;
    }

}
