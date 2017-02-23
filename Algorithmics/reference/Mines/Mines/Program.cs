using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace centre_ski_2
{
    public class Program
    {
        #region Fields

        private static readonly Random _rdm = new Random();
        private static int maxAltitudeDistanceBetweenPoints = 4;
        private static int topMountainPointHeight = 0;
        private static int[,] memo = new int[40, 40];
        private static Tuple<int, int>[,] memoMountain = new Tuple<int, int>[100, 100];

        #endregion

        #region Methods

        public static void Main(string[] args)
        {
            SetProcessDPIAware();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // CreateMontains(10, 5, 25);
            using (TextReader reader = File.OpenText("input-test.txt"))
            {
                var line = reader.ReadLine();
                var caseCount = Convert.ToInt32(line);
                for (var i = 0; i < caseCount; i++)
                {
                    line = reader.ReadLine();
                    maxAltitudeDistanceBetweenPoints = int.Parse(line);
                    line = reader.ReadLine();
                    var mountain = Array.ConvertAll(line.Split(' '), int.Parse);
                    topMountainPointHeight = 50;
                    memo = new int[mountain.Length, topMountainPointHeight];
                    InitWithValue(memo);
                    memoMountain = new Tuple<int, int>[mountain.Length, topMountainPointHeight];

                    var bestHeightForLastPoint = 0;
                    var answer = Solve(mountain, out bestHeightForLastPoint);

                    var validMountain = MemoMontainsToArray(mountain.Length, bestHeightForLastPoint);

                    PrintMountainsDiff(mountain, validMountain, answer, maxAltitudeDistanceBetweenPoints);
                }
            }
        }

        public static int[] MemoMontainsToArray(int montainLenght, int lastPointBestHeight)
        {
            var cur = memoMountain[montainLenght - 1, lastPointBestHeight];
            var validMontain = new int[montainLenght];

            var stack = new Stack<int>();
            stack.Push(lastPointBestHeight);
            var index = montainLenght - 1;
            validMontain[index] = lastPointBestHeight;
            while (cur.Item1 != -1)
            {
                index--;
                validMontain[index] = cur.Item2;
                stack.Push(cur.Item2);
                cur = memoMountain[cur.Item1, cur.Item2];
            }

            return validMontain;
        }

        public static void InitWithValue(int[,] array)
        {
            for (var i = 0; i < array.GetLength(0); i++)
            {
                for (var j = 0; j < array.GetLength(1); j++)
                {
                    array[i, j] = -1;
                }
            }
        }

        public static int Solve(int[] mountain, out int bestHeightForLastPoint)
        {
            bestHeightForLastPoint = int.MaxValue;
            var answer = int.MaxValue;
            for (var i = 0; i < topMountainPointHeight; i++)
            {
                var costForHeight = Cost(mountain, mountain.Length - 1, i);

                if (costForHeight < answer)
                {
                    answer = costForHeight;
                    bestHeightForLastPoint = i;
                }
            }

            return answer;
        }

        public static int Cost(int[] mountain, int index, int height)
        {
            if (index < 0)
            {
                return 0;
            }

            if (memo[index, height] != -1)
            {
                return memo[index, height];
            }

            var ret = int.MaxValue;

            var costToSetHeight = Math.Abs(mountain[index] - height);
            if (height == 0)
            {
                memo[index, height] = Cost(mountain, index - 1, height) + costToSetHeight;
                memoMountain[index, height] = new Tuple<int, int>(index - 1, height);

                // memoHeights[index] = height;
                return memo[index, height];
            }

            for (var i = 1; i < (maxAltitudeDistanceBetweenPoints + 1); i++)
            {
                if (height - i >= 0)
                {
                    var cost = Cost(mountain, index - 1, height - i) + costToSetHeight;
                    if (cost < ret)
                    {
                        memoMountain[index, height] = new Tuple<int, int>(index - 1, height - i);
                        ret = cost;
                    }
                }
            }

            memo[index, height] = ret;

            return memo[index, height];
        }

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern bool SetProcessDPIAware();

        private static int[] GenerateRdmArray(int n, int max)
        {
            var array = new int[n];
            array[0] = max + 25;
            for (var i = 1; i < array.Length; i++)
            {
                array[i] = _rdm.Next(Math.Abs(array.Length - i), Math.Abs((max + 25) - (i * 2)) + 1);
            }

            Array.Reverse(array);

            return array;
        }

        private static void CreateMontains(int n, int minSize, int maxSize)
        {
            var rdm = new Random();
            using (var file = new StreamWriter("small-montains.txt"))
            {
                file.WriteLine(n);
                for (var i = 0; i < n; i++)
                {
                    var montainLength = rdm.Next(minSize, maxSize);

                    // var montainTopIndex = rdm.Next(Convert.ToInt32(montainLength * 0.2), Convert.ToInt32(montainLength - (montainLength * 0.2)));
                    var montain = GenerateRdmArray(montainLength, maxSize);

                    // montain[montainTopIndex] = montainTop;

                    // file.WriteLine(string.Concat(montainLength, " ", montainTopIndex));
                    file.WriteLine(string.Join(" ", montain));
                }
            }
        }

        private static void PrintMountainsDiff(int[] array, int[] validMountain, int operationCost, int maxLatitudDistance)
        {
            var spacingSlotCount = "100";
            var pointWidth = "0.7";

            var chart = new Chart();
            chart.Width = 1460;
            chart.Height = 650;
            var serie1 = new Series();
            serie1.Name = "Avant travaux";
            serie1.Color = Color.FromArgb(112, 255, 200);
            serie1.BorderColor = Color.FromArgb(164, 164, 164);
            serie1.ChartType = SeriesChartType.Column;
            serie1.BorderWidth = 1;
            serie1.ShadowColor = Color.FromArgb(128, 128, 128);
            serie1.ShadowOffset = 1;
            serie1.IsValueShownAsLabel = true;

            serie1.XValueMember = "Name";
            serie1.YValueMembers = "Counter";
            serie1.Font = new Font("Tahoma", 6.0f);
            serie1.BackSecondaryColor = Color.FromArgb(0, 102, 153);
            serie1.LabelForeColor = Color.FromArgb(100, 100, 100);
            serie1["PointWidth"] = pointWidth;
            serie1["SpacingSlotCount"] = spacingSlotCount;

            chart.Series.Add(serie1);
            chart.Series.Add("Après travaux");
            chart.Series["Après travaux"].IsValueShownAsLabel = true;
            chart.Series["Après travaux"].Font = new Font("Tahoma", 6.0f);
            chart.Series["Après travaux"]["PointWidth"] = pointWidth;
            chart.Series["Après travaux"]["SpacingSlotCount"] = spacingSlotCount;

            chart.Legends.Add(new Legend
            {
                MaximumAutoSize = 100, 
                Name = "Montagne avant travaux", 
                BackColor = Color.White, 
                Enabled = true, 
                Docking = Docking.Right
            });

            chart.Legends.Add(new Legend
            {
                Name = "Montagne retravaillé (valide)", 
                MaximumAutoSize = 100, 
                BackColor = Color.Blue, 
                Enabled = true, 
                Docking = Docking.Right
            });

            for (var i = 0; i < array.Length; i++)
            {
                chart.Series[0].Points.AddXY(i, array[i]);
            }

            for (var i = 0; i < validMountain.Length; i++)
            {
                chart.Series["Après travaux"].Points.AddXY(i, validMountain[i]);
            }

            var annotation = new TextAnnotation();
            annotation.Text = string.Format("Le coût optimal est : {0}\nDistance max : {1}", operationCost, maxLatitudDistance);
            annotation.Font = new Font(new FontFamily("Tahoma"), 8f);
            annotation.Alignment = ContentAlignment.MiddleLeft;
            annotation.X = 80;
            annotation.Y = 25;
            annotation.BringToFront();
            chart.Annotations.Add(annotation);

            var ca = new ChartArea();
            ca.Name = "ChartArea1";
            ca.BackColor = Color.White;
            ca.BorderColor = Color.FromArgb(26, 59, 105);
            ca.BorderWidth = 0;
            ca.BorderDashStyle = ChartDashStyle.Dash;
            ca.AxisX = new Axis();
            ca.AxisY = new Axis
            {
                MajorGrid = new TickMark()
                {
                    LineColor = Color.LightGray, 
                    LineDashStyle = ChartDashStyle.Dash
                }
            };
            chart.ChartAreas.Add(ca);

            chart.DataBind();

            // chart.SaveImage(fileName + ".png", System.Drawing.Imaging.ImageFormat.Png);
            var f = new Form();
            f.Controls.Add(chart);
            f.Controls.Add(chart);
            f.Dock = DockStyle.Fill;
            f.AutoScaleMode = AutoScaleMode.Dpi;
            f.AutoSize = true;
            f.StartPosition = FormStartPosition.CenterScreen;

            f.ShowDialog();
        }

        #endregion
    }
}