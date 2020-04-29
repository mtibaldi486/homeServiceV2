package home.service.java;

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;

public class ButtonRenderer extends JButton implements TableCellRenderer {

    public ButtonRenderer() {
        setOpaque(true);
    }

    public Component getTableCellRendererComponent(JTable table, Object value,
                                                   boolean isSelected, boolean hasFocus, int row, int column) {
        if (isSelected) {
            if(value.toString().equals("N") || value.toString().equals("Retirer") || value.toString().equals("Supprimer")){
                setBackground(Color.RED);
            }
            else if(value.toString().equals("Y") || value.toString().equals("Assigner") || value.toString().equals("Affecter")) {
                setBackground(Color.GREEN);
            }
            else {
                setBackground(Color.BLUE);
            }
        } else{
            if(value.toString().equals("N") || value.toString().equals("Retirer") || value.toString().equals("Supprimer")){
                setBackground(Color.RED);
            }
            else if(value.toString().equals("Y") || value.toString().equals("Assigner") || value.toString().equals("Affecter")) {
                setBackground(Color.GREEN);
            }
            else {
                setBackground(Color.BLUE);
            }
        }
        setText( (value ==null) ? "" : value.toString() );
        return this;
    }
}



