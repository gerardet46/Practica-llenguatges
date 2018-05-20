using System.Drawing;
using System.Windows.Forms;
using System;

namespace WinForms_CS
{
    public partial class separador : Panel
    {
        public enum TIPUS { VERTICAL = 0, HORITZONTAL = 1 }
        public separador()
        {
            // Quan carrega l'element
            InitializeComponent();
            this.BackColor = Color.Black;
            Grosor = 2;
            Tipus = TIPUS.VERTICAL;
            this.Width = Grosor;
        }
        private int _gr = 2;
        private TIPUS _t = TIPUS.VERTICAL;

        public int Grosor
        {
            // Propietat nova: estableix el gruix del separador
            get { return _gr; }
            set
            {
                _gr = value;
                if (_t == TIPUS.VERTICAL) this.Width = _gr;
                else this.Height = _gr;
            }
        }
        public TIPUS Tipus
        {
            // Propietat nova: estableix si el separdor ha d'estar en horitzontal o vertical
            get { return _t; }
            set
            {
                _t = value;
                if (_t == TIPUS.VERTICAL) this.Width = _gr;
                else this.Height = _gr;
            }
    }

        protected override void OnSizeChanged(EventArgs e)
        {
            // Canvia el mètode principal de quan es canvia el tamany (el fixa)
            base.OnSizeChanged(e);
            if (_t == TIPUS.VERTICAL) this.Width = _gr;
            else this.Height = _gr;
        }
    }
}
