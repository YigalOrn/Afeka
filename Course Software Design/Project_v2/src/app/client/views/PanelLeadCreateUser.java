package app.client.views;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

public class PanelLeadCreateUser extends JPanel {

	private JTextField textFieldUserName;
	private JTextField textFieldPassWord;

	public PanelLeadCreateUser() {
		init();
	}

	private void init() {

		SpringLayout sl_panel_1 = new SpringLayout();
		setLayout(sl_panel_1);

		JLabel lblFillTheFollowing = new JLabel("Fill the following fields:");
		lblFillTheFollowing.setFont(new Font("Arial Black", Font.BOLD, 12));
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblFillTheFollowing, 36, SpringLayout.NORTH, this);
		sl_panel_1.putConstraint(SpringLayout.WEST, lblFillTheFollowing, 21, SpringLayout.WEST, this);
		add(lblFillTheFollowing);

		JLabel lblUserName = new JLabel("User name:");
		sl_panel_1.putConstraint(SpringLayout.WEST, lblUserName, 0, SpringLayout.WEST, lblFillTheFollowing);
		add(lblUserName);

		textFieldUserName = new JTextField();
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblUserName, 3, SpringLayout.NORTH, textFieldUserName);
		sl_panel_1.putConstraint(SpringLayout.NORTH, textFieldUserName, 29, SpringLayout.SOUTH, lblFillTheFollowing);
		sl_panel_1.putConstraint(SpringLayout.WEST, textFieldUserName, 18, SpringLayout.EAST, lblUserName);
		sl_panel_1.putConstraint(SpringLayout.EAST, textFieldUserName, 191, SpringLayout.EAST, lblUserName);
		add(textFieldUserName);
		textFieldUserName.setColumns(10);

		JLabel lblPassword = new JLabel("Password:");
		sl_panel_1.putConstraint(SpringLayout.WEST, lblPassword, 0, SpringLayout.WEST, lblFillTheFollowing);
		add(lblPassword);

		textFieldPassWord = new JTextField();
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblPassword, 3, SpringLayout.NORTH, textFieldPassWord);
		sl_panel_1.putConstraint(SpringLayout.NORTH, textFieldPassWord, 20, SpringLayout.SOUTH, textFieldUserName);
		sl_panel_1.putConstraint(SpringLayout.WEST, textFieldPassWord, 0, SpringLayout.WEST, textFieldUserName);
		sl_panel_1.putConstraint(SpringLayout.EAST, textFieldPassWord, 0, SpringLayout.EAST, textFieldUserName);
		add(textFieldPassWord);
		textFieldPassWord.setColumns(10);

		JButton btnProceed = new JButton("proceed");
		btnProceed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println("proceed");
				/*
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * */
			}
		});
		sl_panel_1.putConstraint(SpringLayout.NORTH, btnProceed, 36, SpringLayout.SOUTH, lblPassword);
		sl_panel_1.putConstraint(SpringLayout.WEST, btnProceed, 0, SpringLayout.WEST, lblFillTheFollowing);
		add(btnProceed);
	}
}
