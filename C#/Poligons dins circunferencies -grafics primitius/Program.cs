using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForms_CS
{
    static class Program
    {
        /// <summary>
        /// Punt d'entrada principal de l'aplicaió
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frmpol()); // Executar el formulari corresponent
        }
    }
}
