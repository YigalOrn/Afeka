/*
 * https://docs.oracle.com/javase/tutorial/uiswing/components/slider.html
 * 
 * */

package clientSide.ui.clientView;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTextArea;
import javax.swing.SpringLayout;
import javax.swing.SwingUtilities;
import javax.swing.border.BevelBorder;

import clientSide.ui.UserView;

public class ClientPanel extends JPanel implements IConnectionIcon {

	/** Data fields */
	private TabbedPanel tabbedUserMenu;
	private JTextArea jtaChat;
	private JScrollPane jscp;
	private Font chatFont;
	private JSeparator jsp;
	private JLabel lbChatIcon;
	private JLabel lbConnectionStatus;

	private JButton jbCleanTextArea;

	private UserView userView;

	/** C'tor */
	public ClientPanel(UserView userView) {

		this.userView = userView;

		initComponents();
		initLayout();

	}// c'tor

	private void initComponents() {

		tabbedUserMenu = new TabbedPanel(this);

		// -----------
		jbCleanTextArea = new JButton(new ImageIcon(
				"icons\\ClientPanelIcons\\textArea\\1.png"));
		jbCleanTextArea.setPreferredSize(new Dimension(32, 32));
		jbCleanTextArea.setToolTipText("Clean text area");
		jbCleanTextArea.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				jtaChat.setText("");
			}
		});
		// -----------

		// -----------

		lbChatIcon = new JLabel(new ImageIcon(
				"icons\\ClientPanelIcons\\chat\\2.png"), JLabel.CENTER);
		// -----------

		// -----------
		lbConnectionStatus = new JLabel();
		// -----------

		// -----------

		chatFont = new Font("Arial", Font.BOLD, 15);

		jtaChat = new JTextArea();
		// taChat.setBackground(Color.BLACK);

		// taChat.setCaretColor(Color.RED);

		jtaChat.setEditable(false);
		jtaChat.setFont(chatFont);
		jtaChat.setVisible(true);
		jtaChat.setLineWrap(true);
		jtaChat.setWrapStyleWord(true);

		jscp = new JScrollPane(jtaChat);

		jscp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		jscp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

		jscp.setWheelScrollingEnabled(true);

		// jscp.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		jscp.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED,
				Color.GRAY, Color.GRAY));

		// -----------

		// -----------
		jsp = new JSeparator(JSeparator.HORIZONTAL);
		jsp.setBackground(Color.RED);
		jsp.setForeground(Color.RED);
		// -----------

	}//

	private void initLayout() {

		SpringLayout spThis = new SpringLayout();

		setLayout(spThis);

		// -----------
		spThis.putConstraint(SpringLayout.WEST, jbCleanTextArea, 600,
				SpringLayout.WEST, this);
		spThis.putConstraint(SpringLayout.NORTH, jbCleanTextArea, 10,
				SpringLayout.NORTH, this);

		add(jbCleanTextArea);
		// -----------

		// -----------
		jscp.setPreferredSize(new Dimension(500, 300));

		spThis.putConstraint(SpringLayout.WEST, jscp, 90, SpringLayout.WEST,
				this);
		spThis.putConstraint(SpringLayout.NORTH, jscp, 10, SpringLayout.NORTH,
				this);

		add(jscp);
		// -----------

		jsp.setPreferredSize(new Dimension(650, 20));

		spThis.putConstraint(SpringLayout.WEST, jsp, 20, SpringLayout.WEST,
				this);
		spThis.putConstraint(SpringLayout.NORTH, jsp, 325, SpringLayout.NORTH,
				this);

		add(jsp);
		// -----------

		// -----------
		spThis.putConstraint(SpringLayout.WEST, tabbedUserMenu, 5,
				SpringLayout.WEST, this);
		spThis.putConstraint(SpringLayout.NORTH, tabbedUserMenu, 335,
				SpringLayout.NORTH, this);

		add(tabbedUserMenu);
		// -----------

		// -----------
		spThis.putConstraint(SpringLayout.WEST, lbChatIcon, 5,
				SpringLayout.WEST, this);
		spThis.putConstraint(SpringLayout.NORTH, lbChatIcon, 15,
				SpringLayout.NORTH, this);

		add(lbChatIcon);
		// -----------

		// -----------
		spThis.putConstraint(SpringLayout.WEST, lbConnectionStatus, 5,
				SpringLayout.WEST, this);
		spThis.putConstraint(SpringLayout.NORTH, lbConnectionStatus, 90,
				SpringLayout.NORTH, this);

		add(lbConnectionStatus);
		// -----------

	}//

	public void setChatText(String message) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jtaChat.append(message + "\n");
			}
		});
	}//

	// ------------------------------------------
	@Override
	public void setIsConnected() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				lbConnectionStatus.setIcon(new ImageIcon(
						"icons\\TabbedPanelIcons\\connection\\4.png"));
			}// run
		});
	}

	@Override
	public void setDisconnected() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				lbConnectionStatus.setIcon(new ImageIcon(
						"icons\\TabbedPanelIcons\\connection\\2.png"));
			}// run
		});
	}

	// ------------------------------------------

	// ------------------------------------------
	// BL events
	public void requestreSetCmb(int pumpCount) {
		tabbedUserMenu.resetCmb(pumpCount);
	}

	public void requestFreezeConnectionBtns() {
		tabbedUserMenu.freezeConnectionBtns();
	}

	public void requestSetConnectedState() {
		tabbedUserMenu.setConnectedState();
	}

	public void requestSetDisConnectedState() {
		tabbedUserMenu.setDisConnectedState();
	}

	// ------------------------------------------

	// ------------------------------------------
	// UI events
	public void submitAddCarForm(ArrayList<String> formData) {
		userView.submitAddCarForm(formData);
	}

	public void connectToServer(String ip, String port) {
		userView.connectToServer(ip, port);
	}

	public void disconnectFromServer() {
		userView.disconnectFromServer();
	}
	// ------------------------------------------

}// ClientPanel

