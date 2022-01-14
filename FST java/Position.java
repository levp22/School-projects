import java.util.Scanner;
public class Position {
    private double Distancex;//distance from optic device
    private double Distancey;//distance from normal


    public Position(double Dx, double Dy){
        setDistancex(Dx);
        setDistancey(Dy);
    }

    public Position() {
//constructor method
    }

    public void setDistancex(double Dx){
        boolean badData = true;//try catch for DX
        double x = 0;
        do {
            Scanner sc = new Scanner(System.in);
            try {
                System.out.println("What is the distance from the optic device? (no negatives or 0)");
                x = sc.nextDouble();
                badData = false;
            } catch (Exception e) {
                System.out.println("That was not a legitimate double. Please enter again");
            }//end of catch
        } while (badData);
        if(x<0){
            this.Distancex=Math.abs(x);//easy fix to a negative
        }
        else if (x==0){
            this.Distancex=Math.ceil(Math.random()*10);//it can't be zero, this stops a problem
        }
        else{
            this.Distancex=x;//works well
        }
    }

    public double getDistancex(){
        return this.Distancex;
    }//simple get method

    public void setDistancey(double Dy){
        boolean badData = true;// try catch for DY
        double x = 0;
        do {
            Scanner sc = new Scanner(System.in);
            try {
                System.out.println("What is the distance from the normal? (no negatives or 0)");
                x = sc.nextDouble();
                badData = false;
            } catch (Exception e) {
                System.out.println("That was not a legitimate double. Please enter again");
            }//end of catch
        } while (badData);
        if(x<0){
            this.Distancey=Math.abs(x);//fixes negative
        }
        else if (x==0){
            this.Distancey=Math.ceil(Math.random()*10);//can't be 0, easy solution
        }
        else{
            this.Distancey=x;//works well
        }
    }
    public double getDistancey(){
        return this.Distancey;
    }//get method

    public String toString(){
        return "Your distance from the mirror is: "+this.Distancex+" and your distance from the normal is: "+this.Distancey;//toString works for what we need
    }

}
