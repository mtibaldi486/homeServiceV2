package home.service.java;

import javax.swing.*;
import javax.swing.table.TableColumnModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.TemporalAccessor;
import java.util.*;
import java.util.List;

public class PlanningPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTable table1;
    private JScrollPane scroll1;
    private JButton returnButton;
    private JTextField textField1;
    private JTextField textField3;
    private JTextField textField2;
    private JButton button1;
    private JTextField textField4;
    private Prestataire presta;
    private JDBC DataManager;

    public static final long HOUR = 3600*1000;

    public PlanningPage(){
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);

        this.textField1.setText("Date de début");
        this.textField2.setText("Date de fin");
        this.textField3.setText("Heure de début");
        this.textField4.setText("Heure de fin");
        this.button1.setText("Confirmer");
    }

    public PlanningPage(String id){
        this.DataManager = new JDBC();
        this.presta = new Prestataire(id, this.DataManager);

        this.returnButton.addActionListener(this);
        this.returnButton.setActionCommand("back");
        this.button1.addActionListener(this);
        this.button1.setActionCommand("add");
        this.table1.setSize(1000,1000);
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
        this.afficherPlanning();
    }

    public void afficherPlanning(){
        String Query = " SELECT * FROM planning WHERE prestataire_id_prestataire = " + this.presta.getId_prestataire() +" ORDER BY date_debut ASC";

        Object[][] data = this.DataManager.getDataTable(Query, 0);
        Object[] header = this.DataManager.getHeaderTable(Query, 0);

        if(data != null){
            this.table1 = new JTable(data, header);
            TableColumnModel columnModel = this.table1.getColumnModel();
            columnModel.getColumn(0).setWidth(25);
            columnModel.getColumn(1).setWidth(125);
            columnModel.getColumn(2).setWidth(125);
            columnModel.getColumn(3).setWidth(25);
            columnModel.getColumn(4).setWidth(50);
            columnModel.getColumn(0).setPreferredWidth(25);
            columnModel.getColumn(1).setPreferredWidth(125);
            columnModel.getColumn(2).setPreferredWidth(125);
            columnModel.getColumn(3).setPreferredWidth(25);
            columnModel.getColumn(4).setPreferredWidth(50);
            scroll1.setViewportView(table1);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("back")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
        else if(action.equals("add")){
            if(!this.textField1.getText().equals("") && !this.textField2.getText().equals("") && !this.textField3.getText().equals("") && !this.textField4.getText().equals("")) {
                try {
                    String dds = this.textField1.getText() + this.textField3.getText();
                    String dfs = this.textField2.getText() + this.textField4.getText();
                    int h = Integer.parseInt(this.textField4.getText()) - Integer.parseInt(this.textField3.getText());

                    SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyyHH");
                    Date dd = sdf.parse(dds.replaceAll(":(?=..$)", ""));
                    Date df = sdf.parse(dfs.replaceAll(":(?=..$)", ""));
                    Date Current = new Date();
                    System.out.println(sdf.format(Current));
                    System.out.println(sdf.format(dd));
                    if(dd.after(df)) {
                        JOptionPane.showMessageDialog(null, "Veuillez rentrer une date de début supérieure à la date de fin ");
                    }
                    else if(dd.before(Current)){
                        JOptionPane.showMessageDialog(null, "Veuillez rentrer une date de début supérieure à aujourd'hui ");
                    }
                    else{
                        allDate(dd, df, h);
                    }

                } catch (ParseException pe) {
                    JOptionPane.showMessageDialog(null, "Vos dates ne sont pas au bon format. ex : 22-02-2000");
                }
                catch (NumberFormatException a){
                    JOptionPane.showMessageDialog(null, "Veuillez rentrer des heures pleines");
                }
            }
            else{
                JOptionPane.showMessageDialog(null, "Veuillez remplir tous les champs");

            }
        }
    }

    public void allDate(Date date_debut, Date date_fin, int h){
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Calendar start = Calendar.getInstance();
        start.setTime(date_debut);

        Calendar end = Calendar.getInstance();
        end.setTime(date_fin);
        String dd;
        String df;

        while( !start.after(end)){
            Date date_inc = start.getTime();
            Date date_inc_final = new Date(date_inc.getTime() + h * HOUR);

            dd = format.format(date_inc);
            df = format.format(date_inc_final);
            InsertPlan(dd,df);
            start.add(Calendar.DATE, 1);
        }
        this.afficherPlanning();

        return;
    }

    public void InsertPlan(String date_debut, String date_fin){
        String Check = "SELECT * FROM planning WHERE DATE(date_debut) = DATE(\"" + date_debut + "\") AND DATE(date_fin) = DATE(\"" + date_fin + "\") AND prestataire_id_prestataire = " + this.presta.getId_prestataire();
        String[][] QueryCheck = this.DataManager.getDataTable(Check, 0);
        System.out.println(Check);
        String Query;
        if(QueryCheck != null) {
            Query = "UPDATE planning SET date_debut = \""+date_debut+"\", date_fin = \""+date_fin+"\" WHERE id_planning = " + QueryCheck[0][0];
            this.DataManager.updateData(Query);
        }
        else{
            Query = "INSERT INTO planning(date_debut,date_fin,prestataire_id_prestataire,prestataire_categorie_ville,prestataire_categorie_nom) " +
                    "VALUES (\""+date_debut+"\",\""+date_fin+"\","+this.presta.getId_prestataire()+",\""+this.presta.getCategorie_ville()+"\",\""+this.presta.getCategorie_nom()+"\")";
            this.DataManager.updateData(Query);
        }
    }
}
