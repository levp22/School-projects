import java.util.Scanner;
public class Concave extends Reflection {
    private double X;
    private double COC;//centre of curvature
    private double FP;//focal point
    private double V;//vertex
    private String Size;
    private String Attitude;
    private String Location;
    private String Type;

    public Concave (double Dx, int M, double COC, double FP, double V, String S, String A, String L, String T){
        //runs all of the methods that we wrote
        super(M);
        setDistancex(Dx);
        this.X=getDistancex();
        setCOC(COC);
        setFP(FP);
        setV(V);
        setSize(S);
        setAttitude(A);
        setLocation(L);
        setType(T);
    }

    public void setCOC(double coc){
        boolean badData = true;//try catch for the centre of curvature
        double x = 0;
        do {
            Scanner sc = new Scanner(System.in);
            try {
                System.out.println("How far away is the centre of curvature from the mirror? Please no negatives");
                x = sc.nextDouble();
                badData = false;
            } catch (Exception e) {
                System.out.println("That was not a legitimate double. Please enter again");
            }//end of catch
        } while (badData);
        if (x!=0){
            this.COC = Math.abs(x);//cant be negative
        } else{
            this.COC=Math.ceil(Math.random()*10);//if it is 0, gets randomized
        }
    }

    public double getCOC(){
        return this.COC;
    }

    public void setFP(double fp){
        this.FP=this.COC/2;
    }//focal point is half the COC

    public double getFP(){
        return this.FP;
    }

    public void setV(double v){
        this.V=0;
    }//vertex is always 0

    public double getV(){
        return this.V;
    }

    //the next few methods run all of the rules for Concave mirrors

    public void setSize(String S){
        if(this.X>this.COC){
            this.Size="Smaller";
        } else if(this.X==this.COC){
            this.Size="Same";
        } else if(this.X<this.COC && this.X>this.FP){
            this.Size="Larger";
        } else if(this.X==this.FP){
            this.Size="No Image";
        } else{
            this.Size="Larger";
        }
    }

    public String getSize(){
        return this.Size;
    }

    public void setAttitude(String A){
        if(this.X>this.COC){
            this.Attitude="Inverted";
        } else if(this.X==this.COC){
            this.Attitude="Inverted";
        } else if(this.X<this.COC && this.X>this.FP){
            this.Attitude="Inverted";
        } else if(this.X==this.FP){
            this.Attitude="No Image";
        } else{
            this.Attitude="Upright";
        }
    }

    public String getAttitude(){
        return this.Attitude;
    }

    public void setLocation(String L){
        if(this.X>this.COC){
            this.Location="In front of the mirror between the Focal Point and the Centre of Curvature";
        } else if(this.X==this.COC){
            this.Location="In front of the mirror on the Centre of Curvature";
        } else if(this.X<this.COC && this.X>this.FP){
            this.Location="In front of the mirror past the Centre of Curvature";
        } else if(this.X==this.FP){
            this.Location="No Image";
        } else{
            this.Location="Behind the mirror";
        }
    }

    public String getLocation() {
        return this.Location;
    }

    public void setType(String T){
        if(this.X>this.COC){
            this.Type="Real";
        } else if(this.X==this.COC){
            this.Type="Real";
        } else if(this.X<this.COC && this.X>this.FP){
            this.Type="Real";
        } else if(this.X==this.FP){
            this.Type="No Image";
        } else{
            this.Type="Virtual";
        }
    }

    public String getType() {
        return this.Type;
    }

    public String toString(){
        //displays all of the math and if statements that were done
        return"Your distance from the mirror is: "+this.X+"\nYour Centre of Curvature is: "+this.COC+"\nYour Focal Point is: "+this.FP+"\nYour vertex is: 0.0\n\nUsing all of these numbers, we have determined that...\nYour reflected size is: "+this.Size+"\nYour reflected attitude is: "+this.Attitude+"\nYour reflected location is: "+this.Location+"\nYour reflected type is: "+this.Type;
    }
}
