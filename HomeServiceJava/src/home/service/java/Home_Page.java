package home.service.java;

import java.sql.SQLException;

public class Home_Page{

    public static void main(String[] args) throws SQLException {

        JDBC test = new JDBC();
        String[][] presta = test.getTable( "SELECT * FROM prestataire");
        test.afficherTable(presta);
    }



}
