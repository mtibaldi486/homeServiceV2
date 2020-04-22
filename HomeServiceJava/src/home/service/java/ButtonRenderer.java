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
            if(value.toString().equals("N")){
                setBackground(Color.RED);
            }
            else if(value.toString().equals("Y")) {
                setBackground(Color.GREEN);
            }
            else {
                setForeground(table.getSelectionForeground());
                setBackground(table.getSelectionBackground());
            }
        } else{
            if(value.toString().equals("N")){
                setBackground(Color.RED);
            }
            else if(value.toString().equals("Y")) {
                setBackground(Color.GREEN);
            }
            else {
                setForeground(table.getSelectionForeground());
                setBackground(table.getSelectionBackground());
            }
        }
        setText( (value ==null) ? "" : value.toString() );
        return this;
    }
}



