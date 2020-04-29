package home.service.java;

import sun.applet.Main;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTextField ERPBYMALECOT_TIBALDITextField;
    private JButton RQButton;
    private JButton SQLButton;
    private JPanel panel2;
    private JButton restart;
    private JDBC DataManager;

    public MainPage(JDBC DataManager){
        this.DataManager = DataManager;
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);
        if(this.DataManager.getConn() != null) {
            this.SQLButton.addActionListener(this);
            this.SQLButton.setActionCommand("sql");
            this.restart.addActionListener(this);
            this.restart.setActionCommand("restart");
        }
        else{
            JOptionPane.showMessageDialog(null, "La connection à la base de données n'est pas bonne, vérifier l'état du serveur et relancez l'application!");
            this.restart.addActionListener(this);
            this.restart.setActionCommand("restart");
        }


    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("sql")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
        if(action.equals("restart")) {
            this.dispose();
            JDBC newData = new JDBC();
            MainPage hp = new MainPage(newData);
        }
    }
}
