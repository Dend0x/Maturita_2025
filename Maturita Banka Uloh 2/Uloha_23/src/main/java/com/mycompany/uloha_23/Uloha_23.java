/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.uloha_23;

import zvirata.*;

/**
 *
 * @author Danny
 */
public class Uloha_23 {
    
    public static void main(String[] args) {
	Zvire[] zvirata = {new Lev("Simba", 5), new Slon("Dumbo", 10), new Ovce("Bela", 3)};
        

	for(Zvire zvire : zvirata) {
		System.out.println("Druh: " + zvire.getDruh());
		System.out.println("Jméno: " + zvire.getJmeno());
		System.out.println("Věk: " + zvire.getVek());

		System.out.print("Zvuk: ");
		zvire.zarvi();

		System.out.println("------------------");
	}
    }
}
