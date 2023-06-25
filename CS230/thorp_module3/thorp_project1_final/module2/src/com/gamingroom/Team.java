package com.gamingroom;

/**
 * A simple class to hold information about a team
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a team is
 * created.
 * </p>
 * @author coce@snhu.edu
 *
 */
import java.util.List;

public class Team extends Entity {
	private List<Player> players;
	
	/*
	 * Constructor with an identifier and name
	 */
	public Team(long id, String name) {
		this.id = id;
		this.name = name;
	}
	
	//Adds a new player to the team and returns new player object
	public Player addPlayer(String playerName) {
		//generates player Id relative to team used for constructor
		int playerId = this.players.size();
		Player addedPlayer = new Player(playerId, playerName);
		players.add(addedPlayer);
		return addedPlayer;
	}
	
	@Override
	public String toString() {
		return "Team [id=" + id + ", name=" + name + "]";
	}
}
