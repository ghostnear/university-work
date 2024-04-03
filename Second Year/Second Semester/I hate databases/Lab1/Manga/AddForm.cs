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
    public partial class AddForm : Form
    {
        int mangaID = -1;

        public AddForm()
        {
            InitializeComponent();
        }

        public AddForm(int mangaID)
        {
            InitializeComponent();
            this.mangaID = mangaID;
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            SqlConnection sqlConnection = new SqlConnection(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=MangaDB;Integrated Security=True");

            string command = "INSERT INTO MangaCover (FilePath, Manga) VALUES (@filePath, @mangaID)";

            sqlConnection.Open();

            SqlCommand insertCover = new SqlCommand(command, sqlConnection);

            insertCover.Parameters.AddWithValue("@filePath", FilePathTextBox.Text);
            insertCover.Parameters.AddWithValue("@mangaID", mangaID);

            insertCover.ExecuteNonQuery();

            sqlConnection.Close();

            this.Close();
        }
    }
}
