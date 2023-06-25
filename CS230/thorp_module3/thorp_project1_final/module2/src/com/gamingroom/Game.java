package com.gamingroom;

/**
 * A simple class to hold information about a game
 * 
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a game is
 * created.
 * </p>
 * 
 * @author coce@snhu.edu
 *
 */
import java.util.List;

public class Game extends Entity{
	private List<Team> teams;
	
	/**
	 * Constructor with an identifier and name
	 */
	public Game(long id, String name) {
		this.id = id;
		this.name = name;
	}

	//Adds a new player to the team and returns new player object
	public Team addTeam(String teamName) {
		//generates player Id relative to team used for constructor
		int teamId = this.teams.size();
		Team addedTeam = new Team(teamId, teamName);
		teams.add(addedTeam);
		return addedTeam;
	}
	
	@Override
	public String toString() {
		
		return "Game [id=" + id + ", name=" + name + "]";
	}

}
