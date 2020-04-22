package home.service.java;

import java.sql.SQLException;

public class Home_Page{

    public static void main(String[] args) throws SQLException {
        JDBC DataManager = new JDBC();
        try {
            HomePage hp = new HomePage(DataManager);
        }catch (SQLException e){
            System.out.println("SQLException: " + e.getMessage());
            System.out.println("SQLState: " + e.getSQLState());
            System.out.println("CodeError: " + e.getErrorCode());
        }
    }



}
