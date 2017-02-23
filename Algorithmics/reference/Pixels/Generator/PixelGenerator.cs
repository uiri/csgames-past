using System;
using System.Collections.Generic;
using System.Text;

using Common;

namespace Generator
{
    public class PixelGenerator
    {
        #region Fields

        private readonly int _numberOfBoards;
        private readonly int _size;
        private readonly Random _rdm;

        #endregion

        #region Constructors

        public PixelGenerator(int numberOfBoards, int size)
        {
            this._size = size;
            this._numberOfBoards = numberOfBoards;
            this._rdm = new Random();
        }

        #endregion

        #region Methods

        public static void GenerateBoard(int numberOfBoard, int size)
        {
            var outputs = new List<string>();
            outputs.Add(numberOfBoard.ToString());

            var rdm = new Random();
            for (var i = 0; i < numberOfBoard; i++)
            {
                var rowSize = rdm.Next(size / 2, size);
                var colSize = rdm.Next(size / 2, size);
                outputs.Add(rowSize + " " + colSize);

                for (var x = 0; x < rowSize; x++)
                {
                    var line = new int[colSize];
                    for (var y = 0; y < colSize; y++)
                    {
                        line[y] = rdm.Next(0, 8) >= 1 ? 0 : -1;
                    }

                    outputs.Add(string.Join(",", line));
                }

                outputs.Add(string.Empty);
                for (var x = 0; x < rowSize; x++)
                {
                    var line = new int[colSize];
                    for (var y = 0; y < colSize; y++)
                    {
                        line[y] = rdm.Next(0, size) >= 1 ? 0 : 1;
                    }

                    outputs.Add(string.Join(",", line));
                }

                outputs.Add(string.Empty);
            }

            IOUtilities.WriteOutput(string.Join("\n", outputs));
        }

        public static void Main(string[] args)
        {
            var generator = new PixelGenerator(
                int.Parse(args[0]),
                int.Parse(args[1]));

            var boards = generator.GenerateBoards();
            var outputs = new List<string>();

            outputs.Add(boards.Count.ToInvariantString());
            foreach (var boardAndPattern in boards)
            {
                outputs.Add(boardAndPattern.ToString());
            }

            IOUtilities.WriteOutput(string.Join("\n", outputs));
        }

        public List<BoardAndPattern> GenerateBoards()
        {
            var boards = new List<BoardAndPattern>();

            for (var i = 0; i < this._numberOfBoards; i++)
            {
                var rowSize = this._rdm.Next(this._size / 2, this._size);
                var colSize = this._rdm.Next(this._size / 2, this._size);

                var boardAndPattern = this.GenerateBoardAndPattern(rowSize, colSize);

                boards.Add(boardAndPattern);
            }

            return boards;
        }

        public BoardAndPattern GenerateBoardAndPattern(int rowSize, int colSize)
        {
            var board = new int[rowSize, colSize];
            var pattern = new int[rowSize, colSize];

            for (var x = 0; x < rowSize; x++)
            {
                for (var y = 0; y < colSize; y++)
                {
                    board[x, y] = this._rdm.Next(0, 8) >= 1 ? 0 : -1;
                }
            }

            for (var x = 0; x < rowSize; x++)
            {
                for (var y = 0; y < colSize; y++)
                {
                    pattern[x, y] = this._rdm.Next(0, rowSize) >= 1 ? 0 : 1;
                }
            }

            return new BoardAndPattern(board, pattern);
        }

        #endregion

        #region Nested Types

        public sealed class BoardAndPattern
        {
            #region Constructors

            public BoardAndPattern(int[,] board, int[,] pattern)
            {
                this.Board = board;
                this.Pattern = pattern;

                this.RowSize = this.Board.GetLength(0);
                this.ColSize = this.Board.GetLength(1);
            }

            #endregion

            #region Properties

            public int RowSize { get; set; }

            public int ColSize { get; set; }

            public int[,] Board { get; set; }

            public int[,] Pattern { get; set; }

            #endregion

            #region Methods

            public override string ToString()
            {
                var builder = new StringBuilder();
                builder.AppendLine(string.Concat(this.RowSize, " ", this.ColSize));

                for (var i = 0; i < this.RowSize; i++)
                {
                    var row = new List<int>();
                    for (var j = 0; j < this.ColSize; j++)
                    {
                        row.Add(this.Board[i, j]);
                    }

                    builder.AppendLine(string.Join(",", row));
                }

                builder.AppendLine(" ");

                for (var i = 0; i < this.RowSize; i++)
                {
                    var row = new List<int>();
                    for (var j = 0; j < this.ColSize; j++)
                    {
                        row.Add(this.Pattern[i, j]);
                    }

                    builder.AppendLine(string.Join(",", row));
                }

                return builder.ToString();
            }

            #endregion
        }

        #endregion
    }
}