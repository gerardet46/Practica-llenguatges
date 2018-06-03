namespace WinForms_CS
{
    partial class serp_dialeg
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
            this.btnsol = new System.Windows.Forms.Button();
            this.lbdades = new System.Windows.Forms.Label();
            this.btnxocar = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnsol
            // 
            this.btnsol.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnsol.BackColor = System.Drawing.Color.Teal;
            this.btnsol.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnsol.ForeColor = System.Drawing.Color.White;
            this.btnsol.Location = new System.Drawing.Point(14, 76);
            this.btnsol.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnsol.Name = "btnsol";
            this.btnsol.Size = new System.Drawing.Size(580, 122);
            this.btnsol.TabIndex = 2;
            this.btnsol.Text = "Tot sol (aconseguir menjar)";
            this.btnsol.UseVisualStyleBackColor = false;
            // 
            // lbdades
            // 
            this.lbdades.Dock = System.Windows.Forms.DockStyle.Top;
            this.lbdades.Font = new System.Drawing.Font("Segoe UI", 24F);
            this.lbdades.ForeColor = System.Drawing.Color.White;
            this.lbdades.Location = new System.Drawing.Point(0, 0);
            this.lbdades.Name = "lbdades";
            this.lbdades.Size = new System.Drawing.Size(608, 70);
            this.lbdades.TabIndex = 3;
            this.lbdades.Text = "Tria el mode de joc";
            this.lbdades.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnxocar
            // 
            this.btnxocar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnxocar.BackColor = System.Drawing.Color.Teal;
            this.btnxocar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnxocar.ForeColor = System.Drawing.Color.White;
            this.btnxocar.Location = new System.Drawing.Point(14, 210);
            this.btnxocar.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.btnxocar.Name = "btnxocar";
            this.btnxocar.Size = new System.Drawing.Size(580, 122);
            this.btnxocar.TabIndex = 4;
            this.btnxocar.Text = "Dos jugadors (no xocar-se)";
            this.btnxocar.UseVisualStyleBackColor = false;
            // 
            // serp_dialeg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.CadetBlue;
            this.ClientSize = new System.Drawing.Size(608, 362);
            this.Controls.Add(this.btnxocar);
            this.Controls.Add(this.lbdades);
            this.Controls.Add(this.btnsol);
            this.Font = new System.Drawing.Font("Segoe UI", 14F);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.Name = "serp_dialeg";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Mode de joc";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnsol;
        private System.Windows.Forms.Label lbdades;
        private System.Windows.Forms.Button btnxocar;
    }
}
