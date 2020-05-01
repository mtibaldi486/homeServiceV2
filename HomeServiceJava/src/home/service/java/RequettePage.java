package home.service.java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class RequettePage extends JFrame implements ActionListener {
    private JPanel main;
    private JButton BtnReturn;
    private JComboBox CBTable;
    private JTable table1;
    private JScrollPane scroll;

    private JDBC DataManager;

    public RequettePage(JDBC Data){
        this.DataManager = Data;
        this.setContentPane(main);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);

        this.BtnReturn.addActionListener(this);
        this.BtnReturn.setActionCommand("return");
        String[] tables = { "Choix des données", "Utilisateur", "Prestataire", "Prestation"};
        for (int i = 0; i < tables.length; i++) {
            this.CBTable.addItem(tables[i]);
        }

        ItemListener itemListener = new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange() == ItemEvent.SELECTED) {
                    if(e.getItem().toString().equals("Prestataire")) {
                        afficherPrestataire();
                        CBTable.setSelectedIndex(0);
                    }
                    else if(e.getItem().toString().equals("Utilisateur")) {
                        afficherUser();
                        CBTable.setSelectedIndex(0);
                    }
                    else if(e.getItem().toString().equals("Prestation")) {
                        afficherPrestation();
                        CBTable.setSelectedIndex(0);
                    }
                }
            }
        };
        this.CBTable.addItemListener(itemListener);
    }

    public void afficherUser(){
        String Query = " SELECT * FROM user ORDER BY id_user ASC";
        Object[][]data = this.DataManager.getDataTable(Query,4);
        Object[]header = this.DataManager.getHeaderTable(Query,4);
        header[header.length-4] ="Abonnements";
        header[header.length-3] ="Demandes";
        header[header.length-2] ="Reservations";
        header[header.length-1] ="Facturations";

        this.setBtn(data,header,4, "Abonnements");
        this.setBtn(data,header,3, "Demandes");
        this.setBtn(data,header,2, "Reservations");
        this.setBtn(data,header,1, "Facturations");
        this.table1 = new JTable(data, header);
        table1.setDefaultEditor(Object.class, null);
        table1.getColumn("Abonnements").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Abonnements").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Demandes").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Demandes").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Reservations").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Reservations").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Facturations").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Facturations").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        scroll.setViewportView(table1);
    }

    public void afficherPrestation(){
        String Query = " SELECT * FROM prestation ORDER BY id_prestation ASC";
        Object[][]data = this.DataManager.getDataTable(Query,3);
        Object[]header = this.DataManager.getHeaderTable(Query,3);
        header[header.length-3] ="Prestataires";
        header[header.length-2] ="Baremes";
        header[header.length-1] ="Reservations";
        this.setBtn(data,header,3, "Prestataires");
        this.setBtn(data,header,2, "Baremes");
        this.setBtn(data,header,1, "Reservations");
        this.table1 = new JTable(data, header);
        table1.setDefaultEditor(Object.class, null);
        table1.getColumn("Prestataires").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Prestataires").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Baremes").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Baremes").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Reservations").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Reservations").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        scroll.setViewportView(table1);
    }

    public void afficherPrestataire(){
        String Query = " SELECT * FROM prestataire ORDER BY id_prestataire ASC";
        Object[][]data = this.DataManager.getDataTable(Query,3);
        Object[]header = this.DataManager.getHeaderTable(Query,3);

        header[header.length-3] ="Contrats";
        header[header.length-2] ="Plannings";
        header[header.length-1] ="Affectations";
        this.setBtn(data,header,3, "Contrats");
        this.setBtn(data,header,2, "Plannings");
        this.setBtn(data,header,1, "Affectations");
        this.table1 = new JTable(data, header);
        table1.setDefaultEditor(Object.class, null);
        table1.getColumn("Contrats").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Contrats").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Plannings").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Plannings").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        table1.getColumn("Affectations").setCellRenderer(new ButtonRenderer());
        table1.getColumn("Affectations").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,scroll));
        scroll.setViewportView(table1);
    }

    public Object[][] setBtn(Object[][] data,Object[] header, int position, String value){
        for (int i = 0; i < data.length; i++) {
            data[i][header.length - position] = value;
        }
        return data;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("return")) {
            this.dispose();
            MainPage hp = new MainPage(this.DataManager);
        }
    }
}
