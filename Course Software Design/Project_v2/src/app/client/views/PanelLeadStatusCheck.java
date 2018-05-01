package app.client.views;

import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

public class PanelLeadStatusCheck extends JPanel {

	private JTextField textFieldSpecialNum;
	private JLabel lblCheckStatMeesage;

	public PanelLeadStatusCheck() {
		init();
	}

	private void init() {

		SpringLayout sl_panel_1 = new SpringLayout();
		setLayout(sl_panel_1);

		JLabel lblSpecialNumber = new JLabel("special number:");
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblSpecialNumber, 205, SpringLayout.NORTH, this);
		sl_panel_1.putConstraint(SpringLayout.WEST, lblSpecialNumber, 212, SpringLayout.WEST, this);
		add(lblSpecialNumber);

		textFieldSpecialNum = new JTextField();
		sl_panel_1.putConstraint(SpringLayout.NORTH, textFieldSpecialNum, 202, SpringLayout.NORTH, this);
		sl_panel_1.putConstraint(SpringLayout.WEST, textFieldSpecialNum, 43, SpringLayout.EAST, lblSpecialNumber);
		sl_panel_1.putConstraint(SpringLayout.EAST, textFieldSpecialNum, -236, SpringLayout.EAST, this);
		add(textFieldSpecialNum);
		textFieldSpecialNum.setColumns(10);

		JButton btnCheck = new JButton("check");
		btnCheck.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println("check");
				/*
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * */
			}
		});
		sl_panel_1.putConstraint(SpringLayout.NORTH, btnCheck, 83, SpringLayout.SOUTH, textFieldSpecialNum);
		sl_panel_1.putConstraint(SpringLayout.WEST, btnCheck, 390, SpringLayout.WEST, this);
		add(btnCheck);

		lblCheckStatMeesage = new JLabel("# Stat Stat Stat #");
		sl_panel_1.putConstraint(SpringLayout.WEST, lblCheckStatMeesage, 361, SpringLayout.WEST, this);
		sl_panel_1.putConstraint(SpringLayout.SOUTH, lblCheckStatMeesage, -77, SpringLayout.NORTH, textFieldSpecialNum);
		lblCheckStatMeesage.setFont(new Font("Arial", Font.BOLD, 15));
		lblCheckStatMeesage.setForeground(Color.RED);
		add(lblCheckStatMeesage);
	}
}
