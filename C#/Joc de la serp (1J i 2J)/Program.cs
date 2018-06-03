using System;
using System.Windows.Forms;

namespace WinForms_CS
{
    static class Program
    {
        /// <summary>
        /// Punto de entrada principal para la aplicación.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new serp_dialeg()); // Carregar el diàleg per triar el mode de joc (1J o 2J)
        }
    }
}
