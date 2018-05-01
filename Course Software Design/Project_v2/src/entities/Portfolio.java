/*
 * @OneToMany(fetch = javax.persistence.FetchType.EAGER)
 * */

package entities;

import java.io.Serializable;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Portfolio
 *
 */
@Entity
public class Portfolio implements Serializable {

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private int pm_key;
	private Map<String, Integer> assets;
	@OneToMany(cascade=CascadeType.ALL)
	private Set<Command> commands;
	
	private static final long serialVersionUID = 1L;

	public Portfolio() {
		super();
		commands = new HashSet<Command>();
		assets = new HashMap<String, Integer>();
	}

	public int getPm_key() {
		return pm_key;
	}

	public void setPm_key(int pm_key) {
		this.pm_key = pm_key;
	}

	public Set<Command> getCommands() {
		return commands;
	}

	public void setCommands(Set<Command> commands) {
		this.commands = commands;
	}

	public Map<String, Integer> getAssets() {
		return assets;
	}

	public void setAssets(Map<String, Integer> assets) {
		this.assets = assets;
	}

	public int checkAssetsByStockId(String stockId) {
		Integer in = assets.get(stockId);
		if (in == null) {
			return 0;
		} else {
			return in.intValue();
		}
	}

	public void addCommand(Command command) {
		commands.add(command);
	}

}
