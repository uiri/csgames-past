using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

using Microsoft.VisualStudio.TestTools.UnitTesting;

using Pixels;

namespace Test
{
    [TestClass]
    public class UnitTest1
    {
        #region Test Methods

        [TestMethod]
        public void TestSolverExempleCase1()
        {
            var exemple1 =
                "1\n" +
                "5 5\n" +
                "0,0,0,0,0\n" +
                "0,0,0,0,-1\n" +
                "0,0,0,0,-1\n" +
                "0,0,0,-1,-1\n" +
                "0,0,0,0,0\n" +
                " \n" +
                "1,1,1,1,0\n" +
                "0,0,0,0,1\n" +
                "0,0,0,0,0\n" +
                "0,1,0,0,0\n" +
                "0,0,0,0,0";

            Console.SetIn(new StringReader(exemple1));
            var solvers = PixelSolver.InputToSolvers();
            var answer = solvers.First().Solve().Anwser;

            Assert.IsTrue(answer);
        }

        [TestMethod]
        public void TestSolverExempleCase2()
        {
            var exemple2 =
                "1\n" +
                "5 5\n" +
                "0,0,0,-1,0\n" +
                "0,0,0,-1,0\n" +
                "0,0,0,0,-1\n" +
                "0,0,0,-1,0\n" +
                "0,-1,-1,-1,-1\n" +
                " \n" +
                "0,0,0,1,0\n" +
                "0,0,0,0,1\n" +
                "0,0,0,0,0\n" +
                "1,0,0,0,1\n" +
                "1,0,0,0,1";

            Console.SetIn(new StringReader(exemple2));
            var solvers = PixelSolver.InputToSolvers();
            var answer = solvers.First().Solve().Anwser;

            Assert.IsFalse(answer);
        }

        [TestMethod]
        public void TestData1()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data1.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data1.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        [TestMethod]
        public void TestData2()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data2.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data2.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        [TestMethod]
        public void TestData3()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data3.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data3.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        [TestMethod]
        public void TestData4()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data4.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data4.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        [TestMethod]
        public void TestData5()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data5.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data5.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        [TestMethod]
        public void TestData6()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var solutionStream = new StreamReader(assembly.GetManifestResourceStream("Test.Solutions.data6.txt")))
            {
                using (var testStream = assembly.GetManifestResourceStream("Test.Tests.data6.txt"))
                {
                    var solutions = new List<string>();

                    string line;
                    while ((line = solutionStream.ReadLine()) != null)
                    {
                        solutions.Add(line);
                    }

                    Console.SetIn(new StreamReader(testStream));
                    var solvers = PixelSolver.InputToSolvers();
                    var anwsers = solvers.Select(x => x.Solve().Anwser.ToString()).ToList();

                    CollectionAssert.AreEqual(solutions, anwsers);
                }
            }
        }

        #endregion

        #region Methods

        public static void CopyStream(Stream input, Stream output)
        {
            var buffer = new byte[16 * 1024];
            int read;
            while ((read = input.Read(buffer, 0, buffer.Length)) > 0)
            {
                output.Write(buffer, 0, read);
            }
        }

        #endregion
    }
}