namespace WinForms_CS
{
    partial class frmrellotge_analogic
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lbhora = new System.Windows.Forms.Label();
            this.separador1 = new WinForms_CS.separador();
            this.SuspendLayout();
            // 
            // lbhora
            // 
            this.lbhora.Dock = System.Windows.Forms.DockStyle.Top;
            this.lbhora.Font = new System.Drawing.Font("Microsoft Sans Serif", 50F);
            this.lbhora.ForeColor = System.Drawing.Color.White;
            this.lbhora.Location = new System.Drawing.Point(0, 0);
            this.lbhora.Name = "lbhora";
            this.lbhora.Size = new System.Drawing.Size(732, 127);
            this.lbhora.TabIndex = 0;
            this.lbhora.Text = "Hora";
            this.lbhora.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // separador1
            // 
            this.separador1.BackColor = System.Drawing.Color.White;
            this.separador1.Dock = System.Windows.Forms.DockStyle.Top;
            this.separador1.Grosor = 3;
            this.separador1.Location = new System.Drawing.Point(0, 127);
            this.separador1.Name = "separador1";
            this.separador1.Size = new System.Drawing.Size(732, 3);
            this.separador1.TabIndex = 1;
            this.separador1.Tipus = WinForms_CS.separador.TIPUS.HORITZONTAL;
            // 
            // frmrellotge_analogic
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.MediumSeaGreen;
            this.ClientSize = new System.Drawing.Size(732, 658);
            this.Controls.Add(this.separador1);
            this.Controls.Add(this.lbhora);
            this.Name = "frmrellotge_analògic";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "rellotge analògic";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lbhora;
        private separador separador1;
    }
}
