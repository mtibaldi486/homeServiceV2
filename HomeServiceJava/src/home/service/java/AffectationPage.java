package home.service.java;

import javax.swing.*;
import javax.swing.table.TableColumnModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AffectationPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTable table1;
    private JTable table2;
    private JLabel lab1;
    private JLabel label2;
    private JScrollPane scroll1;
    private JScrollPane scroll2;
    private JButton returnButton;

    private Prestataire presta;
    private Prestation prestation;
    private JDBC DataManager;

    public AffectationPage(){
        this.returnButton.addActionListener(this);
        this.returnButton.setActionCommand("back");

        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
    }

    public AffectationPage(String id, String type){
        if(type.equals("prestataire")) {
            this.DataManager = new JDBC();
            this.presta = new Prestataire(id, this.DataManager);
            this.returnButton.addActionListener(this);
            this.returnButton.setActionCommand("back");

            this.setContentPane(panel);
            this.setVisible(true);
            Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
            int height = (totalHeight.height / 8) * 7;
            int width = totalHeight.width;
            this.setSize(width, height);
            this.afficherAffectation();
            this.afficherCategorie();
        }
        else {
            this.DataManager = new JDBC();
            this.prestation = new Prestation(id, this.DataManager);
            this.returnButton.addActionListener(this);
            this.returnButton.setActionCommand("back");

            this.setContentPane(panel);
            this.setVisible(true);
            Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
            int height = (totalHeight.height / 8) * 7;
            int width = totalHeight.width;
            this.setSize(width, height);
            this.afficherPrestationAffectation();
            this.afficherPrestataireCategorie();
        }
    }

    public void afficherPrestationAffectation(){
        String Query = " SELECT * FROM affectation WHERE prestation_id_prestation = " + this.prestation.getId_prestation() +" ORDER BY prestataire_id_prestataire ASC";
        Object[][] data = this.DataManager.getDataTable(Query, 0);
        Object[] header = this.DataManager.getHeaderTable(Query, 0);

        header[header.length-1] ="Retirer";

        if(data != null){
            this.setAffecterBtn(data,header,header.length-1, "Retirer");
            this.table1 = new JTable(data, header);
            scroll1.setViewportView(table1);

            table1.setDefaultEditor(Object.class, null);
            table1.getColumn("Retirer").setCellRenderer(new ButtonRenderer());
            table1.getColumn("Retirer").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,this.prestation));
        }

    }

    public void afficherPrestataireCategorie(){
        String Query = "SELECT * FROM prestataire WHERE categorie_ville = \""+this.prestation.getCategorie_ville()+ "\" AND categorie_nom = \""+this.prestation.getCategorie_nom()+"\" AND id_prestataire NOT IN (SELECT prestataire_id_prestataire FROM affectation WHERE prestation_id_prestation = "+this.prestation.getId_prestation()+")ORDER BY id_prestataire ASC";
        Object[][] data = this.DataManager.getDataTable(Query, 0);
        Object[] header = this.DataManager.getHeaderTable(Query, 0);

        header[header.length-1] ="Assigner";

        if(data != null){
            this.setAffecterBtn(data,header,header.length-1, "Assigner");
            this.table2 = new JTable(data, header);
            scroll2.setViewportView(table2);

            table2.setDefaultEditor(Object.class, null);
            table2.getColumn("Assigner").setCellRenderer(new ButtonRenderer());
            table2.getColumn("Assigner").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager,this.prestation));
        }
    }

    public void afficherAffectation(){
        String Query = " SELECT * FROM affectation WHERE prestataire_id_prestataire = " + this.presta.getId_prestataire() +" ORDER BY prestation_id_prestation ASC";

        Object[][] data = this.DataManager.getDataTable(Query, 1);
        Object[] header = this.DataManager.getHeaderTable(Query, 1);

        header[header.length-1] ="Supprimer";

        if(data != null){
            this.setAffecterBtn(data,header,header.length-1, "Supprimer");
            this.table1 = new JTable(data, header);
            scroll1.setViewportView(table1);

            table1.setDefaultEditor(Object.class, null);
            table1.getColumn("Supprimer").setCellRenderer(new ButtonRenderer());
            table1.getColumn("Supprimer").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager, this.presta));

        }
    }

    public void afficherCategorie(){
        String Query = "SELECT * FROM prestation WHERE categorie_ville = \""+this.presta.getCategorie_ville()+ "\" AND categorie_nom = \""+this.presta.getCategorie_nom()+"\" AND id_prestation NOT IN (SELECT prestation_id_prestation FROM affectation WHERE prestataire_id_prestataire = "+this.presta.getId_prestataire()+" )ORDER BY id_prestation ASC";


        Object[][] data = this.DataManager.getDataTable(Query, 1);
        Object[] header = this.DataManager.getHeaderTable(Query, 1);

        header[header.length-1] ="Affecter";

        if(data != null){
            this.setAffecterBtn(data,header,header.length-1, "Affecter");
            this.table2 = new JTable(data, header);
            scroll2.setViewportView(table2);

            table2.setDefaultEditor(Object.class, null);
            table2.getColumn("Affecter").setCellRenderer(new ButtonRenderer());
            table2.getColumn("Affecter").setCellEditor(new ButtonEditor(new JCheckBox(),this, DataManager, this.presta));

        }
    }

    public Object[][] setAffecterBtn(Object[][] data,Object[] header, int position, String btn_text){
        for (int i = 0; i < data.length; i++) {
            data[i][position] = btn_text;
        }
        return data;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("back")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
    }
}
