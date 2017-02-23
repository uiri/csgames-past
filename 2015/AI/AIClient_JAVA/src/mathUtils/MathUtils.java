package mathUtils;

/**
 * This class contains static methods used in order to build your AI
 */
public class MathUtils {
	/**
	 * Takes two vector representing positions and turns them into a direction
	 * vector
	 * 
	 * @param fromPosition
	 * @param toPosition
	 * @return Vector2
	 */
	public static Vector2 getDirectionVector(Vector2 fromPosition,
			Vector2 toPosition) {
		return new Vector2(toPosition.x - fromPosition.x, toPosition.y
				- fromPosition.y);
	}

	/**
	 * Takes two vector representing positions and turns them into a direction
	 * instruction
	 * 
	 * @param fromPosition
	 * @param toPosition
	 * @return
	 * @throws Exception
	 */
	public static Direction getDirectionFromPositions(Vector2 fromPosition,
			Vector2 toPosition) throws Exception {
		return MathUtils.getDirection(MathUtils.getDirectionVector(
				fromPosition, toPosition));
	}

	/**
	 * Takes a direction vector and turn it into a Direction Enum case.
	 * 
	 * @param direction
	 *            A direction vector
	 * @return MathUtils.Direction
	 * @throws Exception
	 */
	public static Direction getDirection(Vector2 direction) throws Exception {
		if ((direction.x != 0 && direction.y != 0)
				|| (direction.x == 0 && direction.y == 0))
			throw new Exception(
					"No direction found, you must be trying to hit a diagonal or yourself");
		if (direction.y == 0) {
			if (direction.x < 0) {
				return Direction.LEFT;
			} else {
				return Direction.RIGHT;
			}
		}
		if (direction.x == 0) {
			if (direction.y > 0) {
				return Direction.UP;
			} else {
				return Direction.DOWN;
			}
		}
		return null;
	}
}
