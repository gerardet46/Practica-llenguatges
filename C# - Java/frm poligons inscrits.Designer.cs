namespace WinForms_CS
{
    partial class frmpol
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.lbcostats = new System.Windows.Forms.Label();
            this.tbcostats = new System.Windows.Forms.TrackBar();
            this.clpoligon = new System.Windows.Forms.Panel();
            this.clcercle = new System.Windows.Forms.Panel();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbinfinit = new System.Windows.Forms.RadioButton();
            this.rbdos = new System.Windows.Forms.RadioButton();
            this.rbcircuns = new System.Windows.Forms.RadioButton();
            this.rbinscrit = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.radi = new System.Windows.Forms.TrackBar();
            this.separador4 = new WinForms_CS.separador();
            this.separador3 = new WinForms_CS.separador();
            this.separador2 = new WinForms_CS.separador();
            this.separador1 = new WinForms_CS.separador();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tbcostats)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radi)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.BurlyWood;
            this.panel1.Controls.Add(this.lbcostats);
            this.panel1.Controls.Add(this.tbcostats);
            this.panel1.Controls.Add(this.separador3);
            this.panel1.Controls.Add(this.separador2);
            this.panel1.Controls.Add(this.separador1);
            this.panel1.Controls.Add(this.clpoligon);
            this.panel1.Controls.Add(this.clcercle);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.groupBox1);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.radi);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1547, 100);
            this.panel1.TabIndex = 0;
            // 
            // lbcostats
            // 
            this.lbcostats.AutoSize = true;
            this.lbcostats.Location = new System.Drawing.Point(838, 2);
            this.lbcostats.Name = "lbcostats";
            this.lbcostats.Size = new System.Drawing.Size(222, 32);
            this.lbcostats.TabIndex = 13;
            this.lbcostats.Text = "Nombre de costats:";
            // 
            // tbcostats
            // 
            this.tbcostats.Location = new System.Drawing.Point(838, 37);
            this.tbcostats.Maximum = 25;
            this.tbcostats.Minimum = 3;
            this.tbcostats.Name = "tbcostats";
            this.tbcostats.Size = new System.Drawing.Size(388, 56);
            this.tbcostats.TabIndex = 3;
            this.tbcostats.Value = 3;
            // 
            // clpoligon
            // 
            this.clpoligon.BackColor = System.Drawing.Color.Green;
            this.clpoligon.Cursor = System.Windows.Forms.Cursors.Hand;
            this.clpoligon.Location = new System.Drawing.Point(1381, 50);
            this.clpoligon.Name = "clpoligon";
            this.clpoligon.Size = new System.Drawing.Size(49, 35);
            this.clpoligon.TabIndex = 11;
            // 
            // clcercle
            // 
            this.clcercle.BackColor = System.Drawing.Color.DarkRed;
            this.clcercle.Cursor = System.Windows.Forms.Cursors.Hand;
            this.clcercle.Location = new System.Drawing.Point(1381, 9);
            this.clcercle.Name = "clcercle";
            this.clcercle.Size = new System.Drawing.Size(49, 35);
            this.clcercle.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1275, 47);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(100, 32);
            this.label3.TabIndex = 9;
            this.label3.Text = "Polígon:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1275, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 32);
            this.label2.TabIndex = 8;
            this.label2.Text = "Cercle:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbinfinit);
            this.groupBox1.Controls.Add(this.rbdos);
            this.groupBox1.Controls.Add(this.rbcircuns);
            this.groupBox1.Controls.Add(this.rbinscrit);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(346, -16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(486, 116);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // rbinfinit
            // 
            this.rbinfinit.AutoSize = true;
            this.rbinfinit.Location = new System.Drawing.Point(213, 67);
            this.rbinfinit.Name = "rbinfinit";
            this.rbinfinit.Size = new System.Drawing.Size(163, 36);
            this.rbinfinit.TabIndex = 5;
            this.rbinfinit.Text = "Bucle infinit";
            this.rbinfinit.UseVisualStyleBackColor = true;
            // 
            // rbdos
            // 
            this.rbdos.AutoSize = true;
            this.rbdos.Location = new System.Drawing.Point(213, 25);
            this.rbdos.Name = "rbdos";
            this.rbdos.Size = new System.Drawing.Size(195, 36);
            this.rbdos.TabIndex = 4;
            this.rbdos.Text = "Els dos a l\'hora";
            this.rbdos.UseVisualStyleBackColor = true;
            // 
            // rbcircuns
            // 
            this.rbcircuns.AutoSize = true;
            this.rbcircuns.Location = new System.Drawing.Point(8, 67);
            this.rbcircuns.Name = "rbcircuns";
            this.rbcircuns.Size = new System.Drawing.Size(147, 36);
            this.rbcircuns.TabIndex = 3;
            this.rbcircuns.Text = "Circunscrit";
            this.rbcircuns.UseVisualStyleBackColor = true;
            // 
            // rbinscrit
            // 
            this.rbinscrit.AutoSize = true;
            this.rbinscrit.Checked = true;
            this.rbinscrit.Location = new System.Drawing.Point(8, 25);
            this.rbinscrit.Name = "rbinscrit";
            this.rbinscrit.Size = new System.Drawing.Size(99, 36);
            this.rbinscrit.TabIndex = 2;
            this.rbinscrit.TabStop = true;
            this.rbinscrit.Text = "Inscrit";
            this.rbinscrit.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 32);
            this.label1.TabIndex = 1;
            this.label1.Text = "Radi:";
            // 
            // radi
            // 
            this.radi.Location = new System.Drawing.Point(12, 44);
            this.radi.Maximum = 1000;
            this.radi.Minimum = 200;
            this.radi.Name = "radi";
            this.radi.Size = new System.Drawing.Size(304, 56);
            this.radi.TabIndex = 0;
            this.radi.Value = 200;
            // 
            // separador4
            // 
            this.separador4.BackColor = System.Drawing.Color.Black;
            this.separador4.Dock = System.Windows.Forms.DockStyle.Top;
            this.separador4.Grosor = 2;
            this.separador4.Location = new System.Drawing.Point(0, 100);
            this.separador4.Name = "separador4";
            this.separador4.Size = new System.Drawing.Size(1547, 2);
            this.separador4.TabIndex = 2;
            this.separador4.Tipus = WinForms_CS.separador.TIPUS.HORITZONTAL;
            // 
            // separador3
            // 
            this.separador3.BackColor = System.Drawing.Color.Black;
            this.separador3.Grosor = 2;
            this.separador3.Location = new System.Drawing.Point(346, 0);
            this.separador3.Name = "separador3";
            this.separador3.Size = new System.Drawing.Size(2, 100);
            this.separador3.TabIndex = 1;
            this.separador3.Tipus = WinForms_CS.separador.TIPUS.VERTICAL;
            // 
            // separador2
            // 
            this.separador2.BackColor = System.Drawing.Color.Black;
            this.separador2.Grosor = 2;
            this.separador2.Location = new System.Drawing.Point(1242, 0);
            this.separador2.Name = "separador2";
            this.separador2.Size = new System.Drawing.Size(2, 100);
            this.separador2.TabIndex = 1;
            this.separador2.Tipus = WinForms_CS.separador.TIPUS.VERTICAL;
            // 
            // separador1
            // 
            this.separador1.BackColor = System.Drawing.Color.Black;
            this.separador1.Grosor = 2;
            this.separador1.Location = new System.Drawing.Point(830, 2);
            this.separador1.Name = "separador1";
            this.separador1.Size = new System.Drawing.Size(2, 100);
            this.separador1.TabIndex = 0;
            this.separador1.Tipus = WinForms_CS.separador.TIPUS.VERTICAL;
            // 
            // frmpol
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Bisque;
            this.ClientSize = new System.Drawing.Size(1547, 442);
            this.Controls.Add(this.separador4);
            this.Controls.Add(this.panel1);
            this.Font = new System.Drawing.Font("Segoe UI", 14F);
            this.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.MaximizeBox = false;
            this.Name = "frmpol";
            this.Text = "Triàngle inscrit i circunscrit";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tbcostats)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radi)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar radi;
        private System.Windows.Forms.RadioButton rbdos;
        private System.Windows.Forms.RadioButton rbcircuns;
        private System.Windows.Forms.RadioButton rbinscrit;
        private System.Windows.Forms.RadioButton rbinfinit;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel clcercle;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel clpoligon;
        private separador separador1;
        private separador separador3;
        private separador separador2;
        private separador separador4;
        private System.Windows.Forms.Label lbcostats;
        private System.Windows.Forms.TrackBar tbcostats;
    }
}

