using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Lab1
{
    public partial class MainWindow : Form
    {
        private DataSet dataSet = new DataSet();
        private SqlConnection dbConnection;
        private SqlDataAdapter dataAdapterSports, dataAdapterPlayers;
        private BindingSource bindingSourceSports = new BindingSource();
        private BindingSource bindingSourcePlayers = new BindingSource();

        private void InitializeDatabase()
        {
            dbConnection = new SqlConnection("Data Source=localhost;Initial Catalog=SportDB;Integrated Security=True;TrustServerCertificate=True");
            dataAdapterSports = new SqlDataAdapter($"SELECT * FROM Sports", dbConnection);
            dataAdapterPlayers = new SqlDataAdapter($"SELECT * FROM Players", dbConnection);

            new SqlCommandBuilder(dataAdapterPlayers);

            dataAdapterSports.Fill(dataSet, "Sports");
            dataAdapterPlayers.Fill(dataSet, "Players");

            dataSet.Relations.Add(new DataRelation(
                "Playing_Relation",
                dataSet.Tables["Sports"].Columns["ID"],
                dataSet.Tables["Players"].Columns["Sport"]
            ));
        }

        private void InitializeUI()
        {
            bindingSourceSports.DataSource = dataSet;
            bindingSourceSports.DataMember = "Sports";

            bindingSourcePlayers.DataSource = bindingSourceSports;
            bindingSourcePlayers.DataMember = "Playing_Relation";

            dgvSports.DataSource = bindingSourceSports;
            dgvPlayers.DataSource = bindingSourcePlayers;
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            InitializeDatabase();
            InitializeUI();
        }

        private void UpdateDB_Button_Click(object sender, EventArgs e)
        {
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapterSports);
            builder.GetInsertCommand();
            dataAdapterPlayers.Update(dataSet, "Players");
            dataAdapterSports.Update(dataSet, "Sports");

            dataSet.Clear();
            dataAdapterSports.Fill(dataSet, "Sports");
            dataAdapterPlayers.Fill(dataSet, "Players");
        }
    }
}
