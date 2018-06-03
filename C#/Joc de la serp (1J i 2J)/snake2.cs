using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace WinForms_CS
{
    public partial class snake2 : Form
    {
        Point or = new Point();
        Color cl;
        Timer t = new Timer() { Interval = 80 };
        int w_tauler = 0x0, celles = 40, ample, jugats, record = int.Parse(File.ReadAllText("2j.txt"));

        List<Point> q = new List<Point>(), q2 = new List<Point>();
        DIR d1 = DIR.DRETA, d2 = DIR.ESQUERRA;
        bool _mort = false;

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.I)
            {
                if (btnplay.Text[0] == 'I' || btnplay.Text[0] == 'C')
                {
                    btnplay.Text = "Pausar (i)";
                    t.Start();
                }
                else
                {
                    btnplay.Text = "Continuar (i)";
                    t.Stop();
                }
            }
            else if (keyData == Keys.R) Close();
            else if (keyData == Keys.Up && d2 != DIR.ABAIX) d2 = DIR.ADALT;
            else if (keyData == Keys.Down && d2 != DIR.ADALT) d2 = DIR.ABAIX;
            else if (keyData == Keys.Left && d2 != DIR.DRETA) d2 = DIR.ESQUERRA;
            else if (keyData == Keys.Right && d2 != DIR.ESQUERRA) d2 = DIR.DRETA;

            else if (keyData == Keys.W && d1 != DIR.ABAIX) d1 = DIR.ADALT;
            else if (keyData == Keys.S && d1 != DIR.ADALT) d1 = DIR.ABAIX;
            else if (keyData == Keys.A && d1 != DIR.DRETA) d1 = DIR.ESQUERRA;
            else if (keyData == Keys.D && d1 != DIR.ESQUERRA) d1 = DIR.DRETA;

            return base.ProcessCmdKey(ref msg, keyData);
        }

        public snake2()
        {
            InitializeComponent();
            lbrec.Visible = false;
            for (int i = 0; i < 7; i++)
            {
                q.Add(new Point(7 + i, celles / 2));
                q2.Add(new Point(celles - 8 - i, celles / 2));
            }
            q.Reverse();
            q2.Reverse();

            KeyPreview = true;
            cl = Color.FromArgb(pnjoc.BackColor.R - 15, pnjoc.BackColor.G - 15, pnjoc.BackColor.B - 15);

            int w = Screen.GetWorkingArea(this).Width, h = Screen.GetWorkingArea(this).Height;
            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.Size = new Size(w, h);
            or = new Point(pnjoc.Width / 2, pnjoc.Height / 2);
            w_tauler = (pnjoc.Width > pnjoc.Height ? pnjoc.Height : pnjoc.Width) - 16;
            ample = w_tauler / celles;
            this.LocationChanged += (s, e) => this.Location = new Point(0, 0);

            this.FormClosing += (s, e) =>
            {
                t.Stop();
                File.WriteAllText("2j.txt", record.ToString());
                if (_mort) MessageBox.Show("Mort!!!");
            };
            pnjoc.Paint += (s, e) =>
            {
                e.Graphics.DrawRectangle(new Pen(Brushes.White, 4), or.X - w_tauler / 2, or.Y - w_tauler / 2, w_tauler, w_tauler);

                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;
                for (int i = 0; i < celles * celles; i++)
                {
                    Point p = I(i);

                    if ((p.Y % 2 == 0 && p.X % 2 == 1) || (p.Y % 2 == 1 && p.X % 2 == 0))
                        e.Graphics.FillRectangle(new SolidBrush(cl), p.X * ample + pl, p.Y * ample + 10, ample, ample);
                }
                foreach (Point qr in q)
                    e.Graphics.FillRectangle(Brushes.Khaki, qr.X * ample + pl, qr.Y * ample + 10, ample, ample);

                foreach (Point qr in q2)
                    e.Graphics.FillRectangle(Brushes.Plum, qr.X * ample + pl, qr.Y * ample + 10, ample, ample);
            };
            btnplay.Click += (s, e) =>
            {
                if (btnplay.Text[0] == 'I' || btnplay.Text[0] == 'C')
                {
                    btnplay.Text = "Pausar (i)";
                    t.Start();
                }
                else
                {
                    btnplay.Text = "Aturar (i)";
                    t.Stop();
                }
            };
            btnreiniciar.Click += (s, e) => Close();

            t.Tick += (s, e) =>
            {
                Graphics g = pnjoc.CreateGraphics();
                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;

                switch (d1)
                {
                    case DIR.DRETA: q.Insert(0, new Point(q[0].X + 1, q[0].Y)); break;
                    case DIR.ESQUERRA: q.Insert(0, new Point(q[0].X - 1, q[0].Y)); break;
                    case DIR.ADALT: q.Insert(0, new Point(q[0].X, q[0].Y - 1)); break;
                    case DIR.ABAIX: q.Insert(0, new Point(q[0].X, q[0].Y + 1)); break;
                }
                switch (d2)
                {
                    case DIR.DRETA: q2.Insert(0, new Point(q2[0].X + 1, q2[0].Y)); break;
                    case DIR.ESQUERRA: q2.Insert(0, new Point(q2[0].X - 1, q2[0].Y)); break;
                    case DIR.ADALT: q2.Insert(0, new Point(q2[0].X, q2[0].Y - 1)); break;
                    case DIR.ABAIX: q2.Insert(0, new Point(q2[0].X, q2[0].Y + 1)); break;
                }

                if (_mort = mort()) Close();

                if (++jugats > record)
                {
                    lbrec.Visible = true;
                    record = jugats;
                }
                lbdades.Text = $"Caselles: {jugats}\nRecord: {record}";

                g.FillRectangle(Brushes.Khaki, q[0].X * ample + pl, q[0].Y * ample + 10, ample, ample);
                g.FillRectangle(Brushes.Plum, q2[0].X * ample + pl, q2[0].Y * ample + 10, ample, ample);
            };
        }

        int P(Point p) => p.Y * w_tauler + p.X;
        Point I(int p)
        {
            int y = 0;
            while (p >= celles)
            {
                p -= celles;
                y++;
            }
            return new Point(p, y);
        }

        bool mort() => q[0].X > celles - 1 || q[0].X < 0 || q[0].Y > celles - 1 || q[0].Y < 0 || q.Count(n => n == q[0]) > 1 || q2.Contains(q[0]) ||
             q2[0].X > celles - 1 || q2[0].X < 0 || q2[0].Y > celles - 1 || q2[0].Y < 0 || q2.Count(n => n == q2[0]) > 1 || q.Contains(q2[0]);
    }
}