using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace WinForms_CS
{
    public partial class serp_dialeg : Form
    {
        public serp_dialeg()
        {
            InitializeComponent();
            if (!File.Exists("1j.txt") || new Regex(@"^[0-9]+$").IsMatch(File.ReadAllText("1j.txt"))) File.WriteAllText("1j.txt", "0");
            if (!File.Exists("2j.txt") || new Regex(@"^[0-9]+$").IsMatch(File.ReadAllText("2j.txt"))) File.WriteAllText("2j.txt", "0");

            btnsol.Click += (s, e) =>
            {
                ModeSerp.mode = MODE_JOC.J1;
                ShowInTaskbar = false;
                Visible = false;
                new snake().ShowDialog();
                ShowInTaskbar = true;
                Visible = true;
            };
            btnxocar.Click += (s, e) =>
            {
                ModeSerp.mode = MODE_JOC.J2;
                ShowInTaskbar = false;
                Visible = false;
                new snake2().ShowDialog();
                ShowInTaskbar = true;
                Visible = true;
            };
        }
    }
}
