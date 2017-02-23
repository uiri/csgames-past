using System;

using Pixels;

namespace Visualizer
{
    public class PixelVisualizer
    {
        #region Methods

        public static void Main(string[] args)
        {
            var solvers = PixelSolver.InputToSolvers();
            foreach (var pixelSolver in solvers)
            {
                var result = pixelSolver.Solve();
                PrintMergedBoardAndPatternMatch(result);
            }
        }

        private static void PrintMergedBoardAndPatternMatch(PixelSolver.Result result)
        {
            var spaceForABoard = result.Board.GetLength(1) * 2;
            var stringFormat = string.Concat("{0,-", spaceForABoard, "}\t{1,-", spaceForABoard, "}\t{2,-", spaceForABoard, "}");
            Console.WriteLine("\n--Match possible--");
            Console.WriteLine(stringFormat, "Board", "Pattern", "Merged");

            for (var i = 0; i < result.Board.GetLength(0); i++)
            {
                for (var j = 0; j < result.Board.GetLength(1); j++)
                {
                    if (result.Board[i, j] == 0)
                    {
                        Console.BackgroundColor = ConsoleColor.DarkGreen;
                    }

                    Console.Write("{0, 2}", result.Board[i, j]);
                    Console.ResetColor();
                }

                Console.Write("\t");

                for (var j = 0; j < result.Pattern.GetLength(1); j++)
                {
                    if (result.Pattern[i, j] == 1)
                    {
                        Console.BackgroundColor = ConsoleColor.DarkYellow;
                    }

                    Console.Write("{0, 2}", result.Pattern[i, j]);
                    Console.ResetColor();
                }

                Console.Write("\t");

                for (var j = 0; j < result.MatchedBoard.GetLength(1); j++)
                {
                    if (result.MatchedBoard[i, j] == 1)
                    {
                        Console.BackgroundColor = ConsoleColor.Blue;
                    }
                    else if (result.MatchedBoard[i, j] == -1)
                    {
                        Console.BackgroundColor = ConsoleColor.Red;
                    }

                    Console.Write("{0, 2}", result.MatchedBoard[i, j]);
                    Console.ResetColor();
                }

                Console.WriteLine();
            }

            Console.WriteLine();
        }

        #endregion
    }
}