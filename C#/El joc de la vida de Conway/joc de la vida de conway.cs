/* Podríem fer que en el panell es pinti tot: cel·les i graella. De fet, seria unes 70 línies més curt, però la graella parpedetjaria
    al moment en que s'actualitza el tamany, una generació o l'usuari pinti o despinti (quan passa per una viva, la matarà)
*/
using Microsoft.Win32; // Registrar extensió d'arxiu *.dis
using System;
using System.Collections.Generic; // Llistes
using System.Drawing; // Point, Graphics...
using System.IO; // File
using System.Linq; // Consultes LINQ (programació funcional)
using System.Windows.Forms;

namespace WinForms_CS
{
    public partial class conway : Form
    {
        int w = 0, cols = 0, gen = 1; // Amplada de cel·la, columnes, generació
        bool pintar = false, corrent = false;
        Point actual = new Point(-1, -1);

        List<int> pintat = new List<int>(); // Cel·les vives
        Timer t = new Timer() { Interval = 500 };

        public conway()
        {
            InitializeComponent(); // Carrega el formulari
            enregistrar_extensio(); // Enregistram extensió d'arxiu *.dis

            this.WindowState = FormWindowState.Maximized; // Maximitzam
            this.SizeChanged += (s, e) => { // Quan canviï el tamany del formulari, actualitzarem la graeela amb les cel·les
                panel1.Refresh();
                foreach (int i in pintat)
                {
                    Point p2 = P(i, cols);
                    int plus = cbgraella.Checked ? 1 : 0;
                    g.FillRectangle(Brushes.Black, p2.X * w + plus, p2.Y * w + plus, w - plus, w - plus);
                }
            };

            w = amplada.Value;
            cols = panel1.Width / w + (panel1.Width % w > 0 ? 1 : 0);

            panel1.Paint += (s, e) =>
            {
                if (cbgraella.Checked) // Pintam la graella (quadrats de w*w)
                {
                    for (int i = w; i < panel1.Width; i += w) e.Graphics.DrawLine(Pens.DarkGray, i, 0, i, e.ClipRectangle.Height); // Verticals
                    for (int i = w; i < panel1.Height; i += w) e.Graphics.DrawLine(Pens.DarkGray, 0, i, e.ClipRectangle.Width, i); // Horitzontals              
                }
            };              
            cbgraella.CheckedChanged += (s, e) => panel1.Refresh(); // Llevam o posam la graella
            panel1.MouseDown += (s, e) => // Quan l'usuari va a pintar
            {
                if (e.Button == MouseButtons.Left) pintar = !pintar;
                cel_la(e.X, e.Y); // Col·locam cel·la al punt e.X, e.Y (posició del cursor respecte el panell)
            };
            panel1.MouseUp += (s, e) => pintar = !pintar; // Aturam de pintar
            panel1.MouseMove += (s, e) => { if (e.Button == MouseButtons.Left) cel_la(e.X, e.Y); }; // Pintam cel·les si el botó del mouse està presionat
            panel1.MouseWheel += (s, e) => // Canvi del zoom mitjançant la roda o el touchpad
            {
                int fact = 40;
                int d = e.Delta;
                if (amplada.Value + e.Delta / fact <= amplada.Maximum && amplada.Value + e.Delta / fact >= amplada.Minimum)
                {
                    amplada.Value += e.Delta / delta;
                    ample();
                }
            };
            amplada.Scroll += (s, e) => ample(); // Canvi del zoom stàndart
            velocitat.Scroll += (s, e) => // Canvi de velocitat del Timer t
            {
                lbvel.Text = $"Velocitat = {velocitat.Value} gen/s";
                if (corrent) t.Stop();
                t.Interval = 1000 / velocitat.Value; // L'intreval funciona per Ticks, mentre que el TrackBar usa gen/s
                if (corrent) t.Start();
            };
            this.Controls.OfType<Control>().ToList().ForEach(c => // Comands del teclat
            {
                c.KeyPress += (s, e) =>
                {
                    switch (e.KeyChar.ToString().ToLower()[0])
                    {
                        case 'b': aturar(true); break;
                        case 'p': generacio(); break;
                        case 'i':
                            if (btnplay.Text[1] == 'I')
                            {
                                btnplay.Text = "Aturar (i)";
                                t.Start();
                                corrent = true;
                                btnproxim.Enabled = false;
                                amplada.Enabled = false;
                            }
                            else aturar(false);
                            break;
                        case 'g': guardar(); break;
                        case 'o': obrir(""); break;
                        default:
                            break;
                    }
                };
            });
            btnborrar.Click += (s, e) => aturar(true); // borram la distribució
            btnplay.Click += (s, e) => // iniciam o feim pausa
            {
                if (btnplay.Text[1] == 'I')
                {
                    btnplay.Text = "Aturar (i)";
                    t.Start();
                    corrent = true;
                    btnproxim.Enabled = false;
                    amplada.Enabled = false;
                }
                else aturar(false);
            };
            btnproxim.Click += (s, e) => generacio(); // pròxima generació
            t.Tick += (s, e) => // Cada pic que s'executi el Timer, passam a la pròxima generació
            {
                generacio();
                if (pintat.Count < 3) aturar(true);
            };

            btnguardar.Click += (s, e) => guardar(); // Guardam distribució
            btnobrir.Click += (s, e) => obrir(""); // Obrim distribució fora ruta
            
            // Quan l'aplicació s'ha obert per un arxiu *.dis
            var cmd = Environment.CommandLine.Split(new char[] { '"' }, StringSplitOptions.RemoveEmptyEntries);
            if (cmd.Length > 2 && cmd[2].EndsWith(".dis"))
            {
                Timer a = new Timer() { Interval = 10, Enabled = true };
                int cent = 0;
                a.Tick += (s, e) => // Esperam 1/2 segons per evitar problemes
                {
                    cent++;
                    pintar = false;
                    if (cent > 4)
                    {
                        a.Stop();
                        obrir(cmd[2]);
                    }
                };
            }
        }
        Point P(int a, int max) // 1d a 2d (max és el nombre de columnes (cols)
        {
            int y = 0;
            while (a > max)
            {
                a -= max;
                y++;
            }
            return new Point(a - 1, y);
        }

