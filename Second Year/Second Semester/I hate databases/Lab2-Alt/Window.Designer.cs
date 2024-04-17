namespace Lab2
{
    partial class Window
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
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.commitButton = new System.Windows.Forms.Button();
            this.childDataGridView = new System.Windows.Forms.DataGridView();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.parentDataGridView = new System.Windows.Forms.DataGridView();
            this.parentLabel = new System.Windows.Forms.Label();
            this.childLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.commitButton, 0, 0);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(1, 506);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(595, 60);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // commitButton
            // 
            this.commitButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.commitButton.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.commitButton.Location = new System.Drawing.Point(123, 6);
            this.commitButton.Name = "commitButton";
            this.commitButton.Size = new System.Drawing.Size(349, 47);
            this.commitButton.TabIndex = 0;
            this.commitButton.Text = "Save changes";
            this.commitButton.UseVisualStyleBackColor = true;
            this.commitButton.Click += new System.EventHandler(this.commitChangesButton_Click);
            // 
            // childDataGridView
            // 
            this.childDataGridView.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.childDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childDataGridView.Location = new System.Drawing.Point(3, 304);
            this.childDataGridView.Name = "childDataGridView";
            this.childDataGridView.RowHeadersWidth = 51;
            this.childDataGridView.RowTemplate.Height = 24;
            this.childDataGridView.Size = new System.Drawing.Size(589, 196);
            this.childDataGridView.TabIndex = 0;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.childDataGridView, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.parentDataGridView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.parentLabel, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.childLabel, 0, 2);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(1, -3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10.57692F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 89.42308F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 31F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 201F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(595, 503);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // parentDataGridView
            // 
            this.parentDataGridView.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.parentDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentDataGridView.Location = new System.Drawing.Point(3, 31);
            this.parentDataGridView.Name = "parentDataGridView";
            this.parentDataGridView.RowHeadersWidth = 51;
            this.parentDataGridView.RowTemplate.Height = 24;
            this.parentDataGridView.Size = new System.Drawing.Size(589, 235);
            this.parentDataGridView.TabIndex = 1;
            // 
            // parentLabel
            // 
            this.parentLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.parentLabel.AutoSize = true;
            this.parentLabel.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.parentLabel.Location = new System.Drawing.Point(3, 4);
            this.parentLabel.Name = "parentLabel";
            this.parentLabel.Size = new System.Drawing.Size(54, 19);
            this.parentLabel.TabIndex = 2;
            this.parentLabel.Text = "First";
            // 
            // childLabel
            // 
            this.childLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.childLabel.AutoSize = true;
            this.childLabel.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.childLabel.Location = new System.Drawing.Point(3, 276);
            this.childLabel.Name = "childLabel";
            this.childLabel.Size = new System.Drawing.Size(63, 19);
            this.childLabel.TabIndex = 3;
            this.childLabel.Text = "Second";
            // 
            // Window
            // 
            this.ClientSize = new System.Drawing.Size(594, 574);
            this.Controls.Add(this.tableLayoutPanel2);
            this.Controls.Add(this.tableLayoutPanel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "Window";
            this.Text = "Database Viewer";
            this.Load += new System.EventHandler(this.Window_Load);
            this.tableLayoutPanel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).EndInit();
            this.ResumeLayout(false);

        }

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button commitButton;
        private System.Windows.Forms.DataGridView childDataGridView;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridView parentDataGridView;
        private System.Windows.Forms.Label parentLabel;
        private System.Windows.Forms.Label childLabel;
    }
}

