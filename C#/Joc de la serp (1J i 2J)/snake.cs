using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace WinForms_CS
{
    public enum DIR { DRETA = 0, ESQUERRA = 1, ADALT = 2, ABAIX = 3 }; // Direccions

    public partial class snake : Form
    {
        Point or = new Point(), menjar = new Point(); // Centre i posició del menjar
        Color cl;
        Timer t = new Timer() { Interval = 70 }; // cada 60 ticks se mourà la serp
        int w_tauler = 0x0, celles = 24, ample, menjats = 0x0, record = int.Parse(File.ReadAllText("1j.txt"));

        List<Point> q = new List<Point>(); // Els punts de la serp
        DIR direccio = DIR.DRETA; // Direcció del cap
        bool _mort = false; // Si hem mort o no

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) // Dreceres de teclat i ús de fletxes
        {
            if (keyData == Keys.I) // Iniciar
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
            else if (keyData == Keys.R) Close(); // Reiniciar
            else if (keyData == Keys.Up && direccio != DIR.ABAIX) direccio = DIR.ADALT; // Moure adalt
            else if (keyData == Keys.Down && direccio != DIR.ADALT) direccio = DIR.ABAIX; // Moure abaix
            else if (keyData == Keys.Left && direccio != DIR.DRETA) direccio = DIR.ESQUERRA; // Moure a l'esquerra
            else if (keyData == Keys.Right && direccio != DIR.ESQUERRA) direccio = DIR.DRETA; // Moure a la dreta

            return base.ProcessCmdKey(ref msg, keyData); // Cal posar-ho al ser un event "override"
        }

        public snake()
        {
            InitializeComponent(); // Carregam el formulari
            lbrec.Visible = false; // Amagam el label de "Nou Record!!!"
            lbdades.Text = $"Record: {record}";
            for (int i = 0; i < 7; i++) q.Add(new Point(12 - i, celles / 2)); // Inicialitzam la serp

            KeyPreview = true; // Permetem la lectura de tecles
            cl = Color.FromArgb(pnjoc.BackColor.R - 15, pnjoc.BackColor.G - 15, pnjoc.BackColor.B - 15); // Per les caselles del tauler de dos en dos
            
            // Fixar el tamany al màxim possible
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
                // Just abans de acabar la partida
                t.Stop();
                File.WriteAllText("1j.txt", record.ToString());
                if (_mort) MessageBox.Show("Mort!!!");
            };
            pnjoc.Paint += (s, e) => // Graella i menjar
            {
                e.Graphics.DrawRectangle(new Pen(Brushes.White, 4), or.X - w_tauler / 2, or.Y - w_tauler / 2, w_tauler, w_tauler);

                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;
                for (int i = 0; i < celles * celles; i++) // Pintar la graella com un escacs
                {
                    Point p = I(i);

                    if ((p.Y % 2 == 0 && p.X % 2 == 1) || (p.Y % 2 == 1 && p.X % 2 == 0))
                        e.Graphics.FillRectangle(new SolidBrush(cl), p.X * ample + pl, p.Y * ample + 10, ample, ample);
                }
                foreach (Point qr in q) // Pintam la serp
                    e.Graphics.FillRectangle(Brushes.Khaki, qr.X * ample + pl, qr.Y * ample + 10, ample, ample);

                Point p1 = new Point(); // Punt del menjar
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

            t.Tick += (s, e) => // Afegim el cap, eliminam la cua
            {

                Graphics g = pnjoc.CreateGraphics();
                SolidBrush b = new SolidBrush(pnjoc.BackColor);
                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;
                Point pb = q.Last();

                switch (direccio) // Afegir la nova posició del cap segons la direcció
                {
                    case DIR.DRETA: q.Insert(0, new Point(q[0].X + 1, q[0].Y)); break;
                    case DIR.ESQUERRA: q.Insert(0, new Point(q[0].X - 1, q[0].Y)); break;
                    case DIR.ADALT: q.Insert(0, new Point(q[0].X, q[0].Y - 1)); break;
                    case DIR.ABAIX: q.Insert(0, new Point(q[0].X, q[0].Y + 1)); break;
                }

                if (_mort = mort()) Close(); // Comprovar si morim

                if ((pb.Y % 2 == 0 && pb.X % 2 == 1) || (pb.Y % 2 == 1 && pb.X % 2 == 0)) b = new SolidBrush(cl); // Obtenir el color de fons de la graella a la casella en què es troba la cua

                if (!Menjar())
                {
                    g.FillRectangle(b, pb.X * ample + pl, pb.Y * ample + 10, ample, ample); // Esborrar (pintar del color de fons) la cua de la serp
                    q.RemoveAt(q.Count - 1); // Eliminar la cua esborrada
                }

                g.FillRectangle(Brushes.Khaki, q[0].X * ample + pl, q[0].Y * ample + 10, ample, ample); // Pintam el nou cap
            };
        }

        Point I(int p) // Convertir 1d a 2d
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
            if (q[0] == menjar) // Si hem menjat
            {
                Graphics g = pnjoc.CreateGraphics();
                int pl = pnjoc.Width / 2 - w_tauler / 2 + 2;

                if (++menjats > record) // Afegim al menjar i comprovam si hem fet un nou record
                {
                    lbrec.Visible = true;
                    record = menjats;
                }
                lbdades.Text = $"Menjats: {menjats}\nRecord: {record}";

                Point p1 = new Point(); // Punt del nou menjar

                List<int> adalt = new List<int>();
                List<int> abaix = new List<int>();
                for (int i = 0; i < celles * celles; i++) // Afegim els punts segons estiguin per adalt o abaix i que no formin part de la serp
                    if (!q.Contains(I(i)))
                    {
                        if (i < celles * celles / 2) adalt.Add(i);
                        else abaix.Add(i);
                    }
                // Alternam la posició del menjar adalt-abaix
                if (menjats % 2 == 0) p1 = I(adalt[new Random().Next(0, adalt.Count)]);
                else p1 = I(abaix[new Random().Next(0, abaix.Count)]);
                
                // Dibuixam el menjar
                int px = ample / 5;
                g.FillEllipse(Brushes.Firebrick, p1.X * ample + pl + px, p1.Y * ample + 10 + px, ample - 2 * px, ample - 2 * px);
                menjar = p1;

                return true;
            }
            return false;
        }

        bool mort() => q[0].X > celles - 1 || q[0].X < 0 || q[0].Y > celles - 1 || q[0].Y < 0 || q.Count(n => n == q[0]) > 1; // Codi per comprovar si som morts    
    }
}
