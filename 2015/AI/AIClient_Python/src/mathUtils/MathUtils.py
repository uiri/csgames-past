from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction


class MathUtils():
    """ This class contains static methods used in order to build your AI """

    @staticmethod
    def getDirectionVector(fromPosition: Vector2, toPosition: Vector2) -> Vector2:
        """
        Takes two vector representing positions and turns them into a direction vector
        :type fromPosition: Vector2
        :type toPosition: Vector2
        :rtype: Vector2
        """
        return Vector2(toPosition.x - fromPosition.x, toPosition.y - fromPosition.y)

    @staticmethod
    def getDirectionFromPositions(fromPosition: Vector2, toPosition: Vector2) -> Direction:
        """
        Takes two vector representing positions and turns them into a direction instruction
        :type fromPosition: Vector2
        :type toPosition: Vector2
        :rtype: Direction
        """
        return MathUtils.getDirection(MathUtils.getDirectionVector(fromPosition, toPosition))

    @staticmethod
    def getDirection(direction: Vector2) -> Direction:
        """
        Takes a direction vector and turn it into a Direction Enum case.
        :param direction:
        :rtype: Direction
        """
        if (direction.x != 0 and direction.y != 0) or (direction.x == 0 and direction.y == 0):
            raise Exception("No direction found, you must be trying to hit a diagonal")
        if direction.y == 0:
            if direction.x < 0:
                return Direction.LEFT
            else:
                return Direction.RIGHT
        if direction.x == 0:
            if direction.y > 0:
                return Direction.UP
            else:
                return Direction.DOWN
