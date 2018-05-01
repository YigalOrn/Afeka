package app.client.views;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SpringLayout;
import javax.swing.border.LineBorder;

import entities.Person;
import entities.Person.Gender;

import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.ActionEvent;

public class LeadView extends JFrame {

	private JTextField textFieldFirstName;
	private JTextField textFieldLastName;
	private JTextField textFieldAddress;
	private JTextField textFieldDob;
	private JTextField textFieldBankName;
	private JTextField textFieldbankAccount;
	private JComboBox<Person.Gender> comboBox;
	private JTextArea textAreaIntentionsDec;
	private JLabel lblRegFormError;

	private JPanel panelLeadStatusCheck;
	private JPanel panelLeadCreateUser;

	public LeadView() {
		init();
	}

	private void init() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 860, 491);
		setVisible(true);

		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		setContentPane(tabbedPane);

		JPanel panel = new JPanel();
		tabbedPane.addTab("Registration", null, panel, null);
		tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
		SpringLayout sl_panel = new SpringLayout();
		panel.setLayout(sl_panel);

		textFieldFirstName = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldFirstName, 21, SpringLayout.NORTH, panel);
		textFieldFirstName.setColumns(10);
		panel.add(textFieldFirstName);

		JLabel label = new JLabel("First name:");
		sl_panel.putConstraint(SpringLayout.NORTH, label, 24, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, label, 17, SpringLayout.WEST, panel);
		panel.add(label);

		JLabel lblLastName = new JLabel("Last name:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblLastName, 12, SpringLayout.SOUTH, label);
		sl_panel.putConstraint(SpringLayout.WEST, lblLastName, 17, SpringLayout.WEST, panel);
		panel.add(lblLastName);

		textFieldLastName = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldLastName, 6, SpringLayout.SOUTH, textFieldFirstName);
		textFieldLastName.setColumns(10);
		panel.add(textFieldLastName);

		textFieldAddress = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldAddress, 6, SpringLayout.SOUTH, textFieldLastName);
		textFieldAddress.setColumns(10);
		panel.add(textFieldAddress);

		JLabel lblAddress = new JLabel("Address:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblAddress, 12, SpringLayout.SOUTH, lblLastName);
		sl_panel.putConstraint(SpringLayout.WEST, lblAddress, 17, SpringLayout.WEST, panel);
		panel.add(lblAddress);

		JLabel lblGender = new JLabel("Gender:");
		sl_panel.putConstraint(SpringLayout.WEST, lblGender, 17, SpringLayout.WEST, panel);
		panel.add(lblGender);

		comboBox = new JComboBox<Person.Gender>();
		sl_panel.putConstraint(SpringLayout.NORTH, comboBox, -3, SpringLayout.NORTH, lblGender);
		comboBox.setModel(new DefaultComboBoxModel<Person.Gender>(new Gender[] { null, Gender.FEMALE, Gender.MALE }));
		panel.add(comboBox);

		JLabel lblDateOfBirth = new JLabel("Date of birth:");
		sl_panel.putConstraint(SpringLayout.WEST, lblDateOfBirth, 17, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.SOUTH, lblGender, -28, SpringLayout.NORTH, lblDateOfBirth);
		panel.add(lblDateOfBirth);

		textFieldDob = new JTextField();
		textFieldDob.setText("dd/mm/yy");
		panel.add(textFieldDob);
		textFieldDob.setColumns(10);

		JLabel lblBankName = new JLabel("Bank name:");
		sl_panel.putConstraint(SpringLayout.SOUTH, lblDateOfBirth, -20, SpringLayout.NORTH, lblBankName);
		sl_panel.putConstraint(SpringLayout.NORTH, lblBankName, 205, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, lblBankName, 17, SpringLayout.WEST, panel);
		panel.add(lblBankName);

		textFieldBankName = new JTextField();
		sl_panel.putConstraint(SpringLayout.SOUTH, textFieldDob, -14, SpringLayout.NORTH, textFieldBankName);
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldBankName, -3, SpringLayout.NORTH, lblBankName);
		panel.add(textFieldBankName);
		textFieldBankName.setColumns(10);

		JLabel lblBankAccount = new JLabel("Bank account:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblBankAccount, 27, SpringLayout.SOUTH, lblBankName);
		sl_panel.putConstraint(SpringLayout.WEST, lblBankAccount, 0, SpringLayout.WEST, label);
		panel.add(lblBankAccount);

		textFieldbankAccount = new JTextField();
		sl_panel.putConstraint(SpringLayout.WEST, textFieldFirstName, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldLastName, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldAddress, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, comboBox, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldDob, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldBankName, 0, SpringLayout.WEST, textFieldbankAccount);
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldbankAccount, -3, SpringLayout.NORTH, lblBankAccount);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldbankAccount, 20, SpringLayout.EAST, lblBankAccount);
		panel.add(textFieldbankAccount);
		textFieldbankAccount.setColumns(10);

		JLabel lblIntenstionsDeclaration = new JLabel("Intentions declaration:");
		sl_panel.putConstraint(SpringLayout.EAST, textFieldFirstName, -205, SpringLayout.WEST, lblIntenstionsDeclaration);
		sl_panel.putConstraint(SpringLayout.NORTH, lblIntenstionsDeclaration, 21, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, lblIntenstionsDeclaration, 401, SpringLayout.WEST, panel);
		panel.add(lblIntenstionsDeclaration);

		textAreaIntentionsDec = new JTextArea();
		textAreaIntentionsDec.setText("Your declaration here...\n\n\n"
				+ "#\nNOTICE: When registartion is completed your\nspecial num will appear here\n#");
		textAreaIntentionsDec.setBorder(new LineBorder(new Color(0, 0, 0)));
		textAreaIntentionsDec.setFont(new Font("Arial", Font.BOLD, 16));
		textAreaIntentionsDec.setLineWrap(true);

		JScrollPane scrollPane = new JScrollPane(textAreaIntentionsDec);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldLastName, -194, SpringLayout.WEST, scrollPane);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldAddress, -73, SpringLayout.WEST, scrollPane);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldDob, -194, SpringLayout.WEST, scrollPane);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldBankName, -194, SpringLayout.WEST, scrollPane);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldbankAccount, -194, SpringLayout.WEST, scrollPane);
		sl_panel.putConstraint(SpringLayout.NORTH, scrollPane, 10, SpringLayout.SOUTH, lblIntenstionsDeclaration);
		sl_panel.putConstraint(SpringLayout.WEST, scrollPane, 0, SpringLayout.WEST, lblIntenstionsDeclaration);
		sl_panel.putConstraint(SpringLayout.SOUTH, scrollPane, -38, SpringLayout.SOUTH, panel);
		sl_panel.putConstraint(SpringLayout.EAST, scrollPane, 398, SpringLayout.WEST, lblIntenstionsDeclaration);
		panel.add(scrollPane);

		JButton btnRegister = new JButton("register");
		sl_panel.putConstraint(SpringLayout.WEST, btnRegister, 10, SpringLayout.WEST, panel);
		btnRegister.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.out.println("register");
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
				 * */
			}
		});
		sl_panel.putConstraint(SpringLayout.SOUTH, btnRegister, 0, SpringLayout.SOUTH, scrollPane);
		panel.add(btnRegister);

		JButton btnClear = new JButton("clear");
		sl_panel.putConstraint(SpringLayout.EAST, comboBox, 0, SpringLayout.EAST, btnClear);
		btnClear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println("clear");
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
		sl_panel.putConstraint(SpringLayout.WEST, btnClear, 54, SpringLayout.EAST, btnRegister);
		sl_panel.putConstraint(SpringLayout.SOUTH, btnClear, 0, SpringLayout.SOUTH, scrollPane);
		panel.add(btnClear);

		lblRegFormError = new JLabel("# error error error error #");
		sl_panel.putConstraint(SpringLayout.WEST, lblRegFormError, 10, SpringLayout.WEST, panel);
		lblRegFormError.setForeground(Color.RED);
		sl_panel.putConstraint(SpringLayout.SOUTH, lblRegFormError, -39, SpringLayout.NORTH, btnRegister);
		panel.add(lblRegFormError);

		panelLeadStatusCheck = new PanelLeadStatusCheck();
		tabbedPane.addTab("Status", null, panelLeadStatusCheck, null);
		tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);

		// tabbedPane.remove(panelLeadStatusCheck);
		// tabbedPane.addTab("Status", new JPanel());

		// panelLeadCreateUser = new PanelLeadCreateUser();
		// tabbedPane.addTab("User Reg", null, panelLeadCreateUser, null);
		// tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);

	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					LeadView frame = new LeadView();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
