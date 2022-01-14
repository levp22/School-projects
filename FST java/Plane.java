public class Plane extends Reflection{
    private double AI;
    private double X;
    private double Y;

    public Plane (double Dx, double Dy, int M, double AI){
        super (M);
        setDistancex(Dx);//runs the method
        this.X=getDistancex();//makes the method equal to X
        setDistancey(Dy);//runs the method
        this.Y=getDistancey();//makes the method equal to Y
        setAI(AI);
    }

    public void setAI(double AI){
        double x;
        x=this.Y/this.X;
        AI=Math.toDegrees(Math.atan(x));//simple SOHCAHTOA for getting the angle of incidence
        this.AI=AI;
    }

    public double getAI(){
        return this.AI;
    }

    public String toString(){
        //explains what happens in this method, and what each variable does
        return "Your original co-ordinates are ("+this.Y+","+this.X+"), and with an Angle of Incidence of "+this.AI+" , your reflected co-ordinates are ("+this.Y*-1+","+this.X*-1+").\nThis is because plane mirrors produce virtual images, and the angle of reflection is equal to the angle of incidence.";
    }

}
