using System;
using System.Collections.Generic;

using Common;

namespace MineGenerator
{
    public class Generator
    {
        #region Fields

        private static readonly Random Rdm = new Random();

        private readonly int MineCount;

        private readonly int minSlope;

        private readonly int maxSlope;

        private readonly int minLow;

        private readonly int maxHeigth;

        #endregion

        #region Constructors

        public Generator(int mineCount, int minLow, int maxHeigth, int minSlope, int maxSlope)
        {
            this.MineCount = mineCount;
            this.minLow = minLow;
            this.maxHeigth = maxHeigth;
            this.minSlope = minSlope;
            this.maxSlope = maxSlope;
        }

        #endregion

        #region Methods

        public static void Main(string[] args)
        {
            var gen = new Generator(
                int.Parse(args[0]),
                int.Parse(args[1]),
                int.Parse(args[2]),
                int.Parse(args[3]),
                int.Parse(args[4]));

            gen.CreateMontains();
        }

        private static IEnumerable<int> GenerateRdmArray(int slope, int n, int max)
        {
            var array = new int[n];

            for (int i = 0; i < array.Length; i++)
            {
                var minY = i - slope;
                var maxY = (int)((i + slope) * 1.5);

                if (minY < 0)
                {
                    minY = 0;
                }

                array[i] = Rdm.Next(minY, maxY);
            }

            /* var retry = false;
             var array = new int[n];
             for (var i = 1; i <= array.Length; i++)
             {
                 var maxY = Math.Abs(max - (max * (i / array.Length))) + 1;
                 if (i > 1)
                 {
                     var lastPoint = array[i - 2];
                     maxY = max - (lastPoint - (slope * (i / array.Length)));
                 }

                 if (maxY <= 0)
                 {
                     retry = true;
                     break;
                 }

                 if (i == array.Length)
                 {
                     maxY = Math.Abs(max - (max * ((i - 1) / array.Length)));
                 }

                 var minY = maxY - slope;
                 minY = (minY < 0) ? 0 : minY;

                 // var minY = (maxY - i ) < 0 ? 0 : (maxY - i);
                 array[i - 1] = Rdm.Next(0, maxY);
             }

             if (retry)
             {
                return GenerateRdmArray(slope, n, max);
             }


             Array.Reverse(array);*/

            return array;
        }

        private void CreateMontains()
        {
            var rdm = new Random();
            var outputs = new List<string>();
            outputs.Add(this.MineCount.ToInvariantString());
            for (var i = 0; i < this.MineCount; i++)
            {
                var slope = rdm.Next(this.minSlope, this.maxSlope);
                var mineLenght = rdm.Next(this.minLow, this.maxHeigth);

                // var montainTopIndex = rdm.Next(Convert.ToInt32(montainLength * 0.2), Convert.ToInt32(montainLength - (montainLength * 0.2)));
                var montain = GenerateRdmArray(slope, mineLenght, this.maxHeigth);

                // montain[montainTopIndex] = montainTop;
                outputs.Add(slope.ToInvariantString());
                outputs.Add(string.Join(" ", montain));
            }

            IOUtilities.WriteOutput(string.Join("\n", outputs));
        }

        #endregion
    }
}