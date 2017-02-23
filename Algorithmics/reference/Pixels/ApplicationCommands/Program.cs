using System;
using System.Linq;

using Generator;

using Pixels;

using Visualizer;

namespace ApplicationCommands
{
    public class Program
    {
        #region Methods

        public static void Main(string[] args)
        {
            switch (args[0])
            {
                case "-s":
                    InvokeSolver();
                    break;
                case "-v":
                    InvokeVisualizer();
                    break;
                case "-g":
                    InvokeGenerator(args);
                    break;
                default:
                    break;
            }
        }

        private static void InvokeSolver()
        {
            PixelSolver.Main(new string[0]);
        }

        private static void InvokeVisualizer()
        {
            PixelVisualizer.Main(new string[0]);
        }

        private static void InvokeGenerator(string[] args)
        {
            var generatorArgs = args.Skip(1).ToArray();
            PixelGenerator.Main(generatorArgs);
        }

        #endregion
    }
}