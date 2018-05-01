package app.financialmanager.views;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

import app.financialmanager.interfaces.Listeners.FinancialManagerViewEventsListener;
import entities.Investor;
import entities.Lead;
import entities.Lead.LeadStatus;
import utility.mydateandtime.MyDateTime;
import utility.myexecuter.MyExecutor;

public class FinancialManagerView extends JFrame {

	private FinancialManagerViewEventsListener listener;
	private final MyExecutor myExecutor;

	// Advice Tab
	private JTextField txtAdviceSubjectField;
	private JTextArea txtAdviceTextArea;

	// Report Tab
	private DefaultTableModel tblModel;
	private JTextField txtFieldAnnualFeeValue;

	// Lead Approve Tab
	private JTextArea txtLeadTextArea;
	private JButton btnApproveLead;
	private JButton btnDisApproveLead;
	private JButton btnGetLead;

	public FinancialManagerView() {
		myExecutor = new MyExecutor();
		init();
	}

	private void init() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 860, 491);
		setResizable(false);
		setAlwaysOnTop(true);
		setVisible(true);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent arg0) {
				fireViewIsClosing();
			}
		});

		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		setContentPane(tabbedPane);

		JPanel panel = new JPanel();
		tabbedPane.addTab("Advice", null, panel, null);
		tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
		SpringLayout sl_panel = new SpringLayout();
		panel.setLayout(sl_panel);

		JLabel lblSubject = new JLabel("Subject:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblSubject, 39, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, lblSubject, 38, SpringLayout.WEST, panel);
		panel.add(lblSubject);

		txtAdviceSubjectField = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, txtAdviceSubjectField, -2, SpringLayout.NORTH, lblSubject);
		sl_panel.putConstraint(SpringLayout.WEST, txtAdviceSubjectField, 6, SpringLayout.EAST, lblSubject);
		sl_panel.putConstraint(SpringLayout.EAST, txtAdviceSubjectField, 137, SpringLayout.EAST, lblSubject);
		txtAdviceSubjectField.setFont(new Font("Arial", Font.BOLD, 14));
		txtAdviceSubjectField.setBorder(new LineBorder(Color.BLACK));
		panel.add(txtAdviceSubjectField);
		txtAdviceSubjectField.setColumns(10);

		JLabel lblAdvice = new JLabel("Advice:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblAdvice, 23, SpringLayout.SOUTH, lblSubject);
		sl_panel.putConstraint(SpringLayout.WEST, lblAdvice, 0, SpringLayout.WEST, lblSubject);
		panel.add(lblAdvice);

		txtAdviceTextArea = new JTextArea();
		txtAdviceTextArea.setFont(new Font("Arial", Font.BOLD, 16));
		txtAdviceTextArea.setLineWrap(true);
		txtAdviceTextArea.setBorder(new LineBorder(new Color(0, 0, 0)));

		JScrollPane scrollerAdvice = new JScrollPane(txtAdviceTextArea);

		sl_panel.putConstraint(SpringLayout.WEST, scrollerAdvice, 10, SpringLayout.EAST, lblAdvice);
		sl_panel.putConstraint(SpringLayout.EAST, scrollerAdvice, -10, SpringLayout.EAST, panel);
		sl_panel.putConstraint(SpringLayout.NORTH, scrollerAdvice, -4, SpringLayout.NORTH, lblAdvice);
		sl_panel.putConstraint(SpringLayout.SOUTH, scrollerAdvice, 269, SpringLayout.SOUTH, lblAdvice);

		panel.add(scrollerAdvice);

		JButton btnSubmitAdvice = new JButton("submit advice");
		sl_panel.putConstraint(SpringLayout.WEST, btnSubmitAdvice, 0, SpringLayout.WEST, txtAdviceSubjectField);
		btnSubmitAdvice.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String subject = txtAdviceSubjectField.getText();
				String body = txtAdviceTextArea.getText();
				if (subject.equals("") || body.equals("")) {
					txtAdviceTextArea.setText("#\nFill all fields\n#");
				} else {
					fireAdviceSubmited(subject, body);
				}
			}
		});
		panel.add(btnSubmitAdvice);

		JButton btnClear = new JButton("clear");
		btnClear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				txtAdviceSubjectField.setText("");
				txtAdviceTextArea.setText("");
			}
		});
		sl_panel.putConstraint(SpringLayout.NORTH, btnSubmitAdvice, 0, SpringLayout.NORTH, btnClear);
		sl_panel.putConstraint(SpringLayout.WEST, btnClear, 220, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.SOUTH, btnClear, -21, SpringLayout.SOUTH, panel);
		panel.add(btnClear);

		JPanel panel_1 = new JPanel();
		tabbedPane.addTab("Report", null, panel_1, null);
		tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);
		SpringLayout sl_panel_1 = new SpringLayout();
		panel_1.setLayout(sl_panel_1);

		tblModel = new DefaultTableModel();

		JTable tbl = new JTable(tblModel);
		tbl.setPreferredScrollableViewportSize(new Dimension(675, 300));
		tbl.setFont(new Font("Consolas", Font.BOLD, 13));
		tbl.setBorder(new LineBorder(new Color(255, 0, 153)));

		tblModel.setColumnIdentifiers(new Object[] { "Full name", "Bank", "Account #", "Last charge", "Next charge" });
		tblModel.addRow(new Object[] { "Tom Cohen", "Leumi", "02365945-65", "01/01/15", "01/01/16" });

		JScrollPane scrollerTbl = new JScrollPane(tbl);
		scrollerTbl.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scrollerTbl.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		sl_panel_1.putConstraint(SpringLayout.NORTH, scrollerTbl, 10, SpringLayout.NORTH, panel_1);
		sl_panel_1.putConstraint(SpringLayout.WEST, scrollerTbl, 10, SpringLayout.WEST, panel_1);
		sl_panel_1.putConstraint(SpringLayout.EAST, scrollerTbl, -10, SpringLayout.EAST, panel_1);
		panel_1.add(scrollerTbl);

		JButton btnReport = new JButton("report");
		btnReport.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				fireReportRequest();
			}
		});
		panel_1.add(btnReport);

		JLabel lblNewLabel = new JLabel("annual fee value:");
		sl_panel_1.putConstraint(SpringLayout.NORTH, btnReport, -4, SpringLayout.NORTH, lblNewLabel);
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblNewLabel, 39, SpringLayout.SOUTH, scrollerTbl);
		sl_panel_1.putConstraint(SpringLayout.EAST, lblNewLabel, -520, SpringLayout.EAST, panel_1);
		panel_1.add(lblNewLabel);

		txtFieldAnnualFeeValue = new JTextField();
		sl_panel_1.putConstraint(SpringLayout.WEST, btnReport, 40, SpringLayout.EAST, txtFieldAnnualFeeValue);
		sl_panel_1.putConstraint(SpringLayout.NORTH, txtFieldAnnualFeeValue, 36, SpringLayout.SOUTH, scrollerTbl);
		sl_panel_1.putConstraint(SpringLayout.WEST, txtFieldAnnualFeeValue, 9, SpringLayout.EAST, lblNewLabel);
		sl_panel_1.putConstraint(SpringLayout.EAST, txtFieldAnnualFeeValue, -383, SpringLayout.EAST, panel_1);
		panel_1.add(txtFieldAnnualFeeValue);
		txtFieldAnnualFeeValue.setColumns(10);

		JPanel panel_2 = new JPanel();
		tabbedPane.addTab("Lead Approve", null, panel_2, null);
		tabbedPane.setMnemonicAt(2, KeyEvent.VK_3);
		SpringLayout sl_panel_2 = new SpringLayout();
		panel_2.setLayout(sl_panel_2);

		txtLeadTextArea = new JTextArea();
		txtLeadTextArea.setEditable(false);
		txtLeadTextArea.setFont(new Font("Consolas", Font.BOLD, 17));
		txtLeadTextArea.setBorder(new LineBorder(new Color(0, 0, 0)));

		JScrollPane scrollerApprove = new JScrollPane(txtLeadTextArea);

		sl_panel_2.putConstraint(SpringLayout.EAST, scrollerApprove, 763, SpringLayout.WEST, panel_2);
		sl_panel_2.putConstraint(SpringLayout.NORTH, scrollerApprove, 40, SpringLayout.NORTH, panel_2);
		sl_panel_2.putConstraint(SpringLayout.WEST, scrollerApprove, 76, SpringLayout.WEST, panel_2);
		sl_panel_2.putConstraint(SpringLayout.SOUTH, scrollerApprove, 345, SpringLayout.NORTH, panel_2);

		panel_2.add(scrollerApprove);

		btnApproveLead = new JButton("approve");
		btnApproveLead.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fireLeadStatusChanged(LeadStatus.APPROVED);
			}
		});
		sl_panel_2.putConstraint(SpringLayout.WEST, btnApproveLead, 76, SpringLayout.WEST, panel_2);
		sl_panel_2.putConstraint(SpringLayout.SOUTH, btnApproveLead, -25, SpringLayout.SOUTH, panel_2);
		panel_2.add(btnApproveLead);

		btnDisApproveLead = new JButton("disapprove");
		btnDisApproveLead.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fireLeadStatusChanged(LeadStatus.DISAPPROVED);
			}
		});
		sl_panel_2.putConstraint(SpringLayout.NORTH, btnDisApproveLead, 0, SpringLayout.NORTH, btnApproveLead);
		sl_panel_2.putConstraint(SpringLayout.WEST, btnDisApproveLead, 196, SpringLayout.WEST, panel_2);
		panel_2.add(btnDisApproveLead);

		btnGetLead = new JButton("get lead");
		btnGetLead.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fireGetLeadRequest();
			}
		});
		sl_panel_2.putConstraint(SpringLayout.NORTH, btnGetLead, 0, SpringLayout.NORTH, btnApproveLead);
		sl_panel_2.putConstraint(SpringLayout.EAST, btnGetLead, 0, SpringLayout.EAST, scrollerApprove);
		panel_2.add(btnGetLead);

		JLabel lblLead = new JLabel("Lead:");
		sl_panel_2.putConstraint(SpringLayout.WEST, lblLead, 0, SpringLayout.WEST, scrollerApprove);
		sl_panel_2.putConstraint(SpringLayout.SOUTH, lblLead, -6, SpringLayout.NORTH, scrollerApprove);
		panel_2.add(lblLead);

		freezeLeadButtons();
	}

	public void registerListener(FinancialManagerViewEventsListener listener) {
		this.listener = listener;
	}

	public void freezeLeadButtons() {
		btnApproveLead.setEnabled(false);
		btnDisApproveLead.setEnabled(false);
		btnGetLead.setEnabled(true);
	}

	public void unFreezeLeadAStatusButtons() {
		btnApproveLead.setEnabled(true);
		btnDisApproveLead.setEnabled(true);
		btnGetLead.setEnabled(false);
	}

	public void displayLead(Lead lead) {
		txtLeadTextArea.setText(lead.toString());
	}

	public void diaplayChargeReport(List<Investor> investorsToChargeList) {
		tblModel.setRowCount(0);
		for (Investor i : investorsToChargeList) {
			tblModel.addRow(new Object[] { i.getFirstName() + " " + i.getLastName(), i.getBankName(),
					i.getBankAccount(), i.getLastFeeCharge(), MyDateTime.getNextYearFromNow() });
		}

	}

	private void fireViewIsClosing() {
		this.dispose();
		myExecutor.closeExecutorsService();
		listener.executeViewWindowIsClosing();
	}

	private void fireAdviceSubmited(String subject, String body) {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				txtAdviceSubjectField.setText("");
				txtAdviceTextArea.setText("");
				listener.executeAdviceSubmited(subject, body);
			}
		});
	}

	private void fireGetLeadRequest() {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				listener.executeGetLeadRequest();
			}
		});
	}

	private void fireLeadStatusChanged(LeadStatus leadStatus) {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				txtLeadTextArea.setText("");
				listener.executeChangeLeadStatus(leadStatus);
			}
		});
	}

	private void fireReportRequest() {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				try {
					double feeVal = Double.parseDouble(txtFieldAnnualFeeValue.getText());
					txtFieldAnnualFeeValue.setText("");
					listener.executeComposeReport(feeVal);
				} catch (NumberFormatException e) {
					txtFieldAnnualFeeValue.setText("<--double num-->");
				}
			}
		});
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FinancialManagerView frame = new FinancialManagerView();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
