package com.gamingroom;

import java.util.ArrayList;
import java.util.List;

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
public class Team extends Entity{

	public List<Player> players = new ArrayList<Player>();

	/*
	 * Constructor with an identifier and name
	 */
	public Team(long id, String name) {
		super(id,name);
	}

	public Player addPlayer(String name){
		Player newPlayer = new Player(GameService.getInstance().getNextPlayerId(),name);
		players.add(newPlayer);
		return newPlayer;
	}

	@Override
	public String toString() {
		return "Team [id=" + this.getId() + ", name=" + this.getName() + "]";
	}


}
