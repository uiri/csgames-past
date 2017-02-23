#include "stdafx.h"
#include "CppUnitTest.h"

#include "Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{		
	TEST_CLASS(PathFindingTest)
	{
	public:
		
		TEST_METHOD(NoBox1)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(0,0);
			Vector2 targetPosition(8,0);
			Vector2 subStep(1,0);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(NoBox2)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(0,0);
			Vector2 targetPosition(0,8);
			Vector2 subStep(0,1);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(NoBox3)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(8,8);
			Vector2 targetPosition(8,0);
			Vector2 subStep(8,7);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(NoBox4)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(8,8);
			Vector2 targetPosition(0,8);
			Vector2 subStep(7,8);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(WithBox1)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(2,0);
			Vector2 targetPosition(8,0);
			Vector2 subStep(2,1);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(WithBox2)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(6,0);
			Vector2 targetPosition(0,0);
			Vector2 subStep(6,1);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(WithBox3)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(0,2);
			Vector2 targetPosition(0,8);
			Vector2 subStep(1,2);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(WithBox4)
		{
			Map& map = Map::getInstance();

			Vector2 startingPosition(0,6);
			Vector2 targetPosition(0,0);
			Vector2 subStep(1,6);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);
		}

		TEST_METHOD(WithTank1)
		{
			Map& map = Map::getInstance();

			Vector2 othertankPosition(7,2);

			map.setTile(othertankPosition, MapEntity::CHARACTER, 0, 0);

			Vector2 startingPosition(8,2);
			Vector2 lastPosition(8,1);
			Vector2 targetPosition(8,8);
			Vector2 subStep(8,1);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);

			map.setTile(othertankPosition, MapEntity::EMPTY, 0, 0);
		}

		TEST_METHOD(WithTank2)
		{
			Map& map = Map::getInstance();

			Vector2 othertankPosition(7,6);

			map.setTile(othertankPosition, MapEntity::CHARACTER, 0, 0);

			Vector2 startingPosition(8,6);
			Vector2 lastPosition(8,7);
			Vector2 targetPosition(8,0);
			Vector2 subStep(8,7);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);

			map.setTile(othertankPosition, MapEntity::EMPTY, 0, 0);
		}

		TEST_METHOD(WithTank3)
		{
			Map& map = Map::getInstance();

			Vector2 othertankPosition(2,1);

			map.setTile(othertankPosition, MapEntity::CHARACTER, 0, 0);

			Vector2 startingPosition(2,0);
			Vector2 lastPosition(1,0);
			Vector2 targetPosition(8,0);
			Vector2 subStep(1,0);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);

			map.setTile(othertankPosition, MapEntity::EMPTY, 0, 0);
		}

		TEST_METHOD(WithTank4)
		{
			Map& map = Map::getInstance();

			Vector2 othertankPosition(6,1);

			map.setTile(othertankPosition, MapEntity::CHARACTER, 0, 0);

			Vector2 startingPosition(6,0);
			Vector2 lastPosition(7,0);
			Vector2 targetPosition(0,0);
			Vector2 subStep(7,0);

			Assert::AreEqual(subStep.x, map.calculateNextStep(startingPosition, targetPosition, startingPosition).x);
			Assert::AreEqual(subStep.y, map.calculateNextStep(startingPosition, targetPosition, startingPosition).y);

			map.setTile(othertankPosition, MapEntity::EMPTY, 0, 0);
		}
	};
}