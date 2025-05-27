/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package zvirata;

/**
 *
 * @author Danny
 */
public class Zvire {
    protected String jmeno;
    protected String Druh;
    protected int vek;
    
    public void zarvi()
    {
        System.out.println("Nejaky zvuk");
    }

    public Zvire(String jmeno, String Druh, int vek) {
        this.jmeno = jmeno;
        this.Druh = Druh;
        this.vek = vek;
    }

    public String getJmeno() {
        return jmeno;
    }

    public String getDruh() {
        return Druh;
    }

    public int getVek() {
        return vek;
    }
    
    
}
