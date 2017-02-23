/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** World.java
 ** The world
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import java.awt.Point;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import mathUtils.Vector2;

import event.AddPlayerEvent;
import event.QueueController;

/**
 * Class that contain all the informations about the Teams, Characters and Missiles
 */
public class World {

	/**
	 * An Enum that represent all the entity that can be found in the world
	 */
	public enum MapEntity {
		EMPTY, BOX, CHARACTER, MISSILE
	}

	private static World instance = null;
	private int yourId;
	private boolean gameIsStarted = false;
	private boolean gameIsFinished = false;
	private boolean map[][] = null;
	private String teamName = "No name";
	private String[] characterNames = {"No name", "No name"};

	/**
	 * List of all the teams
	 */
	private List<Team> teams = new ArrayList<Team>();
	
	/*
	 * THIS SECTION IS OUT OF ACCESS
	 */
	protected World() {
		// Exists only to defeat instantiation
	}

	public static World getInstance() {
		if (instance == null) {
			instance = new World();
		}
		return instance;
	}

	public void setNames(String teamName, String[] characterNames) {
		this.teamName = teamName;
		this.characterNames = characterNames;
	}

	public void error(String message) {
		System.out.println(message);
	}

	public void joinGame(int id) {
		yourId = id;
		System.out.println("Join game with id:" + yourId);

		AddPlayerEvent event = new AddPlayerEvent(teamName, characterNames);
		QueueController.getInstance().addOutgoingEvent(event);
	}

	public void sendGameInfos(int mapWidth, int mapHeight, int numberOfTeam,
			int numberOfCharacter, List<Integer> teamIDs) {
		System.out.println("Get game infos");
		map = new boolean[mapWidth][mapHeight];
		for (int index = 0; index < numberOfTeam; ++index) {
			teams.add(new Team(teamIDs.get(index), numberOfCharacter));
		}
	}

	public void startGame() {
		System.out.println("Start game");
		gameIsStarted = true;
	}

	public void updateBox(Point position) {
		map[position.x][position.y] = true;
	}
	
	public void endGame() {
		System.out.println("End game");
		gameIsFinished = true;
	}
	
	public boolean isGameIsStarted() {
		return gameIsStarted;
	}

	public boolean isGameIsFinished() {
		return gameIsFinished;
	}
	/*
	 * OUT OF ACCESS
	 */
	
	/**
	 * Return the team associate with a certain id
	 * Important : the id of the team are not starting at 0
	 * 
	 * @param id the id of the team we want
	 * @return the team or null if not found
	 */
	public Team getTeam(int id) {
		for (Iterator<Team> iterator = teams.iterator(); iterator.hasNext();) {
			Team team = iterator.next();
			if (team.getId() == id) {
				return team;
			}
		}
		return null;
	}

	/**
	 * Return the team associate with your id
	 * 
	 * @return your team
	 */
	public Team getOpponentTeam() {
		for (Iterator<Team> iterator = teams.iterator(); iterator.hasNext();) {
			Team team = iterator.next();
			if (team.getId() != yourId) {
				return team;
			}
		}
		return null;
	}

	/**
	 * Return the team associate with your id
	 * 
	 * @return your team
	 */
	public Team getMyTeam() {
		return getTeam(yourId);
	}

	/**
	 * Check if there's a box at a certain position
	 * 
	 * @param position the position to check
	 * @return True if there's a box, else False
	 */
	public boolean isBoxAtPosition(Point position) {
		return map[position.x][position.y];
	}

	/**
	 * check if there's a character at a certain position
	 * 
	 * @param position the position to check
	 * @return True if there's a character, else False
	 */
	public boolean isCharacterAtposition(Point position) {
		for (Iterator<Team> teamIterator = teams.iterator(); teamIterator
				.hasNext();) {
			Team team = teamIterator.next();

			for (Iterator<Character> characterIterator = team.getCharacters()
					.iterator(); characterIterator.hasNext();) {
				Character character = characterIterator.next();
				if (character.getPosition().equals(position)) {
					return true;
				}
			}
		}
		return false;
	}
	
	/**
	 * check if there's a missile at a certain position
	 * 
	 * @param position the position to check
	 * @return True if there's a missile, else False
	 */
	public boolean isMissileAtPosition(Point position) {
		for (Iterator<Team> teamIterator = teams.iterator(); teamIterator
				.hasNext();) {
			Team team = teamIterator.next();

			for (Iterator<Character> characterIterator = team.getCharacters()
					.iterator(); characterIterator.hasNext();) {
				Character character = characterIterator.next();
				if (character.getMissile().getPosition().equals(position) && character.getMissile().isReady() == false) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Return the Entity at a certain position
	 * 
	 * @param position the position to check
	 * @return the entity that is on the specify position
	 */
	public MapEntity whatIsAtPosition(Point position) {
		if (isBoxAtPosition(position)) {
			return MapEntity.BOX;
		} else if (isCharacterAtposition(position)) {
			return MapEntity.CHARACTER;
		} else if (isMissileAtPosition(position)) {
			return MapEntity.MISSILE;
		}
		return MapEntity.EMPTY;
	}
	
	/**
	 * Return a MAP <[x,y],mapEntity> between a position and a direction
	 * @param origin
	 * @param direction
	 * @return
	 * @throws Exception
	 */
	public Map<Vector2, MapEntity> whatIsInTheWay(Vector2 origin, Vector2 direction) throws Exception{
		Map<Vector2, MapEntity> map = new HashMap<Vector2, MapEntity>();
		float length = (float) Math.sqrt(Math.pow(direction.x, 2) + Math.pow(direction.y, 2));
		if(length==0f) return map;
		Vector2 unitDirection = new Vector2((int)(direction.x/length),(int)(direction.y/length));
		if (Math.sqrt(Math.pow(unitDirection.x, 2) + Math.pow(unitDirection.y, 2))!= 1){
			throw new Exception("impossible path");
		}
		for (int i=1; i<(int)length;++i){
			Vector2 currentPosition = new Vector2(origin.x + unitDirection.x * i, origin.y + unitDirection.y * i);
			MapEntity objectAtPosition = this.whatIsAtPosition(currentPosition);
			if(objectAtPosition != MapEntity.EMPTY){
				map.put(currentPosition, objectAtPosition);
			}
		}
		return map;
	}
}
