namespace WinForms_CS
{
    partial class conway
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(conway));
            this.panel1 = new System.Windows.Forms.Panel();
            this.amplada = new System.Windows.Forms.TrackBar();
            this.velocitat = new System.Windows.Forms.TrackBar();
            this.btnborrar = new System.Windows.Forms.Button();
            this.btnproxim = new System.Windows.Forms.Button();
            this.btnplay = new System.Windows.Forms.Button();
            this.lbample = new System.Windows.Forms.Label();
            this.lbvel = new System.Windows.Forms.Label();
            this.lbgen = new System.Windows.Forms.Label();
            this.btnobrir = new System.Windows.Forms.Button();
            this.btnguardar = new System.Windows.Forms.Button();
            this.cbgraella = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.amplada)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.velocitat)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(14, 15);
            this.panel1.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(790, 852);
            this.panel1.TabIndex = 0;
            // 
            // amplada
            // 
            this.amplada.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.amplada.Location = new System.Drawing.Point(814, 177);
            this.amplada.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.amplada.Maximum = 70;
            this.amplada.Minimum = 10;
            this.amplada.Name = "amplada";
            this.amplada.Size = new System.Drawing.Size(344, 56);
            this.amplada.TabIndex = 1;
            this.amplada.Value = 25;
            // 
            // velocitat
            // 
            this.velocitat.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.velocitat.LargeChange = 2;
            this.velocitat.Location = new System.Drawing.Point(818, 289);
            this.velocitat.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.velocitat.Maximum = 25;
            this.velocitat.Minimum = 1;
            this.velocitat.Name = "velocitat";
            this.velocitat.Size = new System.Drawing.Size(340, 56);
            this.velocitat.TabIndex = 2;
            this.velocitat.Value = 2;
            // 
            // btnborrar
            // 
            this.btnborrar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnborrar.Location = new System.Drawing.Point(814, 427);
            this.btnborrar.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnborrar.Name = "btnborrar";
            this.btnborrar.Size = new System.Drawing.Size(344, 68);
            this.btnborrar.TabIndex = 3;
            this.btnborrar.Text = "&Borrar (B)";
            this.btnborrar.UseVisualStyleBackColor = true;
            // 
            // btnproxim
            // 
            this.btnproxim.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnproxim.Location = new System.Drawing.Point(814, 507);
            this.btnproxim.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnproxim.Name = "btnproxim";
            this.btnproxim.Size = new System.Drawing.Size(344, 68);
            this.btnproxim.TabIndex = 4;
            this.btnproxim.Text = "&Pròxima generació (P)";
            this.btnproxim.UseVisualStyleBackColor = true;
            // 
            // btnplay
            // 
            this.btnplay.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnplay.Location = new System.Drawing.Point(814, 587);
            this.btnplay.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnplay.Name = "btnplay";
            this.btnplay.Size = new System.Drawing.Size(344, 68);
            this.btnplay.TabIndex = 5;
            this.btnplay.Text = "&Iniciar (i)";
            this.btnplay.UseVisualStyleBackColor = true;
            // 
            // lbample
            // 
            this.lbample.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbample.AutoSize = true;
            this.lbample.Location = new System.Drawing.Point(812, 127);
            this.lbample.Name = "lbample";
            this.lbample.Size = new System.Drawing.Size(284, 32);
            this.lbample.TabIndex = 6;
            this.lbample.Text = "Amplada de cel·la = 25px";
            // 
            // lbvel
            // 
            this.lbvel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbvel.AutoSize = true;
            this.lbvel.Location = new System.Drawing.Point(812, 239);
            this.lbvel.Name = "lbvel";
            this.lbvel.Size = new System.Drawing.Size(216, 32);
            this.lbvel.TabIndex = 7;
            this.lbvel.Text = "Velocitat = 2 gen/s";
            // 
            // lbgen
            // 
            this.lbgen.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbgen.AutoSize = true;
            this.lbgen.Font = new System.Drawing.Font("Segoe UI", 24F);
            this.lbgen.Location = new System.Drawing.Point(849, 34);
            this.lbgen.Name = "lbgen";
            this.lbgen.Size = new System.Drawing.Size(247, 54);
            this.lbgen.TabIndex = 8;
            this.lbgen.Text = "1º generació";
            // 
            // btnobrir
            // 
            this.btnobrir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnobrir.Location = new System.Drawing.Point(814, 816);
            this.btnobrir.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnobrir.Name = "btnobrir";
            this.btnobrir.Size = new System.Drawing.Size(344, 68);
            this.btnobrir.TabIndex = 10;
            this.btnobrir.Text = "&Obrir distribució (O)";
            this.btnobrir.UseVisualStyleBackColor = true;
            // 
            // btnguardar
            // 
            this.btnguardar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnguardar.Location = new System.Drawing.Point(814, 736);
            this.btnguardar.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnguardar.Name = "btnguardar";
            this.btnguardar.Size = new System.Drawing.Size(344, 68);
            this.btnguardar.TabIndex = 9;
            this.btnguardar.Text = "&Guardar distribució (G)";
            this.btnguardar.UseVisualStyleBackColor = true;
            // 
            // cbgraella
            // 
            this.cbgraella.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbgraella.AutoSize = true;
            this.cbgraella.Checked = true;
            this.cbgraella.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbgraella.Location = new System.Drawing.Point(818, 366);
            this.cbgraella.Name = "cbgraella";
            this.cbgraella.Size = new System.Drawing.Size(110, 36);
            this.cbgraella.TabIndex = 11;
            this.cbgraella.Text = "Graella";
            this.cbgraella.UseVisualStyleBackColor = true;
            // 
            // conway
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1172, 876);
            this.Controls.Add(this.cbgraella);
            this.Controls.Add(this.btnobrir);
            this.Controls.Add(this.btnguardar);
            this.Controls.Add(this.lbgen);
            this.Controls.Add(this.lbvel);
            this.Controls.Add(this.lbample);
            this.Controls.Add(this.btnplay);
            this.Controls.Add(this.btnproxim);
            this.Controls.Add(this.btnborrar);
            this.Controls.Add(this.velocitat);
            this.Controls.Add(this.amplada);
            this.Controls.Add(this.panel1);
            this.Font = new System.Drawing.Font("Segoe UI", 14F);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.MinimumSize = new System.Drawing.Size(1190, 864);
            this.Name = "conway";
            this.Text = "Joc de la vida de Conway";
            ((System.ComponentModel.ISupportInitialize)(this.amplada)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.velocitat)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TrackBar amplada;
        private System.Windows.Forms.TrackBar velocitat;
        private System.Windows.Forms.Button btnborrar;
        private System.Windows.Forms.Button btnproxim;
        private System.Windows.Forms.Button btnplay;
        private System.Windows.Forms.Label lbample;
        private System.Windows.Forms.Label lbvel;
        private System.Windows.Forms.Label lbgen;
        private System.Windows.Forms.Button btnobrir;
        private System.Windows.Forms.Button btnguardar;
        private System.Windows.Forms.CheckBox cbgraella;
    }
}