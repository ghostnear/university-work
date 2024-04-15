namespace Manga
{
    partial class MangaWindow
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
            this.components = new System.ComponentModel.Container();
            this.MangaDataGrid = new System.Windows.Forms.DataGridView();
            this.ID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.titleDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.totalChaptersDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.mangaTypeDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.physicallyOwnedDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.mangaBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.mangaDBDataSet = new Manga.MangaDBDataSet();
            this.DeleteButton = new System.Windows.Forms.Button();
            this.MangaCoverDataGrid = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.mangaTableAdapter = new Manga.MangaDBDataSetTableAdapters.MangaTableAdapter();
            this.mangaCoverBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.mangaCoverTableAdapter = new Manga.MangaDBDataSetTableAdapters.MangaCoverTableAdapter();
            this.AddButton = new System.Windows.Forms.Button();
            this.EditButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.MangaDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaDBDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MangaCoverDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaCoverBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // MangaDataGrid
            // 
            this.MangaDataGrid.AllowUserToAddRows = false;
            this.MangaDataGrid.AllowUserToDeleteRows = false;
            this.MangaDataGrid.AutoGenerateColumns = false;
            this.MangaDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.MangaDataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ID,
            this.titleDataGridViewTextBoxColumn,
            this.totalChaptersDataGridViewTextBoxColumn,
            this.mangaTypeDataGridViewTextBoxColumn,
            this.physicallyOwnedDataGridViewCheckBoxColumn});
            this.MangaDataGrid.DataSource = this.mangaBindingSource;
            this.MangaDataGrid.Location = new System.Drawing.Point(10, 11);
            this.MangaDataGrid.Margin = new System.Windows.Forms.Padding(2);
            this.MangaDataGrid.Name = "MangaDataGrid";
            this.MangaDataGrid.ReadOnly = true;
            this.MangaDataGrid.RowTemplate.Height = 24;
            this.MangaDataGrid.Size = new System.Drawing.Size(564, 266);
            this.MangaDataGrid.TabIndex = 0;
            this.MangaDataGrid.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.MangaDataGrid_CellClick);
            // 
            // ID
            // 
            this.ID.DataPropertyName = "ID";
            this.ID.HeaderText = "ID";
            this.ID.Name = "ID";
            this.ID.ReadOnly = true;
            // 
            // titleDataGridViewTextBoxColumn
            // 
            this.titleDataGridViewTextBoxColumn.DataPropertyName = "Title";
            this.titleDataGridViewTextBoxColumn.HeaderText = "Title";
            this.titleDataGridViewTextBoxColumn.Name = "titleDataGridViewTextBoxColumn";
            this.titleDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // totalChaptersDataGridViewTextBoxColumn
            // 
            this.totalChaptersDataGridViewTextBoxColumn.DataPropertyName = "TotalChapters";
            this.totalChaptersDataGridViewTextBoxColumn.HeaderText = "TotalChapters";
            this.totalChaptersDataGridViewTextBoxColumn.Name = "totalChaptersDataGridViewTextBoxColumn";
            this.totalChaptersDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // mangaTypeDataGridViewTextBoxColumn
            // 
            this.mangaTypeDataGridViewTextBoxColumn.DataPropertyName = "MangaType";
            this.mangaTypeDataGridViewTextBoxColumn.HeaderText = "MangaType";
            this.mangaTypeDataGridViewTextBoxColumn.Name = "mangaTypeDataGridViewTextBoxColumn";
            this.mangaTypeDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // physicallyOwnedDataGridViewCheckBoxColumn
            // 
            this.physicallyOwnedDataGridViewCheckBoxColumn.DataPropertyName = "PhysicallyOwned";
            this.physicallyOwnedDataGridViewCheckBoxColumn.HeaderText = "PhysicallyOwned";
            this.physicallyOwnedDataGridViewCheckBoxColumn.Name = "physicallyOwnedDataGridViewCheckBoxColumn";
            this.physicallyOwnedDataGridViewCheckBoxColumn.ReadOnly = true;
            // 
            // mangaBindingSource
            // 
            this.mangaBindingSource.DataMember = "Manga";
            this.mangaBindingSource.DataSource = this.mangaDBDataSet;
            // 
            // mangaDBDataSet
            // 
            this.mangaDBDataSet.DataSetName = "MangaDBDataSet";
            this.mangaDBDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // DeleteButton
            // 
            this.DeleteButton.Location = new System.Drawing.Point(579, 373);
            this.DeleteButton.Margin = new System.Windows.Forms.Padding(2);
            this.DeleteButton.Name = "DeleteButton";
            this.DeleteButton.Size = new System.Drawing.Size(98, 28);
            this.DeleteButton.TabIndex = 1;
            this.DeleteButton.Text = "Remove cover";
            this.DeleteButton.UseVisualStyleBackColor = true;
            this.DeleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
            // 
            // MangaCoverDataGrid
            // 
            this.MangaCoverDataGrid.AllowUserToAddRows = false;
            this.MangaCoverDataGrid.AllowUserToDeleteRows = false;
            this.MangaCoverDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.MangaCoverDataGrid.Location = new System.Drawing.Point(10, 295);
            this.MangaCoverDataGrid.Margin = new System.Windows.Forms.Padding(2);
            this.MangaCoverDataGrid.Name = "MangaCoverDataGrid";
            this.MangaCoverDataGrid.ReadOnly = true;
            this.MangaCoverDataGrid.RowTemplate.Height = 24;
            this.MangaCoverDataGrid.Size = new System.Drawing.Size(564, 106);
            this.MangaCoverDataGrid.TabIndex = 2;
            this.MangaCoverDataGrid.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.MangaCoverDataGrid_CellClick);
            this.MangaCoverDataGrid.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.MangaCoverDataGrid_CellEndEdit);
            this.MangaCoverDataGrid.UserAddedRow += new System.Windows.Forms.DataGridViewRowEventHandler(this.MangaCoverDataGrid_UserAddedRow);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 280);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(154, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Covers for the selected manga:";
            // 
            // mangaTableAdapter
            // 
            this.mangaTableAdapter.ClearBeforeFill = true;
            // 
            // mangaCoverBindingSource
            // 
            this.mangaCoverBindingSource.DataMember = "MangaCover";
            this.mangaCoverBindingSource.DataSource = this.mangaDBDataSet;
            // 
            // mangaCoverTableAdapter
            // 
            this.mangaCoverTableAdapter.ClearBeforeFill = true;
            // 
            // AddButton
            // 
            this.AddButton.Location = new System.Drawing.Point(579, 295);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(98, 30);
            this.AddButton.TabIndex = 4;
            this.AddButton.Text = "Add Cover";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // EditButton
            // 
            this.EditButton.Location = new System.Drawing.Point(579, 331);
            this.EditButton.Name = "EditButton";
            this.EditButton.Size = new System.Drawing.Size(98, 37);
            this.EditButton.TabIndex = 5;
            this.EditButton.Text = "Edit Cover";
            this.EditButton.UseVisualStyleBackColor = true;
            this.EditButton.Click += new System.EventHandler(this.EditButton_Click);
            // 
            // MangaWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 410);
            this.Controls.Add(this.EditButton);
            this.Controls.Add(this.AddButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MangaCoverDataGrid);
            this.Controls.Add(this.DeleteButton);
            this.Controls.Add(this.MangaDataGrid);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.Name = "MangaWindow";
            this.Text = "MyMangaList";
            this.Load += new System.EventHandler(this.MangaWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.MangaDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaDBDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MangaCoverDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mangaCoverBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView MangaDataGrid;
        private System.Windows.Forms.Button DeleteButton;
        private System.Windows.Forms.DataGridView MangaCoverDataGrid;
        private System.Windows.Forms.Label label1;
        private MangaDBDataSet mangaDBDataSet;
        private System.Windows.Forms.BindingSource mangaBindingSource;
        private MangaDBDataSetTableAdapters.MangaTableAdapter mangaTableAdapter;
        private System.Windows.Forms.BindingSource mangaCoverBindingSource;
        private MangaDBDataSetTableAdapters.MangaCoverTableAdapter mangaCoverTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn ID;
        private System.Windows.Forms.DataGridViewTextBoxColumn titleDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn totalChaptersDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn mangaTypeDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn physicallyOwnedDataGridViewCheckBoxColumn;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.Button EditButton;
    }
}