        int P2(Point p, int max) => p.X + p.Y * max; // 2d a 1d (max és el nombre de columnes (cols)

        void ample()
        { // quan canviam l'amplada de la cel·la (movem tots els punts per a que sigui proporcional)
            w = amplada.Value;
            List<Point> p = new List<Point>();
            pintat.ForEach(n => p.Add(P(n, cols))); // Pasam tots els punts a 2d abans de canviar les columnes

            lbample.Text = $"Amplada = {w}px";
            cols = panel1.Width / w + (panel1.Width % w > 0 ? 1 : 0);

            pintat = new List<int>();
            p.ForEach(n => pintat.Add(P2(n, cols) + 1)); // Ara pasam els punts antics a int

            panel1.Refresh(); // Actualitzam la graella
            Graphics g = panel1.CreateGraphics();
            foreach (int i in pintat) // Pintam les vives
            {
                Point p1 = P(i, cols);
                int plus = cbgraella.Checked ? 1 : 0;
                g.FillRectangle(Brushes.Black, p1.X * w + plus, p1.Y * w + plus, w - plus, w - plus);
            }
        }
        void aturar(bool bor) // Aturam l'execució i si bor = true borram la distribució
        {
            if (bor) pintat = new List<int>();
            btnplay.Text = "&Iniciar/Continuar (i)";
            t.Stop();
            corrent = false;
            btnproxim.Enabled = true;
            amplada.Enabled = true;
            if (bor) gen = 1;
            lbgen.Text = "1º generació";

            if (bor) panel1.Refresh();
            Graphics g = panel1.CreateGraphics();
            foreach (int i in pintat)
            {
                Point p2 = P(i, cols);
                int plus = cbgraella.Checked ? 1 : 0;
                g.FillRectangle(Brushes.Black, p2.X * w + plus, p2.Y * w + plus, w - plus, w - plus);
            }
        }
        void cel_la(int x, int y) // Pintam les cel·les
        {
            if (!corrent)
            {
                Point p = new Point((x - x % w) / w + 1, (y - y % w) / w);
                Graphics g = panel1.CreateGraphics();
                if (!pintar || actual == p || p.X > cols) return;

                int p1 = P2(p, cols);
                if (pintat.Contains(p1)) // Si ja existeix (està viva, l'eliminam de la llista per matar-la)
                {
                    pintat.Remove(p1);
                    Point p2 = P(p1, cols);
                    int plus = cbgraella.Checked ? 1 : 0;
                    g.FillRectangle(new SolidBrush(panel1.BackColor /*Color de fons del panell (efecte borrar)*/), p2.X * w + plus, p2.Y * w + plus, w - plus, w - plus);
                }
                else pintat.Add(p1);

                actual = p; // canviam el punt actual (per evitar matar i reviure la mateixa cel·la si no movem el cursor)
                
                foreach (int i in pintat)
                {
                    Point p2 = P(i, cols);
                    int plus = cbgraella.Checked ? 1 : 0;
                    g.FillRectangle(Brushes.Black, p2.X * w + plus, p2.Y * w + plus, w - plus, w - plus);
                }
            }
        }

