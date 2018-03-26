using System;
using System.Drawing;
using System.Windows.Forms;

namespace WinForms_CS
{
    public partial class frmrellotge_analogic : Form
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
            if (deg < 0) return simplificar(360 + deg);
            if (deg >= interval) return simplificar(deg - interval);
            return deg;
        }

        Color fff = Color.White; // Definim el color de línees i busques (la secundària serà vermella)
        public frmrellotge_analogic()
        {
            InitializeComponent();
            this.MinimumSize = new Size(100, 100); // Tamany mínim del formulari: 100 x 100px
            SizeChanged += (s, e) => Refresh(); // Si canviam el tamany de la finestra, ajustar el rellotge
            Paint += paint; // Event per pintar el formulari (this.Paint)
            while (DateTime.Now.Millisecond > 450 && DateTime.Now.Millisecond < 550) { /*Esperar fins el segon i mig (evitar problemes)*/ }
            Timer t = new Timer() { Interval = 1000, Enabled = true };
            t.Tick += (s, e) => pintar_hora(); // cada 1 segon (1000ms), pintarà l¡hora corresponent
        }

        float cx, cy, r, ant1, ant2, ant3;
        void pintar_hora()
        {
            DateTime n = DateTime.Now; // hora actual
            int h = n.Hour;
            if (h > 12) h -= 12;
            int s = h * 3600 + n.Minute * 60 + n.Second;
            lbhora.Text = $"{n.Hour.ToString("d2")}:{n.Minute.ToString("d2")}:{n.Second.ToString("d2")}"; // "d2" -> {"1" -> "01", "13" -> "13"}

            Graphics e = this.CreateGraphics();

            float ah = simplificar(90 - s / 120), am = simplificar(90 - s / 10), aseg = simplificar(90 - n.Second * 6); // angles corresponents

            // Despintar línees antigues (pintar-les del color de fons
            e.DrawLine(new Pen(Color.SeaGreen, 8), cx, cy, cx + (r * 0.9f) * cos(ant2), cy + (r * 0.9f) * sin(ant2)); // minuts
            e.DrawLine(new Pen(Color.SeaGreen, 15), cx, cy, cx + (r * 0.4f) * cos(ant1), cy + (r * 0.4f) * sin(ant1)); // hores
            e.DrawLine(new Pen(Color.SeaGreen, 1), cx, cy, cx + (r * 0.95f) * cos(ant3), cy + (r * 0.95f) * sin(ant3)); // segons

            // Dibuixar segments de referècia
            for (int i = 0; i < 60; i++)
            {
                float an = i * 6;
                int thick = 2, llarg = 20;
                if (i % 5 == 0)
                {
                    thick = 8;
                    llarg = 35;
                }
                e.DrawLine(new Pen(fff, thick), cx + (r - 5) * cos(an), cy + (r - 5) * sin(an), cx + (r - llarg) * cos(an), cy + (r - llarg) * sin(an));
            }

            // Pintar noves (blanc
            e.DrawLine(new Pen(fff, 8), cx, cy, cx + (r * 0.9f) * cos(am), cy + (r * 0.9f) * sin(am)); // minuts
            e.DrawLine(new Pen(fff, 15), cx, cy, cx + (r * 0.4f) * cos(ah), cy + (r * 0.4f) * sin(ah)); // hores
            e.DrawLine(new Pen(Color.DarkRed, 1), cx, cy, cx + (r * 0.95f) * cos(aseg), cy + (r * 0.95f) * sin(aseg)); // segons
            
            // Ara els angles antics seran els que hem usat
            ant1 = ah;
            ant2 = am;
            ant3 = aseg;
        }

        private void paint(object sender, PaintEventArgs e)
        {
            // Només cercle principal (inici del programa i canvi de tamany, ja que el cercle és constant)
            cx = Width / 2;
            cy = (Height + lbhora.Height - 40) / 2;
            r = cy - lbhora.Height - 25;

            pintar_hora();

            e.Graphics.DrawEllipse(new Pen(fff, 5), cx - r, cy - r, 2 * r, 2 * r);
            e.Graphics.FillEllipse(Brushes.SeaGreen, cx - r, cy - r, 2 * r, 2 * r);
        }
    }
}
