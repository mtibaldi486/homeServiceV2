package home.service.java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.sql.Time;

public class PrestationPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTextField NomField;
    private JTextField DescField;
    private JTextField UniteField;
    private JTextField PrixField;
    private JTextField RecurrentField;
    private JTextField MinField;
    private JTextField TimeField;
    private JButton BtnCreate;
    private JButton BtnReturn;
    private JComboBox BoxVille;
    private JComboBox BoxNom;

    private JDBC DataManager;

    public PrestationPage(JDBC DataManager){
        this.BtnReturn.addActionListener(this);
        this.BtnReturn.setActionCommand("back");
        this.BtnCreate.addActionListener(this);
        this.BtnCreate.setActionCommand("create");
        this.DataManager = DataManager;

        this.BoxNom.setEnabled(false);
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height / 8) * 7;
        int width = totalHeight.width;
        this.setSize(width, height);

        String Query = "SELECT ville FROM categorie GROUP BY ville";
        Object[]dataVille = this.DataManager.getOneDataTable(Query);
        this.BoxVille.addItem("Choix de la ville");
        for (int i = 0; i < dataVille.length; i++) {
            this.BoxVille.addItem(dataVille[i]);
        }

        ItemListener itemListener = new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange() == ItemEvent.SELECTED) {
                    if(! e.getItem().toString().equals("Choix de la ville")) {
                        BoxNom.setEnabled(true);
                        BoxNom.removeAllItems();
                        String Query = "SELECT nom FROM categorie WHERE ville = \"" + e.getItem().toString() + "\"";
                        Object[]dataNom = DataManager.getOneDataTable(Query);
                        BoxNom.addItem("Choix du nom");
                        for (int i = 0; i < dataNom.length; i++) {
                            BoxNom.addItem(dataNom[i]);
                        }
                    }
                }
            }
        };
        this.BoxVille.addItemListener(itemListener);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("back")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
        if(action.equals("create")) {
            if(!NomField.getText().isEmpty() && !DescField.getText().isEmpty() && !UniteField.getText().isEmpty() && !PrixField.getText().isEmpty()
                && !RecurrentField.getText().isEmpty() && !MinField.getText().isEmpty() && !TimeField.getText().isEmpty()){
                String nom = NomField.getText();
                String description = DescField.getText();
                String unite = UniteField.getText();
                String prix = PrixField.getText();
                String reccurent = RecurrentField.getText();
                String min = MinField.getText();
                String time = TimeField.getText();
                if(BoxVille.getItemCount() != 0 && BoxNom.getItemCount() != 0 ) {
                    if( !BoxVille.getSelectedItem().toString().equals("Choix de la ville") && !BoxNom.getSelectedItem().toString().equals("Choix du nom")) {
                        String cat_ville = BoxVille.getSelectedItem().toString();
                        String cat_nom = BoxNom.getSelectedItem().toString();
                        float prix_unite = Float.parseFloat(prix);
                        float prix_recurrent = Float.parseFloat(reccurent);
                        float nb_unit_min = Float.parseFloat(min);
                        float time_unit = Float.parseFloat(time);
                        String IQuery = "INSERT INTO bareme(unite,prix_unite,prix_unit_recurrent,nb_unite_minimum,time_per_unit) " +
                                "VALUES (\""+unite+"\","+prix_unite+","+prix_recurrent+","+nb_unit_min+","+time_unit+")";
                        int lastId = DataManager.insertLastId(IQuery);
                        IQuery = "INSERT INTO prestation(nom,description,categorie_ville,categorie_nom,bareme_id_bareme)"+
                                "VALUES (\""+nom+"\",\""+description+"\",\""+cat_ville+"\",\""+cat_nom+"\","+lastId+")";
                        DataManager.updateData(IQuery);
                        JOptionPane.showMessageDialog(null, "Prestation créée !");
                        this.dispose();
                        HomePage hp = new HomePage(this.DataManager);
                    }
                    else{
                        JOptionPane.showMessageDialog(null, "Choisissez une categorie");
                    }
                }
                else{
                    JOptionPane.showMessageDialog(null, "Choisissez une categorie");
                }

            }
            else{
                JOptionPane.showMessageDialog(null, "Tous les champs de textes doivent être rempli");
            }
        }
    }
}
