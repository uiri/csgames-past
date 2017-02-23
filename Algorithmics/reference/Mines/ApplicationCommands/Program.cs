using System;
using System.Linq;

using MineGenerator;

using Mines;

using MineSolverVisualizer;

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
            Solver.Main(new string[0]);
        }

        private static void InvokeVisualizer()
        {
            Visualizer.Main(new string[0]);
        }

        private static void InvokeGenerator(string[] args)
        {
            var generatorArgs = args.Skip(1).ToArray();
            Generator.Main(generatorArgs);
        }

        #endregion
    }
}