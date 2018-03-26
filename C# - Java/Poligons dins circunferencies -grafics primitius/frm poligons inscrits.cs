using System;
using System.Drawing;
using System.Windows.Forms;

namespace WinForms_CS
{
    // Estructura que sorgeix com a evolucio de Point(int, int) => P(float, float)
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
    // Codi del formulari pels clicks i el disseny del polígon
    public partial class frmpol : Form
    {
        // Funcions personalitzades (sin(10) > 0, no com es mostra aquí, que sur en negatiu) dels sinus i cosinus
        float sin(float deg) // Tenint en compte la y
        {
            bool neg = true;

            if (deg == 0 || deg == 180) return 0;
            if (deg == 90) return -1;
            if (deg == 270) return 1;

            if (deg > 180) neg = false;
            if (deg >= 180) deg -= 180;

            float r = (float)Math.Sin(deg * Math.PI / 180 /* a radians */);
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

            float r = (float)Math.Cos(deg * Math.PI / 180 /* a radians */);
            return neg ? -r : r;
        }
        // Simplificar angles donat un interval (1260º -> 900º -> 540º -> 180º)
        float simplificar(float deg, int interval = 360)
        {
            if (deg >= interval) return simplificar(deg - interval);
            return deg;
        }
        
        // Variables que necessitarem (r -> radi, Pens -> color i gruix de línees)
        float r = 200;
        static float thick = 2;
        Pen cercle = new Pen(Color.DarkRed, thick), poligon = new Pen(Color.Green, thick);
        
        public frmpol()
        {
            // Inicialitza el formulari (mirar InitializeComponent() a l'altre axiu [frm poligons inscrits.designer.cs]
            InitializeComponent();
            // Fixa la posició i tamany del formulari (evitar problemes amb gràfics
            this.WindowState = FormWindowState.Maximized;
            int w = Screen.GetWorkingArea(this).Width, h = Screen.GetWorkingArea(this).Height;

            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.Size = new Size(w, h);
            this.Location = new Point(0, 0);
            radi.Maximum = (Height - panel1.Height - 20) / 2 - 25;

            this.LocationChanged += (s, e) => this.Location = new Point(0, 0);
            this.Paint += paint;
            
            // Quan l'usuari fa "click" en "Incrit", "Circunscrit"..., actualitzarà el formulari (this.Refresh())
            rbinscrit.CheckedChanged += (s, e) => Refresh();
            rbcircuns.CheckedChanged += (s, e) => Refresh();
            rbdos.CheckedChanged += (s, e) => Refresh();
            rbinfinit.CheckedChanged += (s, e) =>
            {
                if (rbinfinit.Checked) tbcostats.Maximum = 15;
                else tbcostats.Maximum = 25;
                Refresh();
            };
            
            // Canvia els colors de les línees
            clcercle.Click += (s, e) =>
              {
                  ColorDialog cd = new ColorDialog() { Color = cercle.Color };
                  if (cd.ShowDialog() == DialogResult.OK)
                  {
                      cercle = new Pen(cd.Color, thick);
                      clcercle.BackColor = cd.Color;
                      Refresh();
                  }
              };
            clpoligon.Click += (s, e) =>
            {
                ColorDialog cd = new ColorDialog() { Color = poligon.Color };
                if (cd.ShowDialog() == DialogResult.OK)
                {
                    poligon = new Pen(cd.Color, thick);
                    clpoligon.BackColor = cd.Color;
                    Refresh();
                }
            };
            // Actualitzar el formulari quan l'usuari canvia el radi o nombre de costats
            tbcostats.Scroll += (sender, e) => Refresh();
            radi.Scroll += (sender, e) => Refresh();
        }
        
        // Dibuixa el cercle i polígon regular segons l'opció triada per l'usuari
        private void paint(object sender, PaintEventArgs e)
        {
            // cx, cy -> centre del cercle (x, y)
            int w = Width, h = this.Height - panel1.Height - 25;
            float cx = w/2, cy = h / 2 + panel1.Height;
            radi.Maximum = h / 2 - 30;

            r = radi.Value;
            if (tbcostats.Value == 3 && !rbinscrit.Checked)
            {
                // Modifica l'altura del cercle si hem de circunscriure un triàngle
                cy = h - r + 30;
                radi.Maximum = h / 3 - 25;
            }
            int n = tbcostats.Value;
            label1.Text = $"Radi = {r}";
            lbcostats.Text = $"Nombre de costats = {n}";

            e.Graphics.DrawEllipse(cercle, w / 2 - r, cy - r, 2 * r, 2 * r); // Cercle principal

            if (rbinscrit.Checked || rbdos.Checked) dibuixar_pol(n, r, new P(cx, cy), e); // Inscrit
            if (rbcircuns.Checked || rbdos.Checked) dibuixar_pol(n, r / cos(180 / n), new P(cx, cy), e); // Circunscrit
            if (rbinfinit.Checked)
            {
                // Posar-ne fins que no càpiguen més
                r /= cos(180 / n); // Augmentar el radi en una proporció definida (-1 <= cos(x) <= 1)
                while (r > 1)
                {
                    dibuixar_pol(n, r, new P(cx, cy), e); // Circunscrit
                    r *= cos(180 / n); // Disminuir el radi (-1 <= cos(x) <= 1) en una proporció matemàtica definida
                    dibuixar_pol(n, r, new P(cx, cy), e); // inscrit -> r /= cos(180 / n)
                    e.Graphics.DrawEllipse(cercle, w / 2 - r, cy - r, 2 * r, 2 * r); // Cercle secundari
                }
            }
        }
        // Dibuixar polígon regular donat el nombre de costats, el radi, el centre (P c) i els gràfics (e)
        void dibuixar_pol(int n, float rd, P c, PaintEventArgs e)
        {
            float alpha = 180 / n;
            float a = rd * cos(alpha), l = -2 * rd * sin(alpha);
            P ultim = new P(c.X + l / 2, c.Y + a);
            
            // Base del polígon (per no obtenir-ho girat, no començarem amb angle = 0º)
            e.Graphics.DrawLine(poligon, c.X - l / 2, c.Y + a, ultim.X, ultim.Y);

            alpha += 270;
            for (int i = 1; i < n; i++)
            {
                // Dibuixar tantes línees com costats (coordenada 1 -> P ultim, coordenda 2 -> nova, la aconseguirem amb un mètode matemàtic)
                alpha += 360 / n;
                if (alpha > 360) alpha = simplificar(alpha);

                P nou = new P(c.X + cos(alpha) * rd, c.Y + sin(alpha) * rd);
                e.Graphics.DrawLine(poligon, ultim.X, ultim.Y, nou.X, nou.Y);
                ultim = nou; // Ara l'última coordenada és la primera
            }
        }
    }
}
