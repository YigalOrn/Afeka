package app.client.views;

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
import java.util.Set;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SpringLayout;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;

import app.client.interfaces.Listeners.ClientViewEventsListener;
import entities.Advice;
import entities.Command;
import stockexchange.client.StockExchangeTransaction;
import utility.myexecuter.MyExecutor;

public class ClientView extends JFrame {

	private ClientViewEventsListener listener;
	private boolean clientViewClosing;
	private final MyExecutor myExecutor;

	// In Advice tab
	private JTextArea txtAreaAdvice;
	private JTextField txtAdviceField;

	// In Report Tab
	private DefaultTableModel tblInvestorCommandsModel;
	private JLabel lblPortfolioValue;
	private JTable tblInvestorCommandTrans;
	private DefaultTableModel tblInvestorCommandTransModel;

	// In Transaction Tab
	private JTextField textFieldStockName;
	private JTextField textFieldAmount;
	private JTextField textFieldLimitPrice;
	private JComboBox<String> comboBoxType;
	private JButton btnSubmit;
	private JButton btnClear;
	private JLabel lblCommandStat;

	// private JTable tblTickers;
	private DefaultTableModel tblTickersModel;
	public JProgressBar progressBarSubmitCommand;

	public ClientView(String username) {
		setClientViewClosing(false);
		myExecutor = new MyExecutor();
		init(username);
	}

