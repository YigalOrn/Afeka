/*
 * https://docs.oracle.com/javase/tutorial/uiswing/components/tabbedpane.html
 * 
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
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.SpringLayout;
import javax.swing.SwingUtilities;
import javax.swing.border.EtchedBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class TabbedPanel extends JTabbedPane {

	/** Data fields */
	private JPanel connectionPanel;
	private JPanel formPanel;

	private JLabel lbCarId;
	private JLabel lbNumOfLiters;
	private JTextField jtfCarId;

	private JLabel lbChoosePumpNum;
	private JComboBox<String> cmbPumpNum;
	private JCheckBox jcbWithCleaning;
	private JButton jbtSubmit;
	private JButton jbtResetForm;

	private JLabel lbServerIp;
	private JLabel lbServerPort;
	private JTextField jtfServerIp;
	private JTextField jtfServerPort;
	private JButton jbtConnect;
	private JButton jbtDisconnect;

	private ClientPanel clientPanel;

	private int FPS_INIT = 0;
	private int FPS_MIN = 0;
	private int FPS_MAX = 100;
	private JSlider jsFuelAmount;
	private JLabel lbFuelGauge;

	/** C'tor */
	public TabbedPanel(ClientPanel clientPanel) {
		super(JTabbedPane.BOTTOM);
		this.clientPanel = clientPanel;
		initiComponents();
		initiLayout();

	}// c'tor

	private void initiComponents() {

		connectionPanel = new JPanel();
		formPanel = new JPanel();

		// -----------
		lbCarId = new JLabel("Car id : ");
		jtfCarId = new JTextField("Notice id pattern", 10);
		// -----------

		// -----------
		lbNumOfLiters = new JLabel("Num of liters : ");
		lbFuelGauge = new JLabel();
		// -----------

		// -----------
		jcbWithCleaning = new JCheckBox("With cleaning ?");
		// -----------

		// -----------
		jbtSubmit = new JButton("Submit");
		jbtSubmit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {

				/*
				 * Check fields first!
				 */
				ArrayList<String> formData = new ArrayList<>(4);
				formData.add(0, jtfCarId.getText());
				if (jcbWithCleaning.isSelected()) {
					formData.add(1, "true");
				} else {
					formData.add(1, "false");
				}

				if (jsFuelAmount.getValue() != 0) {
					formData.add(2, jsFuelAmount.getValue() + "");
				} else {
					formData.add(2, "");
				}

				if (cmbPumpNum.getSelectedIndex() != -1) {
					formData.add(3, (String) cmbPumpNum.getSelectedItem());
				} else {
					formData.add(3, "");
				}

				Thread thr = new Thread(new Runnable() {
					@Override
					public void run() {
						fireFormSubmitted(formData);
					}
				});
				thr.start();
			}
		});

		jbtResetForm = new JButton("Reset form");
		jbtResetForm.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				resetForm();
			}
		});
		// -----------

		// -----------
		cmbPumpNum = new JComboBox<>();
		cmbPumpNum.setPreferredSize(new Dimension(110, 20));

		lbChoosePumpNum = new JLabel("Choose pumpNum : ");
		// -----------

		// -----------
		lbServerIp = new JLabel("Enter Server IP : ");

		jtfServerIp = new JTextField("127.0.0.1", 10);
		// -----------

		// -----------
		lbServerPort = new JLabel("Enter Server Port : ");
		jtfServerPort = new JTextField("65000", 10);
		// -----------

		// -----------
		jbtConnect = new JButton("Connect");
		jbtConnect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {

				/*
				 * Check fields are not empty first!
				 */

				Thread thr = new Thread(new Runnable() {

					@Override
					public void run() {
						fireNewConnectionSubmitted(jtfServerIp.getText(),
								jtfServerPort.getText());
					}// run
				});
				thr.start();

			}
		});
		// -----------

		// -----------
		jbtDisconnect = new JButton("Disconnect");
		jbtDisconnect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {

				Thread thr = new Thread(new Runnable() {

					@Override
					public void run() {
						fireDisconnectionSubmitted();
					}// run
				});
				thr.start();

			}
		});
		// -----------

		// -----------

		jsFuelAmount = new JSlider(JSlider.HORIZONTAL, FPS_MIN, FPS_MAX,
				FPS_INIT);

		jsFuelAmount.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {

				JSlider source = (JSlider) e.getSource();
				if (!source.getValueIsAdjusting()) {
					int fps = (int) source.getValue();
					lbFuelGauge.setText(fps + "");
				}

			}
		});

		// jsFuelAmount.setPreferredSize(new Dimension(15, 5));

		jsFuelAmount.setPaintTicks(true);
		jsFuelAmount.setPaintLabels(true);
		jsFuelAmount.setFont(new Font("Serif", Font.ITALIC + Font.BOLD, 15));

		// Turn on labels at major tick marks.
		jsFuelAmount.setMajorTickSpacing(20);
		jsFuelAmount.setMinorTickSpacing(5);

		// -----------

		// -----------
		formPanel.setBorder(BorderFactory.createEtchedBorder(
				EtchedBorder.LOWERED, Color.GRAY, Color.GRAY));

		formPanel.add(lbCarId);
		formPanel.add(lbNumOfLiters);
		formPanel.add(jtfCarId);
		formPanel.add(lbFuelGauge);
		formPanel.add(cmbPumpNum);
		formPanel.add(jcbWithCleaning);
		formPanel.add(jbtSubmit);
		formPanel.add(jbtResetForm);
		formPanel.add(lbChoosePumpNum);
		formPanel.add(jsFuelAmount);

		// -----------

		// -----------
		connectionPanel.setBorder(BorderFactory.createEtchedBorder(
				EtchedBorder.LOWERED, Color.GRAY, Color.GRAY));

		connectionPanel.add(lbServerIp);
		connectionPanel.add(lbServerPort);
		connectionPanel.add(jtfServerIp);
		connectionPanel.add(jtfServerPort);
		connectionPanel.add(jbtConnect);
		connectionPanel.add(jbtDisconnect);
		// -----------

		// addTab(title, icon, component, tip);
		addTab("Connection", connectionPanel);
		addTab("Add Car", formPanel);

		freezeFormPanel();

	}//

	private void initiLayout() {

		// -----------
		SpringLayout spForm = new SpringLayout();
		formPanel.setLayout(spForm);

		formPanel.setPreferredSize(new Dimension(683, 125));
		initFormLayout(spForm);
		// -----------

		// -----------
		SpringLayout spConnection = new SpringLayout();
		connectionPanel.setLayout(spConnection);

		connectionPanel.setPreferredSize(new Dimension(683, 125));
		initConnectionLayout(spConnection);
		// -----------

	}//

	private void initFormLayout(SpringLayout spForm) {

		// -----------
		spForm.putConstraint(SpringLayout.WEST, lbCarId, 10, SpringLayout.WEST,
				formPanel);
		spForm.putConstraint(SpringLayout.NORTH, lbCarId, 15,
				SpringLayout.NORTH, formPanel);

		spForm.putConstraint(SpringLayout.WEST, jtfCarId, 60,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, jtfCarId, 14,
				SpringLayout.NORTH, formPanel);
		// -----------

		// -----------
		spForm.putConstraint(SpringLayout.WEST, lbNumOfLiters, 430,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, lbNumOfLiters, 15,
				SpringLayout.NORTH, formPanel);

		spForm.putConstraint(SpringLayout.WEST, lbFuelGauge, 520,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, lbFuelGauge, 14,
				SpringLayout.NORTH, formPanel);

		spForm.putConstraint(SpringLayout.WEST, jsFuelAmount, 210,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, jsFuelAmount, 15,
				SpringLayout.NORTH, formPanel);

		// -----------

		// -----------
		spForm.putConstraint(SpringLayout.WEST, cmbPumpNum, 10,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, cmbPumpNum, 80,
				SpringLayout.NORTH, formPanel);

		spForm.putConstraint(SpringLayout.WEST, lbChoosePumpNum, 10,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, lbChoosePumpNum, 61,
				SpringLayout.NORTH, formPanel);

		spForm.putConstraint(SpringLayout.WEST, jcbWithCleaning, 140,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, jcbWithCleaning, 78,
				SpringLayout.NORTH, formPanel);

		// -----------

		// -----------
		spForm.putConstraint(SpringLayout.WEST, jbtSubmit, 500,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, jbtSubmit, 88,
				SpringLayout.NORTH, formPanel);
		// -----------

		// -----------
		spForm.putConstraint(SpringLayout.WEST, jbtResetForm, 380,
				SpringLayout.WEST, formPanel);
		spForm.putConstraint(SpringLayout.NORTH, jbtResetForm, 88,
				SpringLayout.NORTH, formPanel);
		// -----------

	}//

	private void initConnectionLayout(SpringLayout spConnection) {

		// -----------
		spConnection.putConstraint(SpringLayout.WEST, lbServerIp, 10,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, lbServerIp, 15,
				SpringLayout.NORTH, connectionPanel);

		spConnection.putConstraint(SpringLayout.WEST, jtfServerIp, 115,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, jtfServerIp, 14,
				SpringLayout.NORTH, connectionPanel);
		// -----------

		// -----------
		spConnection.putConstraint(SpringLayout.WEST, lbServerPort, 300,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, lbServerPort, 15,
				SpringLayout.NORTH, connectionPanel);

		spConnection.putConstraint(SpringLayout.WEST, jtfServerPort, 415,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, jtfServerPort, 14,
				SpringLayout.NORTH, connectionPanel);
		// -----------

		// -----------
		spConnection.putConstraint(SpringLayout.WEST, jbtConnect, 200,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, jbtConnect, 85,
				SpringLayout.NORTH, connectionPanel);

		spConnection.putConstraint(SpringLayout.WEST, jbtDisconnect, 300,
				SpringLayout.WEST, connectionPanel);
		spConnection.putConstraint(SpringLayout.NORTH, jbtDisconnect, 85,
				SpringLayout.NORTH, connectionPanel);
		// -----------

	}//

	private void freezeFormPanel() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jtfCarId.setEnabled(false);
				lbFuelGauge.setEnabled(false);
				jbtSubmit.setEnabled(false);
				jbtResetForm.setEnabled(false);
				cmbPumpNum.setEnabled(false);
				jcbWithCleaning.setEnabled(false);
				jsFuelAmount.setEnabled(false);
			}// run
		});
	}//

	private void unFreezeFormPanel() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jtfCarId.setEnabled(true);
				lbFuelGauge.setEnabled(true);
				jbtSubmit.setEnabled(true);
				jbtResetForm.setEnabled(true);
				cmbPumpNum.setEnabled(true);
				jcbWithCleaning.setEnabled(true);
				jsFuelAmount.setEnabled(true);
			}// run
		});
	}//

	private void resetForm() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jtfCarId.setText("Notice id pattern");
				lbFuelGauge.setText("");
				cmbPumpNum.setSelectedIndex(-1);
				jcbWithCleaning.setSelected(false);
				jsFuelAmount.setValue(0);
			}// run
		});
	}//

	public void resetCmb(int num) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				cmbPumpNum.removeAllItems();
				for (int i = 0; i < num; i++) {
					cmbPumpNum.addItem("" + i);
				}// for
				cmbPumpNum.setSelectedIndex(-1);
			}// run
		});
		unFreezeFormPanel();
	}//

	public void freezeConnectionBtns() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jbtConnect.setEnabled(false);
				jbtDisconnect.setEnabled(false);
			}// run
		});
	}

	public void setDisConnectedState() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {

				freezeFormPanel();// <<----------------------

				jbtConnect.setEnabled(true);
				jbtDisconnect.setEnabled(false);
				clientPanel.setDisconnected();
			}// run
		});
	}

	public void setConnectedState() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				jbtConnect.setEnabled(false);
				jbtDisconnect.setEnabled(true);
				clientPanel.setIsConnected();
			}// run
		});

	}

	// ------------------------------------------

	private void fireFormSubmitted(ArrayList<String> formData) {
		clientPanel.submitAddCarForm(formData);
	}//

	private void fireNewConnectionSubmitted(String ip, String port) {
		clientPanel.connectToServer(ip, port);
	}//

	private void fireDisconnectionSubmitted() {
		clientPanel.disconnectFromServer();
		freezeFormPanel();
	}
	// ------------------------------------------

}//
