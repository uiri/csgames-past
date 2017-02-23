using System;
using System.IO;
using System.Linq;
using System.Reflection;

using Common;

using Microsoft.VisualStudio.TestTools.UnitTesting;

using Mines;

namespace Test
{
    [TestClass]
    public class UnitTest1
    {
        #region Properties

        public static string GetTestFilesDirectory
        {
            get
            {
                return Path.Combine(Path.GetDirectoryName(new Uri(Assembly.GetExecutingAssembly().CodeBase).LocalPath), "TestFiles");
            }
        }

        #endregion

        #region Test Methods

        [TestMethod]
        public void Test1()
        {
            var testMine = new[] { 2, 3, 6 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("1", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test2()
        {
            var testMine = new[] { 6, 6, 3, 2 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("11", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test3()
        {
            var testMine = new[] { 1, 4, 7 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("2", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test4()
        {
            var testMine = new[] { 1, 3, 3, 4, 8 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("3", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test5()
        {
            var testMine = new[] { 1, 2, 3, 4 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("0", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test6()
        {
            var testMine = new[] { 4, 3, 2, 1 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("8", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test7()
        {
            var testMine = new[] { 1, 4, 8, 9 };
            var slope = 2;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("4", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test8()
        {
            var testMine = new[] { 4, 9, 5, 15, 12, 13, 14, 18, 20, 19, 25, 30 };
            var slope = 4;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("12", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void Test9()
        {
            var testMine = new[] { 0, 1000 };
            var slope = 1;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("999", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void WhenDataComeFromFileItShouldWork()
        {
            var testfile1 = Path.Combine(GetTestFilesDirectory, "test1.txt");

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                using (TextReader textReader = File.OpenText(testfile1))
                {
                    Console.SetIn(textReader);
                    var inputs = IOUtilities.ReadInput();

                    var solver = new Solver(inputs);
                    var answers = solver.Solve();

                    var minimumCosts = answers.Select(x => x.MinimumCost);

                    var expected = string.Join("\n", new[] { 1, 11, 2, 3, 0, 8, 4, 12 });

                    Assert.AreEqual<string>(expected, string.Join("\n", minimumCosts));
                }
            }
        }

        [TestMethod]
        public void WhenMineAlreadyValidCostMustBeZero()
        {
            var testMine = new[] { 31, 33, 36, 38, 40 };
            var slope = 12;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("0", answer.MinimumCost.ToInvariantString());
        }

        [TestMethod]
        public void WhenMineIsOneLenghtLongItIsAlreadyValidCostMustBeZero()
        {
            var testMine = new[] { 30 };
            var slope = 12;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            Assert.AreEqual<string>("0", answer.MinimumCost.ToString());
        }

        [TestMethod]
        public void WhenOnlyZeros()
        {
            var testMine = new[] { 0, 0, 0, 0, 0 };
            var slope = 1;

            var mineSolver = new MineSolver(testMine, slope);
            var answer = mineSolver.SolveMine();

            var expectedResult = new[] { 0, 1, 2, 3, 4 };
            CollectionAssert.AreEqual(expectedResult, answer.ValidMine);
            Assert.AreEqual<string>("10", answer.MinimumCost.ToInvariantString());
        }

        #endregion
    }
}