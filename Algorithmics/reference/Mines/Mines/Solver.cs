using System;
using System.Collections.Generic;
using System.Linq;

using Common;

namespace Mines
{
    public class Solver
    {
        #region Fields

        private readonly List<string> inputLines;

        #endregion

        #region Constructors

        public Solver(List<string> inputLines)
        {
            this.inputLines = inputLines;
        }

        #endregion

        #region Methods

        public static void Main(string[] args)
        {
            var inputs = IOUtilities.ReadInput();
            var solver = new Solver(inputs);

            var anwserList = solver.Solve();
            IOUtilities.WriteOutput(string.Join("\n", anwserList.Select(x => x.MinimumCost)));
        }

        public IList<MineSolver.MineSolverResult> Solve()
        {
            this.inputLines.Reverse();
            var inputStack = new Stack<string>(this.inputLines);

            var caseCount = Convert.ToInt32(inputStack.Pop());

            var answerList = new List<MineSolver.MineSolverResult>();

            for (var i = 0; i < caseCount; i++)
            {
                var maxAltitudeDistanceBetweenPoints = int.Parse(inputStack.Pop());
                var mine = Array.ConvertAll(inputStack.Pop().Split(' '), int.Parse);

                var mineSolver = new MineSolver(mine, maxAltitudeDistanceBetweenPoints);

                var answer = mineSolver.SolveMine();
                answerList.Add(answer);
            }

            return answerList;
        }

        #endregion
    }
}