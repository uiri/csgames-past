from unittest import TestCase
from mathUtils.Vector2 import Vector2
from mathUtils.MathUtils import MathUtils
from mathUtils.Direction import Direction


class TestMathUtils(TestCase):
    def test_getDirectionVector(self):
        a = Vector2(1, 1)
        b = Vector2(7, 7)
        self.assertEqual(Vector2(6, 6), MathUtils.getDirectionVector(a, b))

    def test_getDirectionFromPositions(self):
        a = Vector2(0, 7)
        b = Vector2(7, 7)
        self.assertEqual(Direction.RIGHT, MathUtils.getDirectionFromPositions(a, b))

    def test_getDirection(self):
        self.assertEqual(Direction.RIGHT, MathUtils.getDirection(Vector2(2, 0)))
        self.assertEqual(Direction.LEFT, MathUtils.getDirection(Vector2(-2, 0)))
        self.assertEqual(Direction.UP, MathUtils.getDirection(Vector2(0, 2)))
        self.assertEqual(Direction.DOWN, MathUtils.getDirection(Vector2(0, -2)))
        self.assertRaises(Exception, MathUtils.getDirection, (Vector2(2, 2)))
        self.assertRaises(Exception, MathUtils.getDirection, (Vector2(-2, -2)))
        self.assertRaises(Exception, MathUtils.getDirection, (Vector2(0, 0)))
