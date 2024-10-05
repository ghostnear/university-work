using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Manga
{
    public partial class Window : Form
    {
        int currentlySelectedMangaID = -1, currentlySelectedCoverID = -1;

        public Window()
        {
            InitializeComponent();

            SqlConnection connectionString = new SqlConnection(ConfigurationManager.ConnectionStrings["database"].ConnectionString);

            string command = ConfigurationManager.AppSettings["SelectMainQuery"];

            SqlCommand getMangas = new SqlCommand(command, connectionString);

            DataSet resultData = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter(getMangas);

            dataAdapter.Fill(resultData, ConfigurationManager.AppSettings["MainTable"]);

            MangaDataGrid.DataSource = resultData.Tables[ConfigurationManager.AppSettings["MainTable"]];
            MangaDataGrid.ClearSelection();
        }

        private void Window_Load(object sender, EventArgs e)
        {
            mangaTableAdapter.Fill(this.mangaDBDataSet.Manga);
        }

        void updateMangaCoverGrid()
        {
            SqlConnection connectionString = new SqlConnection(ConfigurationManager.ConnectionStrings["database"].ConnectionString);

            string command = ConfigurationManager.AppSettings["SelectSecondaryQuery"];

            SqlCommand getCoversByManga = new SqlCommand(command, connectionString);
            getCoversByManga.Parameters.AddWithValue(ConfigurationManager.AppSettings["SelectSecondaryQueryID"], currentlySelectedMangaID);

            DataSet resultData = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter(getCoversByManga);

            dataAdapter.Fill(resultData, ConfigurationManager.AppSettings["SecondaryTable"]);

            MangaCoverDataGrid.DataSource = resultData.Tables[ConfigurationManager.AppSettings["SecondaryTable"]];
            MangaCoverDataGrid.ClearSelection();
        }

        private void MangaDataGrid_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;

            currentlySelectedMangaID = (int)MangaDataGrid.Rows[e.RowIndex].Cells[0].Value;
            currentlySelectedCoverID = -1;

            updateMangaCoverGrid();
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if(currentlySelectedCoverID == -1)
            {
                MessageBox.Show("Please seomething to delete first.");
                return;
            }

            SqlConnection sqlConnection = new SqlConnection(ConfigurationManager.ConnectionStrings["database"].ConnectionString);

            string command = ConfigurationManager.AppSettings["DeleteSecondaryQuery"];

            SqlCommand insertCover = new SqlCommand(command, sqlConnection);
            insertCover.Parameters.AddWithValue(ConfigurationManager.AppSettings["DeleteSecondaryQueryID"], currentlySelectedCoverID);

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
                MessageBox.Show("Please something to edit first.");
                return;
            }

            EditForm editForm = new EditForm(currentlySelectedCoverID);
            editForm.ShowDialog();

            updateMangaCoverGrid();
        }
    }
}
