using System;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

using Common;

using Mines;

namespace MineSolverVisualizer
{
    public class Visualizer
    {
        #region Fields

        private readonly Button outputDataButton = new Button();

        private readonly int[] beforeMine;
        private readonly int[] validMine;
        private readonly int minimumCost;
        private readonly int maxDistanceBetweenTwoPoint;

        #endregion

        #region Constructors

        public Visualizer(int[] beforeMine, int[] validMine, int maxDistanceBetweenTwoPoint, int minimumCost)
        {
            this.beforeMine = beforeMine;
            this.validMine = validMine;
            this.maxDistanceBetweenTwoPoint = maxDistanceBetweenTwoPoint;
            this.minimumCost = minimumCost;
        }

        #endregion

        #region Methods

        public static void Main(string[] args)
        {
            SetProcessDPIAware();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            var inputs = IOUtilities.ReadInput();
            var solver = new Solver(inputs);
            var answers = solver.Solve();

            foreach (var mineResult in answers)
            {
                var visualizer = new Visualizer(
                    mineResult.BeforeMine, 
                    mineResult.ValidMine, 
                    mineResult.MaxDistanceBetweenTwoPoint, 
                    mineResult.MinimumCost);

                visualizer.PrintMountainsDiff();
            }
        }

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern bool SetProcessDPIAware();

        private void PrintMountainsDiff()
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

            for (var i = 0; i < this.beforeMine.Length; i++)
            {
                chart.Series[0].Points.AddXY(i, this.beforeMine[i]);
            }

            for (var i = 0; i < this.validMine.Length; i++)
            {
                chart.Series["Après travaux"].Points.AddXY(i, this.validMine[i]);
            }

            var annotation = new TextAnnotation();
            annotation.Text = string.Format("Le coût optimal est : {0}\nDistance max : {1}", this.minimumCost, this.maxDistanceBetweenTwoPoint);
            annotation.Font = new Font(new FontFamily("Tahoma"), 8f);
            annotation.Alignment = System.Drawing.ContentAlignment.MiddleLeft;
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

            // Format controls. Note: Controls inherit color from parent form.
            this.outputDataButton.BackColor = Color.Gray;
            this.outputDataButton.Text = "Output data";
            this.outputDataButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;

            this.outputDataButton.Location = new System.Drawing.Point(1200, 405);
            this.outputDataButton.Size = new System.Drawing.Size(150, 55);
            this.outputDataButton.Click += this.OutputResultOnStdOut;

            // chart.SaveImage(fileName + ".png", System.Drawing.Imaging.ImageFormat.Png);
            var f = new Form();
            f.Controls.Add(this.outputDataButton);
            f.Controls.Add(chart);
            f.Controls.Add(chart);
            f.Dock = DockStyle.Fill;
            f.AutoScaleMode = AutoScaleMode.Dpi;
            f.AutoSize = true;
            f.StartPosition = FormStartPosition.CenterScreen;

            f.ShowDialog();
        }

        private void OutputResultOnStdOut(object sender, EventArgs e)
        {
            IOUtilities.WriteOutput(string.Concat(
                this.maxDistanceBetweenTwoPoint, 
                "\n", 
                string.Join(" ", this.beforeMine),
                "\n"));
        }

        #endregion
    }
}