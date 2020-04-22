package home.service.java;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class HomePage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTable table1;
    private JTable table2;
    private JButton button1;
    private JButton button2;
    private JScrollPane scroll2;
    private JScrollPane scroll1;
    private JLabel label1;
    private JLabel label2;

    public HomePage(JDBC DataManager) throws SQLException{
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
        this.afficherPrestataire(DataManager);
        this.afficherPrestation(DataManager);
        this.label1.setText("Prestataires");
        this.label2.setText("Prestations");

    }


    public void afficherPrestataire( JDBC DataManager) throws SQLException {
        String Query = " SELECT * FROM prestataire ORDER BY id_prestataire ASC";
        Object[][]data = DataManager.getDataTable(Query,3);
        Object[]header = DataManager.getHeaderTable(Query,3);
        Query = "SELECT id_prestataire FROM prestataire WHERE id_prestataire NOT IN (SELECT prestataire_id_prestataire FROM planning WHERE date_debut > NOW() ) ORDER BY id_prestataire ASC";
        Object[]dataPlanning = DataManager.getOneDataTable(Query);
        Query = "SELECT id_prestataire FROM prestataire WHERE id_prestataire NOT IN (SELECT prestataire_id_prestataire FROM affectation) ORDER BY id_prestataire ASC";
        Object[]dataAffect = DataManager.getOneDataTable(Query);
        header[header.length-3] ="Planning";
        header[header.length-2] ="Affectation";
        header[header.length-1] ="Profile";
        this.setBtn(data,header,dataPlanning,3);
        this.setBtn(data,header,dataAffect,2);
        for (int i = 0; i < data.length; i++) {
            String btn = "Link";
            data[i][header.length - 1] = btn;
        }
        data=this.sort(data);
        this.table1 = new JTable(data, header);
        table1.setDefaultEditor(Object.class, null);
        table1.getColumn("Planning").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Planning").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        table1.getColumn("Affectation").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Affectation").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        table1.getColumn("Profile").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Profile").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        scroll1.setViewportView(table1);
    }

    public void afficherPrestation(JDBC DataManager) throws SQLException{
        String Query = " SELECT * FROM prestation ";
        Object[][]data = DataManager.getDataTable(Query,0);
        Object[] header = DataManager.getHeaderTable(Query,0);
        this.table2 = new JTable(data, header);
        scroll2.setViewportView(table2);
    }

    public Object[][] setBtn(Object[][] data,Object[] header, Object[] Use, int position){
        int j = 0;
        for (int i = 0; i < data.length; i++) {
            String btn;
            if(data[i][0].equals(Use[j])){
                btn = "N";
                j++;
            }
            else{
                btn = "Y";
            }
            data[i][header.length - position] = btn;
        }
        return data;
    }

    public Object[][] sort(Object[][] data) {
        Object[][] datafinal = new Object[data.length][data[0].length];
        int k = 0;
        for (int i = 0; i < data.length; i++) {
            if (data[i][15].equals("N") || data[i][16].equals("N")) {
                datafinal[k] = data[i];
                k++;
            }
        }
        while (k < datafinal.length) {
            for (int i = 0; i < data.length; i++) {
                if (data[i][15].equals("Y")) {
                    datafinal[k] = data[i];
                }
            }
            k++;
        }
        return datafinal;
    }


    @Override
    public void actionPerformed(ActionEvent e) {

    }
}
