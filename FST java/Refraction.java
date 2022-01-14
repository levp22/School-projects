import java.util.Scanner;

public class Refraction extends Position {//start of Refraction class, extends position which is where coordinates are from

    private double angleinc;//angle of incidence variable
    private double angleref;//angle of refraction variable
    private double anglecrit;//critical angle variable
    private double destroy;//variable that determines whether the angle of refraction is greater than the critical thus not having an angle of refraction
    private double SOL;// the Speed of light in medium variable


    public double getSOL() {
        return this.SOL;
    }


    public void setSOL() {//sets the speed of light
        boolean badData = true;
        double x = 0;
        do {//error handling
            Scanner sc = new Scanner(System.in);
            try {
                System.out.println("What is the speed of light in the first medium? (we will multiply by 10^8 for you)");
                x = sc.nextDouble();
                badData = false;//will exit the loop as good data was given
            } catch (Exception e) {
                System.out.println("That was not a legitimate double. Please enter again");//will ask again if given bad data
            }
        } while (badData);
        if(x>3){//SOL can't be greater then 3*10^8 which is the speed in a vacuum
            x=3;
        } else if (x>=-3 && x<=3){//removes negative speed of light
            x=Math.abs(x);
        } else{//if x<-3 just give a random number between 0 and 3
            x=Math.random()*3;
        }
        this.SOL=x;//makes SOL=x
    }

    public Refraction(double dx, double dy, double SOL) {//constructor method the numbers being recieved are obsolete as they are just asked for again in the set methods
        setDistancex(dx);//from position
        setDistancey(dy);//from position
        setSOL();//will ask for SOL
        setAngleinc(getDistancex(), getDistancey());//calculates angle of incidence
        setAngleref(getAngleinc(), getSOL());//calculates angle of refraction
        setAnglecrit(getSOL());//calculates critical angle
    }

    public void setAngleinc(double distancex, double distancey) {//broke up variables for better testing and less clutter
        Math.abs(distancey);//removes negatives which aren't possible
        Math.abs(distancex);//removes negatives which aren't possible
        double l = (distancey / distancex);//tan would be y/x
        double compangle = Math.toDegrees(Math.atan((l)));//finds the inverse tan in radians and converts to degrees
        this.angleinc = (Math.round(100 * (90 - compangle)) / 100);//in comparison to the normal the angle of incedence would be the complimentary angle of what was calculated so subtract what we get from 90 and round it to 2 decimal places for simplicity

    }

    public double getAngleinc() {
        return this.angleinc;
    }

    public void setAngleref(double angleinc, double SOL) {//broke up variables for better testing and less clutter
        double siner = Math.sin(Math.toRadians(angleinc));//have to convert back to radians before it does sin
        double checker = ((3.00 * siner)) / SOL;

        if (checker < 1 && checker > 0) {//if the number is between 0 and 1 then it would be possible to inverse sin and the laser would show up
            double asiner = Math.asin(checker);
            this.angleref = (Math.round(100 * (Math.toDegrees(asiner))) / 100);

            destroy = 0;//sets destroy variable to 0 if it does worl
        } else {//if its not between the 2 numbers inverse sin wouldn't work and thus there would be no angle of refraction

            destroy = 1;//sets destroy variable to 1 if it doesn't work
        }


    }

    public double getAngleref() {
        return this.angleref;
    }

    public void setAnglecrit(double SOL) {
        this.anglecrit = (Math.round(100 * (Math.toDegrees(Math.asin((SOL) / (3)))) / 100));//calculates critical angle
    }

    public double getAnglecrit() {
        return this.anglecrit;
    }

    public String toString() {
        if (this.destroy == 0) {//if it works return all the variables
            return "Your Angle of Incidence is: " + this.angleinc + "\nYour Angle of Refraction into your medium is: " + this.angleref + "\nYour critical angle is: " + this.anglecrit + "\nYour speed of light into the medium is " + this.SOL*100000000;
        }
        else if (this.destroy == 1) {//if it doesn't work return that it wouldnt work
            return "Your angle of incidence is: " + this.angleinc + "\nYour speed of light into the medium is " + this.SOL*100000000 + "\nYour critical angle is: " + this.anglecrit + "\nYour angle of refraction was greater than the critical angle thus there will be total internal reflection ";
        }
        return "hello";//requires return outside of if but it will never get here so this is basically obsolete. its just to appeal to java
    }


}//end of refraction