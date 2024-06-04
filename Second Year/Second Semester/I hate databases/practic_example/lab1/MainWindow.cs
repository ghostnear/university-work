using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Lab1
{
    public partial class MainWindow : Form
    {
        private readonly string Main_Table = "Plane";
        private readonly string Secondary_Table = "Passenger";
        private readonly string FK = "Boarding_Relation";

        private DataSet dataSet = new DataSet();
        private SqlConnection dbConnection;
        private SqlDataAdapter dataAdapterMain, dataAdapterChild;
        private BindingSource bindingSourceMain = new BindingSource();
        private BindingSource bindingSourceChild = new BindingSource();

        private void InitializeDatabase()
        {
            dbConnection = new SqlConnection("Data Source=localhost;Initial Catalog=PlaneDB;Integrated Security=True;TrustServerCertificate=True");
            dataAdapterMain = new SqlDataAdapter($"SELECT * FROM {Main_Table}", dbConnection);
            dataAdapterChild = new SqlDataAdapter($"SELECT * FROM {Secondary_Table}", dbConnection);

            new SqlCommandBuilder(dataAdapterChild);

            dataAdapterMain.Fill(dataSet, Main_Table);
            dataAdapterChild.Fill(dataSet, Secondary_Table);

            dataSet.Relations.Add(new DataRelation(
                FK,
                dataSet.Tables[Main_Table].Columns["ID"],
                dataSet.Tables[Secondary_Table].Columns["Plane"]
            ));
        }

        private void InitializeUI()
        {
            bindingSourceMain.DataSource = dataSet;
            bindingSourceMain.DataMember = Main_Table;

            bindingSourceChild.DataSource = bindingSourceMain;
            bindingSourceChild.DataMember = FK;

            dgvUser.DataSource = bindingSourceMain;
            dgvLiked.DataSource = bindingSourceChild;
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
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapterMain);
            builder.GetInsertCommand();
            dataAdapterChild.Update(dataSet, Secondary_Table);
            dataAdapterMain.Update(dataSet, Main_Table);
        }
    }
}