	private void init(String username) {
		setTitle(username);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 860, 491);
		setResizable(false);
		setAlwaysOnTop(true);
		setVisible(true);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent arg0) {
				fireViewClosing();
			}
		});

		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		setContentPane(tabbedPane);

		JPanel panel = new JPanel();
		tabbedPane.addTab("Command", null, panel, null);
		tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
		SpringLayout sl_panel = new SpringLayout();
		panel.setLayout(sl_panel);

		JLabel lblStockName = new JLabel("Stock id:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblStockName, 39, SpringLayout.NORTH, panel);
		panel.add(lblStockName);

		textFieldStockName = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldStockName, -3, SpringLayout.NORTH, lblStockName);
		panel.add(textFieldStockName);
		textFieldStockName.setColumns(10);

		tblTickersModel = new DefaultTableModel();
		JTable tblTickers = new JTable(tblTickersModel);
		tblTickers.setPreferredScrollableViewportSize(new Dimension(300, 210));
		tblTickers.setFont(new Font("Consolas", Font.BOLD, 15));
		tblTickers.setShowHorizontalLines(true);
		tblTickers.setShowVerticalLines(true);
		tblTickers.setForeground(Color.BLUE);
		tblTickers.setBackground(Color.WHITE);

		tblTickersModel.setColumnIdentifiers(new Object[] { "StockID", "Company", "Quote", "Trend", "TimeStamp" });

		JScrollPane scrollerTbTickers = new JScrollPane(tblTickers);
		sl_panel.putConstraint(SpringLayout.SOUTH, scrollerTbTickers, -10, SpringLayout.SOUTH, panel);
		scrollerTbTickers.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		scrollerTbTickers.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		panel.add(scrollerTbTickers);

		JLabel lblUpdates = new JLabel("Tickers:");
		sl_panel.putConstraint(SpringLayout.NORTH, scrollerTbTickers, 6, SpringLayout.SOUTH, lblUpdates);
		sl_panel.putConstraint(SpringLayout.WEST, scrollerTbTickers, 0, SpringLayout.WEST, lblUpdates);
		sl_panel.putConstraint(SpringLayout.EAST, scrollerTbTickers, 526, SpringLayout.WEST, lblUpdates);
		sl_panel.putConstraint(SpringLayout.WEST, lblUpdates, 303, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.NORTH, tblTickers, 6, SpringLayout.SOUTH, lblUpdates);
		sl_panel.putConstraint(SpringLayout.WEST, tblTickers, 0, SpringLayout.WEST, lblUpdates);
		sl_panel.putConstraint(SpringLayout.NORTH, lblUpdates, 0, SpringLayout.NORTH, panel);
		panel.add(lblUpdates);

		btnSubmit = new JButton("submit");
		sl_panel.putConstraint(SpringLayout.WEST, lblStockName, 0, SpringLayout.WEST, btnSubmit);
		sl_panel.putConstraint(SpringLayout.WEST, btnSubmit, 10, SpringLayout.WEST, panel);
		btnSubmit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				fireCommandSubmitPressed();
			}
		});
		panel.add(btnSubmit);

		JLabel lblAmount = new JLabel("Amount:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblAmount, 80, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, lblAmount, 10, SpringLayout.WEST, panel);
		panel.add(lblAmount);

		textFieldAmount = new JTextField();
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldAmount, -3, SpringLayout.NORTH, lblAmount);
		panel.add(textFieldAmount);
		textFieldAmount.setColumns(10);

		JSeparator separator = new JSeparator(JSeparator.VERTICAL);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldStockName, -41, SpringLayout.WEST, separator);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldAmount, -41, SpringLayout.WEST, separator);
		separator.setPreferredSize(new Dimension(10, 100));
		sl_panel.putConstraint(SpringLayout.NORTH, separator, 0, SpringLayout.NORTH, lblUpdates);
		sl_panel.putConstraint(SpringLayout.SOUTH, separator, 0, SpringLayout.SOUTH, panel);
		sl_panel.putConstraint(SpringLayout.EAST, separator, -6, SpringLayout.WEST, tblTickers);
		panel.add(separator);

		JLabel lblLimitPrice = new JLabel("Limit price:");
		sl_panel.putConstraint(SpringLayout.NORTH, lblLimitPrice, 28, SpringLayout.SOUTH, lblAmount);
		sl_panel.putConstraint(SpringLayout.WEST, lblLimitPrice, 10, SpringLayout.WEST, panel);
		panel.add(lblLimitPrice);

		textFieldLimitPrice = new JTextField();
		sl_panel.putConstraint(SpringLayout.WEST, textFieldStockName, 0, SpringLayout.WEST, textFieldLimitPrice);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldAmount, 0, SpringLayout.WEST, textFieldLimitPrice);
		sl_panel.putConstraint(SpringLayout.NORTH, textFieldLimitPrice, -3, SpringLayout.NORTH, lblLimitPrice);
		sl_panel.putConstraint(SpringLayout.WEST, textFieldLimitPrice, 16, SpringLayout.EAST, lblLimitPrice);
		sl_panel.putConstraint(SpringLayout.EAST, textFieldLimitPrice, -41, SpringLayout.WEST, separator);
		panel.add(textFieldLimitPrice);
		textFieldLimitPrice.setColumns(10);

		comboBoxType = new JComboBox<String>();
		sl_panel.putConstraint(SpringLayout.WEST, comboBoxType, 0, SpringLayout.WEST, textFieldStockName);
		sl_panel.putConstraint(SpringLayout.EAST, comboBoxType, -138, SpringLayout.WEST, separator);
		comboBoxType.setModel(new DefaultComboBoxModel<String>(new String[] { "", "ASK", "BID" }));
		panel.add(comboBoxType);

		JLabel lblType = new JLabel("Type:");
		sl_panel.putConstraint(SpringLayout.NORTH, comboBoxType, -3, SpringLayout.NORTH, lblType);
		sl_panel.putConstraint(SpringLayout.WEST, lblType, 10, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.NORTH, btnSubmit, 68, SpringLayout.SOUTH, lblType);
		sl_panel.putConstraint(SpringLayout.NORTH, lblType, 33, SpringLayout.SOUTH, lblLimitPrice);
		panel.add(lblType);

		btnClear = new JButton("clear form");
		btnClear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				clearCommandForm();
			}
		});
		sl_panel.putConstraint(SpringLayout.WEST, btnClear, 36, SpringLayout.EAST, btnSubmit);
		sl_panel.putConstraint(SpringLayout.SOUTH, btnClear, 0, SpringLayout.SOUTH, btnSubmit);
		panel.add(btnClear);

		JSeparator separator_1 = new JSeparator(JSeparator.HORIZONTAL);
		separator_1.setPreferredSize(new Dimension(288, 10));
		sl_panel.putConstraint(SpringLayout.WEST, separator_1, 0, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.NORTH, separator_1, 20, SpringLayout.SOUTH, btnSubmit);
		panel.add(separator_1);

		progressBarSubmitCommand = new JProgressBar();
		progressBarSubmitCommand.setForeground(new Color(0, 153, 0));
		progressBarSubmitCommand.setValue(50);
		sl_panel.putConstraint(SpringLayout.NORTH, progressBarSubmitCommand, 49, SpringLayout.SOUTH, separator_1);
		sl_panel.putConstraint(SpringLayout.WEST, progressBarSubmitCommand, 60, SpringLayout.WEST, panel);
		progressBarSubmitCommand.setIndeterminate(true);
		progressBarSubmitCommand.setVisible(false);
		panel.add(progressBarSubmitCommand);

		lblCommandStat = new JLabel();
		sl_panel.putConstraint(SpringLayout.NORTH, lblCommandStat, 6, SpringLayout.SOUTH, separator_1);
		sl_panel.putConstraint(SpringLayout.WEST, lblCommandStat, 0, SpringLayout.WEST, separator_1);
		lblCommandStat.setFont(new Font("Arial", Font.BOLD, 13));
		lblCommandStat.setForeground(Color.RED);
		lblCommandStat.setVisible(false);
		panel.add(lblCommandStat);

		JPanel panel_1 = new JPanel();
		tabbedPane.addTab("Report", null, panel_1, null);
		tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);
		SpringLayout sl_panel_1 = new SpringLayout();
		panel_1.setLayout(sl_panel_1);

		tblInvestorCommandsModel = new DefaultTableModel();

		JTable tblInvestorCommands = new JTable(tblInvestorCommandsModel);
		tblInvestorCommands.setPreferredScrollableViewportSize(new Dimension(675, 300));
		tblInvestorCommands.setFont(new Font("Consolas", Font.BOLD, 13));
		tblInvestorCommands.setBorder(new LineBorder(new Color(255, 0, 153)));

		tblInvestorCommands.addMouseListener(new java.awt.event.MouseAdapter() {
			@Override
			public void mouseClicked(java.awt.event.MouseEvent evt) {
				int row = tblInvestorCommands.rowAtPoint(evt.getPoint());
				int col = tblInvestorCommands.columnAtPoint(evt.getPoint());
				if (row >= 0 && col >= 0) {
					fireShowTransactionForCommand((long) tblInvestorCommandsModel.getValueAt(row, 7));
				}
			}
		});

		tblInvestorCommandsModel.setColumnIdentifiers(
				new Object[] { "StockId", "Status", "Type", "Amount", "Limit Price", "AP", "Date", "CID" });

		JScrollPane scrollerTblInvestorCommands = new JScrollPane(tblInvestorCommands);
		sl_panel_1.putConstraint(SpringLayout.NORTH, scrollerTblInvestorCommands, 10, SpringLayout.NORTH, panel_1);
		sl_panel_1.putConstraint(SpringLayout.WEST, scrollerTblInvestorCommands, 10, SpringLayout.WEST, panel_1);
		sl_panel_1.putConstraint(SpringLayout.EAST, scrollerTblInvestorCommands, -10, SpringLayout.EAST, panel_1);
		scrollerTblInvestorCommands.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scrollerTblInvestorCommands.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		panel_1.add(scrollerTblInvestorCommands);

		tblInvestorCommandTransModel = new DefaultTableModel();
		tblInvestorCommandTrans = new JTable(tblInvestorCommandTransModel);
		tblInvestorCommandTrans.setPreferredScrollableViewportSize(new Dimension(450, 150));
		tblInvestorCommandTrans.setFont(new Font("Consolas", Font.BOLD, 13));
		tblInvestorCommandTrans.setBorder(new LineBorder(new Color(255, 0, 153)));

		tblInvestorCommandTransModel.setColumnIdentifiers(new Object[] { "id", "amount", "price", "datetime" });

		JScrollPane scrollerTblInvestorCommandTrans = new JScrollPane(tblInvestorCommandTrans);
		sl_panel_1.putConstraint(SpringLayout.SOUTH, scrollerTblInvestorCommands, -6, SpringLayout.NORTH,
				scrollerTblInvestorCommandTrans);
		sl_panel_1.putConstraint(SpringLayout.WEST, scrollerTblInvestorCommandTrans, -623, SpringLayout.EAST, panel_1);
		sl_panel_1.putConstraint(SpringLayout.NORTH, scrollerTblInvestorCommandTrans, 236, SpringLayout.NORTH, panel_1);
		sl_panel_1.putConstraint(SpringLayout.EAST, scrollerTblInvestorCommandTrans, -10, SpringLayout.EAST, panel_1);

		scrollerTblInvestorCommandTrans.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scrollerTblInvestorCommandTrans.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		panel_1.add(scrollerTblInvestorCommandTrans);

		lblPortfolioValue = new JLabel("Portfolio value: 0");
		sl_panel_1.putConstraint(SpringLayout.NORTH, lblPortfolioValue, 23, SpringLayout.SOUTH,
				scrollerTblInvestorCommands);
		sl_panel_1.putConstraint(SpringLayout.WEST, lblPortfolioValue, 0, SpringLayout.WEST,
				scrollerTblInvestorCommands);
		panel_1.add(lblPortfolioValue);

		JButton btnRefresh = new JButton("refresh");
		sl_panel_1.putConstraint(SpringLayout.WEST, btnRefresh, 10, SpringLayout.WEST, panel_1);
		sl_panel_1.putConstraint(SpringLayout.SOUTH, btnRefresh, -29, SpringLayout.SOUTH, panel_1);
		btnRefresh.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				fireRefreshPressed();
			}
		});
		panel_1.add(btnRefresh);

		JPanel panel_2 = new JPanel();
		panel_2.setBorder(null);
		tabbedPane.addTab("Advice", null, panel_2, null);
		tabbedPane.setMnemonicAt(2, KeyEvent.VK_3);
		SpringLayout sl_panel_2 = new SpringLayout();
		panel_2.setLayout(sl_panel_2);

		JLabel lblSubject = new JLabel("Subject:");
		sl_panel_2.putConstraint(SpringLayout.NORTH, lblSubject, 39, SpringLayout.NORTH, panel_2);
		sl_panel_2.putConstraint(SpringLayout.WEST, lblSubject, 38, SpringLayout.WEST, panel_2);
		panel_2.add(lblSubject);

		txtAdviceField = new JTextField();
		sl_panel_2.putConstraint(SpringLayout.NORTH, txtAdviceField, -2, SpringLayout.NORTH, lblSubject);
		sl_panel_2.putConstraint(SpringLayout.WEST, txtAdviceField, 6, SpringLayout.EAST, lblSubject);
		sl_panel_2.putConstraint(SpringLayout.EAST, txtAdviceField, 137, SpringLayout.EAST, lblSubject);
		txtAdviceField.setFont(new Font("Arial", Font.BOLD, 14));
		txtAdviceField.setBorder(new LineBorder(Color.BLACK));
		txtAdviceField.setEditable(false);
		panel_2.add(txtAdviceField);
		txtAdviceField.setColumns(10);

		JLabel lblAdvice = new JLabel("Advice:");
		sl_panel_2.putConstraint(SpringLayout.NORTH, lblAdvice, 23, SpringLayout.SOUTH, lblSubject);
		sl_panel_2.putConstraint(SpringLayout.WEST, lblAdvice, 0, SpringLayout.WEST, lblSubject);
		panel_2.add(lblAdvice);

		txtAreaAdvice = new JTextArea();
		txtAreaAdvice.setEditable(false);
		txtAreaAdvice.setBorder(new LineBorder(new Color(0, 0, 0)));
		txtAreaAdvice.setFont(new Font("Arial", Font.BOLD, 16));
		txtAreaAdvice.setLineWrap(true);

		JScrollPane scrollerAdvice = new JScrollPane(txtAreaAdvice);
		sl_panel_2.putConstraint(SpringLayout.WEST, scrollerAdvice, 10, SpringLayout.EAST, lblAdvice);
		sl_panel_2.putConstraint(SpringLayout.EAST, scrollerAdvice, -10, SpringLayout.EAST, panel_2);
		sl_panel_2.putConstraint(SpringLayout.NORTH, scrollerAdvice, -4, SpringLayout.NORTH, lblAdvice);
		sl_panel_2.putConstraint(SpringLayout.SOUTH, scrollerAdvice, 269, SpringLayout.SOUTH, lblAdvice);

		panel_2.add(scrollerAdvice);

		JButton btnGetAdvice = new JButton("get advice");
		sl_panel_2.putConstraint(SpringLayout.NORTH, btnGetAdvice, 21, SpringLayout.SOUTH, scrollerAdvice);
		sl_panel_2.putConstraint(SpringLayout.WEST, btnGetAdvice, 84, SpringLayout.WEST, panel_2);
		btnGetAdvice.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				fireGetAdvicePressed();
			}
		});
		panel_2.add(btnGetAdvice);

		JScrollPane scrollPane = new JScrollPane();
		tabbedPane.addTab("Glossary", null, scrollPane, null);
		tabbedPane.setMnemonicAt(3, KeyEvent.VK_4);

		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);
		scrollPane.setViewportView(textArea);

		startTickersThreadTimedUpadte();
	}

	private void startTickersThreadTimedUpadte() {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				try {
					Thread.sleep(3000);// delay for controller wakeup
					while (!getClientViewClosing()) {
						Thread.sleep(3000);// 3 sec interval
						listener.executeTickersUpdateRequest(tblTickersModel);
					}
				} catch (InterruptedException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public void registerListener(ClientViewEventsListener listener) {
		this.listener = listener;
	}

	public void showCommandProgressBar() {
		progressBarSubmitCommand.setVisible(true);
	}

	public void hideCommandProgressBar() {
		progressBarSubmitCommand.setVisible(false);
	}

	public void freezeCommandForm() {
		textFieldStockName.setEnabled(false);
		textFieldStockName.setEnabled(false);
		textFieldAmount.setEnabled(false);
		textFieldLimitPrice.setEnabled(false);
		comboBoxType.setEnabled(false);
		btnSubmit.setEnabled(false);
		btnClear.setEnabled(false);
	}

	public void unFreezeCommandForm() {
		textFieldStockName.setEnabled(true);
		textFieldStockName.setEnabled(true);
		textFieldAmount.setEnabled(true);
		textFieldLimitPrice.setEnabled(true);
		comboBoxType.setEnabled(true);
		btnSubmit.setEnabled(true);
		btnClear.setEnabled(true);
	}

	public void clearCommandForm() {
		textFieldStockName.setText("");
		textFieldAmount.setText("");
		textFieldLimitPrice.setText("");
		comboBoxType.setSelectedIndex(0);
	}

	public void showCommandStat(String stat) {
		lblCommandStat.setVisible(true);
		lblCommandStat.setText("# " + stat + " #");
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		lblCommandStat.setVisible(false);
	}

	public void refreshReport(Set<Command> comandsList, double portfolioValue) {

		lblPortfolioValue.setText("Portfolio value: " + portfolioValue);

		tblInvestorCommandsModel.setRowCount(0);
		for (Command c : comandsList) {
			tblInvestorCommandsModel.addRow(new Object[] { c.getStockId(), c.getCommandStatus(), c.getType(),
					c.getAmount(), c.getLimitPrice(), c.getAveragePrice(), c.getDateTime(), c.getCommandId() });
		}
	}

	public void setTransactionsForCommand(List<StockExchangeTransaction> l) {

		tblInvestorCommandTransModel.setRowCount(0);
		for (StockExchangeTransaction st : l) {
			tblInvestorCommandTransModel
					.addRow(new Object[] { st.getId(), st.getActualAmount(), st.getActualPrice(), st.getTimestamp() });
		}
	}

	public void setAdvice(Advice advice) {
		txtAdviceField.setText(advice.getSubject());
		txtAreaAdvice.setText(advice.getBody());
	}

	private synchronized void setClientViewClosing(boolean newVal) {
		clientViewClosing = newVal;
	}

	private synchronized boolean getClientViewClosing() {
		return clientViewClosing;
	}

	private void fireCommandSubmitPressed() {

		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				try {
					int amount = Integer.parseInt(textFieldAmount.getText());
					double limitPrice = Double.parseDouble(textFieldLimitPrice.getText());
					listener.executeCommand(textFieldStockName.getText(), amount, limitPrice,
							(String) comboBoxType.getSelectedItem());
				} catch (NumberFormatException e) {
					showCommandStat("some form fields are incorrect");
				}
			}
		});
	}

	private void fireRefreshPressed() {

		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				listener.executeReportRequest();
			}
		});
	}

	private void fireGetAdvicePressed() {

		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				listener.executeAdviceRequest();
			}
		});
	}

	private void fireViewClosing() {
		setClientViewClosing(true);
		this.dispose();
		myExecutor.closeExecutorsService();
		listener.executeViewWindowIsClosing();
	}

	private void fireShowTransactionForCommand(long cid) {
		myExecutor.submitTask(new Runnable() {

			@Override
			public void run() {
				listener.executeTransactionsrequestForCommand(cid);
			}
		});
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ClientView frame = new ClientView("Dummy");
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
