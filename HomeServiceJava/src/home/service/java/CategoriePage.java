package home.service.java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CategoriePage  extends JFrame implements ActionListener {
    private JPanel panel;
    private JComboBox BoxVille;
    private JTextField NomField;
    private JButton BtnConfirm;
    private JButton BtnReturn;
    private JDBC DataManager;


    public CategoriePage(JDBC Data){
        this.DataManager = Data;
        this.BtnReturn.addActionListener(this);
        this.BtnReturn.setActionCommand("back");
        this.BtnConfirm.addActionListener(this);
        this.BtnConfirm.setActionCommand("create");

        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);

        String Query = "SELECT ville FROM categorie GROUP BY ville";
        Object[]dataVille = this.DataManager.getOneDataTable(Query);
        this.BoxVille.addItem("Choix de la ville");
        for (int i = 0; i < dataVille.length; i++) {
            this.BoxVille.addItem(dataVille[i]);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("back")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
        if(action.equals("create")) {
            if(!NomField.getText().isEmpty() ){
                if(BoxVille.getItemCount() != 0 && !BoxVille.getSelectedItem().toString().equals("Choix de la ville")) {
                    String nom = NomField.getText();
                    String ville = BoxVille.getSelectedItem().toString();
                    String Query = "INSERT INTO categorie(nom, ville) VALUES (" +
                            "\""+nom+
                            "\",\""+ville+
                            "\")";
                    this.DataManager.updateData(Query);
                    JOptionPane.showMessageDialog(null, "Categorie créée");
                    this.dispose();
                    HomePage hp = new HomePage(this.DataManager);

                }
                else{
                    JOptionPane.showMessageDialog(null, "Choisissez une categorie");
                }
            }
            else{
                JOptionPane.showMessageDialog(null, "Veuillez renseigner le nom");
            }
        }
    }
}
