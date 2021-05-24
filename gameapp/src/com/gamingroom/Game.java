package com.gamingroom;

import java.util.ArrayList;
import java.util.List;

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
public class Game extends Entity {

	public List<Team> teams = new ArrayList<Team>();




	/**
	 * Hide the default constructor to prevent creating empty instances.
	 */

	/**
	 * Constructor with an identifier and name
	 */
	public Game(long id, String name) {
		super(id,name);
	}

	public Team addTeam(String name){
		Team newTeam = new Team(GameService.getInstance().getNextTeamId(), name);
		teams.add(newTeam);
		return newTeam;
	}


	@Override
	public String toString() {
		
		return "Game [id=" + this.getId() + ", name=" + this.getName() + "]";
	}


}
