namespace WinForms_CS
{
    partial class snake2
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

        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnreiniciar = new System.Windows.Forms.Button();
            this.btnplay = new System.Windows.Forms.Button();
            this.lbdades = new System.Windows.Forms.Label();
            this.pnjoc = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.lbrec = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Teal;
            this.panel1.Controls.Add(this.lbrec);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.btnreiniciar);
            this.panel1.Controls.Add(this.btnplay);
            this.panel1.Controls.Add(this.lbdades);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel1.Location = new System.Drawing.Point(515, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(387, 513);
            this.panel1.TabIndex = 0;
            // 
            // btnreiniciar
            // 
            this.btnreiniciar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnreiniciar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnreiniciar.Location = new System.Drawing.Point(12, 186);
            this.btnreiniciar.Name = "btnreiniciar";
            this.btnreiniciar.Size = new System.Drawing.Size(354, 63);
            this.btnreiniciar.TabIndex = 2;
            this.btnreiniciar.Text = "Reiniciar (r)";
            this.btnreiniciar.UseVisualStyleBackColor = true;
            // 
            // btnplay
            // 
            this.btnplay.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnplay.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnplay.Location = new System.Drawing.Point(12, 117);
            this.btnplay.Name = "btnplay";
            this.btnplay.Size = new System.Drawing.Size(354, 63);
            this.btnplay.TabIndex = 1;
            this.btnplay.Text = "Iniciar (i)";
            this.btnplay.UseVisualStyleBackColor = true;
            // 
            // lbdades
            // 
            this.lbdades.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbdades.Font = new System.Drawing.Font("Segoe UI", 24F);
            this.lbdades.Location = new System.Drawing.Point(6, 9);
            this.lbdades.Name = "lbdades";
            this.lbdades.Size = new System.Drawing.Size(366, 70);
            this.lbdades.TabIndex = 0;
            this.lbdades.Text = "Rècord: 0";
            this.lbdades.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // pnjoc
            // 
            this.pnjoc.BackColor = System.Drawing.Color.CadetBlue;
            this.pnjoc.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnjoc.Location = new System.Drawing.Point(0, 0);
            this.pnjoc.Name = "pnjoc";
            this.pnjoc.Size = new System.Drawing.Size(515, 513);
            this.pnjoc.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.Location = new System.Drawing.Point(9, 252);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(366, 107);
            this.label1.TabIndex = 3;
            this.label1.Text = "Groc: WASD\r\nLila: fletxes";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lbrec
            // 
            this.lbrec.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbrec.Font = new System.Drawing.Font("Segoe UI", 34F);
            this.lbrec.ForeColor = System.Drawing.Color.Gold;
            this.lbrec.Location = new System.Drawing.Point(9, 338);
            this.lbrec.Name = "lbrec";
            this.lbrec.Size = new System.Drawing.Size(366, 112);
            this.lbrec.TabIndex = 5;
            this.lbrec.Text = "Nou Record!!";
            this.lbrec.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // snake2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightBlue;
            this.ClientSize = new System.Drawing.Size(902, 513);
            this.Controls.Add(this.pnjoc);
            this.Controls.Add(this.panel1);
            this.Font = new System.Drawing.Font("Segoe UI", 14F);
            this.ForeColor = System.Drawing.Color.White;
            this.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(889, 546);
            this.Name = "snake2";
            this.Text = "Joc de la serp";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnreiniciar;
        private System.Windows.Forms.Button btnplay;
        private System.Windows.Forms.Label lbdades;
        private System.Windows.Forms.Panel pnjoc;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lbrec;
    }
}