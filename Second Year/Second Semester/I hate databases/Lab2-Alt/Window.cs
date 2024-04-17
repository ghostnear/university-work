using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;

namespace Lab2
{
    public partial class Window : Form
    {
        DataSet dataSet = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();

        BindingSource parentSource = new BindingSource();
        BindingSource childSource = new BindingSource();

        static readonly string server = ConfigurationManager.AppSettings.Get("server");
        static readonly string database = ConfigurationManager.AppSettings.Get("database");
        static readonly string parentTable = ConfigurationManager.AppSettings.Get("parentTable");
        static readonly string childTable = ConfigurationManager.AppSettings.Get("childTable");
        static readonly string parentPK = ConfigurationManager.AppSettings.Get("parentPK");
        static readonly string childFK = ConfigurationManager.AppSettings.Get("childFK");

        SqlConnection connection = new SqlConnection(
            "Data Source=" + server + ";Initial Catalog=" + database + ";Integrated Security=SSPI"
        );

        public Window()
        {
            InitializeComponent();
        }

        private void Window_Load(object sender, EventArgs e)
        {
            parentLabel.Text = parentTable + " (Parent)";
            childLabel.Text = childTable + " (Child)";

            parentAdapter = new SqlDataAdapter("SELECT * FROM " + parentTable, connection);
            childAdapter = new SqlDataAdapter("SELECT * FROM " + childTable, connection);

            SqlCommandBuilder parentCommand = new SqlCommandBuilder(parentAdapter);
            SqlCommandBuilder childCommand = new SqlCommandBuilder(childAdapter);

            dataSet.Clear();
            parentAdapter.Fill(dataSet, parentTable);
            childAdapter.Fill(dataSet, childTable);

            DataColumn parentColumn = dataSet.Tables[parentTable].Columns[parentPK];
            DataColumn childColumn = dataSet.Tables[childTable].Columns[childFK];

            DataRelation relation = new DataRelation("fk_parent_child", parentColumn, childColumn);
            dataSet.Relations.Add(relation);

            parentSource.DataSource = dataSet;
            parentSource.DataMember = parentTable;

            childSource.DataSource = parentSource;
            childSource.DataMember = "fk_parent_child";

            parentDataGridView.DataSource = parentSource;
            childDataGridView.DataSource = childSource;
        }

        private void commitChangesButton_Click(object sender, EventArgs e)
        {
            try
            {
                parentAdapter.Update(dataSet, parentTable);
                childAdapter.Update(dataSet, childTable);

                dataSet.Clear();
                parentAdapter.Fill(dataSet, parentTable);
                childAdapter.Fill(dataSet, childTable);

                MessageBox.Show("Changes saved successfully!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Saving changes failed: " + ex.Message);
                connection.Close();
            }
        }
    }
}
