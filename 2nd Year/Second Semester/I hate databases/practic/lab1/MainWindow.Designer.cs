namespace Lab1
{
    partial class MainWindow
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
            this.dgvSports = new System.Windows.Forms.DataGridView();
            this.dgvPlayers = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.UpdateDB_Button = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvPlayers)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvSports
            // 
            this.dgvSports.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvSports.Location = new System.Drawing.Point(16, 33);
            this.dgvSports.Margin = new System.Windows.Forms.Padding(4);
            this.dgvSports.Name = "dgvSports";
            this.dgvSports.RowHeadersWidth = 51;
            this.dgvSports.Size = new System.Drawing.Size(479, 448);
            this.dgvSports.TabIndex = 0;
            // 
            // dgvPlayers
            // 
            this.dgvPlayers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvPlayers.Location = new System.Drawing.Point(553, 33);
            this.dgvPlayers.Margin = new System.Windows.Forms.Padding(4);
            this.dgvPlayers.Name = "dgvPlayers";
            this.dgvPlayers.RowHeadersWidth = 51;
            this.dgvPlayers.Size = new System.Drawing.Size(479, 448);
            this.dgvPlayers.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 10);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 16);
            this.label1.TabIndex = 2;
            this.label1.Text = "Sports";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(565, 10);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 16);
            this.label2.TabIndex = 3;
            this.label2.Text = "Players";
            // 
            // UpdateDB_Button
            // 
            this.UpdateDB_Button.Location = new System.Drawing.Point(407, 502);
            this.UpdateDB_Button.Margin = new System.Windows.Forms.Padding(4);
            this.UpdateDB_Button.Name = "UpdateDB_Button";
            this.UpdateDB_Button.Size = new System.Drawing.Size(238, 28);
            this.UpdateDB_Button.TabIndex = 4;
            this.UpdateDB_Button.Text = "Save changes to database";
            this.UpdateDB_Button.UseVisualStyleBackColor = true;
            this.UpdateDB_Button.Click += new System.EventHandler(this.UpdateDB_Button_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1067, 554);
            this.Controls.Add(this.UpdateDB_Button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dgvPlayers);
            this.Controls.Add(this.dgvSports);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "MainWindow";
            this.Text = "MainWindow";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvPlayers)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvSports;
        private System.Windows.Forms.DataGridView dgvPlayers;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button UpdateDB_Button;
    }
}

