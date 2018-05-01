package app.auth.view;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SpringLayout;
import javax.swing.border.BevelBorder;

import app.auth.interfaces.AuthViewEventsListener;

public class AuthView extends JFrame {

	protected JTextField textField;
	protected JPasswordField passwordField;
	protected JLabel lblerrorLabel;
	protected AuthViewEventsListener listener;

	public AuthView(String winName) {
		init(winName);
	}

	private void init(String winName) {
		setTitle(winName);
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		setAlwaysOnTop(true);

		JPanel panel = new JPanel();
		setContentPane(panel);

		panel.setForeground(Color.BLACK);
		SpringLayout sl_panel = new SpringLayout();
		panel.setLayout(sl_panel);

		JLabel lbTitle = new JLabel("Digital Stock Trading Platform");
		lbTitle.setForeground(new Color(204, 0, 0));
		sl_panel.putConstraint(SpringLayout.NORTH, lbTitle, 20, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, lbTitle, 82, SpringLayout.WEST, panel);
		lbTitle.setFont(new Font("Arial Black", Font.PLAIN, 16));
		lbTitle.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		panel.add(lbTitle);

		lblerrorLabel = new JLabel("");
		sl_panel.putConstraint(SpringLayout.NORTH, lblerrorLabel, 29, SpringLayout.SOUTH, lbTitle);
		sl_panel.putConstraint(SpringLayout.WEST, lblerrorLabel, 137, SpringLayout.WEST, panel);
		panel.add(lblerrorLabel);

		JLabel lblUserName = new JLabel("User Name:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblUserName, 31, SpringLayout.SOUTH, lblerrorLabel);
		sl_panel.putConstraint(SpringLayout.WEST, lblUserName, 0, SpringLayout.WEST, lbTitle);
		panel.add(lblUserName);

		textField = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textField, -3, SpringLayout.NORTH, lblUserName);
		sl_panel.putConstraint(SpringLayout.EAST, textField, -105, SpringLayout.EAST, panel);
		panel.add(textField);
		textField.setColumns(10);

		JLabel lblPassword = new JLabel("Password:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblPassword, 30, SpringLayout.SOUTH, lblUserName);
		sl_panel.putConstraint(SpringLayout.WEST, lblPassword, 0, SpringLayout.WEST, lbTitle);
		panel.add(lblPassword);

		passwordField = new JPasswordField();
		passwordField.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					fireLoginPressed();
				}
			}
		});
		sl_panel.putConstraint(SpringLayout.WEST, textField, 0, SpringLayout.WEST, passwordField);
		sl_panel.putConstraint(SpringLayout.NORTH, passwordField, -3, SpringLayout.NORTH, lblPassword);
		sl_panel.putConstraint(SpringLayout.WEST, passwordField, 19, SpringLayout.EAST, lblPassword);
		sl_panel.putConstraint(SpringLayout.EAST, passwordField, -105, SpringLayout.EAST, panel);
		panel.add(passwordField);

		JButton btnLogin = new JButton("Login");
		sl_panel.putConstraint(SpringLayout.EAST, btnLogin, -105, SpringLayout.EAST, panel);
		btnLogin.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				fireLoginPressed();
			}
		});
		sl_panel.putConstraint(SpringLayout.NORTH, btnLogin, 29, SpringLayout.SOUTH, passwordField);
		panel.add(btnLogin);

		setVisible(true);
	}

	public void registerListener(AuthViewEventsListener listener) {
		this.listener = listener;
	}

	public void setLoginError(String error) {
		lblerrorLabel.setText("# error: " + error + " #");
	}

	private void fireLoginPressed() {

		String username = textField.getText();
		String password = passwordField.getText();

		if (username.equals("") || password.equals("")) {
			setLoginError("some fields are empty");
			return;
		} else {
			listener.loginSubmission(username, password);
		}
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					AuthView frame = new AuthView("Auth view");
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
