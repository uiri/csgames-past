using System;
using System.Collections.Generic;
using System.Linq;

using Common;

namespace Pixels
{
    public struct Point
    {
        #region Fields

        public int X;
        public int Y;

        #endregion

        #region Constructors

        public Point(int x, int y)
        {
            this.X = x;
            this.Y = y;
        }

        #endregion
    }

    public class PixelSolver
    {
        #region Fields

        private const int PATTERN_PIXEL = 1;
        private const int DEATH_PIXEL = -1;

        private readonly int[,] board;
        private readonly int[,] pattern;
        private readonly int sizeX;
        private readonly int sizeY;

        #endregion

        #region Constructors

        public PixelSolver(int[,] board, int[,] pattern)
        {
            this.board = board;
            this.pattern = pattern;

            this.sizeX = board.GetLength(0);
            this.sizeY = board.GetLength(1);
        }

        #endregion

        #region Methods

        public static void Main(string[] args)
        {
            var solvers = InputToSolvers();

            IOUtilities.WriteOutput(string.Join("\n", solvers.Select(x => x.Solve().Anwser)));
        }

        public static IEnumerable<PixelSolver> InputToSolvers()
        {
            var solvers = new List<PixelSolver>();
            var inputs = IOUtilities.ReadInput();
            inputs.Reverse();
            var inputStack = new Stack<string>(inputs);
            var numberOfCases = int.Parse(inputStack.Pop());

            for (var i = 0; i < numberOfCases; i++)
            {
                var line = inputStack.Pop();
                var rowSize = int.Parse(line.Split(' ')[0]);
                var colSize = int.Parse(line.Split(' ')[1]);

                var board = new int[rowSize, colSize];
                var pattern = new int[rowSize, colSize];

                for (var x = 0; x < rowSize; x++)
                {
                    var splitedRow = Array.ConvertAll(inputStack.Pop().Split(','), int.Parse);
                    for (var y = 0; y < colSize; y++)
                    {
                        board[x, y] = splitedRow[y];
                    }
                }

                inputStack.Pop();

                for (var x = 0; x < rowSize; x++)
                {
                    var splitedRow = Array.ConvertAll(inputStack.Pop().Split(','), int.Parse);
                    for (var y = 0; y < colSize; y++)
                    {
                        pattern[x, y] = splitedRow[y];
                    }
                }

                if (inputStack.Count != 0)
                {
                    inputStack.Pop();
                }

                solvers.Add(new PixelSolver(board, pattern));
            }

            return solvers;
        }

        public Result Solve()
        {
            var answer = false;
            int[,] matchedBoard = new int[this.sizeX, this.sizeY];
            var firstPixel = FindFirstPatternPixel(this.pattern);

            if (!firstPixel.HasValue)
            {
                answer = true;
            }
            else
            {
                var currentPatternOrientation = this.pattern;
                for (var i = 0; i < 4; i++)
                {
                    if (this.TryMatchPattern(this.board, currentPatternOrientation, out matchedBoard))
                    {
                        answer = true;
                        break;
                    }

                    currentPatternOrientation = Rotate90DegreeRight(currentPatternOrientation);
                }
            }

            return new Result
            {
                Anwser = answer, 
                Board = this.board, 
                Pattern = this.pattern, 
                MatchedBoard = matchedBoard
            };
        }

        private static Point? FindFirstPatternPixel(int[,] pattern)
        {
            for (var row = 0; row < pattern.GetLength(0); row++)
            {
                for (var col = 0; col < pattern.GetLength(1); col++)
                {
                    if (pattern[row, col] == 1)
                    {
                        return new Point(row, col);
                    }
                }
            }

            return null;
        }

        /*
         * This will put the first pixel of the pattern board to 0,0 and translate all the other points
         * */
        private static IEnumerable<Point> MovePatternToOriginPoint(int[,] pattern, Point firstPixel)
        {
            for (var row = 0; row < pattern.GetLength(0); row++)
            {
                for (var col = 0; col < pattern.GetLength(1); col++)
                {
                    if (pattern[row, col] == 1)
                    {
                        var shiftPixel = new Point(row - firstPixel.X, col - firstPixel.Y);
                        yield return shiftPixel;
                    }
                }
            }
        }

        private static int[,] Rotate90DegreeRight(int[,] pattern)
        {
            var boardCopy = new int[pattern.GetLength(1), pattern.GetLength(0)];

            for (var x = 0; x < pattern.GetLength(0); x++)
            {
                for (var y = 0; y < pattern.GetLength(1); y++)
                {
                    var rotateX = y;
                    var rotateY = pattern.GetLength(0) - x - 1;
                    boardCopy[rotateX, rotateY] = pattern[x, y];
                }
            }

            return boardCopy;
        }

        private static bool CheckPatternFromPoint(int[,] board, IEnumerable<Point> shiftedPatternPoints, Point point)
        {
            foreach (var patternPoint in shiftedPatternPoints)
            {
                var x = patternPoint.X + point.X;
                var y = patternPoint.Y + point.Y;
                if (x < 0 || x >= board.GetLength(0) || y < 0 || y >= board.GetLength(1) || board[x, y] == -1)
                {
                    return false;
                }
            }

            return true;
        }

        private bool TryMatchPattern(int[,] board, int[,] pattern, out int[,] matchedBoard)
        {
            var firstPixel = FindFirstPatternPixel(pattern);
            matchedBoard = new int[this.sizeX, this.sizeY];

            var movedPatternToOriginPoint = MovePatternToOriginPoint(pattern, firstPixel.Value).ToList();

            for (var row = 0; row < this.sizeX; row++)
            {
                for (var col = 0; col < this.sizeY; col++)
                {
                    var pointToCheckPattern = new Point(row, col);
                    if (CheckPatternFromPoint(board, movedPatternToOriginPoint, pointToCheckPattern))
                    {
                        Buffer.BlockCopy(board, 0, matchedBoard, 0, board.Length * sizeof(int));

                        foreach (var i in movedPatternToOriginPoint)
                        {
                            var x = i.X + pointToCheckPattern.X;
                            var y = i.Y + pointToCheckPattern.Y;
                            matchedBoard[x, y] = PATTERN_PIXEL;
                        }

                        // PrintMergedBoardAndPatternMatch(board, pattern, shiftedPatternToOriginPoint, pointToCheckPattern, originalPattern);
                        return true;
                    }
                }
            }

            // PrintMergedBoardAndPatternMatch(board, pattern, shiftedPatternToOriginPoint, firstPixel.Value, originalPattern);
            return false;
        }

        #endregion

        #region Nested Types

        public sealed class Result
        {
            #region Properties

            public int[,] Board { get; set; }

            public int[,] Pattern { get; set; }

            public int[,] MatchedBoard { get; set; }

            public bool Anwser { get; set; }

            #endregion
        }

        #endregion
    }
}