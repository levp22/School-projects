import java.util.Scanner;
public class Optics{//start of optics
    public static void main(String[] args) {//start of main method
        int loop=0;//starts with it 0
        do {//error handling
            boolean badData = true;
            int dec = 0;
            do {
                Scanner sc = new Scanner(System.in);
                try {
                    System.out.println("Would you like to do refraction(>=0), or reflection(<0)?");//asks which type of optics you want to do
                    dec = sc.nextInt();
                    badData = false;
                } catch (Exception e) {
                    System.out.println("That was not a legitimate integer. Please enter again");//will ask again if bad data given
                }//end of catch
            } while (badData);

            if (dec >= 0) {//if you want to do refraction will create new refraction variable, ask for the position and SOL and then calculate all variables
                Refraction z = new Refraction(8, 3, 40000);//these values are obsolete
                System.out.println(z);//prints the variables
            } else {
                badData = true;
                int x = 0;
                do {//error handling
                    Scanner sc = new Scanner(System.in);
                    try {
                        System.out.println("Which mirror would you like to use? (-ve for plane, 0 for concave, +ve for convex)");//asks which mirror you want to do
                        x = sc.nextInt();
                        badData = false;
                    } catch (Exception e) {
                        System.out.println("That was not a legitimate integer. Please enter again"); //will ask again if bad data given
                    }//end of catch
                } while (badData);
                if (x < 0) {//depending on what asked make new variable of that mirror type
                    Plane x1 = new Plane(3, 8, 1, 65);//variables are obsolete
                    System.out.println(x1);//prints the variables
                } else if (x == 0) {
                    Concave x1 = new Concave(3, 8, 1, 65, 4, "s", "d", "D", "t");//variables are obsolete
                    System.out.println(x1);//prints the variables
                } else {
                    Convex x1 = new Convex(3, 8, "s", "d", "D", "t");//variables are obsolete
                    System.out.println(x1);//prints the variables
                }
            }

            badData = true;
            loop = 0;
            do {//error handling
                Scanner sc = new Scanner(System.in);
                try {//asks if you want to loop it
                    System.out.println("Would you like to run our code again? (0 for yes, any other int for no)");
                    loop = sc.nextInt();
                    badData = false;
                } catch (Exception e) {
                    System.out.println("That was not a legitimate integer. Please enter again");//will ask again if bad data given
                }//end of catch
            } while (badData);
        }while(loop==0);

        System.out.println("Thank you for trying our FST! We really enjoyed making it!");
    }//end of main
}//end of optics
