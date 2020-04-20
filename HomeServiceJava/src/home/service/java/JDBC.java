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
       /* try {
            test = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
            int affectedRows = test.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating user failed, no rows affected.");
            }

            try (ResultSet generatedKeys = test.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    System.out.println(generatedKeys.getLong(1));
                } else {
                    throw new SQLException("Creating user failed, no ID obtained.");
                }
            }
        }
        catch (SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }*/

       /*try {
            String test;
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT * FROM RESERVATION");
            int i;
            int j;
            while(rs.next()){
                i = 1;
                while(i <= rs.getMetaData().getColumnCount()){
                    System.out.print(rs.getMetaData().getColumnLabel(i) + " : " + rs.getString(i) + ", ");
                    i++;
                }
                System.out.println();
                test = "SELECT * FROM FACTURATION WHERE reservation_id_reservation = " + rs.getString(1);
                stmt2 = conn.createStatement();
                rs2 = stmt2.executeQuery(test);
                System.out.print("FACTURATION CORRESPONDANTE : ");
                j = 1;
                if(rs2.next()) {
                    while (j <= rs2.getMetaData().getColumnCount()) {
                        System.out.print(rs2.getMetaData().getColumnLabel(j) + " : " + rs2.getString(j) + ", ");
                        j++;
                    }
                }
                stmt2.close();
                System.out.println();

            }
            stmt.close();
        }
        catch (SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }*/


    }

    public String[][] getTable(String Query) throws SQLException{
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(Query);
        }
        catch(SQLException e){
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
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


}
