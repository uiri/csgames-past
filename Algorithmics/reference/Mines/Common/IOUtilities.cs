using System;
using System.Collections.Generic;
using System.IO;

namespace Common
{
    public class IOUtilities
    {
        #region Methods

        public static List<string> ReadInput()
        {
            var inputs = new List<string>();
            string line;
            while ((line = Console.ReadLine()) != null)
            {
                inputs.Add(line);
            }

            return inputs;
        }

        public static string GetGeneratedMineFolderPath()
        {
            return Path.Combine(Directory.GetParent(System.IO.Directory.GetCurrentDirectory()).Parent.Parent.FullName, "GeneratedMines");
        }

        public static void WriteOutput(string someString)
        {
            Console.SetOut(Console.Out);
            var output = Console.OpenStandardOutput();
            var sw = new StreamWriter(output);
            sw.Write(someString);
            sw.Flush();
            sw.Close();
            output.Close();
            Console.SetOut(System.IO.TextWriter.Null);
        }

        #endregion
    }
}