package app.auth.view;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import app.auth.interfaces.ClientAuthViewEventsListener;

public class ClientAuthView extends AuthView {

	public ClientAuthView(String winName) {
		super(winName);
		init();
	}

	private void init() {

		JLabel lblIsLead = new JLabel("Are you a Lead? click here");
		lblIsLead.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				((ClientAuthViewEventsListener) listener).leadRegistartion();
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				lblIsLead.setForeground(Color.MAGENTA);
			}

			@Override
			public void mouseExited(MouseEvent e) {
				lblIsLead.setForeground(Color.BLACK);
			}
		});

		JPanel panel = (JPanel) this.getContentPane();
		SpringLayout sl_panel = (SpringLayout) panel.getLayout();

		lblIsLead.setForeground(Color.BLACK);

		sl_panel.putConstraint(SpringLayout.WEST, lblIsLead, 10, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.SOUTH, lblIsLead, -10, SpringLayout.SOUTH, panel);

		panel.add(lblIsLead);
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ClientAuthView frame = new ClientAuthView("Client Auth View");
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

}
