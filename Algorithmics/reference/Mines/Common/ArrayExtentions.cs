using System;

namespace Common
{
    public static class ArrayExtentions
    {
        #region Methods

        public static void InitializeWithValue(this int[,] array, int value)
        {
            for (var i = 0; i < array.GetLength(0); i++)
            {
                for (var j = 0; j < array.GetLength(1); j++)
                {
                    array[i, j] = value;
                }
            }
        }

        public static int[] Copy(this int[] array)
        {
            var copy = new int[array.Length];
            Array.Copy(array, copy, array.Length);
            return copy;
        }

        #endregion
    }
}