using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Manga
{
    public partial class MangaWindow : Form
    {
        int currentlySelectedMangaID = -1, currentlySelectedCoverID = -1;

        public MangaWindow()
        {
            InitializeComponent();
        }

        private void MangaWindow_Load(object sender, EventArgs e)
        {
            mangaTableAdapter.Fill(this.mangaDBDataSet.Manga);
        }

        void updateMangaCoverGrid()
        {
            SqlConnection connectionString = new SqlConnection(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=MangaDB;Integrated Security=True");

            string command = "SELECT * FROM MangaCover WHERE Manga=@mangaID";

            SqlCommand getCoversByManga = new SqlCommand(command, connectionString);
            getCoversByManga.Parameters.AddWithValue("@mangaID", currentlySelectedMangaID);

            DataSet resultData = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter(getCoversByManga);

            dataAdapter.Fill(resultData, "MangaCovers");

            MangaCoverDataGrid.DataSource = resultData.Tables["MangaCovers"];
            MangaCoverDataGrid.Columns[0].Visible = false;
            MangaCoverDataGrid.Columns[2].Visible = false;
            MangaCoverDataGrid.Columns[1].Width = 500;

            MangaCoverDataGrid.ClearSelection();
        }

        private void MangaDataGrid_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;

            currentlySelectedMangaID = (int)MangaDataGrid.Rows[e.RowIndex].Cells[0].Value;
            currentlySelectedCoverID = -1;

            updateMangaCoverGrid();
        }

        private void MangaCoverDataGrid_UserAddedRow(object sender, DataGridViewRowEventArgs e)
        {
            // Done somewhere else.
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if(currentlySelectedCoverID == -1)
            {
                MessageBox.Show("Please select a cover to delete first.");
                return;
            }

            SqlConnection sqlConnection = new SqlConnection(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=MangaDB;Integrated Security=True");

            string command = "DELETE FROM MangaCover WHERE ID=@coverID";

            SqlCommand insertCover = new SqlCommand(command, sqlConnection);
            insertCover.Parameters.AddWithValue("@coverID", currentlySelectedCoverID);

            sqlConnection.Open();

            insertCover.ExecuteNonQuery();

            sqlConnection.Close();

            updateMangaCoverGrid();
        }

        private void MangaCoverDataGrid_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;

            currentlySelectedCoverID = (int)MangaCoverDataGrid.Rows[e.RowIndex].Cells[0].Value;
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            AddForm addForm = new AddForm(currentlySelectedMangaID);
            addForm.ShowDialog();

            updateMangaCoverGrid();
        }

        private void EditButton_Click(object sender, EventArgs e)
        {
            if (currentlySelectedCoverID == -1)
            {
                MessageBox.Show("Please select a cover to edit first.");
                return;
            }

            EditForm editForm = new EditForm(currentlySelectedCoverID);
            editForm.ShowDialog();

            updateMangaCoverGrid();
        }

        private void MangaCoverDataGrid_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            // Done somewhere else.
        }
    }
}
