package home.service.java;
import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.awt.*;
import java.awt.event.*;
import java.sql.SQLException;
import javax.swing.*;
import javax.swing.table.*;
import javax.xml.crypto.Data;

public class ButtonEditor extends DefaultCellEditor implements ActionListener{
    protected JButton button;
    private String    label;
    private boolean   isPushed;
    private String column;
    private JDBC data;
    private int row;
    private JTable table;
    private JScrollPane scroll;

    private JFrame last;
    private Prestataire prestataire;
    private Prestation prestation;

    public ButtonEditor(JCheckBox checkBox, JFrame last, JDBC DataManager) {
        super(checkBox);
        button = new JButton();
        button.setOpaque(true);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fireEditingStopped();
            }
        });
        this.last = last;
        this.data = DataManager;
    }

    public ButtonEditor(JCheckBox checkBox, JFrame last, JDBC DataManager, JScrollPane pane) {
        super(checkBox);
        button = new JButton();
        button.setOpaque(true);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fireEditingStopped();
            }
        });
        this.last = last;
        this.data = DataManager;
        this.scroll = pane;
    }

    public ButtonEditor(JCheckBox checkBox, JFrame last, JDBC DataManager, Prestataire prest) {
        super(checkBox);
        button = new JButton();
        button.setOpaque(true);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fireEditingStopped();
            }
        });
        this.last = last;
        this.data = DataManager;
        this.prestataire = prest;
    }

    public ButtonEditor(JCheckBox checkBox, JFrame last, JDBC DataManager, Prestation prest) {
        super(checkBox);
        button = new JButton();
        button.setOpaque(true);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fireEditingStopped();
            }
        });
        this.last = last;
        this.data = DataManager;
        this.prestation = prest;
    }

    public Component getTableCellEditorComponent(JTable table, Object value,
                                                 boolean isSelected, int row, int column) {
        if (isSelected) {
            button.setForeground(table.getSelectionForeground());
            button.setBackground(table.getSelectionBackground());
        } else{
            button.setForeground(table.getForeground());
            button.setBackground(table.getBackground());
        }
        label = (value ==null) ? "" : value.toString();
        button.setText( label );
        isPushed = true;
        this.column = table.getColumnName(column);

        this.table = table;
        this.row = row;

        return button;
    }

    public Object getCellEditorValue() {
        if (isPushed)  {
            if(this.column.equals("Planning")) {
                this.last.dispose();
                PlanningPage next = new PlanningPage(this.table.getValueAt(row, 0).toString());
            }
            else if(this.column.equals("Affectation")){
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.table.getValueAt(row, 0).toString(), "prestataire");
            }
            else if(this.column.equals("Prestataire")){
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.table.getValueAt(row, 0).toString(), "prestation");
            }
            else if(this.column.equals("Affecter")){
                Prestation prestation = new Prestation(this.table.getValueAt(row, 0).toString(), this.data);
                Bareme bareme = new Bareme(prestation.getBareme_id_bareme(),this.data);
                bareme = bareme.checkPrice(this.prestataire);
                String Query = "INSERT INTO affectation (prestataire_id_prestataire,prestataire_categorie_ville,prestataire_categorie_nom,prestation_id_prestation,prestation_categorie_ville,prestation_categorie_nom)" +
                        " VALUES (\""+this.prestataire.getId_prestataire()+
                        "\",\""+this.prestataire.getCategorie_ville()+
                        "\",\""+this.prestataire.getCategorie_nom()+
                        "\",\""+prestation.getId_prestation()+
                        "\",\""+prestation.getCategorie_ville()+
                        "\",\""+prestation.getCategorie_nom()+"\")";
                this.data.updateData(Query);
                Query = "UPDATE bareme SET prix_unite = "+bareme.getPrix_unite()+
                        ", prix_unit_recurrent = "+bareme.getPrix_unit_recurrent()+
                        ", nb_unite_minimum = "+bareme.getNb_unit_minimum()+
                        " WHERE id_bareme = "+bareme.getId_bareme();
                this.data.updateData(Query);
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.prestataire.getId_prestataire(), "prestataire");
            }
            else if(this.column.equals("Assigner")){
                Prestataire prestataire = new Prestataire(this.table.getValueAt(row, 0).toString(), this.data);
                Bareme bareme = new Bareme(this.prestation.getBareme_id_bareme(),this.data);
                bareme = bareme.checkPrice(prestataire);
                String Query = "INSERT INTO affectation (prestataire_id_prestataire,prestataire_categorie_ville,prestataire_categorie_nom,prestation_id_prestation,prestation_categorie_ville,prestation_categorie_nom)" +
                        " VALUES (\'"+prestataire.getId_prestataire()+
                        "\',\'"+prestataire.getCategorie_ville()+
                        "\',\'"+prestataire.getCategorie_nom()+
                        "\',\'"+this.prestation.getId_prestation()+
                        "\',\'"+this.prestation.getCategorie_ville()+
                        "\',\'"+this.prestation.getCategorie_nom()+"\')";
                this.data.updateData(Query);
                Query = "UPDATE bareme SET prix_unite = "+bareme.getPrix_unite()+
                        ", prix_unit_recurrent = "+bareme.getPrix_unit_recurrent()+
                        ", nb_unite_minimum = "+bareme.getNb_unit_minimum()+
                        " WHERE id_bareme = "+bareme.getId_bareme();
                this.data.updateData(Query);
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.prestation.getId_prestation(), "prestation");
            }
            else if(this.column.equals("Supprimer")){
                Prestation prestation = new Prestation(this.table.getValueAt(row, 3).toString(), this.data);
                String Query = "DELETE FROM affectation WHERE prestataire_id_prestataire = "+this.table.getValueAt(row, 0).toString()+" AND prestation_id_prestation = "+prestation.getId_prestation();
                this.data.updateData(Query);
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.prestataire.getId_prestataire(), "prestataire");
            }
            else if(this.column.equals("Retirer")){
                Prestataire prestataire = new Prestataire(this.table.getValueAt(row, 0).toString(), this.data);
                String Query = "DELETE FROM affectation WHERE prestation_id_prestation = "+this.prestation.getId_prestation()+" AND prestataire_id_prestataire = "+prestataire.getId_prestataire();
                this.data.updateData(Query);
                this.last.dispose();
                AffectationPage next = new AffectationPage(this.prestation.getId_prestation(), "prestation");
            }
            else if(this.column.equals("Contrats")){
                String Query = "SELECT * FROM contrat WHERE prestataire_id_prestataire = "+this.table.getValueAt(row, 0).toString();
                Object[][]data = this.data.getDataTable(Query,0);
                Object[]header = this.data.getHeaderTable(Query,0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if(this.column.equals("Plannings")){
                String Query = "SELECT * FROM planning WHERE prestataire_id_prestataire = "+this.table.getValueAt(row, 0).toString();
                Object[][]data = this.data.getDataTable(Query,0);
                Object[]header = this.data.getHeaderTable(Query,0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if(this.column.equals("Affectations")){
                String Query = "SELECT * FROM prestation WHERE id_prestation IN (SELECT prestation_id_prestation FROM affectation WHERE prestataire_id_prestataire = "+this.table.getValueAt(row, 0).toString()+")";
                Object[][]data = this.data.getDataTable(Query,0);
                Object[]header = this.data.getHeaderTable(Query,0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if (this.column.equals("Prestataires")){
                String Query = "SELECT * FROM prestataire WHERE id_prestataire IN (SELECT prestataire_id_prestataire FROM affectation WHERE prestation_id_prestation ="+this.table.getValueAt(row, 0).toString()+")";
                Object[][]data = this.data.getDataTable(Query,0);
                Object[]header = this.data.getHeaderTable(Query,0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if (this.column.equals("Baremes")){
                String Query = "SELECT * FROM bareme WHERE id_bareme = "+this.table.getValueAt(row, 5).toString();
                Object[][]data = this.data.getDataTable(Query,0);
                Object[]header = this.data.getHeaderTable(Query,0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if (this.column.equals("Reservations")){
                if(this.table.getColumnName(0).equals("id_prestation")) {
                    String Query = "SELECT * FROM reservation WHERE prestation_id_prestation = " + this.table.getValueAt(row, 0).toString();
                    Object[][] data = this.data.getDataTable(Query, 0);
                    Object[] header = this.data.getHeaderTable(Query, 0);
                    if (data != null) {
                        this.table = new JTable(data, header);
                        this.scroll.setViewportView(table);
                    } else {
                        JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                    }
                }
                else if(this.table.getColumnName(0).equals("id_user")){
                    String Query = "SELECT * FROM reservation WHERE user_id_user = " + this.table.getValueAt(row, 0).toString();
                    Object[][] data = this.data.getDataTable(Query, 0);
                    Object[] header = this.data.getHeaderTable(Query, 0);
                    if (data != null) {
                        this.table = new JTable(data, header);
                        this.scroll.setViewportView(table);
                    } else {
                        JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                    }
                }
            }
            else if(this.column.equals("Abonnements")){
                String Query = "SELECT * FROM abonnement WHERE id_abonnement = (SELECT abonnement_id_abonnement FROM souscription WHERE user_id_user = " + this.table.getValueAt(row, 0).toString() +")";
                Object[][] data = this.data.getDataTable(Query, 0);
                Object[] header = this.data.getHeaderTable(Query, 0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if(this.column.equals("Demandes")){
                String Query = "SELECT * FROM demande WHERE user_id_user = "+ this.table.getValueAt(row, 0).toString();
                Object[][] data = this.data.getDataTable(Query, 0);
                Object[] header = this.data.getHeaderTable(Query, 0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
            else if(this.column.equals("Facturations")){
                String Query = "SELECT * FROM facturation WHERE id_user = "+ this.table.getValueAt(row, 0).toString();
                Object[][] data = this.data.getDataTable(Query, 0);
                Object[] header = this.data.getHeaderTable(Query, 0);
                if(data != null) {
                    this.table = new JTable(data, header);
                    this.scroll.setViewportView(table);
                }
                else{
                    JOptionPane.showMessageDialog(null, "Aucune donnée à afficher");
                }
            }
        }
        isPushed = false;
        return label;
    }

    public boolean stopCellEditing() {
        isPushed = false;
        return super.stopCellEditing();
    }

    protected void fireEditingStopped() {
        super.fireEditingStopped();
    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }
}
