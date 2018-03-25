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
            base.OnSizeChanged(e);
            if (_t == TIPUS.VERTICAL) this.Width = _gr;
            else this.Height = _gr;
        }
    }
}
