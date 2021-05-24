package com.gamingroom;

/**
 * Application start-up program
 * 
 * @author coce@snhu.edu
 */
public class ProgramDriver {
	
	/**
	 * The one-and-only main() method
	 * 
	 * @param args command line arguments
	 */
	public static void main(String[] args) {
		
		// FIXME: obtain reference to the singleton instance
		GameService service = GameService.getInstance(); // replace null with ???
		
		System.out.println("\nAbout to test initializing game data...");
		
		// initialize with some game data
		Game game1 = service.addGame("Game #1");
		Game game2 = service.addGame("Game #2");

		Team team1 = game1.addTeam("Team #1");
		team1.addPlayer("Player #1");


		team1 = game2.addTeam("Team #1");
		team1.addPlayer("Player #1");
		team1.addPlayer("Player #2");


		game2.addTeam("Team #2");

		for (int i = 0; i < service.getGameCount(); i++) {
			System.out.println();
			Game g = service.getGame(i);
			System.out.println(g);
			for(Team t : g.teams){
				System.out.println("\t"+t);
				for(Player p : t.players){
					System.out.println("\t\t"+p);
				}
			}
		}
		
		// use another class to prove there is only one instance
		SingletonTester tester = new SingletonTester();
		tester.testSingleton();
	}
}
