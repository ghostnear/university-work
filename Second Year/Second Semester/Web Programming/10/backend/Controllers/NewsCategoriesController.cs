using backend.Domain;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;

namespace backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class NewsCategoriesController : ControllerBase
    {
        private static MySqlConnection GetConnection()
        {
            return new MySqlConnection("server=localhost;port=3306;database=WeaselNews;user=root;password=;");
        }

        [HttpGet(Name = "GetNewsCategories")]
        public IEnumerable<string> Get()
        {
            List<string> list = new List<string>();

            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("SELECT DISTINCT Category FROM News", conn);
                using (MySqlDataReader reader = cmd.ExecuteReader())
                    while (reader.Read())
                        list.Add(reader.GetString(0));
                conn.Close();
            }

            return list;
        }
    }
}
