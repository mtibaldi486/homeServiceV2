package esgi.hs.gui;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Gui {
    private JButton btn_home;
    private JPanel home_panel;



    public static void main(String[] args) {
        JFrame frame = new JFrame("App");
        frame.setContentPane(new Gui().home_panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
