package org.csgames;

import java.math.BigInteger;
import java.util.Scanner;

public class Java2 {
    // D0ing_m4th_on_j4va_ch4r_is_s0_3v1l
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("#  WELCOME TO THE SECOND JAVA REVERSING CHALLENGE  #");
        System.out.println("====================================================");
        System.out.println();

        System.out.print("Enter the password : ");

        String pass = new Scanner(System.in).nextLine();

        if (isValidPassword(pass.toCharArray())) {
            System.out.println("Success! The flag is : UQAM{" + pass + "}");
        } else {
            System.out.println("Wrong password... Try harder");
        }
    }

    private static boolean isValidPassword(char[] pass) {
        BigInteger result = new BigInteger("33");

        for (int i = 0; i < pass.length; i++) {
            result = result.multiply(new BigInteger("97"));
            result = result.add(new BigInteger("" + (byte) pass[i]));
        }

        return result.equals(new BigInteger("1196601068455751604172765025142834742772692164339541821505998319783121"));
    }
}