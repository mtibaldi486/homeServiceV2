package home.service.java;

import sun.applet.Main;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainPage extends JFrame implements ActionListener {
    private JPanel panel;
    private JTextField ERPBYMALECOT_TIBALDITextField;
    private JButton REQUETTAGEButton;
    private JButton SQLButton;
    private JPanel panel2;
    private JDBC DataManager;

    public MainPage(JDBC DataManager){
        this.DataManager = DataManager;
        this.setContentPane(panel);
        this.setVisible(true);
        Dimension totalHeight = Toolkit.getDefaultToolkit().getScreenSize();
        int height = (totalHeight.height/8) * 7;
        int width = totalHeight.width;
        this.setSize(width ,height);

        this.SQLButton.addActionListener(this);
        this.SQLButton.setActionCommand("sql");


    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if(action.equals("sql")) {
            this.dispose();
            HomePage hp = new HomePage(this.DataManager);
        }
    }
}
