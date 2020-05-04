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
    private JButton returnBtn;
    private JButton createBtn;
    private JScrollPane scroll2;
    private JScrollPane scroll1;
    private JLabel label1;
    private JLabel label2;
    private JButton CatBtn;
    private JDBC DataManager;

    public HomePage(JDBC DataManager){
        this.returnBtn.addActionListener(this);
        this.returnBtn.setActionCommand("back");
        this.createBtn.addActionListener(this);
        this.createBtn.setActionCommand("create");
        this.CatBtn.addActionListener(this);
        this.CatBtn.setActionCommand("categorie");

        this.DataManager = DataManager;

        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
        this.afficherPrestataire();
        this.afficherPrestation();

    }


    public void afficherPrestataire(){
        String Query = " SELECT * FROM prestataire ORDER BY id_prestataire ASC";
        Object[][]data = this.DataManager.getDataTable(Query,2);
        Object[]header = this.DataManager.getHeaderTable(Query,2);
        Query = "SELECT id_prestataire FROM prestataire WHERE id_prestataire NOT IN (SELECT prestataire_id_prestataire FROM planning WHERE date_debut > NOW() ) ORDER BY id_prestataire ASC";
        Object[]dataPlanning = this.DataManager.getOneDataTable(Query);
        Query = "SELECT id_prestataire FROM prestataire WHERE id_prestataire NOT IN (SELECT prestataire_id_prestataire FROM affectation) ORDER BY id_prestataire ASC";
        Object[]dataAffect = this.DataManager.getOneDataTable(Query);


        header[header.length-2] ="Planning";
        header[header.length-1] ="Affectation";
        this.setBtn(data,header,dataPlanning,2);
        this.setBtn(data,header,dataAffect,1);
        data=this.sortPrestataire(data);
        this.table1 = new JTable(data, header);
        table1.setDefaultEditor(Object.class, null);
        table1.getColumn("Planning").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Planning").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        table1.getColumn("Affectation").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Affectation").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        scroll1.setViewportView(table1);
    }

    public void afficherPrestation(){
        String Query = " SELECT * FROM prestation ";
        Object[][]data = this.DataManager.getDataTable(Query,1);
        Object[] header = this.DataManager.getHeaderTable(Query,1);
        Query = "SELECT id_prestation FROM prestation WHERE id_prestation NOT IN (SELECT prestation_id_prestation FROM affectation) ORDER BY id_prestation ASC";
        Object[]prestaAffect = this.DataManager.getOneDataTable(Query);
        header[header.length-1] ="Prestataire";
        this.setBtn(data,header,prestaAffect,1);
        data=this.sortPrestation(data);

        this.table2 = new JTable(data, header);
        table2.setDefaultEditor(Object.class, null);
        table2.getColumn("Prestataire").setCellRenderer(new ButtonRenderer());
        table2.getColumn("Prestataire").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager));
        scroll2.setViewportView(table2);
    }

    public Object[][] setBtn(Object[][] data,Object[] header, Object[] Use, int position){
        if(Use != null) {
            int j = 0;
            String btn;
            for (int i = 0; i < data.length; i++) {
                if (j < Use.length && data[i][0].equals(Use[j])) {
                    btn = "N";
                    j++;
                } else {
                    btn = "Y";
                }
                data[i][header.length - position] = btn;
            }
            return data;
        }
        else{
            String btn;
            for (int i = 0; i < data.length; i++) {
                btn = "Y";
                data[i][header.length - position] = btn;
            }
            return data;
        }
    }

    public Object[][] sortPrestataire(Object[][] data) {
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
                if (data[i][15].equals("Y") && data[i][16].equals("Y")) {
                    datafinal[k] = data[i];
                    k++;
                }
            }
        }
        return datafinal;
    }

    public Object[][] sortPrestation(Object[][] data) {
        Object[][] datafinal = new Object[data.length][data[0].length];
        int k = 0;
        for (int i = 0; i < data.length; i++) {
            if (data[i][6].equals("N")) {
                datafinal[k] = data[i];
                k++;
            }
        }
        while (k < datafinal.length) {
            for (int i = 0; i < data.length; i++) {
                if (data[i][6].equals("Y")) {
                    datafinal[k] = data[i];
                    k++;
                }
            }
        }
        return datafinal;
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("back")) {
            this.dispose();
            MainPage np = new MainPage(this.DataManager);
        }
        if(action.equals("create")) {
            this.dispose();
            PrestationPage pp = new PrestationPage(this.DataManager);
        }
        if(action.equals("categorie")) {
            this.dispose();
            CategoriePage pp = new CategoriePage(this.DataManager);
        }
    }
}
