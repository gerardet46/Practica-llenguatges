using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace WinForms_CS
{
    public enum DIR { DRETA = 0, ESQUERRA = 1, ADALT = 2, ABAIX = 3 };

    public partial class snake : Form
    {
        Point or = new Point(), menjar = new Point();
        Color cl;
        Timer t = new Timer() { Interval = 60 };
        int w_tauler = 0x0, celles = 40, ample, menjats = 0x0, record = int.Parse(File.ReadAllText("1j.txt"));

        List<Point> q = new List<Point>();
        DIR direccio = DIR.DRETA;
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
            else if (keyData == Keys.Up && direccio != DIR.ABAIX) direccio = DIR.ADALT;
            else if (keyData == Keys.Down && direccio != DIR.ADALT) direccio = DIR.ABAIX;
            else if (keyData == Keys.Left && direccio != DIR.DRETA) direccio = DIR.ESQUERRA;
            else if (keyData == Keys.Right && direccio != DIR.ESQUERRA) direccio = DIR.DRETA;

            return base.ProcessCmdKey(ref msg, keyData);
        }

        public snake()
        {
            InitializeComponent();
            lbrec.Visible = false;
            lbdades.Text = $"Record: {record}";
            for (int i = 0; i < 7; i++) q.Add(new Point(12 - i, celles / 2));

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
                File.WriteAllText("1j.txt", record.ToString());
                if (_mort) MessageBox.Show("Mort!!!");
            };
            pnjoc.Paint += (s, e) => // Graella i menjar
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

                Point p1 = new Point();
                bool bucle = true;
                while (bucle)
                {
                    p1 = I(new Random().Next(0, celles * celles));
                    bucle = false;
                    foreach (Point qr in q)
                        if (qr == p1)
                        {
                            bucle = true;
                            break;
                        }
                }
                int px = ample / 5;
                e.Graphics.FillEllipse(Brushes.Firebrick, p1.X * ample + pl + px, p1.Y * ample + 10 + px, ample - 2 * px, ample - 2 * px);
                menjar = p1;
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
                SolidBrush b = new SolidBrush(pnjoc.BackColor);
                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;
                Point pb = q.Last();

                switch (direccio)
                {
                    case DIR.DRETA: q.Insert(0, new Point(q[0].X + 1, q[0].Y)); break;
                    case DIR.ESQUERRA: q.Insert(0, new Point(q[0].X - 1, q[0].Y)); break;
                    case DIR.ADALT: q.Insert(0, new Point(q[0].X, q[0].Y - 1)); break;
                    case DIR.ABAIX: q.Insert(0, new Point(q[0].X, q[0].Y + 1)); break;
                }

                if (_mort = mort()) Close();

                if ((pb.Y % 2 == 0 && pb.X % 2 == 1) || (pb.Y % 2 == 1 && pb.X % 2 == 0)) b = new SolidBrush(cl);

                if (!Menjar())
                {
                    g.FillRectangle(b, pb.X * ample + pl, pb.Y * ample + 10, ample, ample);
                    q.RemoveAt(q.Count - 1);
                }

                g.FillRectangle(Brushes.Khaki, q[0].X * ample + pl, q[0].Y * ample + 10, ample, ample);
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
        bool Menjar()
        {
            if (q[0] == menjar)
            {
                Graphics g = pnjoc.CreateGraphics();
                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;

                if (++menjats > record)
                {
                    lbrec.Visible = true;
                    record = menjats;
                }
                lbdades.Text = $"Menjats: {menjats}\nRecord: {record}";

                Point p1 = new Point();

                List<int> adalt = new List<int>();
                List<int> abaix = new List<int>();
                for (int i = 0; i < celles * celles; i++)
                    if (!q.Contains(I(i)))
                    {
                        if (i < celles * celles / 2) adalt.Add(i);
                        else abaix.Add(i);
                    }

                if (menjats % 2 == 0) p1 = I(adalt[new Random().Next(0, adalt.Count)]);
                else p1 = I(abaix[new Random().Next(0, abaix.Count)]);

                int px = ample / 5;
                g.FillEllipse(Brushes.Firebrick, p1.X * ample + pl + px, p1.Y * ample + 10 + px, ample - 2 * px, ample - 2 * px);
                menjar = p1;

                return true;
            }
            return false;
        }

        bool mort() => q[0].X > celles - 1 || q[0].X < 0 || q[0].Y > celles - 1 || q[0].Y < 0 || q.Count(n => n == q[0]) > 1;
    }
}