        void generacio()
        {
            gen++;
            lbgen.Text = $"{gen}º generació";

            List<int> nou = new List<int>();
            int rows = panel1.Height / w + (panel1.Width % w > 0 ? 1 : 0);
            for (int x = -6; x < cols + 7; x++)
            {
                for (int y = -6; y < rows + 7; y++)
                {
                    int c = 0;
                    List<int> veines = new List<int>() // veïnes de la cel·la actual (per ara és l'altura)
                    {
                        cols * y - 1,
                        cols * y + 1,
                        cols * (y + 1),
                        cols * (y - 1),
                        cols * (y + 1) + 1,
                        cols * (y + 1) - 1,
                        cols * (y - 1) + 1,
                        cols * (y - 1) - 1,
                    };
                    veines.ForEach(n => // sumam a totes la x
                    {
                        n += x;
                        c = c + (pintat.IndexOf(n) >= 0 ? 1 : 0);
                    });
                    int ac = x + cols * y; // actua
                    if (pintat.IndexOf(ac) >= 0)
                    { // és important l'us de "{}" (per evitar confusions amb el següent "else if")
                        if (c == 2 || c == 3) nou.Add(ac); // Si una viva té 2 ó 3 veïnes, continuarà viva
                    }
                    else if (c == 3) nou.Add(ac); // Si una morta té exactament 3 veïnes, reviurà
                }
            }
            Graphics g = panel1.CreateGraphics();
            foreach (int i in nou) // Pintam les noves
            {
                Point p1 = P(i, cols);
                int plus = cbgraella.Checked ? 1 : 0;
                g.FillRectangle(Brushes.Black, p1.X * w + plus, p1.Y * w + plus, w - plus, w - plus);
            }
            pintat.Where(n => !nou.Contains(n)).ToList().ForEach(i => // Despintam les antigues (pintar del color de fons)
            {
                Point p1 = P(i, cols);
                int plus = cbgraella.Checked ? 1 : 0;
                g.FillRectangle(new SolidBrush(panel1.BackColor), p1.X * w + plus, p1.Y * w + plus, w - plus, w - plus);
            });
            pintat = nou;          
        }
        void guardar() // Guardam la distribució (*.dis) en el format següent: $"{M si està maximitzat}{amplada de cel·la},{ample formulari},{alt formulari},{cel·les separades per ","}"
        {
            SaveFileDialog sf = new SaveFileDialog() { Filter = "Distribució de Conway (.dis)|*.dis" };
            if (sf.ShowDialog() == DialogResult.OK)
            {
                string f = (this.WindowState == FormWindowState.Maximized ? "M" : "") + $"{amplada.Value},{this.Width},{this.Height}";
                pintat.ForEach(x => f += $",{x}");
                File.WriteAllText(sf.FileName, f);
            }
        }
        void obrir(string ruta) // Obrim una distribució (si ruta = "", obrirem un diàleg per seleccionar l'arxiu)
        {
            OpenFileDialog of = new OpenFileDialog() { Filter = "Distribució de Conway (.dis)|*.dis" };
            if (ruta.Length > 0 || of.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if (ruta.Length < 1) ruta = of.FileName;

                    string[] dades = File.ReadAllText(ruta).Split(new char[] { ',' });
                    if (dades[0][0] == 'M') this.WindowState = FormWindowState.Maximized;
                    dades[0] = dades[0].Replace("M", "");

                    amplada.Value = int.Parse(dades[0]);
                    ample();

                    cols = panel1.Width / w + (panel1.Width % w > 0 ? 1 : 0);
                    this.Size = new Size(int.Parse(dades[1]), int.Parse(dades[2]));

                    pintat = new List<int>();
                    for (int i = 3; i < dades.Length; i++) pintat.Add(int.Parse(dades[i]));

                    panel1.Refresh();
                    Graphics g = panel1.CreateGraphics();
                    foreach (int i in pintat) // Pintam
                    {
                        Point p2 = P(i, cols);
                        int plus = cbgraella.Checked ? 1 : 0;
                        g.FillRectangle(Brushes.Black, p2.X * w + plus, p2.Y * w + plus, w - plus, w - plus);
                    }
                }
                catch (Exception e) { MessageBox.Show($"Error al llegir l'arxiu:\n\"{e.Message}\""); }
            }
            Timer t = new Timer() { Interval = 10, Enabled = true };
            int cent = 0;
            t.Tick += (s, e) => // Timer per evitar problemes
            {
                cent++;
                pintar = false;
                if (cent > 4) t.Stop();
            };
        }

