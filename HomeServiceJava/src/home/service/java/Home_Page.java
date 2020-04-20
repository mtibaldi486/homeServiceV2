package home.service.java;

import java.sql.SQLException;

public class Home_Page{

    public static void main(String[] args) throws SQLException {

        JDBC test = new JDBC();
        String[][] presta = test.getTable( "SELECT * FROM prestataire");
        int i = 0;
        int j;
        while(i < presta.length){
            j=0;
            while(j<presta[i].length){
                System.out.print(presta[i][j] + ", ");
                j++;
            }
            System.out.println(" ");
            i++;
        }
    }

}
