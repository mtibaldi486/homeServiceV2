package home.service.java;

import javax.swing.*;
import javax.swing.plaf.nimbus.State;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;


public class JDBC {
    private Connection conn = null;
    Statement stmt = null;
    Statement stmt2 = null;
    ResultSet rs = null;
    ResultSet rs2 = null;
    PreparedStatement test = null;

    public JDBC(){
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost/db_lille" ,"root","root");

        } catch (SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
    }

    public String[][] getTable(String Query) throws SQLException{
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(Query);

            int i;
            int j = 0;
            int k;
            rs.last();
            String Prestataire[][] = new String[rs.getRow()][rs.getMetaData().getColumnCount()];
            rs.first();
            do{
                i=1;
                k = 0;
                while(i <= rs.getMetaData().getColumnCount()){
                    Prestataire[j][k] = rs.getString(i);
                    i++;
                    k++;
                }
                j++;
            }while(rs.next());
            return Prestataire;
        }
        catch(SQLException e){
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
        return null;
    }

    public void afficherTable(String[][] presta){
        int i = 0;
        int j;
        if(presta.length != 0) {
            while (i < presta.length) {
                j = 0;
                while (j < presta[i].length) {
                    System.out.print(presta[i][j] + ", ");
                    j++;
                }
                System.out.println(" ");
                i++;
            }
        }
    }


}
