using backend.Domain;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;

namespace backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class NewsListController : ControllerBase
    {
        private static MySqlConnection GetConnection()
        {
            return new MySqlConnection("server=localhost;port=3306;database=WeaselNews;user=root;password=;");
        }

        [HttpGet(Name = "GetNews")]
        public IEnumerable<News> Get()
        {
            List<News> list = new List<News>();

            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("SELECT * FROM News ORDER BY Date DESC", conn);
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        News item = new News()
                        {
                            ID = reader.GetInt32("ID"),
                            Title = reader.GetString("Title"),
                            Category = reader.GetString("Category"),
                            Date = DateOnly.FromDateTime(reader.GetDateTime("Date")),
                            Contents = reader.GetString("Contents"),
                        };

                        using (MySqlConnection connection = GetConnection())
                        {
                            connection.Open();

                            MySqlCommand cmd2 = new MySqlCommand("SELECT * FROM Users WHERE ID = " + reader.GetInt32("Producer").ToString(), connection);
                            using (MySqlDataReader reader2 = cmd2.ExecuteReader())
                            {
                                while (reader2.Read())
                                {
                                    item.Producer = new PublicUser()
                                    {
                                        ID = reader2.GetInt32("ID"),
                                        Username = reader2.GetString("Username"),
                                    };
                                }
                            }

                            connection.Close();
                        }
                        

                        list.Add(item);
                    }
                }
                conn.Close();
            }

            return list;
        }
    }
}
