using System;
using System.Drawing;
using System.Windows.Forms;

namespace WinForms_CS
{
    public struct P
    {
        public P(float x, float y)
        {
            X = x;
            Y = y;
        }
        public float X;
        public float Y;
    }
    public partial class frmpol : Form
    {
        float sin(float deg) // Tenint en compte la y
        {
            bool neg = true;

            if (deg == 0 || deg == 180) return 0;
            if (deg == 90) return -1;
            if (deg == 270) return 1;

            if (deg > 180) neg = false;
            if (deg >= 180) deg -= 180;

            float r = (float)Math.Sin(deg * Math.PI / 180);
            return neg ? -r : r;
        }
        float cos(float deg) // Tenint en compte la x
        {
            bool neg = true;

            if (deg == 0) return 1;
            if (deg == 90 || deg == 270) return 0;
            if (deg == 180) return -1;

            if (deg < 180) neg = false;
            if (deg > 180) deg -= 180;

            float r = (float)Math.Cos(deg * Math.PI / 180);
            return neg ? -r : r;
        }
        float simplificar(float deg, int interval = 360)
        {
            if (deg >= interval) return simplificar(deg - interval);
            return deg;
        }

        float r = 200;
        static float thick = 2;
        Pen cercle = new Pen(Color.DarkRed, thick), poligon = new Pen(Color.Green, thick);
        
        public frmpol()
        {
            InitializeComponent();
            this.WindowState = FormWindowState.Maximized;
            int w = Screen.GetWorkingArea(this).Width, h = Screen.GetWorkingArea(this).Height;

            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.Size = new Size(w, h);
            this.Location = new Point(0, 0);
            radi.Maximum = (Height - panel1.Height - 20) / 2 - 25;

            this.LocationChanged += (object s, EventArgs e) => this.Location = new Point(0, 0);
            this.Paint += paint;

            rbinscrit.CheckedChanged += (object s, EventArgs e) => Refresh();
            rbcircuns.CheckedChanged += (object s, EventArgs e) => Refresh();
            rbdos.CheckedChanged += (object s, EventArgs e) => Refresh();
            rbinfinit.CheckedChanged += (object s, EventArgs e) =>
            {
                if (rbinfinit.Checked) tbcostats.Maximum = 15;
                else tbcostats.Maximum = 25;
                Refresh();
            };

            clcercle.Click += delegate (object s, EventArgs e)
              {
                  ColorDialog cd = new ColorDialog() { Color = cercle.Color };
                  if (cd.ShowDialog() == DialogResult.OK)
                  {
                      cercle = new Pen(cd.Color, thick);
                      clcercle.BackColor = cd.Color;
                      Refresh();
                  }
              };
            clpoligon.Click += delegate (object s, EventArgs e)
            {
                ColorDialog cd = new ColorDialog() { Color = poligon.Color };
                if (cd.ShowDialog() == DialogResult.OK)
                {
                    poligon = new Pen(cd.Color, thick);
                    clpoligon.BackColor = cd.Color;
                    Refresh();
                }
            };
            tbcostats.Scroll += (object sender, EventArgs e) => Refresh();
            radi.Scroll += (object sender, EventArgs e) => Refresh();
        }

        private void paint(object sender, PaintEventArgs e)
        {
            int w = Width, h = this.Height - panel1.Height - 25;
            float cx = w/2, cy = h / 2 + panel1.Height;
            radi.Maximum = h / 2 - 30;

            r = radi.Value;
            if (tbcostats.Value == 3 && !rbinscrit.Checked)
            {
                cy = h - r + 30;
                radi.Maximum = h / 3 - 25;
            }
            int n = tbcostats.Value;
            label1.Text = $"Radi = {r}";
            lbcostats.Text = $"Nombre de costats = {n}";

            e.Graphics.DrawEllipse(cercle, w / 2 - r, cy - r, 2 * r, 2 * r);

            if (rbinscrit.Checked || rbdos.Checked) dibuixar_pol(n, r, new P(cx, cy), e);
            if (rbcircuns.Checked || rbdos.Checked) dibuixar_pol(n, r / cos(180 / n), new P(cx, cy), e);
            if (rbinfinit.Checked)
            {
                r /= cos(180 / n);
                while (r > 1)
                {
                    dibuixar_pol(n, r, new P(cx, cy), e); // Circunscrit
                    r *= cos(180 / n);
                    dibuixar_pol(n, r, new P(cx, cy), e); // inscrit -> r /= cos(180 / n)
                    e.Graphics.DrawEllipse(cercle, w / 2 - r, cy - r, 2 * r, 2 * r); // Cercle
                }
            }
        }
        void dibuixar_pol(int n, float rd, P c, PaintEventArgs e)
        {
            float alpha = 180 / n;
            float a = rd * cos(alpha), l = -2 * rd * sin(alpha);
            P ultim = new P(c.X + l / 2, c.Y + a);

            e.Graphics.DrawLine(poligon, c.X - l / 2, c.Y + a, ultim.X, ultim.Y);

            alpha += 270;
            for (int i = 1; i < n; i++)
            {
                alpha += 360 / n;
                if (alpha > 360) alpha = simplificar(alpha);

                P nou = new P(c.X + cos(alpha) * rd, c.Y + sin(alpha) * rd);
                e.Graphics.DrawLine(poligon, ultim.X, ultim.Y, nou.X, nou.Y);
                ultim = nou;
            }
        }
    }
}