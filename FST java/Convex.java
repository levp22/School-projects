import java.util.Scanner;
public class Convex extends Reflection {
    private double X;
    private double COC;//centre of curvature
    private double FP;//focal point
    private double V;//vertex
    private String Size;
    private String Attitude;
    private String Location;
    private String Type;

    public Convex (double Dx, int M, String S, String A, String L, String T){
       //runs all of the methods
        super(M);
        setDistancex(Dx);
        this.X=getDistancex();
        setSize(S);
        setAttitude(A);
        setLocation(L);
        setType(T);
    }

//there is no math needed since all of the situations will display the same way

    public void setSize(String S){
        this.Size="Smaller";
    }

    public String getSize(){
        return this.Size;
    }

    public void setAttitude(String A){
        this.Attitude="Upright";
    }


    public String getAttitude(){
        return this.Attitude;
    }

    public void setLocation(String L){
        this.Location="Behind the mirror";
    }


    public String getLocation() {
        return this.Location;
    }

    public void setType(String T){
       this.Type="Virtual";
    }


    public String getType() {
        return this.Type;
    }

    public String toString(){
        //displays all of the if statements that were done
        return"Your distance from the mirror is: "+this.X+". However, all convex mirrors work the same.....\n\nYour reflected size is: "+this.Size+"\nYour reflected attitude is: "+this.Attitude+"\nYour reflected location is: "+this.Location+"\nYour reflected type is: "+this.Type;
    }

}

