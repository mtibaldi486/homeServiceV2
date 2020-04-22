package home.service.java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class PlanningPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTable table1;
    private JScrollPane scroll1;
    private JButton returnButton;
    private String id_prestataire;
    private JDBC DataManager;

    public PlanningPage(){
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
    }

    public PlanningPage(String id) throws SQLException {
        this.id_prestataire = id;
        this.DataManager = new JDBC();
        this.returnButton.addActionListener(this);
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
        this.afficherPlanning();


    }

    public void afficherPlanning() throws SQLException {
        String Query = " SELECT * FROM planning WHERE prestataire_id_prestataire = " + this.id_prestataire;

        Object[][] data = this.DataManager.getDataTable(Query, 0);
        Object[] header = this.DataManager.getHeaderTable(Query, 0);

        if(data != null){
            this.table1 = new JTable(data, header);
            scroll1.setViewportView(table1);
        }


    }

    @Override
    public void actionPerformed(ActionEvent e){
        this.dispose();
        try {
            HomePage hp = new HomePage(this.DataManager);
        }catch(SQLException sqe){
            System.out.println("SQLException: " + sqe.getMessage());
            System.out.println("SQLState: " + sqe.getSQLState());
            System.out.println("CodeError: " + sqe.getErrorCode());
        }
    }
}
