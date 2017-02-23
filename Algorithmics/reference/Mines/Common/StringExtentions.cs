using System;
using System.Globalization;

namespace Common
{
    public static class StringExtentions
    {
        #region Methods

        public static string ToInvariantString(this string value)
        {
            return value.ToString(CultureInfo.InvariantCulture);
        }

        public static string ToInvariantString(this int value)
        {
            return value.ToString(CultureInfo.InvariantCulture);
        }

        #endregion
    }
}