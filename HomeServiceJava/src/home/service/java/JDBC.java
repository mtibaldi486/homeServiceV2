package home.service.java;

import javax.swing.*;
import javax.swing.plaf.nimbus.State;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;


public class JDBC {
    private Connection conn = null;
    private Statement stmt = null;
    private ResultSet rs = null;
    private PreparedStatement pst = null;

    public JDBC(){
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost/db_lille" ,"root","root");

        } catch (SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
    }

    public String[][] getDataTable(String Query, int nb_button){
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(Query);

            int i;
            int j = 0;
            int k;
            rs.last();
            String Result[][] = new String[rs.getRow()][rs.getMetaData().getColumnCount() + nb_button];
            rs.first();
            do{
                i=1;
                k = 0;
                while(i <= rs.getMetaData().getColumnCount()){
                    if(rs.getString(i) != null) {
                        Result[j][k] = rs.getString(i);
                        i++;
                        k++;
                    }
                    else{
                        i++;
                        k++;
                    }
                }
                j++;
            }while(rs.next());
            rs.close();
            return Result;
        }
        catch(SQLException e){
            return null;
        }
    }

    public String[] getOneDataTable(String Query){
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(Query);

            int i;
            int j = 0;
            int k;
            rs.last();
            String Result[] = new String[rs.getRow()];
            rs.first();
            do{
                i=1;
                while(i <= rs.getMetaData().getColumnCount()){
                    Result[j] = rs.getString(i);
                    i++;
                }
                j++;
            }while(rs.next());
            rs.close();
            return Result;
        }
        catch(SQLException e){
            return null;
        }
    }

    public String[] getHeaderTable(String Query, int nb_button){
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(Query);

            int i = 1;
            String header[] = new String[rs.getMetaData().getColumnCount() + nb_button];

            while(i <= rs.getMetaData().getColumnCount()){
                header[i-1] = rs.getMetaData().getColumnLabel(i);
                i++;
            }
            if(nb_button > 0) {
                while (i <= rs.getMetaData().getColumnCount() + nb_button) {
                    header[i - 1] = "";
                    i++;
                }
            }
            rs.close();
            return header;
        }
        catch(SQLException e){
            return null;
        }
    }

    public void updateData(String Query){
        try {
            stmt = conn.createStatement();
            stmt.executeUpdate(Query);
        }
        catch (SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
    }

    public int insertLastId(String Query){
        try{
            stmt = conn.createStatement();
            pst = conn.prepareStatement(Query, Statement.RETURN_GENERATED_KEYS );
            pst.executeUpdate();

            rs = pst.getGeneratedKeys();
            if(rs.next()){
                rs.close();
                return rs.getInt(1);
            }
            rs.close();
        }catch(SQLException e) {
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
        return -1;
    }


    public Connection getConn() {
        return conn;
    }

    public void setConn(Connection conn) {
        this.conn = conn;
    }

}
