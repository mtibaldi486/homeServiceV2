package home.service.java;
import java.awt.*;
import java.awt.event.*;
import java.sql.SQLException;
import javax.swing.*;
import javax.swing.table.*;

public class ButtonEditor extends DefaultCellEditor implements ActionListener{
    protected JButton button;
    private String    label;
    private boolean   isPushed;
    private String id;
    private PlanningPage next;
    private HomePage last;
    private String column;
    private JDBC data;

    public ButtonEditor(JCheckBox checkBox, HomePage last, JDBC data) {
        super(checkBox);
        button = new JButton();
        button.setOpaque(true);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fireEditingStopped();
            }
        });
        this.last = last;
        this.data = data;
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
        this.id = table.getValueAt(row, 0).toString();
        this.column = table.getColumnName(column).toString();

        return button;
    }

    public Object getCellEditorValue() {
        if (isPushed)  {
            if(this.column.equals("Planning")) {
                this.last.dispose();
                try {
                    next = new PlanningPage(this.id);
                }
                catch (SQLException e){
                    System.out.println("SQLException: " + e.getMessage());
                    System.out.println("SQLState: " + e.getSQLState());
                    System.out.println("CodeError: " + e.getErrorCode());
                }
            }
            else if(this.column.equals("Affectation")){
                JOptionPane.showMessageDialog(button ,label + this.column);
            }
            else if(this.column.equals("Profile")){
                JOptionPane.showMessageDialog(button ,label + this.column);
            }
        }
        isPushed = false;
        return new String( label ) ;
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
