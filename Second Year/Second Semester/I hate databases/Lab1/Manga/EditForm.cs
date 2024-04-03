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
    public partial class EditForm : Form
    {
        int coverID = -1;

        public EditForm(int coverID)
        {
            InitializeComponent();

            this.coverID = coverID;

            updateCoverData();
        }

        void updateCoverData()
        {
            SqlConnection connectionString = new SqlConnection(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=MangaDB;Integrated Security=True");

            string command = "SELECT ID, FilePath, Manga FROM MangaCover WHERE ID=@coverID";

            SqlCommand getCoversByManga = new SqlCommand(command, connectionString);
            getCoversByManga.Parameters.AddWithValue("@coverID", coverID);

            DataSet resultData = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter(getCoversByManga);

            dataAdapter.Fill(resultData, "MangaCovers");

            FilePathTextBox.Text = (string)resultData.Tables["MangaCovers"].Rows[0]["FilePath"];
        }

        private void EditButton_Click(object sender, EventArgs e)
        {
            SqlConnection connectionString = new SqlConnection(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=MangaDB;Integrated Security=True");

            string command = "UPDATE MangaCover SET FilePath=@filePath WHERE ID=@coverID";

            SqlCommand updateCover = new SqlCommand(command, connectionString);

            updateCover.Parameters.AddWithValue("@filePath", FilePathTextBox.Text);

            updateCover.Parameters.AddWithValue("@coverID", coverID);

            connectionString.Open();

            updateCover.ExecuteNonQuery();

            connectionString.Close();

            this.Close();
        }
    }
}