        // Registrar extensió *.dis
        void enregistrar_extensio()
        {
            RegistryKey c1 = Registry.CurrentUser.OpenSubKey("Software", true);
            c1.CreateSubKey("Classes");
            c1 = c1.OpenSubKey("Classes", true);

            c1.CreateSubKey(".dis");
            c1 = c1.OpenSubKey(".dis", true);
            c1.SetValue("", "conway.dis");

            c1.Close();
            ////////////////////////////////////////
            RegistryKey c2 = Registry.CurrentUser.OpenSubKey("Software", true);
            c2.CreateSubKey("Classes");
            c2 = c2.OpenSubKey("Classes", true);

            c2.CreateSubKey("conway.dis");
            c2 = c2.OpenSubKey("conway.dis", true);
            c2.SetValue("", "Distribució de Conway");

            c2.CreateSubKey("DefaultIcon");
            c2 = c2.OpenSubKey("DefaultIcon", true);
            c2.SetValue("", "conway.ico");

            c2.Close();
            ////////////////////////////////////////
            RegistryKey c3 = Registry.CurrentUser.OpenSubKey("Software", true);
            c3.CreateSubKey("Classes");
            c3 = c3.OpenSubKey("Classes", true);

            c3.CreateSubKey("conway.dis");
            c3 = c3.OpenSubKey("conway.dis", true);
            c3.SetValue("", "Distribució de Conway");

            c3.CreateSubKey("shell");
            c3 = c3.OpenSubKey("shell", true);

            c3.CreateSubKey("open");
            c3 = c3.OpenSubKey("open", true);

            c3.CreateSubKey("command");
            c3 = c3.OpenSubKey("command", true);
            c3.SetValue("", "\"" + Directory.GetFiles(Application.StartupPath).Where(x => x.EndsWith(".exe")).ToList()[0] + "\" \"%1\"");

            c3.Close();
        }
    }
}
