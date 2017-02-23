using System;
using System.Collections.Generic;
using System.Linq;

using Common;

namespace Mines
{
    public class MineSolver
    {
        #region Fields

        private const int Maxvalue = 999999;
        private readonly int highestPointPossible;
        private readonly int[] imperialMine;
        private readonly int maxAltitudeDistanceBetweenPoints;
        private readonly int[,] memo;

        // this Matrix is just used for the visualisation of the solution found
        private readonly Point[,] bestHeightMineMatrix;

        #endregion

        #region Constructors

        public MineSolver(int[] imperialMine, int maxAltitudeDistanceBetweenPoints)
        {
            var maxMineValue = imperialMine.Max() == 0 ? imperialMine.Length : imperialMine.Max();
            this.highestPointPossible = maxMineValue + maxAltitudeDistanceBetweenPoints;

            this.memo = new int[imperialMine.Length, this.highestPointPossible + 1];
            this.memo.InitializeWithValue(-1);

            this.bestHeightMineMatrix = new Point[imperialMine.Length, this.highestPointPossible + 1];

            this.imperialMine = imperialMine;
            this.maxAltitudeDistanceBetweenPoints = maxAltitudeDistanceBetweenPoints;
        }

        #endregion

        #region Methods

        public MineSolverResult SolveMine()
        {
            var bestHeightForLastPoint = int.MaxValue;
            var minimumCost = int.MaxValue;

            for (var i = 0; i <= this.highestPointPossible; i++)
            {
                var costForHeight = this.Cost(this.imperialMine.Length - 1, i);

                if (costForHeight < minimumCost)
                {
                    minimumCost = costForHeight;
                    bestHeightForLastPoint = i;
                }
            }

            return new MineSolverResult
            {
                MinimumCost = minimumCost,
                ValidMine = this.ResolveBestMineFound(bestHeightForLastPoint).Copy(),
                BeforeMine = this.imperialMine.Copy(),
                MaxDistanceBetweenTwoPoint = this.maxAltitudeDistanceBetweenPoints
            };
        }

        private int[] ResolveBestMineFound(int lastPointBestHeight)
        {
            var cur = this.bestHeightMineMatrix[this.imperialMine.Length - 1, lastPointBestHeight];
            var validMontain = new int[this.imperialMine.Length];

            var stack = new Stack<int>();
            stack.Push(lastPointBestHeight);
            var index = this.imperialMine.Length - 1;
            validMontain[index] = lastPointBestHeight;
            while (cur.x != -1)
            {
                index--;
                validMontain[index] = cur.y;
                stack.Push(cur.y);
                cur = this.bestHeightMineMatrix[cur.x, cur.y];
            }

            return validMontain;
        }

        private int Cost(int index, int height)
        {
            if (index < 0)
            {
                return 0;
            }

            // only the first index can be 0
            if (height == 0 && index > 0)
            {
                return Maxvalue;
            }

            if (this.memo[index, height] != -1)
            {
                return this.memo[index, height];
            }

            var ret = Maxvalue;
            var costToSetHeight = Math.Abs(this.imperialMine[index] - height);

            if (height == 0)
            {
                this.memo[index, height] = this.Cost(index - 1, height) + costToSetHeight;
                this.bestHeightMineMatrix[index, height] = new Point(index - 1, height);

                return this.memo[index, height];
            }

            for (var i = 1; i <= this.maxAltitudeDistanceBetweenPoints && height - i >= 0; i++)
            {
                var cost = this.Cost(index - 1, height - i) + costToSetHeight;
                if (cost < ret)
                {
                    this.bestHeightMineMatrix[index, height] = new Point(index - 1, height - i);
                    ret = cost;
                }
            }

            this.memo[index, height] = ret;

            return this.memo[index, height];
        }

        #endregion

        #region Nested Types

        private struct Point
        {
            #region Fields

            public readonly int x;
            public readonly int y;

            #endregion

            #region Constructors

            public Point(int x, int y)
                : this()
            {
                this.x = x;
                this.y = y;
            }

            #endregion
        }

        public sealed class MineSolverResult
        {
            #region Properties

            public int MaxDistanceBetweenTwoPoint { get; set; }

            public int MinimumCost { get; set; }

            public int[] ValidMine { get; set; }

            public int[] BeforeMine { get; set; }

            #endregion
        }

        #endregion
    }
}