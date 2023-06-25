package com.gamingroom;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * A singleton service for the game engine
 * 
 * @author coce@snhu.edu
 */
public class GameService {

	/**
	 * A list of the active games
	 */
	private static List<Game> games = new ArrayList<Game>();

	/*
	 * Holds the next game identifier
	 */
	private static long nextGameId = 1;

	
	//The private GameService is a new object created, in order to allow GameService to be used as a singleton
	private static GameService instance = new GameService();
	
	//GameService is a private constructor so that other objects cannot be created outside the class
	private GameService() {}

	/**
	 * Construct a new game instance
	 * 
	 * @param name the unique name of the game
	 * @return the game instance (new or existing)
	 */
	
	//getInstance is used to access the single private instance for GameService.
	public static GameService getInstance() {
		return instance;
	}
	
	public Game addGame(String name) {

		// a local game instance
		Game game = null;

		//This iterator is used to go through all games within the games list and return one(if any) with the same name
		Iterator<Game> iter = games.iterator();
		while(iter.hasNext()) {
			Game currentGame = iter.next();
			if(currentGame.name == name) {
				return currentGame;
			}
		}
		
		//Old manual iterator, replaced by above code.
		/*for (int i = 0; i  < instance.getGameCount(); i++)
		{
			if (games.get(i).name == name)
			{
				return games.get(i);
			}
		}*/
		
		// if not found, make a new game instance and add to list of games
		if (game == null) {
			game = new Game(nextGameId++, name);
			games.add(game);
		}

		// return the new/existing game instance to the caller
		return game;
	}

	/**
	 * Returns the game instance at the specified index.
	 * <p>
	 * Scope is package/local for testing purposes.
	 * </p>
	 * @param index index position in the list to return
	 * @return requested game instance
	 */
	Game getGame(int index) {
		return games.get(index);
	}
	
	/**
	 * Returns the game instance with the specified id.
	 * 
	 * @param id unique identifier of game to search for
	 * @return requested game instance
	 */
	public Game getGame(long id) {

		// a local game instance
		Game game = null;

		//This iterator is used to go through all games within the games list and assigns to game one(if any) with the same id
		Iterator<Game> iter = games.iterator();
		while(iter.hasNext()) {
			Game currentGame = iter.next();
			if(currentGame.id == id) {
				game = currentGame;
			}
		}
		
		//Old manual iterator, replaced by above code.
		/*for (int i = 0; i  < instance.getGameCount(); i++)
		{
			if (games.get(i).id == id)
			{
				game = games.get(i);
			}
		}*/
		
		return game;
	}

	/**
	 * Returns the game instance with the specified name.
	 * 
	 * @param name unique name of game to search for
	 * @return requested game instance
	 */
	public Game getGame(String name) {

		// a local game instance
		Game game = null;

		//This iterator is used to go through all games within the games list and assigns to game one(if any) with the same name
		Iterator<Game> iter = games.iterator();
		while(iter.hasNext()) {
			Game currentGame = iter.next();
			if(currentGame.name == name) {
				game = currentGame;
			}
		}
		
		//Old manual iterator, replaced by above code.		
		/*for (int i = 0; i  < instance.getGameCount(); i++)
		{
			if (games.get(i).name == name)
			{
				game = games.get(i);
			}
		}*/
		
		return game;
	}

	/**
	 * Returns the number of games currently active
	 * 
	 * @return the number of games currently active
	 */
	public int getGameCount() {
		return games.size();
	}
}
