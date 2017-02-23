package aiclient;

import java.util.Map;

import mathUtils.Direction;
import mathUtils.MathUtils;
import mathUtils.Vector2;
import world.Character;
import world.Team;
import world.World;
import world.World.MapEntity;

public class SamAI extends AI{

	World world = World.getInstance();
    Team otherTeam = null;
    Character oponent1 = null;
    Character oponent2 = null;
    Character tank1 = null;
    Character tank2 = null;
    Vector2 oponentLastPosition1 = null;
    Vector2 oponentLastPosition2 = null;
    boolean firstTick = true;
    
	public void setNames() {
		String teamName = "Java Team";
		String[] characternames = {"WALL-E", "Eve"};
		world.setNames(teamName, characternames);
	}
	
	public void init() {
	    otherTeam = world.getOpponentTeam();
	    oponent1 = otherTeam.getFirstCharacter();
	    oponent2 = otherTeam.getSecondCharacter();
	    tank1 = world.getMyTeam().getFirstCharacter();
	    tank2 = world.getMyTeam().getSecondCharacter();
	    oponentLastPosition1 = null;
	    oponentLastPosition2 = null;
	    firstTick = false;
	}
	
	public void tick() {
		if(firstTick) {
			init();
		}
		
		if(isAttackable(tank1.getPosition(), oponent1.getPosition()) && tank1.isAlive() && oponent1.isAlive()) {
			try {
				Direction targetDir = MathUtils.getDirectionFromPositions(tank1.getPosition(), oponent1.getPosition());
				tank1.shootMissile(targetDir);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		else if(!oponent1.getPosition().equals(oponentLastPosition1)){
			tank1.move(oponent1.getPosition());
			oponentLastPosition1 = new Vector2(oponent1.getPosition());
		}
		
		if(isAttackable(tank2.getPosition(), oponent2.getPosition()) && tank2.isAlive() && oponent2.isAlive()) {
			try {
				Direction targetDir = MathUtils.getDirectionFromPositions(tank2.getPosition(), oponent2.getPosition());
				tank2.shootMissile(targetDir);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		else if(!oponent2.getPosition().equals(oponentLastPosition2)){
			tank2.move(oponent2.getPosition());
			oponentLastPosition2 = new Vector2(oponent2.getPosition());
		}
	}
	
	public boolean isAttackable(Vector2 fromposition, Vector2 toposition) {
		boolean result = fromposition.x == toposition.x || fromposition.y == toposition.y;
		if(result) {
			try {
				Map<Vector2, MapEntity> myMap = world.whatIsInTheWay(fromposition, MathUtils.getDirectionVector(fromposition, toposition));
				result = myMap.size() == 0;
			} catch (Exception e) {
				e.printStackTrace();
				result = false;
			}
		}
		
		return result;
	}
}
